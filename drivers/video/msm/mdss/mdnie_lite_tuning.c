/* Copyright (c) 2009-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <linux/ctype.h>
#include <linux/miscdevice.h>
#include <linux/dma-mapping.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fb.h>
#include <linux/msm_mdp.h>
#include <linux/ioctl.h>
#include <linux/lcd.h>

#include "mdss_fb.h"
#include "mdss_panel.h"
#include "mdss_dsi.h"
#include "mdnie_lite_tuning.h"

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL) // H
#include "mdnie_lite_tuning_data_hlte.h"
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_FULL_HD_PT_PANEL) // KS01
#include "mdnie_lite_tuning_data.h"
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_YOUM_CMD_FULL_HD_PT_PANEL) // F
#include "mdnie_lite_tuning_data_flte.h"
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) // K
#include "mdnie_lite_tuning_data_klte_fhd_s6e3fa2.h"
#elif defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)
#include "mdnie_lite_tuning_data_slte_hd_ea8064g.h"
#elif defined(CONFIG_FB_MSM_MIPI_JDI_TFT_VIDEO_FULL_HD_PT_PANEL) // JACTIVE
#include "mdnie_lite_tuning_data_jactiveltexx.h"
/*
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_WVGA_S6E88A0_PT_PANEL) // ?
#include "mdnie_lite_tuning_data_wvga_s6e88a0.h"
#elif defined(CONFIG_MACH_JS01LTEDCM) || defined(CONFIG_MACH_JS01LTESBM) // JS01
#include "mdnie_lite_tuning_data_js01.h"
*/
#elif defined(CONFIG_FB_MSM_MDSS_SAMSUNG_OCTA_VIDEO_720P_PT_PANEL)
#include "mdnie_lite_tuning_data_fresco.h"
#elif defined(CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL) \
	|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
#include "mdnie_lite_tuning_data_kmini.h"
#elif defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL) // KANAS
#include "mdnie_lite_tuning_data_wvga_nt35502.h"
#elif defined (CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
#include "mdss_ms01_panel.h"
#include "mdnie_lite_tuning_data_ms01.h"
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)
#include "mdnie_lite_tuning_data_klimt.h"
#else
#include "mdnie_lite_tuning_data.h"
#endif

#if defined(CONFIG_TDMB)
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) // K
#include "mdnie_lite_tuning_data_dmb_fhd_s6e3fa2.h"
#else
#include "mdnie_lite_tuning_data_dmb.h"
#endif
#endif

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
static struct mdss_dsi_driver_data *mdnie_msd;
#if defined(CONFIG_FB_MSM_MDSS_DSI_DBG)
int dsi_ctrl_on;
#endif
#else
static struct mipi_samsung_driver_data *mdnie_msd;
#endif

//#define MDNIE_LITE_TUN_DEBUG

#ifdef MDNIE_LITE_TUN_DEBUG
#define DPRINT(x...)	printk(KERN_ERR "[mdnie lite] " x)
#else
#define DPRINT(x...)
#endif

#define MAX_LUT_SIZE	256

/*#define MDNIE_LITE_TUN_DATA_DEBUG*/

#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
#define PAYLOAD1 mdni_tune_cmd[1]
#define PAYLOAD2 mdni_tune_cmd[2]
#define PAYLOAD3 mdni_tune_cmd[3]
#define PAYLOAD4 mdni_tune_cmd[4]
#define PAYLOAD5 mdni_tune_cmd[5]

#define INPUT_PAYLOAD1(x) PAYLOAD1.payload = x
#define INPUT_PAYLOAD2(x) PAYLOAD2.payload = x
#define INPUT_PAYLOAD3(x) PAYLOAD3.payload = x
#define INPUT_PAYLOAD4(x) PAYLOAD4.payload = x
#define INPUT_PAYLOAD5(x) PAYLOAD5.payload = x
#else
#define PAYLOAD1 mdni_tune_cmd[3]
#define PAYLOAD2 mdni_tune_cmd[2]

#define INPUT_PAYLOAD1(x) PAYLOAD1.payload = x
#define INPUT_PAYLOAD2(x) PAYLOAD2.payload = x
#endif

static unsigned char LITE_CONTROL_1[5];
static unsigned char LITE_CONTROL_2[108];

static unsigned int effects_bit = 3;
static unsigned int sharpen_bit = 2;
static unsigned int chroma_bit = 1;
static unsigned int gamma_bit = 0;

static unsigned int hijack = 0;
static unsigned int black[3] = {0, 0, 0};
static unsigned int white[3] = {0, 0, 0};
static unsigned int red[3] = {0, 0, 0};
static unsigned int green[3] = {0, 0, 0};
static unsigned int blue[3] = {0, 0, 0};

/* Hijack Extra includes the following  */
static unsigned int hijack_effects = 0;
static unsigned int effects = 0;
static unsigned int sharpen = 0;
static unsigned int chroma = 0;
static unsigned int gamma = 0;
/* Hijack Extra End  */

static unsigned int previous_mode;
unsigned int play_speed_1_5;

struct dsi_buf dsi_mdnie_tx_buf;

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)
#if defined(CONFIG_LCD_CLASS_DEVICE) && defined(DDI_VIDEO_ENHANCE_TUNING)
extern int mdnie_adb_test;
#endif
int get_lcd_panel_res(void);
#endif

struct mdnie_lite_tun_type mdnie_tun_state = {
	.mdnie_enable = false,
	.scenario = mDNIe_UI_MODE,
#ifdef MDNIE_LITE_MODE
	.background = 0,
#else
	.background = AUTO_MODE,
#endif /* MDNIE_LITE_MODE */
	.outdoor = OUTDOOR_OFF_MODE,
	.accessibility = ACCESSIBILITY_OFF,
#if defined(CONFIG_TDMB)
	.dmb = DMB_MODE_OFF,
#endif
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
	.scr_white_red = 0xff,
	.scr_white_green = 0xff,
	.scr_white_blue = 0xff,
#endif
};

#if !defined(CONFIG_TDMB)
const
#endif
char scenario_name[MAX_mDNIe_MODE][16] = {
	"UI_MODE",
	"VIDEO_MODE",
	"VIDEO_WARM_MODE",
	"VIDEO_COLD_MODE",
	"CAMERA_MODE",
	"NAVI",
	"GALLERY_MODE",
	"VT_MODE",
	"BROWSER",
	"eBOOK",
	"EMAIL",
#if defined(CONFIG_LCD_HMT)
	"HMT_8",
	"HMT_16",
#endif
};

const char background_name[MAX_BACKGROUND_MODE][10] = {
	"DYNAMIC",
	"STANDARD",
	"NATURAL",
	"MOVIE",
	"AUTO",
};

const char outdoor_name[MAX_OUTDOOR_MODE][20] = {
	"OUTDOOR_OFF_MODE",
#ifndef MDNIE_LITE_MODE
	"OUTDOOR_ON_MODE",
#endif /* MDNIE_LITE_MODE */
};

const char accessibility_name[ACCESSIBILITY_MAX][20] = {
	"ACCESSIBILITY_OFF",
	"NEGATIVE_MODE",
#ifndef	NEGATIVE_COLOR_USE_ACCESSIBILLITY
	"COLOR_BLIND_MODE",
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL) || defined (CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)||\
	defined(CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL)	|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL) ||\
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_FULL_HD_PT_PANEL)
	"SCREEN_CURTAIN_MODE",
#endif
#endif /* NEGATIVE_COLOR_USE_ACCESSIBILLITY */
};

#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
static char cmd_enable[6] = { 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x00 };
#else
static char level1_key[] = {
	0xF0,
	0x5A, 0x5A,
};

#if defined(CONFIG_FB_MSM_MDSS_SAMSUNG_OCTA_VIDEO_720P_PT_PANEL) ||defined(CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL) \
	|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
static char level2_key[] = {
	0xF1,
	0x5A, 0x5A,
};
#else
static char level2_key[] = {
	0xF0,
	0x5A, 0x5A,
};
#endif
#endif

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || defined (CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)
static char level1_key_disable[] = {
	0xF0,
	0xA5, 0xA5,
};
#elif defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
static char cmd_disable[6] = { 0xF0, 0x55, 0xAA, 0x52, 0x00, 0x00 };
#endif

#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
static char tune_data1[MDNIE_TUNE_FIRST_SIZE] = {0,};
static char tune_data2[MDNIE_TUNE_SECOND_SIZE] = {0,};
static char tune_data3[MDNIE_TUNE_THIRD_SIZE] = { 0,};
static char tune_data4[MDNIE_TUNE_FOURTH_SIZE] = { 0,};
static char tune_data5[MDNIE_TUNE_FIFTH_SIZE] = { 0,};
#else
static char tune_data1[MDNIE_TUNE_FIRST_SIZE] = {0,};
static char tune_data2[MDNIE_TUNE_SECOND_SIZE] = {0,};
#endif

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
static char white_rgb_buf[MDNIE_TUNE_FIRST_SIZE] = {0,};
#endif

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) \
	|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
static char tune_data1_adb[MDNIE_TUNE_FIRST_SIZE] = {0,};
static char tune_data2_adb[MDNIE_TUNE_SECOND_SIZE] = {0,};

