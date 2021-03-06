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

#define MDNIE_LITE_TUN_DEBUG

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

#if defined(CONFIG_MDNIE_LITE_CONTROL)
static unsigned int hijack = 0; /* By default, do not enable hijacking */
static unsigned int curve = 0;
static unsigned int copy_mode = 0;
static unsigned int black = 0;
static unsigned int black_r = 0;
static unsigned int black_g = 0;
static unsigned int black_b = 0;
static unsigned int sharpen_control[3];
static unsigned int red_control[3];
static unsigned int green_control[3];
static unsigned int blue_control[3];
static unsigned int cyan_control[3];
static unsigned int magenta_control[3];
static unsigned int yellow_control[3];
static unsigned int white_control[3];
static unsigned int black_control[3];
#endif

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
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(level1_key)}, level1_key},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(level2_key)}, level2_key},

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

#if defined(CONFIG_MDNIE_LITE_CONTROL)
void update_mdnie_curve(void)
{
	char *source;
	unsigned int i;

	// Determine the source to copy the curves from
	switch (curve) {
		case DYNAMIC_MODE:	source = DYNAMIC_UI_2;
					break;
		case STANDARD_MODE:	source = STANDARD_UI_2;
					break;
		case NATURAL_MODE:	source = NATURAL_UI_2;
					break;
		case MOVIE_MODE:	source = MOVIE_UI_2;
					break;
		case AUTO_MODE:		source = AUTO_UI_2;
					break;
		default: return;
	}

	for (i = 42; i < 107; i++)
		LITE_CONTROL_2[i] = source[i];

	pr_debug(" = update curve values =\n");
}

void update_mdnie_mode(void)
{
	char *source_1, *source_2;
	int	i;

	// Determine the source to copy the mode from
	switch (copy_mode) {
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
			return;
	}

	LITE_CONTROL_1[4] = source_1[4]; // Copy sharpen

	for (i = 18; i < 107; i++)
		LITE_CONTROL_2[i] = source_2[i]; // Copy mode

	// Apply black crush delta
	LITE_CONTROL_2[37] = max(0,min(255, LITE_CONTROL_2[37] + black));
	LITE_CONTROL_2[39] = max(0,min(255, LITE_CONTROL_2[39] + black));
	LITE_CONTROL_2[41] = max(0,min(255, LITE_CONTROL_2[41] + black));

	pr_debug(" = update mode values =\n");
}
#endif

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

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
	if (!mdnie_tun_state.mdnie_enable) {
		DPRINT("[ERROR] mDNIE engine is OFF.\n");
		return;
	}

#if defined(CONFIG_FB_MSM_MDSS_DSI_DBG)
	if(!dsi_ctrl_on) {
		DPRINT("[ERROR] dsi_on (%d). do not send mipi cmd.\n", dsi_ctrl_on);
		return;
	}
#endif
#endif

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)
#if defined(CONFIG_LCD_CLASS_DEVICE) && defined(DDI_VIDEO_ENHANCE_TUNING)
	if (mdnie_adb_test) {
		DPRINT("[ERROR] mdnie_adb_test is doning .. copy from adb data .. \n");
		INPUT_PAYLOAD1(tune_data2_adb);
		INPUT_PAYLOAD2(tune_data1_adb);
	}
#endif
#endif

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

#if defined(CONFIG_LCD_FORCE_VIDEO_MODE)
	DPRINT("mDNIe_Set_Mode start : return cause of video mode\n");
	return;