void copy_tuning_data_from_adb(char *data1, char *data2)
{
	memcpy(tune_data1_adb, data1, MDNIE_TUNE_FIRST_SIZE);
	memcpy(tune_data2_adb, data2, MDNIE_TUNE_SECOND_SIZE);
}
#endif

static struct dsi_cmd_desc mdni_tune_cmd[] = {
#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(cmd_enable)}, cmd_enable},
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(tune_data1)}, tune_data1},
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(tune_data2)}, tune_data2},
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(tune_data3)}, tune_data3},
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0, sizeof(tune_data4)}, tune_data4},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(tune_data5)}, tune_data5},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(cmd_disable)}, cmd_disable},
#else
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(level1_key)}, level1_key},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(level2_key)}, level2_key},

	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(tune_data1)}, tune_data1},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(tune_data2)}, tune_data2},

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(level1_key_disable)}, level1_key_disable},
#endif
#endif
};

void print_tun_data(void)
{
	int i;

	DPRINT("\n");
	DPRINT("---- size1 : %d", PAYLOAD1.dchdr.dlen);
	for (i = 0; i < MDNIE_TUNE_SECOND_SIZE ; i++)
		DPRINT("0x%x ", PAYLOAD1.payload[i]);
	DPRINT("\n");
	DPRINT("---- size2 : %d", PAYLOAD2.dchdr.dlen);
	for (i = 0; i < MDNIE_TUNE_FIRST_SIZE ; i++)
		DPRINT("0x%x ", PAYLOAD2.payload[i]);
	DPRINT("\n");
}

void update_mdnie_mode(void)
{
	char *source_1, *source_2;
	unsigned int i = 0;
	int result;
	// Determine the source to copy the mode from
	switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
			source_1 = DYNAMIC_UI_1;
			source_2 = DYNAMIC_UI_2;
			break;
		case STANDARD_MODE:
			source_1 = STANDARD_UI_1;
			source_2 = STANDARD_UI_2;
			break;
		case NATURAL_MODE:
			source_1 = NATURAL_UI_1;
			source_2 = NATURAL_UI_2;
			break;
		case MOVIE_MODE:
			source_1 = MOVIE_UI_1;
			source_2 = MOVIE_UI_2;
			break;
		case AUTO_MODE:
			source_1 = AUTO_UI_1;
			source_2 = AUTO_UI_2;
			break;
		default:
			source_1 = MOVIE_UI_1;
			source_2 = MOVIE_UI_2;
			break;
	}

/*
Black
[37]  	0x00, BLACK RED
[39]  	0x00, BLACK GREEN
[41]  	0x00, BLACK BLUE

White
[36]  	0xff, WHITE RED
[38]  	0xff, WHITE GREEN
[40]  	0xff, WHITE BLUE

Red
[19]  	0xff, RED RED
[21]  	0x00, RED GREEN
[23]  	0x00, RED BLUE

Green
[25]  	0x00, GREEN RED
[27]  	0xff, GREEN GREEN
[29]  	0x00, GREEN BLUE

Blue
[31]  	0x00, BLUE RED
[33]  	0x00, BLUE GREEN
[35]  	0xff, BLUE BLUE

Yellow
[30]  	0xff, YELLOW RED
[32]  	0xff, YELLOW GREEN
[34]  	0x00, YELLOW BLUE
*/
	if (hijack) {
		for (i = 0; i < 107; i++) {
			if (i == 37)
				LITE_CONTROL_2[i] = black[0];
			else if (i == 39)
				LITE_CONTROL_2[i] = black[1];
			else if (i == 41)
				LITE_CONTROL_2[i] = black[2];
			else if (i == 36)
				LITE_CONTROL_2[i] = white[0];
			else if (i == 38)
				LITE_CONTROL_2[i] = white[1];
			else if (i == 40)
				LITE_CONTROL_2[i] = white[2];
			else if (i == 19)
				LITE_CONTROL_2[i] = red[0];
			else if (i == 21)
				LITE_CONTROL_2[i] = red[1];
			else if (i == 23)
				LITE_CONTROL_2[i] = red[2];
			else if (i == 25)
				LITE_CONTROL_2[i] = green[0];
			else if (i == 27)
				LITE_CONTROL_2[i] = green[1];
			else if (i == 29)
				LITE_CONTROL_2[i] = green[2];
			else if (i == 31)
				LITE_CONTROL_2[i] = blue[0];
			else if (i == 33)
				LITE_CONTROL_2[i] = blue[1];
			else if (i == 35)
				LITE_CONTROL_2[i] = blue[2];
			else
				LITE_CONTROL_2[i] = source_2[i];
		}
	} else {
		for (i = 0; i < 107; i++) {
			if (i == 37)
				black[0] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 39)
				black[1] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 41)
				black[2] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 36)
				white[0] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 38)
				white[1] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 40)
				white[2] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 19)
				red[0] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 21)
				red[1] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 23)
				red[2] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 25)
				green[0] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 27)
				green[1] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 29)
				green[2] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 31)
				blue[0] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 33)
				blue[1] = LITE_CONTROL_2[i] = source_2[i];
			else if (i == 35)
				blue[2] = LITE_CONTROL_2[i] = source_2[i];
			else
				LITE_CONTROL_2[i] = source_2[i]; // Copy Everything else
		}
	}

	for (i = 0; i < 3; i++)
		LITE_CONTROL_1[i] = source_1[i];

	if (hijack_effects) {
		if (effects)
			LITE_CONTROL_1[4] |= 1 << effects_bit;
		else
			LITE_CONTROL_1[4] &= ~(1 << effects_bit);

		if (sharpen)
			LITE_CONTROL_1[4] |= 1 << sharpen_bit;
		else
			LITE_CONTROL_1[4] &= ~(1 << sharpen_bit);
		
		if (chroma)
			LITE_CONTROL_1[4] |= 1 << chroma_bit;
		else
			LITE_CONTROL_1[4] &= ~(1 << chroma_bit);

		if (gamma)
			LITE_CONTROL_1[4] |= 1 << gamma_bit;
		else
			LITE_CONTROL_1[4] &= ~(1 << gamma_bit);
	} else {
		LITE_CONTROL_1[4] = source_1[4];

		result = (LITE_CONTROL_1[4] >> (effects_bit));
		effects = result & 1;

		result = (LITE_CONTROL_1[4] >> (sharpen_bit));
		sharpen = result & 1;

		result = (LITE_CONTROL_1[4] >> (chroma_bit));
		chroma = result & 1;

		result = (LITE_CONTROL_1[4] >> (gamma_bit));
		gamma = result & 1;
	}
}

void free_tun_cmd(void)
{
#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
	memset(tune_data1, 0, MDNIE_TUNE_FIRST_SIZE);
	memset(tune_data2, 0, MDNIE_TUNE_SECOND_SIZE);
	memset(tune_data3, 0, MDNIE_TUNE_THIRD_SIZE);
	memset(tune_data4, 0, MDNIE_TUNE_FOURTH_SIZE);
	memset(tune_data5, 0, MDNIE_TUNE_FIFTH_SIZE);
#else
	memset(tune_data1, 0, MDNIE_TUNE_FIRST_SIZE);
	memset(tune_data2, 0, MDNIE_TUNE_SECOND_SIZE);
#endif
}

void sending_tuning_cmd(void)
{
	struct msm_fb_data_type *mfd;
	struct mdss_dsi_ctrl_pdata *ctrl_pdata;

	mfd = mdnie_msd->mfd;
	ctrl_pdata = mdnie_msd->ctrl_pdata;

	if (mfd->resume_state == MIPI_SUSPEND_STATE) {
		DPRINT("[ERROR] not ST_DSI_RESUME. do not send mipi cmd.\n");
		return;
	}

	mutex_lock(&mdnie_msd->lock);

#ifdef MDNIE_LITE_TUN_DATA_DEBUG
	print_tun_data();
#endif
	mdss_dsi_cmds_send(ctrl_pdata, mdni_tune_cmd, ARRAY_SIZE(mdni_tune_cmd), 0);
	mutex_unlock(&mdnie_msd->lock);
	}
/*
 * mDnie priority
 * Accessibility > HBM > Screen Mode
 */
void mDNIe_Set_Mode(void)
{
	struct msm_fb_data_type *mfd;
	mfd = mdnie_msd->mfd;

/*	DPRINT("mDNIe_Set_Mode start\n");*/

	if (!mfd) {
		DPRINT("[ERROR] mfd is null!\n");
		return;
	}

	if ((mfd->blank_mode) || (mfd->resume_state == MIPI_SUSPEND_STATE) || \
		(!mdnie_tun_state.mdnie_enable))
		return;

	play_speed_1_5 = 0;

	update_mdnie_mode();
	if (hijack == 1) {
		DPRINT(" = CONTROL MODE =\n");
		INPUT_PAYLOAD1(LITE_CONTROL_1);
		INPUT_PAYLOAD2(LITE_CONTROL_2);
	} else if (mdnie_tun_state.accessibility) {
		DPRINT(" = ACCESSIBILITY MODE =\n");
		INPUT_PAYLOAD1(blind_tune_value[mdnie_tun_state.accessibility][0]);
		INPUT_PAYLOAD2(blind_tune_value[mdnie_tun_state.accessibility][1]);
	} else {
		if ((!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]) || \
			(!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]))
			return;
		else
			INPUT_PAYLOAD1(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
			INPUT_PAYLOAD2(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
	}

	sending_tuning_cmd();
	free_tun_cmd();
}

void is_play_speed_1_5(int enable)
{
	play_speed_1_5 = enable;
}

/* ##########################################################
 * #
 * # MDNIE BG Sysfs node
 * #
 * ##########################################################*/

/* ##########################################################
 * #
 * #	0. Dynamic
 * #	1. Standard (Lite control)
 * #	2. Natural (Professional photo)
 * #	3. Movie
 * #	4. Auto (Adapt display)
 * #
 * #	echo 1 > /sys/class/mdnie/mdnie/mode
 * #
 * ##########################################################*/

static ssize_t mode_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return snprintf(buf, 256, "Current Background Mode : %s\n",
		background_name[mdnie_tun_state.background]);
}

static ssize_t mode_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	int value;

	sscanf(buf, "%d", &value);

	if (value <= DYNAMIC_MODE)
		value = DYNAMIC_MODE;
	if (value >= AUTO_MODE)
		value = AUTO_MODE;

	previous_mode = mdnie_tun_state.background;

	mdnie_tun_state.background = value;

	if (mdnie_tun_state.accessibility != NEGATIVE)
		mDNIe_Set_Mode();

	return size;
}

static ssize_t scenario_show(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	DPRINT("Current Scenario Mode : %s\n",
		scenario_name[mdnie_tun_state.scenario]);

	return snprintf(buf, 256, "Current Scenario Mode : %s\n",
		scenario_name[mdnie_tun_state.scenario]);
}

static ssize_t scenario_store(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t size)
{
	int value;
	int backup;

	sscanf(buf, "%d", &value);

	if (value < mDNIe_UI_MODE || value >= MAX_mDNIe_MODE) {
		DPRINT("[ERROR] wrong Scenario mode value : %d\n",
			value);
		return size;
	}

	backup = mdnie_tun_state.scenario;
	mdnie_tun_state.scenario = value;

#if defined(CONFIG_TDMB)
	/* mDNIe_DMB_MODE = 20 */
	if (value >= mDNIe_DMB_MODE && value <= mDNIe_DMB_COLD_MODE) {
		DPRINT("DMB scenario.. (%d)\n", mdnie_tun_state.scenario);
		mdnie_tun_state.dmb = value - mDNIe_DMB_MODE;
	} else
		mdnie_tun_state.dmb = DMB_MODE_OFF;
#endif

	if (mdnie_tun_state.accessibility == NEGATIVE) {
		DPRINT("already negative mode(%d), do not set mode(%d)\n",
			mdnie_tun_state.accessibility, mdnie_tun_state.scenario);
	} else {
		DPRINT(" %s : (%s) -> (%s)\n",
			__func__, scenario_name[backup], scenario_name[mdnie_tun_state.scenario]);
		mDNIe_Set_Mode();
	}
	return size;
}

/* LITE_CONTROL_1[4] */

static ssize_t lcfour_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "Decimal:%u\nHex:0x%x\n", LITE_CONTROL_1[4], LITE_CONTROL_1[4]);
}

/* hijack */

static ssize_t hijack_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", hijack);
}

static ssize_t hijack_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	hijack = clamp_val(new_val, 0, 1);
	mDNIe_Set_Mode();
	return size;
}

/* hijack_effects */

static ssize_t hijack_effects_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", hijack_effects);
}

static ssize_t hijack_effects_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	hijack_effects = clamp_val(new_val, 0, 1);
	mDNIe_Set_Mode();
	return size;
}

/* effects */

static ssize_t effects_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", effects);
}

static ssize_t effects_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	effects = clamp_val(new_val, 0, 1);
	mDNIe_Set_Mode();
	return size;
}


/* sharpen */

static ssize_t sharpen_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", sharpen);
}

static ssize_t sharpen_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	sharpen = clamp_val(new_val, 0, 1);
	mDNIe_Set_Mode();
	return size;
}

static ssize_t chroma_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", chroma);
}

static ssize_t chroma_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	chroma = clamp_val(new_val, 0, 1);
	mDNIe_Set_Mode();
	return size;
}

static ssize_t gamma_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", gamma);
}

static ssize_t gamma_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	gamma = clamp_val(new_val, 0, 1);
	mDNIe_Set_Mode();
	return size;
}

/* black */

static ssize_t black_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", black[0], black[1], black[2]);
}

static ssize_t black_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int i, new_val, newred, newgreen, newblue;

	if (sscanf(buf, "%d %d %d", &newred, &newgreen, &newblue) == 3) {
		black[0] = clamp_val(newred, 0, 255);
		black[1] = clamp_val(newgreen, 0, 255);
		black[2] = clamp_val(newblue, 0, 255);
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		black[0] = clamp_val(new_val, 0, 255);
		black[1] = clamp_val(new_val, 0, 255);
		black[2] = clamp_val(new_val, 0, 255);
	} else {
		return size;
	}

	mDNIe_Set_Mode();

	return size;
}

/* white */

static ssize_t white_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", white[0], white[1], white[2]);
}

static ssize_t white_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int i, new_val, newred, newgreen, newblue;

	if (sscanf(buf, "%d %d %d", &newred, &newgreen, &newblue) == 3) {
		white[0] = clamp_val(newred, 0, 255);
		white[1] = clamp_val(newgreen, 0, 255);
		white[2] = clamp_val(newblue, 0, 255);
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		white[0] = clamp_val(new_val, 0, 255);
		white[1] = clamp_val(new_val, 0, 255);
		white[2] = clamp_val(new_val, 0, 255);
	} else {
		return size;
	}

	mDNIe_Set_Mode();

	return size;
}

/* red */

static ssize_t red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", red[0], red[1], red[2]);
}

static ssize_t red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int i, new_val, newred, newgreen, newblue;

	if (sscanf(buf, "%d %d %d", &newred, &newgreen, &newblue) == 3) {
		red[0] = clamp_val(newred, 0, 255);
		red[1] = clamp_val(newgreen, 0, 255);
		red[2] = clamp_val(newblue, 0, 255);
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		red[0] = clamp_val(new_val, 0, 255);
		red[1] = clamp_val(new_val, 0, 255);
		red[2] = clamp_val(new_val, 0, 255);
	} else {
		return size;
	}

	mDNIe_Set_Mode();

	return size;
}

/* green */

static ssize_t green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", green[0], green[1], green[2]);
}

static ssize_t green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int i, new_val, newred, newgreen, newblue;

	if (sscanf(buf, "%d %d %d", &newred, &newgreen, &newblue) == 3) {
		green[0] = clamp_val(newred, 0, 255);
		green[1] = clamp_val(newgreen, 0, 255);
		green[2] = clamp_val(newblue, 0, 255);
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		green[0] = clamp_val(new_val, 0, 255);
		green[1] = clamp_val(new_val, 0, 255);
		green[2] = clamp_val(new_val, 0, 255);
	} else {
		return size;
	}

	mDNIe_Set_Mode();

	return size;
}

/* blue */

static ssize_t blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", blue[0], blue[1], blue[2]);
}

static ssize_t blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int i, new_val, newred, newgreen, newblue;

	if (sscanf(buf, "%d %d %d", &newred, &newgreen, &newblue) == 3) {
		blue[0] = clamp_val(newred, 0, 255);
		blue[1] = clamp_val(newgreen, 0, 255);
		blue[2] = clamp_val(newblue, 0, 255);
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		blue[0] = clamp_val(new_val, 0, 255);
		blue[1] = clamp_val(new_val, 0, 255);
		blue[2] = clamp_val(new_val, 0, 255);
	} else {
		return size;
	}

	mDNIe_Set_Mode();

	return size;
}

static ssize_t mdnieset_user_select_file_cmd_show(struct device *dev,
						  struct device_attribute *attr,
						  char *buf)
{
	int mdnie_ui = 0;
	DPRINT("called %s\n", __func__);

	return snprintf(buf, 256, "%u\n", mdnie_ui);
}

static ssize_t mdnieset_user_select_file_cmd_store(struct device *dev,
						   struct device_attribute
						   *attr, const char *buf,
						   size_t size)
{
	int value;

	sscanf(buf, "%d", &value);
	DPRINT
	("inmdnieset_user_select_file_cmd_store, input value = %d\n",
	     value);

	return size;
}

static ssize_t mdnieset_init_file_cmd_show(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	char temp[] = "mdnieset_init_file_cmd_show\n\0";
	DPRINT("called %s\n", __func__);
	strcat(buf, temp);
	return strlen(buf);
}

static ssize_t mdnieset_init_file_cmd_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t size)
{
	int value;

	sscanf(buf, "%d", &value);
	DPRINT("mdnieset_init_file_cmd_store  : value(%d)\n", value);

	switch (value) {
	case 0:
		mdnie_tun_state.scenario = mDNIe_UI_MODE;
		break;

	default:
		printk(KERN_ERR
		       "mdnieset_init_file_cmd_store value is wrong : value(%d)\n",
		       value);
		break;
	}
	mDNIe_Set_Mode();

	return size;
}