#endif

	if (mfd->blank_mode) {
		DPRINT("[ERROR] blank_mode (%d). do not send mipi cmd.\n",
			mfd->blank_mode);
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

	if (mdnie_tun_state.scenario < mDNIe_UI_MODE || mdnie_tun_state.scenario >= MAX_mDNIe_MODE) {
		DPRINT("[ERROR] wrong Scenario mode value : %d\n",
			mdnie_tun_state.scenario);
		return;
	}

	play_speed_1_5 = 0;

#ifdef CONFIG_MDNIE_LITE_CONTROL
	if (hijack == HIJACK_ENABLED) {
		DPRINT(" = CONTROL MODE =\n");
		INPUT_PAYLOAD1(LITE_CONTROL_1);
		INPUT_PAYLOAD2(LITE_CONTROL_2);
	} else 
#endif
	if (mdnie_tun_state.accessibility) {
		DPRINT(" = ACCESSIBILITY MODE =\n");
		INPUT_PAYLOAD1(blind_tune_value[mdnie_tun_state.accessibility][0]);
		INPUT_PAYLOAD2(blind_tune_value[mdnie_tun_state.accessibility][1]);
	}

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || defined (CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) \
	|| defined (CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL)
	else if (mdnie_msd->dstat.auto_brightness == 6) {
		DPRINT("[LOCAL CE] HBM mode! only LOCAL CE tuning\n");
#if defined(CONFIG_MDNIE_ENHENCED_LOCAL_CE)
			INPUT_PAYLOAD1(LOCAL_CE_1_ENHENCED);
			INPUT_PAYLOAD2(LOCAL_CE_2_ENHENCED);
#else
#if defined (CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL)
			if((mdnie_tun_state.scenario == mDNIe_BROWSER_MODE)||(mdnie_tun_state.scenario == mDNIe_eBOOK_MODE))
			{
				INPUT_PAYLOAD1(LOCAL_CE_1_TEXT);
				INPUT_PAYLOAD2(LOCAL_CE_2_TEXT);
			}
			else
#endif
			{
				INPUT_PAYLOAD1(LOCAL_CE_1);
				INPUT_PAYLOAD2(LOCAL_CE_2);
			}
#endif
	}
#endif
#if defined(CONFIG_TDMB)
	else if (mdnie_tun_state.dmb > DMB_MODE_OFF){
		if (!dmb_tune_value[mdnie_tun_state.dmb][mdnie_tun_state.background][mdnie_tun_state.outdoor][0] ||
			!dmb_tune_value[mdnie_tun_state.dmb][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]) {
			pr_err("dmb tune data is NULL!\n");
			return;
		} else {
			INPUT_PAYLOAD1(
				dmb_tune_value[mdnie_tun_state.dmb][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
			INPUT_PAYLOAD2(
				dmb_tune_value[mdnie_tun_state.dmb][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
		}
	}
#endif
	else {
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
			if (!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0] ||
				!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]) {
				pr_err("mdnie tune data is NULL!\n");
				return;
			} else {
				INPUT_PAYLOAD1(
					mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
				INPUT_PAYLOAD2(
					mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
				mdnie_tun_state.scr_white_red = mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1][ADDRESS_SCR_WHITE_RED];
				mdnie_tun_state.scr_white_green = mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1][ADDRESS_SCR_WHITE_GREEN];
				mdnie_tun_state.scr_white_blue= mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1][ADDRESS_SCR_WHITE_BLUE];
			}
#else
#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
		if (!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0] ||
			!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1] ||
			!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][2] ||
			!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][3] ||
			!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][4]) {
#else
		if (!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0] ||
			!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]) {
#endif
			pr_err("mdnie tune data is NULL!\n");
			return;
		} else {
#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
			INPUT_PAYLOAD1(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
			INPUT_PAYLOAD2(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
			INPUT_PAYLOAD3(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][2]);
			INPUT_PAYLOAD4(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][3]);
			INPUT_PAYLOAD5(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][4]);
#else
			INPUT_PAYLOAD1(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
			INPUT_PAYLOAD2(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
#endif
		}
#endif
}

	sending_tuning_cmd();
	free_tun_cmd();

	DPRINT("mDNIe_Set_Mode end , %s(%d), %s(%d), %s(%d), %s(%d)\n",
		scenario_name[mdnie_tun_state.scenario], mdnie_tun_state.scenario,
		background_name[mdnie_tun_state.background], mdnie_tun_state.background,
		outdoor_name[mdnie_tun_state.outdoor], mdnie_tun_state.outdoor,
		accessibility_name[mdnie_tun_state.accessibility], mdnie_tun_state.accessibility);

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
	DPRINT("Current Background Mode : %s\n",
		background_name[mdnie_tun_state.background]);

	return snprintf(buf, 256, "Current Background Mode : %s\n",
		background_name[mdnie_tun_state.background]);
}

static ssize_t mode_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	int value;
	int backup;

	sscanf(buf, "%d", &value);

	if (value < DYNAMIC_MODE || value >= MAX_BACKGROUND_MODE) {
		DPRINT("[ERROR] wrong backgound mode value : %d\n",
			value);
		return size;
	}
	backup = mdnie_tun_state.background;
	mdnie_tun_state.background = value;

	if (mdnie_tun_state.accessibility == NEGATIVE) {
		DPRINT("already negative mode(%d), do not set background(%d)\n",
			mdnie_tun_state.accessibility, mdnie_tun_state.background);
	} else {
		DPRINT(" %s : (%s) -> (%s)\n",
			__func__, background_name[backup], background_name[mdnie_tun_state.background]);

		mDNIe_Set_Mode();
	}

	return size;
}

static DEVICE_ATTR(mode, 0664, mode_show, mode_store);

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

#if defined(CONFIG_MDNIE_LITE_CONTROL)
/* hijack */

static ssize_t hijack_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", hijack);
}

static ssize_t hijack_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val <= 0)
		new_val = 0;
	if (new_val >= 1);
		new_val = 1;

	hijack = new_val;
	mDNIe_Set_Mode();
	return size;
}

/* curve */

static ssize_t curve_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", curve);
}

static ssize_t curve_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val <= DYNAMIC_MODE)
		new_val = DYNAMIC_MODE;
	if (new_val >= AUTO_MODE);
		new_val = AUTO_MODE;

	curve = new_val;

	update_mdnie_curve();

	if (hijack == HIJACK_ENABLED)
		mDNIe_Set_Mode();

	return size;
}

/* copy_mode */

static ssize_t copy_mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", copy_mode);
}

static ssize_t copy_mode_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val <= DYNAMIC_MODE)
		new_val = DYNAMIC_MODE;
	if (new_val >= AUTO_MODE);
		new_val = AUTO_MODE;

	copy_mode = new_val;

	update_mdnie_mode();

	if (hijack == HIJACK_ENABLED)
		mDNIe_Set_Mode();

	return size;
}

/* sharpen */

static ssize_t sharpen_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_1[4]);
}

static ssize_t sharpen_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val <= 0)
		new_val = 0;
	if (new_val >= 11)
		new_val = 11;

	LITE_CONTROL_1[4] = new_val;

	if (hijack == HIJACK_ENABLED)
		mDNIe_Set_Mode();

	return size;
}

/* red */

static ssize_t red_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[19]);
}

static ssize_t red_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[19]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new red_red: %d\n", new_val);
		LITE_CONTROL_2[19] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t red_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[21]);
}

static ssize_t red_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[21]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new red_green: %d\n", new_val);
		LITE_CONTROL_2[21] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t red_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[23]);
}

static ssize_t red_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[23]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new red_blue: %d\n", new_val);
		LITE_CONTROL_2[23] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* cyan */

static ssize_t cyan_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[18]);
}

static ssize_t cyan_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[18]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new cyan_red: %d\n", new_val);
		LITE_CONTROL_2[18] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t cyan_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[20]);
}

static ssize_t cyan_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
    int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[20]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new cyan_green: %d\n", new_val);
		LITE_CONTROL_2[20] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t cyan_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[22]);
}

static ssize_t cyan_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[22]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new cyan_blue: %d\n", new_val);
		LITE_CONTROL_2[22] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* green */

static ssize_t green_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[25]);
}

static ssize_t green_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[25]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new green_red: %d\n", new_val);
		LITE_CONTROL_2[25] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t green_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[27]);
}

static ssize_t green_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[27]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new green_green: %d\n", new_val);
		LITE_CONTROL_2[27] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t green_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[29]);
}

static ssize_t green_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[29]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new green_blue: %d\n", new_val);
		LITE_CONTROL_2[29] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* magenta */

static ssize_t magenta_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[24]);
}

static ssize_t magenta_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[24]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new magenta_red: %d\n", new_val);
		LITE_CONTROL_2[24] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t magenta_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[26]);
}

static ssize_t magenta_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[26]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new magenta_green: %d\n", new_val);
		LITE_CONTROL_2[26] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t magenta_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[28]);
}

static ssize_t magenta_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[28]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new magenta_blue: %d\n", new_val);
		LITE_CONTROL_2[28] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* blue */

static ssize_t blue_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[31]);
}

static ssize_t blue_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[31]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new blue_red: %d\n", new_val);
		LITE_CONTROL_2[31] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t blue_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[33]);
}

static ssize_t blue_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[33]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new blue_green: %d\n", new_val);
		LITE_CONTROL_2[33] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t blue_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[35]);
}

static ssize_t blue_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[35]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new blue_blue: %d\n", new_val);
		LITE_CONTROL_2[35] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* yellow */

static ssize_t yellow_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[30]);
}

static ssize_t yellow_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[30]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new yellow_red: %d\n", new_val);
		LITE_CONTROL_2[30] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t yellow_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[32]);
}

static ssize_t yellow_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[32]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new yellow_green: %d\n", new_val);
		LITE_CONTROL_2[32] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t yellow_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[34]);
}

static ssize_t yellow_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[34]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new yellow_blue: %d\n", new_val);
		LITE_CONTROL_2[34] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* black */

static ssize_t black_crush_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", black);
}

static ssize_t black_crush_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	black = new_val;
	LITE_CONTROL_2[37] = max(0,min(255, black_r + black));
	LITE_CONTROL_2[39] = max(0,min(255, black_g + black));
	LITE_CONTROL_2[41] = max(0,min(255, black_b + black));
	if (hijack == HIJACK_ENABLED)
		mDNIe_Set_Mode();

	return size;
}

static ssize_t black_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", black_r);
}

static ssize_t black_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != black_r) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new black_red: %d\n", new_val);
		black_r = new_val;
		LITE_CONTROL_2[37] = max(0,min(255, black_r + black));
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t black_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", black_g);
}

static ssize_t black_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != black_g) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new black_green: %d\n", new_val);
		black_g = new_val;
		LITE_CONTROL_2[39] = max(0,min(255, black_g + black));
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t black_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", max(0, black_b));
}

static ssize_t black_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != black_b) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new black_blue: %d\n", new_val);
		black_b = new_val;
		LITE_CONTROL_2[41] = max(0,min(255, black_b + black));
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

/* white */

static ssize_t white_red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[36]);
}

static ssize_t white_red_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[36]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new white_red: %d\n", new_val);
		LITE_CONTROL_2[36] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t white_green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[38]);
}

static ssize_t white_green_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[38]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new white_green: %d\n", new_val);
		LITE_CONTROL_2[38] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t white_blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", LITE_CONTROL_2[40]);
}

static ssize_t white_blue_store(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
	int new_val;
	sscanf(buf, "%d", &new_val);

	if (new_val != LITE_CONTROL_2[40]) {
		if (new_val < 0 || new_val > 255)
			return -EINVAL;
		DPRINT("new white_blue: %d\n", new_val);
		LITE_CONTROL_2[40] = new_val;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
	return size;
}

static ssize_t red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[19], LITE_CONTROL_2[21], LITE_CONTROL_2[23]);
}

static ssize_t red_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[19] || green != LITE_CONTROL_2[21] || blue != LITE_CONTROL_2[23]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[RED] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[19] = red;
		LITE_CONTROL_2[21] = green;
		LITE_CONTROL_2[23] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* green */