static ssize_t outdoor_show(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	DPRINT("Current outdoor Mode : %s\n",
		outdoor_name[mdnie_tun_state.outdoor]);

	return snprintf(buf, 256, "Current outdoor Mode : %s\n",
		outdoor_name[mdnie_tun_state.outdoor]);
}

static ssize_t outdoor_store(struct device *dev,
					       struct device_attribute *attr,
					       const char *buf, size_t size)
{
	int value;
	int backup;

	sscanf(buf, "%d", &value);

	DPRINT("outdoor value = %d, scenario = %d\n",
		value, mdnie_tun_state.scenario);

	if (value < OUTDOOR_OFF_MODE || value >= MAX_OUTDOOR_MODE) {
		DPRINT("[ERROR] : wrong outdoor mode value : %d\n",
				value);
#ifdef MDNIE_LITE_MODE
		return size;
#endif
	}

	backup = mdnie_tun_state.outdoor;
	mdnie_tun_state.outdoor = value;

	if (mdnie_tun_state.accessibility == NEGATIVE) {
		DPRINT("already negative mode(%d), do not outdoor mode(%d)\n",
			mdnie_tun_state.accessibility, mdnie_tun_state.outdoor);
	} else {
		DPRINT(" %s : (%s) -> (%s)\n",
			__func__, outdoor_name[backup], outdoor_name[mdnie_tun_state.outdoor]);
		mDNIe_Set_Mode();
	}

	return size;
}

#if 0 // accessibility
static ssize_t negative_show(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	return snprintf(buf, 256, "Current negative Value : %s\n",
		(mdnie_tun_state.accessibility == 1) ? "Enabled" : "Disabled");
}

static ssize_t negative_store(struct device *dev,
					       struct device_attribute *attr,
					       const char *buf, size_t size)
{
	int value;

	sscanf(buf, "%d", &value);

	DPRINT
	    ("negative_store, input value = %d\n",
	     value);

	mdnie_tun_state.accessibility = value;

	mDNIe_Set_Mode();

	return size;
}
static DEVICE_ATTR(negative, 0664,
		   negative_show,
		   negative_store);

#endif

void is_negative_on(void)
{
	DPRINT("is negative Mode On = %d\n", mdnie_tun_state.accessibility);

	mDNIe_Set_Mode();
}

static ssize_t playspeed_show(struct device *dev,
			struct device_attribute *attr,
			char *buf)
{
	DPRINT("called %s\n", __func__);
	return snprintf(buf, 256, "%d\n", play_speed_1_5);
}

static ssize_t playspeed_store(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t size)
{
	int value;
	sscanf(buf, "%d", &value);

	DPRINT("[Play Speed Set]play speed value = %d\n", value);

	is_play_speed_1_5(value);
	return size;
}

static ssize_t accessibility_show(struct device *dev,
			struct device_attribute *attr,
			char *buf)
{
	DPRINT("Current accessibility Mode : %s\n",
		accessibility_name[mdnie_tun_state.accessibility]);

	return snprintf(buf, 256, "Current accessibility Mode : %s\n",
		accessibility_name[mdnie_tun_state.accessibility]);
}

static ssize_t accessibility_store(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t size)
{
	int cmd_value;
	char buffer[MDNIE_COLOR_BLINDE_CMD] = {0,};
	int buffer2[MDNIE_COLOR_BLINDE_CMD/2] = {0,};
	int loop;
	char temp;
	int backup;

	sscanf(buf, "%d %x %x %x %x %x %x %x %x %x", &cmd_value,
		&buffer2[0], &buffer2[1], &buffer2[2], &buffer2[3], &buffer2[4],
		&buffer2[5], &buffer2[6], &buffer2[7], &buffer2[8]);

	for(loop = 0; loop < MDNIE_COLOR_BLINDE_CMD/2; loop++) {
		buffer2[loop] = buffer2[loop] & 0xFFFF;

		buffer[loop * 2] = (buffer2[loop] & 0xFF00) >> 8;
		buffer[loop * 2 + 1] = buffer2[loop] & 0xFF;
	}

	for(loop = 0; loop < MDNIE_COLOR_BLINDE_CMD; loop+=2) {
		temp = buffer[loop];
		buffer[loop] = buffer[loop + 1];
		buffer[loop + 1] = temp;
	}

	backup = mdnie_tun_state.accessibility;

	if (cmd_value == NEGATIVE) {
		mdnie_tun_state.accessibility = NEGATIVE;
	}
#ifndef	NEGATIVE_COLOR_USE_ACCESSIBILLITY
	else if (cmd_value == COLOR_BLIND) {
		mdnie_tun_state.accessibility = COLOR_BLIND;

		#if defined (CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
        memcpy(&COLOR_BLIND_2[MDNIE_COLOR_BLINDE_CMD],
                                buffer, MDNIE_COLOR_BLINDE_CMD);
		#else
		memcpy(&COLOR_BLIND_2[MDNIE_COLOR_BLINDE_OFFSET],
				buffer, MDNIE_COLOR_BLINDE_CMD);
		}
		#endif
	else if (cmd_value == SCREEN_CURTAIN) {
		mdnie_tun_state.accessibility = SCREEN_CURTAIN;
	}
#endif /* NEGATIVE_COLOR_USE_ACCESSIBILLITY */
	else if (cmd_value == ACCESSIBILITY_OFF) {
		mdnie_tun_state.accessibility = ACCESSIBILITY_OFF;
	} else
		pr_info("%s ACCESSIBILITY_MAX", __func__);

	DPRINT(" %s : (%s) -> (%s)\n",
			__func__, accessibility_name[backup], accessibility_name[mdnie_tun_state.accessibility]);

	mDNIe_Set_Mode();

	pr_info("%s cmd_value : %d size : %d", __func__, cmd_value, size);

	return size;
}

static DEVICE_ATTR(lcfour, 0440, lcfour_show, NULL);
static DEVICE_ATTR(hijack, 0664, hijack_show, hijack_store);
static DEVICE_ATTR(hijack_effects, 0664, hijack_effects_show, hijack_effects_store);
static DEVICE_ATTR(effects, 0664, effects_show, effects_store);
static DEVICE_ATTR(sharpen, 0664, sharpen_show, sharpen_store);
static DEVICE_ATTR(chroma, 0664, chroma_show, chroma_store);
static DEVICE_ATTR(gamma, 0664, gamma_show, gamma_store);
static DEVICE_ATTR(black, 0664, black_show, black_store);
static DEVICE_ATTR(white, 0664, white_show, white_store);
static DEVICE_ATTR(red, 0664, red_show, red_store);
static DEVICE_ATTR(green, 0664, green_show, green_store);
static DEVICE_ATTR(blue, 0664, blue_show, blue_store);
static DEVICE_ATTR(scenario, 0664, scenario_show, scenario_store);
static DEVICE_ATTR(mode, 0664, mode_show, mode_store);
static DEVICE_ATTR(mdnieset_user_select_file_cmd, 0664,
		   mdnieset_user_select_file_cmd_show,
		   mdnieset_user_select_file_cmd_store);
static DEVICE_ATTR(mdnieset_init_file_cmd, 0664, mdnieset_init_file_cmd_show,
		   mdnieset_init_file_cmd_store);
static DEVICE_ATTR(outdoor, 0664, outdoor_show, outdoor_store);
static DEVICE_ATTR(playspeed, 0664,
			playspeed_show,
			playspeed_store);
static DEVICE_ATTR(accessibility, 0664,
			accessibility_show,
			accessibility_store);

static struct class *mdnie_class;
struct device *tune_mdnie_dev;