static ssize_t green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[25], LITE_CONTROL_2[27], LITE_CONTROL_2[29]);
}

static ssize_t green_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[25] || green != LITE_CONTROL_2[27] || blue != LITE_CONTROL_2[29]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[GREEN] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[25] = red;
		LITE_CONTROL_2[27] = green;
		LITE_CONTROL_2[29] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* blue */

static ssize_t blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[31], LITE_CONTROL_2[33], LITE_CONTROL_2[35]);
}

static ssize_t blue_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[31] || green != LITE_CONTROL_2[33] || blue != LITE_CONTROL_2[35]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[BLUE] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[31] = red;
		LITE_CONTROL_2[33] = green;
		LITE_CONTROL_2[35] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* cyan */

static ssize_t cyan_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[18], LITE_CONTROL_2[20], LITE_CONTROL_2[22]);
}

static ssize_t cyan_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[18] || green != LITE_CONTROL_2[20] || blue != LITE_CONTROL_2[22]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[CYAN] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[18] = red;
		LITE_CONTROL_2[20] = green;
		LITE_CONTROL_2[22] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* magenta */

static ssize_t magenta_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[24], LITE_CONTROL_2[26], LITE_CONTROL_2[28]);
}

static ssize_t magenta_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[24] || green != LITE_CONTROL_2[26] || blue != LITE_CONTROL_2[28]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[MAGENTA] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[24] = red;
		LITE_CONTROL_2[26] = green;
		LITE_CONTROL_2[28] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* yellow */

static ssize_t yellow_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[30], LITE_CONTROL_2[32], LITE_CONTROL_2[34]);
}

static ssize_t yellow_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[30] || green != LITE_CONTROL_2[32] || blue != LITE_CONTROL_2[34]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[YELLOW] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[30] = red;
		LITE_CONTROL_2[32] = green;
		LITE_CONTROL_2[34] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* white */

static ssize_t white_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[36], LITE_CONTROL_2[38], LITE_CONTROL_2[40]);
}

static ssize_t white_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[36] || green != LITE_CONTROL_2[38] || blue != LITE_CONTROL_2[40]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[WHITE] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[36] = red;
		LITE_CONTROL_2[38] = green;
		LITE_CONTROL_2[40] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

/* black */

static ssize_t black_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%u %d %d\n", LITE_CONTROL_2[37], LITE_CONTROL_2[39], LITE_CONTROL_2[41]);
}

static ssize_t black_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != LITE_CONTROL_2[37] || green != LITE_CONTROL_2[39] || blue != LITE_CONTROL_2[41]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[BLACK] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		LITE_CONTROL_2[37] = red;
		LITE_CONTROL_2[39] = green;
		LITE_CONTROL_2[41] = blue;
		if (hijack == HIJACK_ENABLED)
			mDNIe_Set_Mode();
	}
    return size;
}

static DEVICE_ATTR(hijack, 0664, hijack_show, hijack_store);
static DEVICE_ATTR(curve, 0664, curve_show, curve_store);
static DEVICE_ATTR(copy_mode, 0664, copy_mode_show, copy_mode_store);
static DEVICE_ATTR(sharpen, 0664, sharpen_show, sharpen_store);
static DEVICE_ATTR(red_red, 0664, red_red_show, red_red_store);
static DEVICE_ATTR(red_green, 0664, red_green_show, red_green_store);
static DEVICE_ATTR(red_blue, 0664, red_blue_show, red_blue_store);
static DEVICE_ATTR(cyan_red, 0664, cyan_red_show, cyan_red_store);
static DEVICE_ATTR(cyan_green, 0664, cyan_green_show, cyan_green_store);
static DEVICE_ATTR(cyan_blue, 0664, cyan_blue_show, cyan_blue_store);
static DEVICE_ATTR(green_red, 0664, green_red_show, green_red_store);
static DEVICE_ATTR(green_green, 0664, green_green_show, green_green_store);
static DEVICE_ATTR(green_blue, 0664, green_blue_show, green_blue_store);
static DEVICE_ATTR(magenta_red, 0664, magenta_red_show, magenta_red_store);
static DEVICE_ATTR(magenta_green, 0664, magenta_green_show, magenta_green_store);
static DEVICE_ATTR(magenta_blue, 0664, magenta_blue_show, magenta_blue_store);
static DEVICE_ATTR(blue_red, 0664, blue_red_show, blue_red_store);
static DEVICE_ATTR(blue_green, 0664, blue_green_show, blue_green_store);
static DEVICE_ATTR(blue_blue, 0664, blue_blue_show, blue_blue_store);
static DEVICE_ATTR(yellow_red, 0664, yellow_red_show, yellow_red_store);
static DEVICE_ATTR(yellow_green, 0664, yellow_green_show, yellow_green_store);
static DEVICE_ATTR(yellow_blue, 0664, yellow_blue_show, yellow_blue_store);
static DEVICE_ATTR(black, 0664, black_crush_show, black_crush_store);
static DEVICE_ATTR(black_red, 0664, black_red_show, black_red_store);
static DEVICE_ATTR(black_green, 0664, black_green_show, black_green_store);
static DEVICE_ATTR(black_blue, 0664, black_blue_show, black_blue_store);
static DEVICE_ATTR(white_red, 0664, white_red_show, white_red_store);
static DEVICE_ATTR(white_green, 0664, white_green_show, white_green_store);
static DEVICE_ATTR(white_blue, 0664, white_blue_show, white_blue_store);
static DEVICE_ATTR(control_sharpen, 0664, sharpen_show, sharpen_store);
static DEVICE_ATTR(control_red, 0664, red_show, red_store);
static DEVICE_ATTR(control_green, 0664, green_show, green_store);
static DEVICE_ATTR(control_blue, 0664, blue_show, blue_store);
static DEVICE_ATTR(control_cyan, 0664, cyan_show, cyan_store);
static DEVICE_ATTR(control_magenta, 0664, magenta_show, magenta_store);
static DEVICE_ATTR(control_yellow, 0664, yellow_show, yellow_store);
static DEVICE_ATTR(control_white, 0664, white_show, white_store);
static DEVICE_ATTR(control_black, 0664, black_show, black_store);
#endif