void init_mdnie_class(void)
{
	if (mdnie_tun_state.mdnie_enable) {
		pr_err("%s : mdnie already enable.. \n",__func__);
		return;
	}

	mdnie_class = class_create(THIS_MODULE, "mdnie");
	if (IS_ERR(mdnie_class))
		pr_err("Failed to create class(mdnie)!\n");

	tune_mdnie_dev =
	    device_create(mdnie_class, NULL, 0, NULL,
		  "mdnie");
	if (IS_ERR(tune_mdnie_dev))
		pr_err("Failed to create device(mdnie)!\n");

	if (device_create_file
	    (tune_mdnie_dev, &dev_attr_scenario) < 0)
		pr_err("Failed to create device file(%s)!\n",
	       dev_attr_scenario.attr.name);

	if (device_create_file
	    (tune_mdnie_dev,
	     &dev_attr_mdnieset_user_select_file_cmd) < 0)
		pr_err("Failed to create device file(%s)!\n",
			dev_attr_mdnieset_user_select_file_cmd.attr.name);

	if (device_create_file
	    (tune_mdnie_dev, &dev_attr_mdnieset_init_file_cmd) < 0)
		pr_err("Failed to create device file(%s)!\n",
			dev_attr_mdnieset_init_file_cmd.attr.name);

	if (device_create_file
		(tune_mdnie_dev, &dev_attr_mode) < 0)
		pr_err("Failed to create device file(%s)!\n",
			dev_attr_mode.attr.name);

	if (device_create_file
		(tune_mdnie_dev, &dev_attr_outdoor) < 0)
		pr_err("Failed to create device file(%s)!\n",
	       dev_attr_outdoor.attr.name);

#if 0 // accessibility
	if (device_create_file
		(tune_mdnie_dev, &dev_attr_negative) < 0)
		pr_err("Failed to create device file(%s)!\n",
			dev_attr_negative.attr.name);
#endif

	if (device_create_file
		(tune_mdnie_dev, &dev_attr_playspeed) < 0)
		pr_err("Failed to create device file(%s)!=n",
			dev_attr_playspeed.attr.name);

	if (device_create_file
		(tune_mdnie_dev, &dev_attr_accessibility) < 0)
		pr_err("Failed to create device file(%s)!=n",
			dev_attr_accessibility.attr.name);

	device_create_file(tune_mdnie_dev, &dev_attr_hijack);
	device_create_file(tune_mdnie_dev, &dev_attr_hijack_effects);
	device_create_file(tune_mdnie_dev, &dev_attr_effects);
	device_create_file(tune_mdnie_dev, &dev_attr_sharpen);
	device_create_file(tune_mdnie_dev, &dev_attr_black);
	device_create_file(tune_mdnie_dev, &dev_attr_white);
	device_create_file(tune_mdnie_dev, &dev_attr_red);
	device_create_file(tune_mdnie_dev, &dev_attr_green);
	device_create_file(tune_mdnie_dev, &dev_attr_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_gamma);
	device_create_file(tune_mdnie_dev, &dev_attr_chroma);
	device_create_file(tune_mdnie_dev, &dev_attr_lcfour);
	mdnie_tun_state.mdnie_enable = true;
}

void mdnie_lite_tuning_init(struct mipi_samsung_driver_data *msd)
{
	mdnie_msd = msd;
}

#define coordinate_data_size 6
#define scr_wr_addr 36

#define F1(x,y) ((y)-((99*(x))/91)-6)
#define F2(x,y) ((y)-((164*(x))/157)-8)
#define F3(x,y) ((y)+((218*(x))/39)-20166)
#define F4(x,y) ((y)+((23*(x))/8)-11610)

static char coordinate_data[][coordinate_data_size] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* dummy */
	{0xff, 0x00, 0xf7, 0x00, 0xf8, 0x00}, /* Tune_1 */
	{0xff, 0x00, 0xfa, 0x00, 0xfe, 0x00}, /* Tune_2 */
	{0xfb, 0x00, 0xf9, 0x00, 0xff, 0x00}, /* Tune_3 */
	{0xff, 0x00, 0xfd, 0x00, 0xfa, 0x00}, /* Tune_4 */
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_5 */
	{0xf9, 0x00, 0xfb, 0x00, 0xff, 0x00}, /* Tune_6 */
	{0xfc, 0x00, 0xff, 0x00, 0xf8, 0x00}, /* Tune_7 */
	{0xfb, 0x00, 0xff, 0x00, 0xfb, 0x00}, /* Tune_8 */
	{0xf9, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_9 */
};

void coordinate_tunning(int x, int y)
{
	return;
}

#if 0
void coordinate_tunning(int x, int y)
{
	int tune_number = 0;

	if (F1(x,y) > 0) {
		if (F3(x,y) > 0) {
			tune_number = 3;
		} else {
			if (F4(x,y) < 0)
				tune_number = 1;
			else
				tune_number = 2;
		}
	} else {
		if (F2(x,y) < 0) {
			if (F3(x,y) > 0) {
				tune_number = 9;
			} else {
				if (F4(x,y) < 0)
					tune_number = 7;
				else
					tune_number = 8;
			}
		} else {
			if (F3(x,y) > 0)
				tune_number = 6;
			else {
				if (F4(x,y) < 0)
					tune_number = 4;
				else
					tune_number = 5;
			}
		}
	}

	pr_info("MDNIE %s x : %d, y : %d, tune_number : %d", __func__, x, y, tune_number);
	memcpy(&DYNAMIC_BROWSER_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&DYNAMIC_GALLERY_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&DYNAMIC_UI_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&DYNAMIC_VIDEO_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&DYNAMIC_VT_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&DYNAMIC_EBOOK_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);

	memcpy(&STANDARD_BROWSER_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&STANDARD_GALLERY_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&STANDARD_UI_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&STANDARD_VIDEO_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&STANDARD_VT_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&STANDARD_EBOOK_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);

	memcpy(&AUTO_BROWSER_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&AUTO_CAMERA_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&AUTO_GALLERY_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&AUTO_UI_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&AUTO_VIDEO_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
	memcpy(&AUTO_VT_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);

	memcpy(&CAMERA_2[scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
}
#endif
#if 0
void mDNIe_Set_Mode(enum Lcd_mDNIe_UI mode)
{
	struct msm_fb_data_type *mfd;
	mfd = mdnie_msd->mfd;

	DPRINT("mDNIe_Set_Mode start , mode(%d), background(%d)\n",
		mode, mdnie_tun_state.background);

	if (!mfd) {
		DPRINT("[ERROR] mfd is null!\n");
		return;
	}

	if (mfd->resume_state == MIPI_SUSPEND_STATE) {
		DPRINT("[ERROR] not ST_DSI_RESUME. do not send mipi cmd.\n");
		return;
	}

	if (!mdnie_tun_state.mdnie_enable) {
		DPRINT("[ERROR] mDNIE engine is OFF.\n");
		return;
	}

	if (mode < mDNIe_UI_MODE || mode >= MAX_mDNIe_MODE) {
		DPRINT("[ERROR] wrong Scenario mode value : %d\n",
			mode);
		return;
	}

	if (mdnie_tun_state.negative) {
		DPRINT("already negative mode(%d), do not set background(%d)\n",
			mdnie_tun_state.negative, mdnie_tun_state.background);
		return;
	}

	play_speed_1_5 = 0;

	/*
	*	Blind mode & Screen mode has separated menu.
	*	To make a sync below code added.
	*	Bline mode has priority than Screen mode
	*/
	if (mdnie_tun_state.accessibility == COLOR_BLIND)
		mode = mDNIE_BLINE_MODE;
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
	if (get_lcd_panel_res() == 0) { // 0 : wqhd
#endif

	switch (mode) {
	case mDNIe_UI_MODE:
		DPRINT(" = UI MODE =\n");
		if (mdnie_tun_state.background == STANDARD_MODE) {
			DPRINT(" = STANDARD MODE =\n");
			INPUT_PAYLOAD1(STANDARD_UI_1);
			INPUT_PAYLOAD2(STANDARD_UI_2);
		} else if (mdnie_tun_state.background == NATURAL_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(NATURAL_UI_1);
			INPUT_PAYLOAD2(NATURAL_UI_2);
		} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
			DPRINT(" = DYNAMIC MODE =\n");
			INPUT_PAYLOAD1(DYNAMIC_UI_1);
			INPUT_PAYLOAD2(DYNAMIC_UI_2);
		} else if (mdnie_tun_state.background == MOVIE_MODE) {
			DPRINT(" = MOVIE MODE =\n");
			INPUT_PAYLOAD1(MOVIE_UI_1);
			INPUT_PAYLOAD2(MOVIE_UI_2);
		} else if (mdnie_tun_state.background == AUTO_MODE) {
			DPRINT(" = AUTO MODE =\n");
			INPUT_PAYLOAD1(AUTO_UI_1);
			INPUT_PAYLOAD2(AUTO_UI_2);
		}
		break;

	case mDNIe_VIDEO_MODE:
		DPRINT(" = VIDEO MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = OUTDOOR ON MODE =\n");
			INPUT_PAYLOAD1(OUTDOOR_VIDEO_1);
			INPUT_PAYLOAD2(OUTDOOR_VIDEO_2);
		} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			DPRINT(" = OUTDOOR OFF MODE =\n");
			if (mdnie_tun_state.background == STANDARD_MODE) {
				DPRINT(" = STANDARD MODE =\n");
				INPUT_PAYLOAD1(STANDARD_VIDEO_1);
				INPUT_PAYLOAD2(STANDARD_VIDEO_2);
			} else if (mdnie_tun_state.background == NATURAL_MODE) {
				DPRINT(" = NATURAL MODE =\n");
				INPUT_PAYLOAD1(NATURAL_VIDEO_1);
				INPUT_PAYLOAD2(NATURAL_VIDEO_2);
			} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
				DPRINT(" = DYNAMIC MODE =\n");
				INPUT_PAYLOAD1(DYNAMIC_VIDEO_1);
				INPUT_PAYLOAD2(DYNAMIC_VIDEO_2);
			} else if (mdnie_tun_state.background == MOVIE_MODE) {
				DPRINT(" = MOVIE MODE =\n");
				INPUT_PAYLOAD1(MOVIE_VIDEO_1);
				INPUT_PAYLOAD2(MOVIE_VIDEO_2);
			} else if (mdnie_tun_state.background == AUTO_MODE) {
				DPRINT(" = AUTO MODE =\n");
				INPUT_PAYLOAD1(AUTO_VIDEO_1);
				INPUT_PAYLOAD2(AUTO_VIDEO_2);
			}
		}
		break;

	case mDNIe_VIDEO_WARM_MODE:
		DPRINT(" = VIDEO WARM MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = OUTDOOR ON MODE =\n");
			INPUT_PAYLOAD1(WARM_OUTDOOR_1);
			INPUT_PAYLOAD2(WARM_OUTDOOR_2);
		} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			DPRINT(" = OUTDOOR OFF MODE =\n");
			INPUT_PAYLOAD1(WARM_1);
			INPUT_PAYLOAD2(WARM_2);
		}
		break;

	case mDNIe_VIDEO_COLD_MODE:
		DPRINT(" = VIDEO COLD MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = OUTDOOR ON MODE =\n");
			INPUT_PAYLOAD1(COLD_OUTDOOR_1);
			INPUT_PAYLOAD2(COLD_OUTDOOR_2);
		} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			DPRINT(" = OUTDOOR OFF MODE =\n");
			INPUT_PAYLOAD1(COLD_1);
			INPUT_PAYLOAD2(COLD_2);
		}
		break;

	case mDNIe_CAMERA_MODE:
		DPRINT(" = CAMERA MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			if (mdnie_tun_state.background == AUTO_MODE) {
				DPRINT(" = AUTO MODE =\n");
				INPUT_PAYLOAD1(AUTO_CAMERA_1);
				INPUT_PAYLOAD2(AUTO_CAMERA_2);
			} else {
				DPRINT(" = STANDARD MODE =\n");
				INPUT_PAYLOAD1(CAMERA_1);
				INPUT_PAYLOAD2(CAMERA_2);
			}
		} else if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(CAMERA_OUTDOOR_1);
			INPUT_PAYLOAD2(CAMERA_OUTDOOR_2);
		}
		break;

	case mDNIe_NAVI:
		DPRINT(" = NAVI MODE =\n");
		DPRINT("no data for NAVI MODE..\n");
		break;

	case mDNIe_GALLERY:
		DPRINT(" = GALLERY MODE =\n");
		if (mdnie_tun_state.background == STANDARD_MODE) {
			DPRINT(" = STANDARD MODE =\n");
			INPUT_PAYLOAD1(STANDARD_GALLERY_1);
			INPUT_PAYLOAD2(STANDARD_GALLERY_2);
		} else if (mdnie_tun_state.background == NATURAL_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(NATURAL_GALLERY_1);
			INPUT_PAYLOAD2(NATURAL_GALLERY_2);
		} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
			DPRINT(" = DYNAMIC MODE =\n");
			INPUT_PAYLOAD1(DYNAMIC_GALLERY_1);
			INPUT_PAYLOAD2(DYNAMIC_GALLERY_2);
		} else if (mdnie_tun_state.background == MOVIE_MODE) {
			DPRINT(" = MOVIE MODE =\n");
			INPUT_PAYLOAD1(MOVIE_GALLERY_1);
			INPUT_PAYLOAD2(MOVIE_GALLERY_2);
		} else if (mdnie_tun_state.background == AUTO_MODE) {
			DPRINT(" = AUTO MODE =\n");
			INPUT_PAYLOAD1(AUTO_GALLERY_1);
			INPUT_PAYLOAD2(AUTO_GALLERY_2);
		}
		break;

	case mDNIe_VT_MODE:
		DPRINT(" = VT MODE =\n");
		if (mdnie_tun_state.background == STANDARD_MODE) {
			DPRINT(" = STANDARD MODE =\n");
			INPUT_PAYLOAD1(STANDARD_VT_1);
			INPUT_PAYLOAD2(STANDARD_VT_2);
		} else if (mdnie_tun_state.background == NATURAL_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(NATURAL_VT_1);
			INPUT_PAYLOAD2(NATURAL_VT_2);
		} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
			DPRINT(" = DYNAMIC MODE =\n");
			INPUT_PAYLOAD1(DYNAMIC_VT_1);
			INPUT_PAYLOAD2(DYNAMIC_VT_2);
		} else if (mdnie_tun_state.background == MOVIE_MODE) {
			DPRINT(" = MOVIE MODE =\n");
			INPUT_PAYLOAD1(MOVIE_VT_1);
			INPUT_PAYLOAD2(MOVIE_VT_2);
		} else if (mdnie_tun_state.background == AUTO_MODE) {
			DPRINT(" = AUTO MODE =\n");
			INPUT_PAYLOAD1(AUTO_VT_1);
			INPUT_PAYLOAD2(AUTO_VT_2);
		}
		break;

#if defined(CONFIG_TDMB)
	case mDNIe_DMB_MODE:
		DPRINT(" = DMB MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = OUTDOOR ON MODE =\n");
			INPUT_PAYLOAD1(OUTDOOR_DMB_1);
			INPUT_PAYLOAD2(OUTDOOR_DMB_2);
		} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			DPRINT(" = OUTDOOR OFF MODE =\n");
			if (mdnie_tun_state.background == STANDARD_MODE) {
				DPRINT(" = STANDARD MODE =\n");
				INPUT_PAYLOAD1(STANDARD_DMB_1);
				INPUT_PAYLOAD2(STANDARD_DMB_2);
			} else if (mdnie_tun_state.background == NATURAL_MODE) {
				DPRINT(" = NATURAL MODE =\n");
				INPUT_PAYLOAD1(NATURAL_DMB_1);
				INPUT_PAYLOAD2(NATURAL_DMB_2);
			} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
				DPRINT(" = DYNAMIC MODE =\n");
				INPUT_PAYLOAD1(DYNAMIC_DMB_1);
				INPUT_PAYLOAD2(DYNAMIC_DMB_2);
			} else if (mdnie_tun_state.background == MOVIE_MODE) {
				DPRINT(" = MOVIE MODE =\n");
				INPUT_PAYLOAD1(MOVIE_DMB_1);
				INPUT_PAYLOAD2(MOVIE_DMB_2);
			} else if (mdnie_tun_state.background == AUTO_MODE) {
				DPRINT(" = AUTO MODE =\n");
				INPUT_PAYLOAD1(AUTO_DMB_1);
				INPUT_PAYLOAD2(AUTO_DMB_2);
			}
		}
		break;

	case mDNIe_DMB_WARM_MODE:
		DPRINT(" = DMB WARM MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = OUTDOOR ON MODE =\n");
			INPUT_PAYLOAD1(WARM_OUTDOOR_DMB_1);
			INPUT_PAYLOAD2(WARM_OUTDOOR_DMB_2);
		} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			DPRINT(" = OUTDOOR OFF MODE =\n");
			INPUT_PAYLOAD1(WARM_DMB_1);
			INPUT_PAYLOAD2(WARM_DMB_2);
		}
		break;

	case mDNIe_DMB_COLD_MODE:
		DPRINT(" = DMB COLD MODE =\n");
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			DPRINT(" = OUTDOOR ON MODE =\n");
			INPUT_PAYLOAD1(COLD_OUTDOOR_DMB_1);
			INPUT_PAYLOAD2(COLD_OUTDOOR_DMB_2);
		} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
			DPRINT(" = OUTDOOR OFF MODE =\n");
			INPUT_PAYLOAD1(COLD_DMB_1);
			INPUT_PAYLOAD2(COLD_DMB_2);
		}
		break;