static DEVICE_ATTR(scenario, 0664, scenario_show, scenario_store);

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

static DEVICE_ATTR(mdnieset_user_select_file_cmd, 0664,
		   mdnieset_user_select_file_cmd_show,
		   mdnieset_user_select_file_cmd_store);

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

static DEVICE_ATTR(mdnieset_init_file_cmd, 0664, mdnieset_init_file_cmd_show,
		   mdnieset_init_file_cmd_store);

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

static DEVICE_ATTR(outdoor, 0664, outdoor_show, outdoor_store);

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
static DEVICE_ATTR(playspeed, 0664,
			playspeed_show,
			playspeed_store);

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
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL) || defined (CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) ||\
	defined(CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL) || defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL) ||\
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_FULL_HD_PT_PANEL)
	else if (cmd_value == SCREEN_CURTAIN) {
		mdnie_tun_state.accessibility = SCREEN_CURTAIN;
	}
#endif
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

static DEVICE_ATTR(accessibility, 0664,
			accessibility_show,
			accessibility_store);

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
static ssize_t sensorRGB_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
		return sprintf(buf, "%d %d %d\n", mdnie_tun_state.scr_white_red, mdnie_tun_state.scr_white_green, mdnie_tun_state.scr_white_blue);
}

static ssize_t sensorRGB_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	int red, green, blue;
	char white_red, white_green, white_blue;

	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if ((mdnie_tun_state.accessibility == ACCESSIBILITY_OFF) && (mdnie_tun_state.background == AUTO_MODE) &&	\
		((mdnie_tun_state.scenario == mDNIe_BROWSER_MODE) || (mdnie_tun_state.scenario == mDNIe_eBOOK_MODE)))
	{
		white_red = (char)(red);
		white_green = (char)(green);
		white_blue= (char)(blue);
		mdnie_tun_state.scr_white_red = red;
		mdnie_tun_state.scr_white_green = green;
		mdnie_tun_state.scr_white_blue= blue;
		DPRINT("%s: white_red = %d, white_green = %d, white_blue = %d\n", __func__, white_red, white_green, white_blue);

			INPUT_PAYLOAD1(mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
			memcpy( white_rgb_buf, mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1], MDNIE_TUNE_FIRST_SIZE);

		white_rgb_buf[ADDRESS_SCR_WHITE_RED] = white_red;
		white_rgb_buf[ADDRESS_SCR_WHITE_GREEN] = white_green;
		white_rgb_buf[ADDRESS_SCR_WHITE_BLUE] = white_blue;

		INPUT_PAYLOAD2(white_rgb_buf);
		sending_tuning_cmd();
		free_tun_cmd();
	}

	return size;
}

static DEVICE_ATTR(sensorRGB, 0664, sensorRGB_show, sensorRGB_store);
#endif

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
#if defined(DDI_VIDEO_ENHANCE_TUNING)
#define MAX_FILE_NAME	128
#define TUNING_FILE_PATH "/sdcard/"
static char tuning_file[MAX_FILE_NAME];

static char char_to_dec(char data1, char data2)
{
	char dec;

	dec = 0;

	if (data1 >= 'a') {
		data1 -= 'a';
		data1 += 10;
	} else if (data1 >= 'A') {
		data1 -= 'A';
		data1 += 10;
	} else
		data1 -= '0';

	dec = data1 << 4;

	if (data2 >= 'a') {
		data2 -= 'a';
		data2 += 10;
	} else if (data2 >= 'A') {
		data2 -= 'A';
		data2 += 10;
	} else
		data2 -= '0';

	dec |= data2;

	return dec;
}

static void sending_tune_cmd(char *src, int len)
{
	int data_pos = 0;
	int cmd_step = 0;
	int cmd_pos = 0;
	int tbl_cnt = 0;

	for (data_pos = 0; data_pos < len;) {
		if (*(src + data_pos) == '0') {
			if (*(src + data_pos + 1) == 'x') {

#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
				if (cmd_step == 0) {
					tune_data1[cmd_pos] = char_to_dec(*(src + data_pos + 2), *(src + data_pos + 3));
				} else if (cmd_step == 1) {
					tune_data2[cmd_pos] = char_to_dec(*(src + data_pos + 2), *(src + data_pos + 3));
				} else if (cmd_step == 2) {
					tune_data3[cmd_pos] = char_to_dec(*(src + data_pos + 2), *(src + data_pos + 3));
				} else if (cmd_step == 3) {
					tune_data4[cmd_pos] = char_to_dec(*(src + data_pos + 2), *(src + data_pos + 3));
				} else if (cmd_step == 4) {
					tune_data5[cmd_pos] = char_to_dec(*(src + data_pos + 2), *(src + data_pos + 3));
				}
#endif

				data_pos += 3;
				cmd_pos++;

				if (cmd_pos == tune_size_tbl[tbl_cnt] && cmd_step == tbl_cnt) {
					cmd_pos = 0;
					cmd_step++;
					tbl_cnt++;
				}
			} else
				data_pos++;
		} else {
			data_pos++;
		}
	}


#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
	INPUT_PAYLOAD1(tune_data1);
	INPUT_PAYLOAD2(tune_data2);
	INPUT_PAYLOAD3(tune_data3);
	INPUT_PAYLOAD4(tune_data4);
	INPUT_PAYLOAD5(tune_data5);
#endif

	print_tun_data();

	sending_tuning_cmd();
	free_tun_cmd();
}

static void load_tuning_file(char *filename)
{
	struct file *filp;
	char *dp;
	long l;
	loff_t pos;
	int ret;
	mm_segment_t fs;

	pr_info("%s called loading file name : [%s]\n", __func__,
	       filename);

	fs = get_fs();
	set_fs(get_ds());

	filp = filp_open(filename, O_RDONLY, 0);
	if (IS_ERR(filp)) {
		printk(KERN_ERR "%s File open failed\n", __func__);
		return;
	}

	l = filp->f_path.dentry->d_inode->i_size;
	pr_info("%s Loading File Size : %ld(bytes)", __func__, l);

	dp = kmalloc(l + 10, GFP_KERNEL);
	if (dp == NULL) {
		pr_info("Can't not alloc memory for tuning file load\n");
		filp_close(filp, current->files);
		return;
	}
	pos = 0;
	memset(dp, 0, l);

	pr_info("%s before vfs_read()\n", __func__);
	ret = vfs_read(filp, (char __user *)dp, l, &pos);
	pr_info("%s after vfs_read()\n", __func__);

	if (ret != l) {
		pr_info("vfs_read() filed ret : %d\n", ret);
		kfree(dp);
		filp_close(filp, current->files);
		return;
	}

	filp_close(filp, current->files);

	set_fs(fs);

	sending_tune_cmd(dp, l);

	kfree(dp);
}

static ssize_t tuning_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int ret = 0;

	ret = snprintf(buf, MAX_FILE_NAME, "tuned file name : %s\n", tuning_file);

	return ret;
}

static ssize_t tuning_store(struct device *dev,
			struct device_attribute *attr, const char *buf, size_t size)
{
	char *pt;
	memset(tuning_file, 0, sizeof(tuning_file));
	snprintf(tuning_file, MAX_FILE_NAME, "%s%s", TUNING_FILE_PATH, buf);

	pt = tuning_file;
	while (*pt) {
		if (*pt == '\r' || *pt == '\n') {
			*pt = 0;
			break;
		}
		pt++;
	}

	DPRINT("%s\n", tuning_file);

	load_tuning_file(tuning_file);

	return size;
}
static DEVICE_ATTR(tuning, S_IRUGO | S_IWUSR | S_IWGRP,
						tuning_show,
						tuning_store);

#endif /* DDI_VIDEO_ENHANCE_TUNING */
#endif /* CONFIG_FB_MSM_MDSS_MDP3 */

static struct class *mdnie_class;
struct device *tune_mdnie_dev;