#endif

	case mDNIe_BROWSER_MODE:
		DPRINT(" = BROWSER MODE =\n");
		if (mdnie_tun_state.background == STANDARD_MODE) {
			DPRINT(" = STANDARD MODE =\n");
			INPUT_PAYLOAD1(STANDARD_BROWSER_1);
			INPUT_PAYLOAD2(STANDARD_BROWSER_2);
		} else if (mdnie_tun_state.background == NATURAL_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(NATURAL_BROWSER_1);
			INPUT_PAYLOAD2(NATURAL_BROWSER_2);
		} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
			DPRINT(" = DYNAMIC MODE =\n");
			INPUT_PAYLOAD1(DYNAMIC_BROWSER_1);
			INPUT_PAYLOAD2(DYNAMIC_BROWSER_2);
		} else if (mdnie_tun_state.background == MOVIE_MODE) {
			DPRINT(" = MOVIE MODE =\n");
			INPUT_PAYLOAD1(MOVIE_BROWSER_1);
			INPUT_PAYLOAD2(MOVIE_BROWSER_2);
		} else if (mdnie_tun_state.background == AUTO_MODE) {
			DPRINT(" = AUTO MODE =\n");
			INPUT_PAYLOAD1(AUTO_BROWSER_1);
			INPUT_PAYLOAD2(AUTO_BROWSER_2);
		}
		break;

	case mDNIe_eBOOK_MODE:
		DPRINT(" = eBOOK MODE =\n");
		if (mdnie_tun_state.background == STANDARD_MODE) {
			DPRINT(" = STANDARD MODE =\n");
			INPUT_PAYLOAD1(STANDARD_EBOOK_1);
			INPUT_PAYLOAD2(STANDARD_EBOOK_2);
		} else if (mdnie_tun_state.background == NATURAL_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(NATURAL_EBOOK_1);
			INPUT_PAYLOAD2(NATURAL_EBOOK_2);
		} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
			DPRINT(" = DYNAMIC MODE =\n");
			INPUT_PAYLOAD1(DYNAMIC_EBOOK_1);
			INPUT_PAYLOAD2(DYNAMIC_EBOOK_2);
		} else if (mdnie_tun_state.background == MOVIE_MODE) {
			DPRINT(" = MOVIE MODE =\n");
			INPUT_PAYLOAD1(MOVIE_EBOOK_1);
			INPUT_PAYLOAD2(MOVIE_EBOOK_2);
		} else if (mdnie_tun_state.background == AUTO_MODE) {
			DPRINT(" = AUTO MODE =\n");
			INPUT_PAYLOAD1(AUTO_EBOOK_1);
			INPUT_PAYLOAD2(AUTO_EBOOK_2);
		}
		break;
	case mDNIe_EMAIL_MODE:
		DPRINT(" = EMAIL MODE =\n");
		if (mdnie_tun_state.background == STANDARD_MODE) {
			DPRINT(" = STANDARD MODE =\n");
			INPUT_PAYLOAD1(AUTO_EMAIL_1);
			INPUT_PAYLOAD2(AUTO_EMAIL_2);
		} else if (mdnie_tun_state.background == NATURAL_MODE) {
			DPRINT(" = NATURAL MODE =\n");
			INPUT_PAYLOAD1(AUTO_EMAIL_1);
			INPUT_PAYLOAD2(AUTO_EMAIL_2);
		} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
			DPRINT(" = DYNAMIC MODE =\n");
			INPUT_PAYLOAD1(AUTO_EMAIL_1);
			INPUT_PAYLOAD2(AUTO_EMAIL_2);
		} else if (mdnie_tun_state.background == MOVIE_MODE) {
			DPRINT(" = MOVIE MODE =\n");
			INPUT_PAYLOAD1(AUTO_EMAIL_1);
			INPUT_PAYLOAD2(AUTO_EMAIL_2);
		} else if (mdnie_tun_state.background == AUTO_MODE) {
			DPRINT(" = AUTO MODE =\n");
			INPUT_PAYLOAD1(AUTO_EMAIL_1);
			INPUT_PAYLOAD2(AUTO_EMAIL_2);
		}
		break;

	case mDNIE_BLINE_MODE:
		DPRINT(" = BLIND MODE =\n");
		INPUT_PAYLOAD1(COLOR_BLIND_1);
		INPUT_PAYLOAD2(COLOR_BLIND_2);
		break;

	default:
		DPRINT("[%s] no option (%d)\n", __func__, mode);
		return;
	}

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
	 }else { // 1: fhd

		switch (mode) {
			case mDNIe_UI_MODE:
				DPRINT(" = UI MODE =\n");
				if (mdnie_tun_state.background == STANDARD_MODE) {
					DPRINT(" = STANDARD MODE =\n");
					INPUT_PAYLOAD1(STANDARD_UI_1_FHD);
					INPUT_PAYLOAD2(STANDARD_UI_2_FHD);
				} else if (mdnie_tun_state.background == NATURAL_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(NATURAL_UI_1_FHD);
					INPUT_PAYLOAD2(NATURAL_UI_2_FHD);
				} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
					DPRINT(" = DYNAMIC MODE =\n");
					INPUT_PAYLOAD1(DYNAMIC_UI_1_FHD);
					INPUT_PAYLOAD2(DYNAMIC_UI_2_FHD);
				} else if (mdnie_tun_state.background == MOVIE_MODE) {
					DPRINT(" = MOVIE MODE =\n");
					INPUT_PAYLOAD1(MOVIE_UI_1_FHD);
					INPUT_PAYLOAD2(MOVIE_UI_2_FHD);
				} else if (mdnie_tun_state.background == AUTO_MODE) {
					DPRINT(" = AUTO MODE =\n");
					INPUT_PAYLOAD1(AUTO_UI_1_FHD);
					INPUT_PAYLOAD2(AUTO_UI_2_FHD);
				}
				break;

			case mDNIe_VIDEO_MODE:
				DPRINT(" = VIDEO MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = OUTDOOR ON MODE =\n");
					INPUT_PAYLOAD1(OUTDOOR_VIDEO_1_FHD);
					INPUT_PAYLOAD2(OUTDOOR_VIDEO_2_FHD);
				} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					DPRINT(" = OUTDOOR OFF MODE =\n");
					if (mdnie_tun_state.background == STANDARD_MODE) {
						DPRINT(" = STANDARD MODE =\n");
						INPUT_PAYLOAD1(STANDARD_VIDEO_1_FHD);
						INPUT_PAYLOAD2(STANDARD_VIDEO_2_FHD);
					} else if (mdnie_tun_state.background == NATURAL_MODE) {
						DPRINT(" = NATURAL MODE =\n");
						INPUT_PAYLOAD1(NATURAL_VIDEO_1_FHD);
						INPUT_PAYLOAD2(NATURAL_VIDEO_2_FHD);
					} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
						DPRINT(" = DYNAMIC MODE =\n");
						INPUT_PAYLOAD1(DYNAMIC_VIDEO_1_FHD);
						INPUT_PAYLOAD2(DYNAMIC_VIDEO_2_FHD);
					} else if (mdnie_tun_state.background == MOVIE_MODE) {
						DPRINT(" = MOVIE MODE =\n");
						INPUT_PAYLOAD1(MOVIE_VIDEO_1_FHD);
						INPUT_PAYLOAD2(MOVIE_VIDEO_2_FHD);
					} else if (mdnie_tun_state.background == AUTO_MODE) {
						DPRINT(" = AUTO MODE =\n");
						INPUT_PAYLOAD1(AUTO_VIDEO_1_FHD);
						INPUT_PAYLOAD2(AUTO_VIDEO_2_FHD);
					}
				}
				break;

			case mDNIe_VIDEO_WARM_MODE:
				DPRINT(" = VIDEO WARM MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = OUTDOOR ON MODE =\n");
					INPUT_PAYLOAD1(WARM_OUTDOOR_1_FHD);
					INPUT_PAYLOAD2(WARM_OUTDOOR_2_FHD);
				} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					DPRINT(" = OUTDOOR OFF MODE =\n");
					INPUT_PAYLOAD1(WARM_1_FHD);
					INPUT_PAYLOAD2(WARM_2_FHD);
				}
				break;

			case mDNIe_VIDEO_COLD_MODE:
				DPRINT(" = VIDEO COLD MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = OUTDOOR ON MODE =\n");
					INPUT_PAYLOAD1(COLD_OUTDOOR_1_FHD);
					INPUT_PAYLOAD2(COLD_OUTDOOR_2_FHD);
				} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					DPRINT(" = OUTDOOR OFF MODE =\n");
					INPUT_PAYLOAD1(COLD_1_FHD);
					INPUT_PAYLOAD2(COLD_2_FHD);
				}
				break;

			case mDNIe_CAMERA_MODE:
				DPRINT(" = CAMERA MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					if (mdnie_tun_state.background == AUTO_MODE) {
						DPRINT(" = AUTO MODE =\n");
						INPUT_PAYLOAD1(AUTO_CAMERA_1_FHD);
						INPUT_PAYLOAD2(AUTO_CAMERA_2_FHD);
					} else {
						DPRINT(" = STANDARD MODE =\n");
						INPUT_PAYLOAD1(CAMERA_1_FHD);
						INPUT_PAYLOAD2(CAMERA_2_FHD);
					}
				} else if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(CAMERA_OUTDOOR_1_FHD);
					INPUT_PAYLOAD2(CAMERA_OUTDOOR_2_FHD);
				}
				break;

			case mDNIe_NAVI:
				DPRINT(" = NAVI MODE =\n");
				DPRINT("no data for NAVI MODE..\n");
				break;

			case mDNIe_GALLERY:
				DPRINT(" = GALLERY MODE =\n");
				if (mdnie_tun_state.background == STANDARD_MODE) {
					DPRINT(" = STANDARD MODE =\n");
					INPUT_PAYLOAD1(STANDARD_GALLERY_1_FHD);
					INPUT_PAYLOAD2(STANDARD_GALLERY_2_FHD);
				} else if (mdnie_tun_state.background == NATURAL_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(NATURAL_GALLERY_1_FHD);
					INPUT_PAYLOAD2(NATURAL_GALLERY_2_FHD);
				} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
					DPRINT(" = DYNAMIC MODE =\n");
					INPUT_PAYLOAD1(DYNAMIC_GALLERY_1_FHD);
					INPUT_PAYLOAD2(DYNAMIC_GALLERY_2_FHD);
				} else if (mdnie_tun_state.background == MOVIE_MODE) {
					DPRINT(" = MOVIE MODE =\n");
					INPUT_PAYLOAD1(MOVIE_GALLERY_1_FHD);
					INPUT_PAYLOAD2(MOVIE_GALLERY_2_FHD);
				} else if (mdnie_tun_state.background == AUTO_MODE) {
					DPRINT(" = AUTO MODE =\n");
					INPUT_PAYLOAD1(AUTO_GALLERY_1_FHD);
					INPUT_PAYLOAD2(AUTO_GALLERY_2_FHD);
				}
				break;

			case mDNIe_VT_MODE:
				DPRINT(" = VT MODE =\n");
				if (mdnie_tun_state.background == STANDARD_MODE) {
					DPRINT(" = STANDARD MODE =\n");
					INPUT_PAYLOAD1(STANDARD_VT_1_FHD);
					INPUT_PAYLOAD2(STANDARD_VT_2_FHD);
				} else if (mdnie_tun_state.background == NATURAL_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(NATURAL_VT_1_FHD);
					INPUT_PAYLOAD2(NATURAL_VT_2_FHD);
				} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
					DPRINT(" = DYNAMIC MODE =\n");
					INPUT_PAYLOAD1(DYNAMIC_VT_1_FHD);
					INPUT_PAYLOAD2(DYNAMIC_VT_2_FHD);
				} else if (mdnie_tun_state.background == MOVIE_MODE) {
					DPRINT(" = MOVIE MODE =\n");
					INPUT_PAYLOAD1(MOVIE_VT_1_FHD);
					INPUT_PAYLOAD2(MOVIE_VT_2_FHD);
				} else if (mdnie_tun_state.background == AUTO_MODE) {
					DPRINT(" = AUTO MODE =\n");
					INPUT_PAYLOAD1(AUTO_VT_1_FHD);
					INPUT_PAYLOAD2(AUTO_VT_2_FHD);
				}
				break;