void init_mdnie_class(void)
{
	if (mdnie_tun_state.mdnie_enable) {
		pr_err("%s : mdnie already enable.. \n",__func__);
		return;
	}

	DPRINT("start!\n");

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

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
	if (device_create_file
		(tune_mdnie_dev, &dev_attr_sensorRGB) < 0)
		pr_err("Failed to create device file(%s)!=n",
			dev_attr_sensorRGB.attr.name);
#endif

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
#if defined(DDI_VIDEO_ENHANCE_TUNING)
	if (device_create_file
		(tune_mdnie_dev, &dev_attr_tuning) < 0)
		pr_err("Failed to create device file(%s)!=n",
			dev_attr_tuning.attr.name);
#endif
#endif

#if defined(CONFIG_MDNIE_LITE_CONTROL)
	device_create_file(tune_mdnie_dev, &dev_attr_hijack);
	device_create_file(tune_mdnie_dev, &dev_attr_curve);
	device_create_file(tune_mdnie_dev, &dev_attr_copy_mode);
	device_create_file(tune_mdnie_dev, &dev_attr_sharpen);
	device_create_file(tune_mdnie_dev, &dev_attr_red_red);
	device_create_file(tune_mdnie_dev, &dev_attr_red_green);
	device_create_file(tune_mdnie_dev, &dev_attr_red_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_cyan_red);
	device_create_file(tune_mdnie_dev, &dev_attr_cyan_green);
	device_create_file(tune_mdnie_dev, &dev_attr_cyan_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_green_red);
	device_create_file(tune_mdnie_dev, &dev_attr_green_green);
	device_create_file(tune_mdnie_dev, &dev_attr_green_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_magenta_red);
	device_create_file(tune_mdnie_dev, &dev_attr_magenta_green);
	device_create_file(tune_mdnie_dev, &dev_attr_magenta_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_blue_red);
	device_create_file(tune_mdnie_dev, &dev_attr_blue_green);
	device_create_file(tune_mdnie_dev, &dev_attr_blue_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_yellow_red);
	device_create_file(tune_mdnie_dev, &dev_attr_yellow_green);
	device_create_file(tune_mdnie_dev, &dev_attr_yellow_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_black);
	device_create_file(tune_mdnie_dev, &dev_attr_black_red);
	device_create_file(tune_mdnie_dev, &dev_attr_black_green);
	device_create_file(tune_mdnie_dev, &dev_attr_black_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_white_red);
	device_create_file(tune_mdnie_dev, &dev_attr_white_green);
	device_create_file(tune_mdnie_dev, &dev_attr_white_blue);
	/* -------------------------------------------------------
	 * Add whathub's new interface
	 * 
	 * NB: Current interface is kept as more app friendly.
	 * 
	 * (Yank555.lu)
	 * ------------------------------------------------------- */
	device_create_file(tune_mdnie_dev, &dev_attr_control_sharpen);
	device_create_file(tune_mdnie_dev, &dev_attr_control_red);
	device_create_file(tune_mdnie_dev, &dev_attr_control_green);
	device_create_file(tune_mdnie_dev, &dev_attr_control_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_control_cyan);
	device_create_file(tune_mdnie_dev, &dev_attr_control_magenta);
	device_create_file(tune_mdnie_dev, &dev_attr_control_yellow);
	device_create_file(tune_mdnie_dev, &dev_attr_control_white);
	device_create_file(tune_mdnie_dev, &dev_attr_control_black);
#endif

	mdnie_tun_state.mdnie_enable = true;

#if defined(CONFIG_TDMB)
	strcpy((char*) scenario_name[mDNIe_DMB_MODE], "DMB_MODE");
	strcpy((char*) scenario_name[mDNIe_DMB_WARM_MODE], "DMB_WARM_MODE");
	strcpy((char*) scenario_name[mDNIe_DMB_COLD_MODE], "DMB_COLD_MODE");
#endif

	DPRINT("end!\n");
}

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
void mdnie_lite_tuning_init(struct mdss_dsi_driver_data *msd)
#else
void mdnie_lite_tuning_init(struct mipi_samsung_driver_data *msd)
#endif
{
	mdnie_msd = msd;
}

#ifndef COORDINATE_DATA_NONE
#define coordinate_data_size 6
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_FULL_HD_PT_PANEL) || defined(CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
#define scr_wr_addr 36
#endif

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL) \
	|| defined(CONFIG_FB_MSM_MIPI_SAMSUNG_YOUM_CMD_FULL_HD_PT_PANEL)

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

#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || defined (CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)

#define scr_wr_addr 122

#define F1(x,y) ((y)-((164*(x))/151)+8)
#define F2(x,y) ((y)-((70*(x))/67)-7)
#define F3(x,y) ((y)+((181*(x))/35)-18852)
#define F4(x,y) ((y)+((157*(x))/52)-12055)

static char coordinate_data[][coordinate_data_size] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* dummy */
	{0xff, 0x00, 0xfa, 0x00, 0xfa, 0x00}, /* Tune_1 */
	{0xff, 0x00, 0xfb, 0x00, 0xfe, 0x00}, /* Tune_2 */
	{0xfc, 0x00, 0xfb, 0x00, 0xff, 0x00}, /* Tune_3 */
	{0xff, 0x00, 0xfe, 0x00, 0xfb, 0x00}, /* Tune_4 */
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_5 */
	{0xfb, 0x00, 0xfc, 0x00, 0xff, 0x00}, /* Tune_6 */
	{0xfc, 0x00, 0xff, 0x00, 0xfa, 0x00}, /* Tune_7 */
	{0xfb, 0x00, 0xff, 0x00, 0xfb, 0x00}, /* Tune_8 */
	{0xfb, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_9 */
};

#elif defined (CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL)

#define scr_wr_addr 36

#define F1(x,y) ((y)-((164*(x))/151)+8)
#define F2(x,y) ((y)-((70*(x))/67)-7)
#define F3(x,y) ((y)+((181*(x))/35)-18852)
#define F4(x,y) ((y)+((157*(x))/52)-12055)

static char coordinate_data[][coordinate_data_size] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* dummy */
	{0xff, 0x00, 0xfa, 0x00, 0xfa, 0x00}, /* Tune_1 */
	{0xff, 0x00, 0xfb, 0x00, 0xfe, 0x00}, /* Tune_2 */
	{0xfc, 0x00, 0xfb, 0x00, 0xff, 0x00}, /* Tune_3 */
	{0xff, 0x00, 0xfe, 0x00, 0xfb, 0x00}, /* Tune_4 */
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_5 */
	{0xfb, 0x00, 0xfc, 0x00, 0xff, 0x00}, /* Tune_6 */
	{0xfc, 0x00, 0xff, 0x00, 0xfa, 0x00}, /* Tune_7 */
	{0xfb, 0x00, 0xff, 0x00, 0xfb, 0x00}, /* Tune_8 */
	{0xfb, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_9 */
};

#elif defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
extern int flip;

#define scr_wr_addr 36

#define F1(x,y) ((y)-((164*(x))/151)+8)
#define F2(x,y) ((y)-((70*(x))/67)-7)
#define F3(x,y) ((y)+((181*(x))/35)-18852)
#define F4(x,y) ((y)+((157*(x))/52)-12055)

static char coordinate_data_main[][coordinate_data_size] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* dummy */
	{0xff, 0x00, 0xfa, 0x00, 0xfa, 0x00}, /* Tune_1 */
	{0xff, 0x00, 0xfb, 0x00, 0xfe, 0x00}, /* Tune_2 */
	{0xfc, 0x00, 0xfb, 0x00, 0xff, 0x00}, /* Tune_3 */
	{0xff, 0x00, 0xfe, 0x00, 0xfb, 0x00}, /* Tune_4 */
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_5 */
	{0xfb, 0x00, 0xfc, 0x00, 0xff, 0x00}, /* Tune_6 */
	{0xfc, 0x00, 0xff, 0x00, 0xfa, 0x00}, /* Tune_7 */
	{0xfb, 0x00, 0xff, 0x00, 0xfb, 0x00}, /* Tune_8 */
	{0xfa, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_9 */
};

static char coordinate_data_sub[][coordinate_data_size] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* dummy */
	{0xff, 0x00, 0xfa, 0x00, 0xfa, 0x00}, /* Tune_1 */
	{0xff, 0x00, 0xfb, 0x00, 0xfe, 0x00}, /* Tune_2 */
	{0xfc, 0x00, 0xfb, 0x00, 0xff, 0x00}, /* Tune_3 */
	{0xff, 0x00, 0xfe, 0x00, 0xfb, 0x00}, /* Tune_4 */
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_5 */
	{0xfb, 0x00, 0xfc, 0x00, 0xff, 0x00}, /* Tune_6 */
	{0xfc, 0x00, 0xff, 0x00, 0xfa, 0x00}, /* Tune_7 */
	{0xfb, 0x00, 0xff, 0x00, 0xfb, 0x00}, /* Tune_8 */
	{0xfa, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_9 */
};

static char coordinate_data[][coordinate_data_size] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* dummy */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_1 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_2 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_3 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_4 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_5 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_6 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_7 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_8 */
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /* Tune_9 */
};

#else
#if defined(CONFIG_FB_MSM_MDSS_SAMSUNG_OCTA_VIDEO_720P_PT_PANEL) \
	|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
#define scr_wr_addr 36
#endif

#define F1(x,y) ((y)-((107*(x))/100)-60)
#define F2(x,y) ((y)-((44*(x))/43)-72)
#define F3(x,y) ((y)+((57*(x))/8)-25161)
#define F4(x,y) ((y)+((19*(x))/6)-12613)

static char coordinate_data[][coordinate_data_size] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* dummy */
	{0xff, 0x00, 0xf7, 0x00, 0xf8, 0x00}, /* Tune_1 */
	{0xff, 0x00, 0xf9, 0x00, 0xfe, 0x00}, /* Tune_2 */
	{0xfa, 0x00, 0xf8, 0x00, 0xff, 0x00}, /* Tune_3 */
	{0xff, 0x00, 0xfc, 0x00, 0xf9, 0x00}, /* Tune_4 */
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_5 */
	{0xf8, 0x00, 0xfa, 0x00, 0xff, 0x00}, /* Tune_6 */
	{0xfc, 0x00, 0xff, 0x00, 0xf8, 0x00}, /* Tune_7 */
	{0xfb, 0x00, 0xff, 0x00, 0xfb, 0x00}, /* Tune_8 */
	{0xf9, 0x00, 0xff, 0x00, 0xff, 0x00}, /* Tune_9 */
};
#endif

void coordinate_tunning(int x, int y)
{
	int tune_number;
#if defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)
	int i, j;
#endif
	tune_number = 0;

#if defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
	pr_info("%s : coordinate for %s panel\n", __func__, flip?"main":"sub");

	if (flip)
		memcpy(coordinate_data, coordinate_data_main, 60);
	else
		memcpy(coordinate_data, coordinate_data_sub, 60);
#endif

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

	pr_info("%s x : %d, y : %d, tune_number : %d", __func__, x, y, tune_number);
#if defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) || defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)
	for(i = 0; i < mDNIe_eBOOK_MODE; i++)
	{
		for(j = 0; j < AUTO_MODE; j++)
		{
			if(mdnie_tune_value[i][j][0][1] != NULL)
			{
				if((mdnie_tune_value[i][j][0][1][scr_wr_addr] == 0xff) && (mdnie_tune_value[i][j][0][1][scr_wr_addr+2] == 0xff) && (mdnie_tune_value[i][j][0][1][scr_wr_addr+4] == 0xff))
				{
					memcpy(&mdnie_tune_value[i][j][0][1][scr_wr_addr], &coordinate_data[tune_number][0], coordinate_data_size);
				}
			}
		}
	}
#else
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
#endif

}
#endif /* COORDINATE_DATA_NONE */

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