#if defined(CONFIG_TDMB)
			case mDNIe_DMB_MODE:
				DPRINT(" = DMB MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = OUTDOOR ON MODE =\n");
					INPUT_PAYLOAD1(OUTDOOR_DMB_1);
					INPUT_PAYLOAD2(OUTDOOR_DMB_2);
				} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					DPRINT(" = OUTDOOR OFF MODE =\n");
					if (mdnie_tun_state.background == STANDARD_MODE) {
						DPRINT(" = STANDARD MODE =\n");
						INPUT_PAYLOAD1(STANDARD_DMB_1);
						INPUT_PAYLOAD2(STANDARD_DMB_2);
					} else if (mdnie_tun_state.background == NATURAL_MODE) {
						DPRINT(" = NATURAL MODE =\n");
						INPUT_PAYLOAD1(NATURAL_DMB_1);
						INPUT_PAYLOAD2(NATURAL_DMB_2);
					} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
						DPRINT(" = DYNAMIC MODE =\n");
						INPUT_PAYLOAD1(DYNAMIC_DMB_1);
						INPUT_PAYLOAD2(DYNAMIC_DMB_2);
					} else if (mdnie_tun_state.background == MOVIE_MODE) {
						DPRINT(" = MOVIE MODE =\n");
						INPUT_PAYLOAD1(MOVIE_DMB_1);
						INPUT_PAYLOAD2(MOVIE_DMB_2);
					} else if (mdnie_tun_state.background == AUTO_MODE) {
						DPRINT(" = AUTO MODE =\n");
						INPUT_PAYLOAD1(AUTO_DMB_1);
						INPUT_PAYLOAD2(AUTO_DMB_2);
					}
				}
				break;

			case mDNIe_DMB_WARM_MODE:
				DPRINT(" = DMB WARM MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = OUTDOOR ON MODE =\n");
					INPUT_PAYLOAD1(WARM_OUTDOOR_DMB_1);
					INPUT_PAYLOAD2(WARM_OUTDOOR_DMB_2);
				} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					DPRINT(" = OUTDOOR OFF MODE =\n");
					INPUT_PAYLOAD1(WARM_DMB_1);
					INPUT_PAYLOAD2(WARM_DMB_2);
				}
				break;

			case mDNIe_DMB_COLD_MODE:
				DPRINT(" = DMB COLD MODE =\n");
				if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
					DPRINT(" = OUTDOOR ON MODE =\n");
					INPUT_PAYLOAD1(COLD_OUTDOOR_DMB_1);
					INPUT_PAYLOAD2(COLD_OUTDOOR_DMB_2);
				} else if (mdnie_tun_state.outdoor == OUTDOOR_OFF_MODE) {
					DPRINT(" = OUTDOOR OFF MODE =\n");
					INPUT_PAYLOAD1(COLD_DMB_1);
					INPUT_PAYLOAD2(COLD_DMB_2);
				}
				break;
#endif

			case mDNIe_BROWSER_MODE:
				DPRINT(" = BROWSER MODE =\n");
				if (mdnie_tun_state.background == STANDARD_MODE) {
					DPRINT(" = STANDARD MODE =\n");
					INPUT_PAYLOAD1(STANDARD_BROWSER_1);
					INPUT_PAYLOAD2(STANDARD_BROWSER_2);
				} else if (mdnie_tun_state.background == NATURAL_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(NATURAL_BROWSER_1);
					INPUT_PAYLOAD2(NATURAL_BROWSER_2);
				} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
					DPRINT(" = DYNAMIC MODE =\n");
					INPUT_PAYLOAD1(DYNAMIC_BROWSER_1);
					INPUT_PAYLOAD2(DYNAMIC_BROWSER_2);
				} else if (mdnie_tun_state.background == MOVIE_MODE) {
					DPRINT(" = MOVIE MODE =\n");
					INPUT_PAYLOAD1(MOVIE_BROWSER_1);
					INPUT_PAYLOAD2(MOVIE_BROWSER_2);
				} else if (mdnie_tun_state.background == AUTO_MODE) {
					DPRINT(" = AUTO MODE =\n");
					INPUT_PAYLOAD1(AUTO_BROWSER_1);
					INPUT_PAYLOAD2(AUTO_BROWSER_2);
				}
				break;

			case mDNIe_eBOOK_MODE:
				DPRINT(" = eBOOK MODE =\n");
				if (mdnie_tun_state.background == STANDARD_MODE) {
					DPRINT(" = STANDARD MODE =\n");
					INPUT_PAYLOAD1(STANDARD_EBOOK_1);
					INPUT_PAYLOAD2(STANDARD_EBOOK_2);
				} else if (mdnie_tun_state.background == NATURAL_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(NATURAL_EBOOK_1);
					INPUT_PAYLOAD2(NATURAL_EBOOK_2);
				} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
					DPRINT(" = DYNAMIC MODE =\n");
					INPUT_PAYLOAD1(DYNAMIC_EBOOK_1);
					INPUT_PAYLOAD2(DYNAMIC_EBOOK_2);
				} else if (mdnie_tun_state.background == MOVIE_MODE) {
					DPRINT(" = MOVIE MODE =\n");
					INPUT_PAYLOAD1(MOVIE_EBOOK_1);
					INPUT_PAYLOAD2(MOVIE_EBOOK_2);
				} else if (mdnie_tun_state.background == AUTO_MODE) {
					DPRINT(" = AUTO MODE =\n");
					INPUT_PAYLOAD1(AUTO_EBOOK_1);
					INPUT_PAYLOAD2(AUTO_EBOOK_2);
				}
				break;

			case mDNIe_EMAIL_MODE:
				DPRINT(" = EMAIL MODE =\n");
				if (mdnie_tun_state.background == STANDARD_MODE) {
					DPRINT(" = STANDARD MODE =\n");
					INPUT_PAYLOAD1(AUTO_EMAIL_1);
					INPUT_PAYLOAD2(AUTO_EMAIL_2);
				} else if (mdnie_tun_state.background == NATURAL_MODE) {
					DPRINT(" = NATURAL MODE =\n");
					INPUT_PAYLOAD1(AUTO_EMAIL_1);
					INPUT_PAYLOAD2(AUTO_EMAIL_2);
				} else if (mdnie_tun_state.background == DYNAMIC_MODE) {
					DPRINT(" = DYNAMIC MODE =\n");
					INPUT_PAYLOAD1(AUTO_EMAIL_1);
					INPUT_PAYLOAD2(AUTO_EMAIL_2);
				} else if (mdnie_tun_state.background == MOVIE_MODE) {
					DPRINT(" = MOVIE MODE =\n");
					INPUT_PAYLOAD1(AUTO_EMAIL_1);
					INPUT_PAYLOAD2(AUTO_EMAIL_2);
				} else if (mdnie_tun_state.background == AUTO_MODE) {
					DPRINT(" = AUTO MODE =\n");
					INPUT_PAYLOAD1(AUTO_EMAIL_1);
					INPUT_PAYLOAD2(AUTO_EMAIL_2);
				}
				break;
			case mDNIE_BLINE_MODE:
				DPRINT(" = BLIND MODE =\n");
				INPUT_PAYLOAD1(COLOR_BLIND_1);
				INPUT_PAYLOAD2(COLOR_BLIND_2);
				break;

			default:
				DPRINT("[%s] no option (%d)\n", __func__, mode);
				return;
			}
	 }
#endif
	sending_tuning_cmd();
	free_tun_cmd();

	DPRINT("mDNIe_Set_Mode end , mode(%d), background(%d)\n",
		mode, mdnie_tun_state.background);
}
#endif
