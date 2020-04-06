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

#define ADDRESS_SCR_WHITE_RED 0x24  // 36 0x7A
#define ADDRESS_SCR_WHITE_GREEN 0x26 // 38 0x7C
#define ADDRESS_SCR_WHITE_BLUE 0x28 // 40 0x7E

/* Hijack */

static unsigned char LITE_CONTROL_1[5];
static unsigned char LITE_CONTROL_2[108];

static unsigned int hijack = 0;
static unsigned int black[3] = {0, 0, 0};
static unsigned int white[3] = {0, 0, 0};
static unsigned int red[3] = {0, 0, 0};
static unsigned int green[3] = {0, 0, 0};
static unsigned int blue[3] = {0, 0, 0};
static unsigned int yellow[3] = {0, 0, 0};
static unsigned int magenta[3] = {0, 0, 0};
static unsigned int cyan[3] = {0, 0, 0};

static unsigned int offset_mode = 1;
static int offset_black[3] = {0, 0, 0};
static int offset_white[3] = {0, 0, 0};
static int offset_red[3] = {0, 0, 0};
static int offset_green[3] = {0, 0, 0};
static int offset_blue[3] = {0, 0, 0};
static int offset_yellow[3] = {0, 0, 0};
static int offset_magenta[3] = {0, 0, 0};
static int offset_cyan[3] = {0, 0, 0};

static unsigned int sharpen_dark = 0;
static unsigned int sharpen_light = 0;
static unsigned int chroma = 0;
static unsigned int gamma = 0;
static int sharpen_light_bit = 3;
static int sharpen_dark_bit = 2;
static int chroma_bit = 1;
static int gamma_bit = 0;

static unsigned char custom_curve[48];
static unsigned char chroma_correction[18];
/* Hijack Extra End  */

//static unsigned int previous_mode;
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
	.background = NATURAL_MODE,
	.outdoor = OUTDOOR_OFF_MODE,
	.accessibility = ACCESSIBILITY_OFF,
	.scr_white_red = 0xff,
	.scr_white_green = 0xff,
	.scr_white_blue = 0xff,
};

const char scenario_name[MAX_mDNIe_MODE][16] = {
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
	"OUTDOOR_ON_MODE",
};

const char accessibility_name[ACCESSIBILITY_MAX][20] = {
	"ACCESSIBILITY_OFF",
	"NEGATIVE_MODE",
	"COLOR_BLIND_MODE",
	"SCREEN_CURTAIN_MODE",
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

static char level1_key_disable[] = {
	0xF0,
	0xA5, 0xA5,
};
#if defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL)
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

static char white_rgb_buf[MDNIE_TUNE_FIRST_SIZE] = {0,};

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
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0,
		sizeof(level1_key)}, level1_key},
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0,
		sizeof(level2_key)}, level2_key},

	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(tune_data1)}, tune_data1},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(tune_data2)}, tune_data2},


	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(level1_key_disable)}, level1_key_disable},

#endif
};

void print_tun_data(void)
{
	int i;

	DPRINT("\n");
	DPRINT("---- size1 : %d", PAYLOAD1.dchdr.dlen);
	for (i = 0; i < (MDNIE_TUNE_SECOND_SIZE - 1); i++)
		DPRINT("0x%x ", PAYLOAD1.payload[i]);
	DPRINT("\n");
	DPRINT("---- size2 : %d", PAYLOAD2.dchdr.dlen);
	for (i = 0; i < (MDNIE_TUNE_FIRST_SIZE - 1); i++)
		DPRINT("0x%x ", PAYLOAD2.payload[i]);
	DPRINT("\n");
}

void free_tun_cmd(void)
{
	memset(tune_data1, 0, MDNIE_TUNE_FIRST_SIZE);
	memset(tune_data2, 0, MDNIE_TUNE_SECOND_SIZE);
}

void sending_tuning_cmd(void)
{
	struct msm_fb_data_type *mfd;
	struct mdss_dsi_ctrl_pdata *ctrl_pdata;

	if (mdnie_msd == NULL)
		return;

	ctrl_pdata = mdnie_msd->ctrl_pdata;
	if (ctrl_pdata == NULL)
		return;

	mfd = mdnie_msd->mfd;
	if (mfd == NULL)
		return;

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

static int sanitize_offset(int Lnewval, int Loldval)
{
	int newval = Lnewval;
	int oldval = Loldval;
	int outset = 0;

	clamp_val(newval, 0, 255);
	clamp_val(oldval, 0, 255);
	if (newval == oldval) {
		return outset;
	} else if (newval > oldval) {
		outset = newval - oldval;
	} else if (newval < oldval) {
		outset = oldval - newval;
		outset *= -1;
	}
	return outset;
}

static void update_mdnie_mode(void)
{
	unsigned char *source_1, *source_2;
	int result;
	unsigned int i, new_control;

	switch (mdnie_tun_state.scenario) {
	case mDNIe_UI_MODE:
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
			return;
		}
		break;
	case mDNIe_VIDEO_MODE:
		if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
			source_1 = OUTDOOR_VIDEO_1;
			source_2 = OUTDOOR_VIDEO_2;
		} else {
			switch (mdnie_tun_state.background) {
			case DYNAMIC_MODE:
				source_1 = DYNAMIC_VIDEO_1;
				source_2 = DYNAMIC_VIDEO_2;
				break;
			case STANDARD_MODE:
				source_1 = STANDARD_VIDEO_1;
				source_2 = STANDARD_VIDEO_2;
				break;
			case NATURAL_MODE:
				source_1 = NATURAL_VIDEO_1;
				source_2 = NATURAL_VIDEO_2;
				break;
			case MOVIE_MODE:
				source_1 = MOVIE_VIDEO_1;
				source_2 = MOVIE_VIDEO_2;
				break;
			case AUTO_MODE:
				source_1 = AUTO_VIDEO_1;
				source_2 = AUTO_VIDEO_2;
				break;
			default:
				return;
			}
		}
		break;
	case mDNIe_VIDEO_WARM_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
		case STANDARD_MODE:
		case NATURAL_MODE:
		case MOVIE_MODE:
		case AUTO_MODE:
			if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
				source_1 = WARM_OUTDOOR_1;
				source_2 = WARM_OUTDOOR_2;
			} else {
				source_1 = WARM_1;
				source_2 = WARM_2;
			}
			break;
		default:
			return;
		}
		break;
	case mDNIe_VIDEO_COLD_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
		case STANDARD_MODE:
		case NATURAL_MODE:
		case MOVIE_MODE:
		case AUTO_MODE:
			if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
				source_1 = COLD_OUTDOOR_1;
				source_2 = COLD_OUTDOOR_2;
			} else {
				source_1 = COLD_1;
				source_2 = COLD_2;
			}
			break;
		default:
			return;
		}
		break;
	case mDNIe_CAMERA_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
		case STANDARD_MODE:
		case NATURAL_MODE:
		case MOVIE_MODE:
			if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
				source_1 = CAMERA_OUTDOOR_1;
				source_2 = CAMERA_OUTDOOR_2;
			} else {
				source_1 = CAMERA_1;
				source_2 = CAMERA_2;
			}
			break;
		case AUTO_MODE:
			if (mdnie_tun_state.outdoor == OUTDOOR_ON_MODE) {
				source_1 = CAMERA_OUTDOOR_1;
				source_2 = CAMERA_OUTDOOR_2;
			} else {
				source_1 = AUTO_CAMERA_1;
				source_2 = AUTO_CAMERA_2;
			}
			break;
		default:
			return;
		}
		break;
	case mDNIe_NAVI:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
			source_1 = DYNAMIC_BROWSER_1;
			source_2 = DYNAMIC_BROWSER_2;
			break;
		case STANDARD_MODE:
			source_1 = STANDARD_BROWSER_1;
			source_2 = STANDARD_BROWSER_2;
			break;
		case NATURAL_MODE:
			source_1 = NATURAL_BROWSER_1;
			source_2 = NATURAL_BROWSER_2;
			break;
		case MOVIE_MODE:
			source_1 = MOVIE_BROWSER_1;
			source_2 = MOVIE_BROWSER_2;
			break;
		case AUTO_MODE:
			source_1 = AUTO_BROWSER_1;
			source_2 = AUTO_BROWSER_2;
			break;
		default:
			return;
		}
		break;
	case mDNIe_GALLERY:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
			source_1 = DYNAMIC_GALLERY_1;
			source_2 = DYNAMIC_GALLERY_2;
			break;
		case STANDARD_MODE:
			source_1 = STANDARD_GALLERY_1;
			source_2 = STANDARD_GALLERY_2;
			break;
		case NATURAL_MODE:
			source_1 = NATURAL_GALLERY_1;
			source_2 = NATURAL_GALLERY_2;
			break;
		case MOVIE_MODE:
			source_1 = MOVIE_GALLERY_1;
			source_2 = MOVIE_GALLERY_2;
			break;
		case AUTO_MODE:
			source_1 = AUTO_GALLERY_1;
			source_2 = AUTO_GALLERY_2;
			break;
		default:
			return;
		}
		break;
	case mDNIe_VT_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
			source_1 = DYNAMIC_VT_1;
			source_2 = DYNAMIC_VT_2;
			break;
		case STANDARD_MODE:
			source_1 = STANDARD_VT_1;
			source_2 = STANDARD_VT_2;
			break;
		case NATURAL_MODE:
			source_1 = NATURAL_VT_1;
			source_2 = NATURAL_VT_2;
			break;
		case MOVIE_MODE:
			source_1 = MOVIE_VT_1;
			source_2 = MOVIE_VT_2;
			break;
		case AUTO_MODE:
			source_1 = AUTO_VT_1;
			source_2 = AUTO_VT_2;
			break;
		default:
			return;
		}
		break;
	case mDNIe_BROWSER_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
			source_1 = DYNAMIC_BROWSER_1;
			source_2 = DYNAMIC_BROWSER_2;
			break;
		case STANDARD_MODE:
			source_1 = STANDARD_BROWSER_1;
			source_2 = STANDARD_BROWSER_2;
			break;
		case NATURAL_MODE:
			source_1 = NATURAL_BROWSER_1;
			source_2 = NATURAL_BROWSER_2;
			break;
		case MOVIE_MODE:
			source_1 = MOVIE_BROWSER_1;
			source_2 = MOVIE_BROWSER_2;
			break;
		case AUTO_MODE:
			source_1 = AUTO_BROWSER_1;
			source_2 = AUTO_BROWSER_2;
			break;
		default:
			return;
		}
		break;
	case mDNIe_eBOOK_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
			source_1 = DYNAMIC_EBOOK_1;
			source_2 = DYNAMIC_EBOOK_2;
			break;
		case STANDARD_MODE:
			source_1 = STANDARD_EBOOK_1;
			source_2 = STANDARD_EBOOK_2;
			break;
		case NATURAL_MODE:
			source_1 = NATURAL_EBOOK_1;
			source_2 = NATURAL_EBOOK_2;
			break;
		case MOVIE_MODE:
			source_1 = MOVIE_EBOOK_1;
			source_2 = MOVIE_EBOOK_2;
			break;
		case AUTO_MODE:
			source_1 = AUTO_EBOOK_1;
			source_2 = AUTO_EBOOK_2;
			break;
		default:
			return;
		}
		break;
	case mDNIe_EMAIL_MODE:
		switch (mdnie_tun_state.background) {
		case DYNAMIC_MODE:
		case STANDARD_MODE:
		case NATURAL_MODE:
		case MOVIE_MODE:
		case AUTO_MODE:
			source_1 = AUTO_EMAIL_1;
			source_2 = AUTO_EMAIL_2;
			break;
		default:
			return;
		}
	default:
		return;
	}

	for (i = 0; i < 4 ; i++)
		LITE_CONTROL_1[i] = source_1[i];

	for (i = 0; i < 107 ; i++)
		LITE_CONTROL_2[i] = source_2[i];

	if (hijack) {

		for (i = 0; i < 47; i++)
			LITE_CONTROL_2[i + 42] = custom_curve[i];

		for (i = 0; i < 17; i++)
			LITE_CONTROL_2[i + 90] = chroma_correction[i];

		result = (LITE_CONTROL_1[4] >> (sharpen_dark_bit));
		if (sharpen_dark) {
			if (!(result & 1))
				LITE_CONTROL_1[4] |= 1 << sharpen_dark_bit;
		} else {
			if (result & 1)
				LITE_CONTROL_1[4] &= ~(1 << sharpen_dark_bit);
		}

		result = (LITE_CONTROL_1[4] >> (sharpen_light_bit));
		if (sharpen_light) {
			if (!(result & 1))
				LITE_CONTROL_1[4] |= 1 << sharpen_light_bit;
		} else {
			if (result & 1)
				LITE_CONTROL_1[4] &= ~(1 << sharpen_light_bit);
		}

		result = (LITE_CONTROL_1[4] >> (chroma_bit));
		if (chroma) {
			if (!(result & 1))
				LITE_CONTROL_1[4] |= 1 << chroma_bit;
		} else {
			if (result & 1)
				LITE_CONTROL_1[4] &= ~(1 << chroma_bit);
		}

		result = (LITE_CONTROL_1[4] >> (gamma_bit));
		if (gamma) {
			if (!(result & 1))
				LITE_CONTROL_1[4] |= 1 << gamma_bit;
		} else {
			if (result & 1)
				LITE_CONTROL_1[4] &= ~(1 << gamma_bit);
		}

		if (offset_mode) {
			new_control = LITE_CONTROL_2[18];
			new_control += offset_cyan[0];
			clamp_val(new_control, 0, 255);
			offset_cyan[0] = sanitize_offset(new_control, LITE_CONTROL_2[18]);

			new_control = LITE_CONTROL_2[19];
			new_control += offset_red[0];
			clamp_val(new_control, 0, 255);
			offset_red[0] = sanitize_offset(new_control, LITE_CONTROL_2[19]);

			new_control = LITE_CONTROL_2[20];
			new_control += offset_cyan[1];
			clamp_val(new_control, 0, 255);
			offset_cyan[1] = sanitize_offset(new_control, LITE_CONTROL_2[20]);

			new_control = LITE_CONTROL_2[21];
			new_control += offset_red[1];
			clamp_val(new_control, 0, 255);
			offset_red[1] = sanitize_offset(new_control, LITE_CONTROL_2[21]);

			new_control = LITE_CONTROL_2[22];
			new_control += offset_cyan[2];
			clamp_val(new_control, 0, 255);
			offset_cyan[2] = sanitize_offset(new_control, LITE_CONTROL_2[22]);

			new_control = LITE_CONTROL_2[23];
			new_control += offset_red[2];
			clamp_val(new_control, 0, 255);
			offset_red[2] = sanitize_offset(new_control, LITE_CONTROL_2[23]);

			new_control = LITE_CONTROL_2[24];
			new_control += offset_magenta[0];
			clamp_val(new_control, 0, 255);
			offset_magenta[0] = sanitize_offset(new_control, LITE_CONTROL_2[24]);

			new_control = LITE_CONTROL_2[25];
			new_control += offset_green[0];
			clamp_val(new_control, 0, 255);
			offset_green[0] = sanitize_offset(new_control, LITE_CONTROL_2[25]);

			new_control = LITE_CONTROL_2[26];
			new_control += offset_magenta[1];
			clamp_val(new_control, 0, 255);
			offset_magenta[1] = sanitize_offset(new_control, LITE_CONTROL_2[26]);

			new_control = LITE_CONTROL_2[27];
			new_control += offset_green[1];
			clamp_val(new_control, 0, 255);
			offset_green[1] = sanitize_offset(new_control, LITE_CONTROL_2[27]);

			new_control = LITE_CONTROL_2[28];
			new_control += offset_magenta[2];
			clamp_val(new_control, 0, 255);
			offset_magenta[2] = sanitize_offset(new_control, LITE_CONTROL_2[28]);

			new_control = LITE_CONTROL_2[29];
			new_control += offset_green[2];
			clamp_val(new_control, 0, 255);
			offset_green[2] = sanitize_offset(new_control, LITE_CONTROL_2[29]);

			new_control = LITE_CONTROL_2[30];
			new_control += offset_yellow[0];
			clamp_val(new_control, 0, 255);
			offset_yellow[0] = sanitize_offset(new_control, LITE_CONTROL_2[30]);

			new_control = LITE_CONTROL_2[31];
			new_control += offset_blue[0];
			clamp_val(new_control, 0, 255);
			offset_blue[0] = sanitize_offset(new_control, LITE_CONTROL_2[31]);

			new_control = LITE_CONTROL_2[32];
			new_control += offset_yellow[1];
			clamp_val(new_control, 0, 255);
			offset_yellow[1] = sanitize_offset(new_control, LITE_CONTROL_2[32]);

			new_control = LITE_CONTROL_2[33];
			new_control += offset_blue[1];
			clamp_val(new_control, 0, 255);
			offset_blue[1] = sanitize_offset(new_control, LITE_CONTROL_2[33]);

			new_control = LITE_CONTROL_2[34];
			new_control += offset_yellow[2];
			clamp_val(new_control, 0, 255);
			offset_yellow[2] = sanitize_offset(new_control, LITE_CONTROL_2[34]);

			new_control = LITE_CONTROL_2[35];
			new_control += offset_blue[2];
			clamp_val(new_control, 0, 255);
			offset_blue[2] = sanitize_offset(new_control, LITE_CONTROL_2[35]);

			new_control = LITE_CONTROL_2[36];
			new_control += offset_white[0];
			clamp_val(new_control, 0, 255);
			offset_white[0] = sanitize_offset(new_control, LITE_CONTROL_2[36]);

			new_control = LITE_CONTROL_2[37];
			new_control += offset_black[0];
			clamp_val(new_control, 0, 255);
			offset_black[0] = sanitize_offset(new_control, LITE_CONTROL_2[37]);

			new_control = LITE_CONTROL_2[38];
			new_control += offset_white[1];
			clamp_val(new_control, 0, 255);
			offset_white[1] = sanitize_offset(new_control, LITE_CONTROL_2[38]);

			new_control = LITE_CONTROL_2[39];
			new_control += offset_black[1];
			clamp_val(new_control, 0, 255);
			offset_black[1] = sanitize_offset(new_control, LITE_CONTROL_2[39]);

			new_control = LITE_CONTROL_2[40];
			new_control += offset_white[2];
			clamp_val(new_control, 0, 255);
			offset_white[2] = sanitize_offset(new_control, LITE_CONTROL_2[40]);

			new_control = LITE_CONTROL_2[41];
			new_control += offset_black[2];
			clamp_val(new_control, 0, 255);
			offset_black[2] = sanitize_offset(new_control, LITE_CONTROL_2[41]);

			LITE_CONTROL_2[18] += offset_cyan[0];
			LITE_CONTROL_2[19] += offset_red[0];
			LITE_CONTROL_2[20] += offset_cyan[1];
			LITE_CONTROL_2[21] += offset_red[1];
			LITE_CONTROL_2[22] += offset_cyan[2];
			LITE_CONTROL_2[23] += offset_red[2];
			LITE_CONTROL_2[24] += offset_magenta[0];
			LITE_CONTROL_2[25] += offset_green[0];
			LITE_CONTROL_2[26] += offset_magenta[1];
			LITE_CONTROL_2[27] += offset_green[1];
			LITE_CONTROL_2[28] += offset_magenta[2];
			LITE_CONTROL_2[29] += offset_green[2];
			LITE_CONTROL_2[30] += offset_yellow[0];
			LITE_CONTROL_2[31] += offset_blue[0];
			LITE_CONTROL_2[32] += offset_yellow[1];
			LITE_CONTROL_2[33] += offset_blue[1];
			LITE_CONTROL_2[34] += offset_yellow[2];
			LITE_CONTROL_2[35] += offset_blue[2];
			LITE_CONTROL_2[36] += offset_white[0];
			LITE_CONTROL_2[37] += offset_black[0];
			LITE_CONTROL_2[38] += offset_white[1];
			LITE_CONTROL_2[39] += offset_black[1];
			LITE_CONTROL_2[40] += offset_white[2];
			LITE_CONTROL_2[41] += offset_black[2];

			cyan[0] = LITE_CONTROL_2[18];
			red[0] = LITE_CONTROL_2[19];
			cyan[1] = LITE_CONTROL_2[20];
			red[1] = LITE_CONTROL_2[21];
			cyan[2] = LITE_CONTROL_2[22];
			red[2] = LITE_CONTROL_2[23];
			magenta[0] = LITE_CONTROL_2[24];
			green[0] = LITE_CONTROL_2[25];
			magenta[1] = LITE_CONTROL_2[26];
			green[1] = LITE_CONTROL_2[27];
			magenta[2] = LITE_CONTROL_2[28];
			green[2] = LITE_CONTROL_2[29];
			yellow[0] = LITE_CONTROL_2[30];
			blue[0] = LITE_CONTROL_2[31];
			yellow[1] = LITE_CONTROL_2[32];
			blue[1] = LITE_CONTROL_2[33];
			yellow[2] = LITE_CONTROL_2[34];
			blue[2] = LITE_CONTROL_2[35];
			white[0] = LITE_CONTROL_2[36];
			black[0] = LITE_CONTROL_2[37];
			white[1] = LITE_CONTROL_2[38];
			black[1] = LITE_CONTROL_2[39];
			white[2] = LITE_CONTROL_2[40];
			black[2] = LITE_CONTROL_2[41];
		} else {
			LITE_CONTROL_2[18] = cyan[0];
			LITE_CONTROL_2[19] = red[0];
			LITE_CONTROL_2[20] = cyan[1];
			LITE_CONTROL_2[21] = red[1];
			LITE_CONTROL_2[22] = cyan[2];
			LITE_CONTROL_2[23] = red[2];
			LITE_CONTROL_2[24] = magenta[0];
			LITE_CONTROL_2[25] = green[0];
			LITE_CONTROL_2[26] = magenta[1];
			LITE_CONTROL_2[27] = green[1];
			LITE_CONTROL_2[28] = magenta[2];
			LITE_CONTROL_2[29] = green[2];
			LITE_CONTROL_2[30] = yellow[0];
			LITE_CONTROL_2[31] = blue[0];
			LITE_CONTROL_2[32] = yellow[1];
			LITE_CONTROL_2[33] = blue[1];
			LITE_CONTROL_2[34] = yellow[2];
			LITE_CONTROL_2[35] = blue[2];
			LITE_CONTROL_2[36] = white[0];
			LITE_CONTROL_2[37] = black[0];
			LITE_CONTROL_2[38] = white[1];
			LITE_CONTROL_2[39] = black[1];
			LITE_CONTROL_2[40] = white[2];
			LITE_CONTROL_2[41] = black[2];
		}
	} else {

		for (i = 0; i < 47; i++)
			custom_curve[i] = LITE_CONTROL_2[i + 42];
		for (i = 0; i < 17; i++)
			chroma_correction[i] = LITE_CONTROL_2[i + 90];

		LITE_CONTROL_1[4] = source_1[4];

		result = (LITE_CONTROL_1[4] >> (sharpen_dark_bit));
		sharpen_dark = result & 1;

		result = (LITE_CONTROL_1[4] >> (sharpen_light_bit));
		sharpen_light = result & 1;

		result = (LITE_CONTROL_1[4] >> (chroma_bit));
		chroma = result & 1;

		result = (LITE_CONTROL_1[4] >> (gamma_bit));
		gamma = result & 1;

		cyan[0] = LITE_CONTROL_2[18];
		red[0] = LITE_CONTROL_2[19];
		cyan[1] = LITE_CONTROL_2[20];
		red[1] = LITE_CONTROL_2[21];
		cyan[2] = LITE_CONTROL_2[22];
		red[2] = LITE_CONTROL_2[23];
		magenta[0] = LITE_CONTROL_2[24];
		green[0] = LITE_CONTROL_2[25];
		magenta[1] = LITE_CONTROL_2[26];
		green[1] = LITE_CONTROL_2[27];
		magenta[2] = LITE_CONTROL_2[28];
		green[2] = LITE_CONTROL_2[29];
		yellow[0] = LITE_CONTROL_2[30];
		blue[0] = LITE_CONTROL_2[31];
		yellow[1] = LITE_CONTROL_2[32];
		blue[1] = LITE_CONTROL_2[33];
		yellow[2] = LITE_CONTROL_2[34];
		blue[2] = LITE_CONTROL_2[35];
		white[0] = LITE_CONTROL_2[36];
		black[0] = LITE_CONTROL_2[37];
		white[1] = LITE_CONTROL_2[38];
		black[1] = LITE_CONTROL_2[39];
		white[2] = LITE_CONTROL_2[40];
		black[2] = LITE_CONTROL_2[41];
	}
}

/*
 * mDnie priority
 * Accessibility > HBM > Screen Mode
 */
void mDNIe_Set_Mode(void)
{
	struct msm_fb_data_type *mfd;
	if (mdnie_msd == NULL)
		return;

	mfd = mdnie_msd->mfd;

/*	DPRINT("mDNIe_Set_Mode start\n");*/

	if (mfd == NULL) {
		DPRINT("[ERROR] mfd is null!\n");
		return;
	}

	if ((mfd->blank_mode) || (mfd->resume_state == MIPI_SUSPEND_STATE))
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
		INPUT_PAYLOAD1(
			mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
		INPUT_PAYLOAD2(
			mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
			mdnie_tun_state.scr_white_red = mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1][ADDRESS_SCR_WHITE_RED];
			mdnie_tun_state.scr_white_green = mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1][ADDRESS_SCR_WHITE_GREEN];
			mdnie_tun_state.scr_white_blue= mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1][ADDRESS_SCR_WHITE_BLUE];

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

	//previous_mode = mdnie_tun_state.background;

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

	if (value <= mDNIe_UI_MODE)
		value = mDNIe_UI_MODE;
	if (value >= mDNIe_EMAIL_MODE)
		value = mDNIe_EMAIL_MODE;

	backup = mdnie_tun_state.scenario;
	mdnie_tun_state.scenario = value;

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

	if (value < OUTDOOR_OFF_MODE)
		value = OUTDOOR_OFF_MODE;
	if (value >= OUTDOOR_ON_MODE)
		value = OUTDOOR_ON_MODE;

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
		memcpy(&COLOR_BLIND_2[MDNIE_COLOR_BLINDE_OFFSET],
				buffer, MDNIE_COLOR_BLINDE_CMD);
		}
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
			memcpy(white_rgb_buf, mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1], MDNIE_TUNE_FIRST_SIZE);

		white_rgb_buf[ADDRESS_SCR_WHITE_RED] = white_red;
		white_rgb_buf[ADDRESS_SCR_WHITE_GREEN] = white_green;
		white_rgb_buf[ADDRESS_SCR_WHITE_BLUE] = white_blue;

		INPUT_PAYLOAD2(white_rgb_buf);
		sending_tuning_cmd();
		free_tun_cmd();
	}

	return size;
}

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
static DEVICE_ATTR(sensorRGB, 0664, sensorRGB_show, sensorRGB_store);

static struct class *mdnie_class;
struct device *tune_mdnie_dev;

/* hijack */
static ssize_t hijack_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", hijack);
}

static ssize_t hijack_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	if (new_val < 0)
		new_val = 0;
	if (new_val > 1)
		new_val = 1;
	hijack = new_val;
	mDNIe_Set_Mode();
	return count;
}

/* LITE_CONTROL_1[4] */
static ssize_t effect_mask_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "Decimal:%u\nHex:0x%x\n", LITE_CONTROL_1[4], LITE_CONTROL_1[4]);
}

/* offset_mode */

static ssize_t offset_mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", offset_mode);
}

static ssize_t offset_mode_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	if (new_val < 0)
		new_val = 0;
	if (new_val > 1)
		new_val = 1;
	offset_mode = new_val;
	mDNIe_Set_Mode();
	return count;
}

/* sharpen_dark */

static ssize_t sharpen_dark_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", sharpen_dark);
}

static ssize_t sharpen_dark_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	if (new_val < 0)
		new_val = 0;
	if (new_val > 1)
		new_val = 1;
	sharpen_dark = new_val;
	mDNIe_Set_Mode();
	return count;
}


/* sharpen_light */

static ssize_t sharpen_light_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", sharpen_light);
}

static ssize_t sharpen_light_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	if (new_val < 0)
		new_val = 0;
	if (new_val > 1)
		new_val = 1;
	sharpen_light = new_val;
	mDNIe_Set_Mode();
	return count;
}

static ssize_t chroma_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", chroma);
}

static ssize_t chroma_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	if (new_val < 0)
		new_val = 0;
	if (new_val > 1)
		new_val = 1;
	chroma = new_val;
	mDNIe_Set_Mode();
	return count;
}

static ssize_t gamma_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", gamma);
}

static ssize_t gamma_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val;
	sscanf(buf, "%d", &new_val);
	if (new_val < 0)
		new_val = 0;
	if (new_val > 1)
		new_val = 1;
	gamma = new_val;
	mDNIe_Set_Mode();
	return count;
}

/* Custom Curve */

#define show_one_curve(_name, bval, aval)			\
static ssize_t _name##_show					\
(struct kobject *kobj, struct kobj_attribute *attr, char *buf)	\
{								\
	return sprintf(buf, "%u %u\n", custom_curve[bval], custom_curve[aval]);			\
}

#define store_one_curve(_name, bval, aval)		\
static ssize_t _name##_store		\
(struct kobject *kobj,				\
 struct kobj_attribute *attr,			\
 const char *buf, size_t count)			\
{						\
	int i, curve_b, curve_a;			\
	if (sscanf(buf, "%d %d", &curve_b, &curve_a) == 2) {				\
		clamp_val(custom_curve[bval], 0, 255);		\
		clamp_val(custom_curve[aval], 0, 255);		\
		custom_curve[bval] = curve_b;		\
		custom_curve[aval] = curve_a;		\
	} else {		\
		return count;		\
	}						\
	mDNIe_Set_Mode();		\
	return count;			\
}

show_one_curve(gcurve1, 0, 1);
show_one_curve(gcurve2, 2, 3);
show_one_curve(gcurve3, 4, 5);
show_one_curve(gcurve4, 6, 7);
show_one_curve(gcurve5, 8, 9);
show_one_curve(gcurve6, 10, 11);
show_one_curve(gcurve7, 12, 13);
show_one_curve(gcurve8, 14, 15);
show_one_curve(gcurve9, 16, 17);
show_one_curve(gcurve10, 18, 19);
show_one_curve(gcurve11, 20, 21);
show_one_curve(gcurve12, 22, 23);
show_one_curve(gcurve13, 24, 25);
show_one_curve(gcurve14, 26, 27);
show_one_curve(gcurve15, 28, 29);
show_one_curve(gcurve16, 30, 31);
show_one_curve(gcurve17, 32, 33);
show_one_curve(gcurve18, 34, 35);
show_one_curve(gcurve19, 36, 37);
show_one_curve(gcurve20, 38, 39);
show_one_curve(gcurve21, 40, 41);
show_one_curve(gcurve22, 42, 43);
show_one_curve(gcurve23, 44, 45);
show_one_curve(gcurve24, 46, 47);

store_one_curve(gcurve1, 0, 1);
store_one_curve(gcurve2, 2, 3);
store_one_curve(gcurve3, 4, 5);
store_one_curve(gcurve4, 6, 7);
store_one_curve(gcurve5, 8, 9);
store_one_curve(gcurve6, 10, 11);
store_one_curve(gcurve7, 12, 13);
store_one_curve(gcurve8, 14, 15);
store_one_curve(gcurve9, 16, 17);
store_one_curve(gcurve10, 18, 19);
store_one_curve(gcurve11, 20, 21);
store_one_curve(gcurve12, 22, 23);
store_one_curve(gcurve13, 24, 25);
store_one_curve(gcurve14, 26, 27);
store_one_curve(gcurve15, 28, 29);
store_one_curve(gcurve16, 30, 31);
store_one_curve(gcurve17, 32, 33);
store_one_curve(gcurve18, 34, 35);
store_one_curve(gcurve19, 36, 37);
store_one_curve(gcurve20, 38, 39);
store_one_curve(gcurve21, 40, 41);
store_one_curve(gcurve22, 42, 43);
store_one_curve(gcurve23, 44, 45);
store_one_curve(gcurve24, 46, 47);

#define show_one_cc(_name, firstval, secondval)			\
static ssize_t _name##_show					\
(struct kobject *kobj, struct kobj_attribute *attr, char *buf)	\
{								\
	return sprintf(buf, "%u %u\n", chroma_correction[firstval], chroma_correction[secondval]);			\
}

#define store_one_cc(_name, firstval, secondval)		\
static ssize_t _name##_store		\
(struct kobject *kobj,				\
 struct kobj_attribute *attr,			\
 const char *buf, size_t count)			\
{						\
	int i, cc_highlow, cc_strength;			\
	if (sscanf(buf, "%d %d", &cc_highlow, &cc_strength) == 2) {				\
		if ((cc_highlow != 4) && (cc_highlow != 31))	\
			chroma_correction[firstval] = LITE_CONTROL_2[firstval + 90];		\
		else	\
			chroma_correction[firstval] = cc_highlow;		\
		clamp_val(chroma_correction[secondval], 0, 255);		\
		chroma_correction[secondval] = cc_strength;		\
	} else {		\
		return count;		\
	}						\
	mDNIe_Set_Mode();		\
	return count;			\
}

show_one_cc(cc_r1, 0, 1);
show_one_cc(cc_r2, 2, 3);
show_one_cc(cc_r3, 4, 5);
show_one_cc(cc_g1, 6, 7);
show_one_cc(cc_g2, 8, 9);
show_one_cc(cc_g3, 10, 11);
show_one_cc(cc_b1, 12, 13);
show_one_cc(cc_b2, 14, 15);
show_one_cc(cc_b3, 16, 17);

store_one_cc(cc_r1, 0, 1);
store_one_cc(cc_r2, 2, 3);
store_one_cc(cc_r3, 4, 5);
store_one_cc(cc_g1, 6, 7);
store_one_cc(cc_g2, 8, 9);
store_one_cc(cc_g3, 10, 11);
store_one_cc(cc_b1, 12, 13);
store_one_cc(cc_b2, 14, 15);
store_one_cc(cc_b3, 16, 17);

/* black */

static ssize_t black_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", black[0], black[1], black[2]);
}

static ssize_t black_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		black[0] = NEWRED;
		black[1] = NEWGREEN;
		black[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		black[0] = new_val;
		black[1] = new_val;
		black[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* white */

static ssize_t white_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", white[0], white[1], white[2]);
}

static ssize_t white_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		white[0] = NEWRED;
		white[1] = NEWGREEN;
		white[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		white[0] = new_val;
		white[1] = new_val;
		white[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* red */

static ssize_t red_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", red[0], red[1], red[2]);
}

static ssize_t red_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		red[0] = NEWRED;
		red[1] = NEWGREEN;
		red[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		red[0] = new_val;
		red[1] = 0;
		red[2] = 0;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* green */

static ssize_t green_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", green[0], green[1], green[2]);
}

static ssize_t green_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		green[0] = NEWRED;
		green[1] = NEWGREEN;
		green[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		green[0] = 0;
		green[1] = new_val;
		green[2] = 0;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* blue */

static ssize_t blue_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", blue[0], blue[1], blue[2]);
}

static ssize_t blue_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		blue[0] = NEWRED;
		blue[1] = NEWGREEN;
		blue[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		blue[0] = 0;
		blue[1] = 0;
		blue[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* yellow */
static ssize_t yellow_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", yellow[0], yellow[1], yellow[2]);
}

static ssize_t yellow_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		yellow[0] = NEWRED;
		yellow[1] = NEWGREEN;
		yellow[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		yellow[0] = new_val;
		yellow[1] = new_val;
		yellow[2] = 0;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* magenta */
static ssize_t magenta_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", magenta[0], magenta[1], magenta[2]);
}

static ssize_t magenta_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		magenta[0] = NEWRED;
		magenta[1] = NEWGREEN;
		magenta[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		magenta[0] = new_val;
		magenta[1] = 0;
		magenta[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* cyan */
static ssize_t cyan_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u %u %u\n", cyan[0], cyan[1], cyan[2]);
}

static ssize_t cyan_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int i, new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, 0, 255);
		clamp_val(NEWGREEN, 0, 255);
		clamp_val(NEWBLUE, 0, 255);
		cyan[0] = NEWRED;
		cyan[1] = NEWGREEN;
		cyan[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, 0, 255);
		cyan[0] = 0;
		cyan[1] = new_val;
		cyan[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_black */

static ssize_t offset_black_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_black[0], offset_black[1], offset_black[2]);
}

static ssize_t offset_black_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_black[0] = NEWRED;
		offset_black[1] = NEWGREEN;
		offset_black[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_black[0] = new_val;
		offset_black[1] = new_val;
		offset_black[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_white */

static ssize_t offset_white_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_white[0], offset_white[1], offset_white[2]);
}

static ssize_t offset_white_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_white[0] = NEWRED;
		offset_white[1] = NEWGREEN;
		offset_white[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_white[0] = new_val;
		offset_white[1] = new_val;
		offset_white[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_red */

static ssize_t offset_red_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_red[0], offset_red[1], offset_red[2]);
}

static ssize_t offset_red_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_red[0] = NEWRED;
		offset_red[1] = NEWGREEN;
		offset_red[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_red[0] = new_val;
		offset_red[1] = 0;
		offset_red[2] = 0;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_green */

static ssize_t offset_green_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_green[0], offset_green[1], offset_green[2]);
}

static ssize_t offset_green_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_green[0] = NEWRED;
		offset_green[1] = NEWGREEN;
		offset_green[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_green[0] = 0;
		offset_green[1] = new_val;
		offset_green[2] = 0;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_blue */

static ssize_t offset_blue_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_blue[0], offset_blue[1], offset_blue[2]);
}

static ssize_t offset_blue_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_blue[0] = NEWRED;
		offset_blue[1] = NEWGREEN;
		offset_blue[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_blue[0] = 0;
		offset_blue[1] = 0;
		offset_blue[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_yellow */
static ssize_t offset_yellow_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_yellow[0], offset_yellow[1], offset_yellow[2]);
}

static ssize_t offset_yellow_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_yellow[0] = NEWRED;
		offset_yellow[1] = NEWGREEN;
		offset_yellow[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_yellow[0] = new_val;
		offset_yellow[1] = new_val;
		offset_yellow[2] = 0;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_magenta */
static ssize_t offset_magenta_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_magenta[0], offset_magenta[1], offset_magenta[2]);
}

static ssize_t offset_magenta_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_magenta[0] = NEWRED;
		offset_magenta[1] = NEWGREEN;
		offset_magenta[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_magenta[0] = new_val;
		offset_magenta[1] = 0;
		offset_magenta[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}

/* offset_cyan */
static ssize_t offset_cyan_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", offset_cyan[0], offset_cyan[1], offset_cyan[2]);
}

static ssize_t offset_cyan_store(struct kobject *kobj,
			   struct kobj_attribute *attr, const char *buf, size_t count)
{
	int new_val, NEWRED, NEWGREEN, NEWBLUE;

	if (sscanf(buf, "%d %d %d", &NEWRED, &NEWGREEN, &NEWBLUE) == 3) {
		clamp_val(NEWRED, -255, 255);
		clamp_val(NEWGREEN, -255, 255);
		clamp_val(NEWBLUE, -255, 255);
		offset_cyan[0] = NEWRED;
		offset_cyan[1] = NEWGREEN;
		offset_cyan[2] = NEWBLUE;
	} else if (sscanf(buf, "%d", &new_val) == 1) {
		clamp_val(new_val, -255, 255);
		offset_cyan[0] = 0;
		offset_cyan[1] = new_val;
		offset_cyan[2] = new_val;
	} else {
		return count;
	}

	mDNIe_Set_Mode();

	return count;
}
MX_ATTR_RW(hijack);
MX_ATTR_RW(offset_mode);
MX_ATTR_RO(effect_mask);
MX_ATTR_RW(sharpen_dark);
MX_ATTR_RW(sharpen_light);
MX_ATTR_RW(chroma);
MX_ATTR_RW(gamma);

static struct attribute *mdnie_control_attrs[] = {
	&hijack_attr.attr,
	&offset_mode_attr.attr,
	&effect_mask_attr.attr,
	&sharpen_dark_attr.attr,
	&sharpen_light_attr.attr,
	&chroma_attr.attr,
	&gamma_attr.attr,
	NULL,
};

static struct attribute_group mdnie_control_attr_group = {
	.attrs = mdnie_control_attrs,
};

MX_ATTR_RW(black);
MX_ATTR_RW(white);
MX_ATTR_RW(red);
MX_ATTR_RW(green);
MX_ATTR_RW(blue);
MX_ATTR_RW(cyan);
MX_ATTR_RW(magenta);
MX_ATTR_RW(yellow);

static struct attribute *override_attrs[] = {
	&black_attr.attr,
	&white_attr.attr,
	&red_attr.attr,
	&green_attr.attr,
	&blue_attr.attr,
	&cyan_attr.attr,
	&magenta_attr.attr,
	&yellow_attr.attr,
	NULL,
};

static struct attribute_group override_attr_group = {
	.attrs = override_attrs,
};

MX_ATTR_RW(offset_black);
MX_ATTR_RW(offset_white);
MX_ATTR_RW(offset_red);
MX_ATTR_RW(offset_green);
MX_ATTR_RW(offset_blue);
MX_ATTR_RW(offset_cyan);
MX_ATTR_RW(offset_magenta);
MX_ATTR_RW(offset_yellow);

static struct attribute *offset_attrs[] = {
	&offset_black_attr.attr,
	&offset_white_attr.attr,
	&offset_red_attr.attr,
	&offset_green_attr.attr,
	&offset_blue_attr.attr,
	&offset_cyan_attr.attr,
	&offset_magenta_attr.attr,
	&offset_yellow_attr.attr,
	NULL,
};

static struct attribute_group offset_attr_group = {
	.attrs = offset_attrs,
};

MX_ATTR_RW(gcurve1);
MX_ATTR_RW(gcurve2);
MX_ATTR_RW(gcurve3);
MX_ATTR_RW(gcurve4);
MX_ATTR_RW(gcurve5);
MX_ATTR_RW(gcurve6);
MX_ATTR_RW(gcurve7);
MX_ATTR_RW(gcurve8);
MX_ATTR_RW(gcurve9);
MX_ATTR_RW(gcurve10);
MX_ATTR_RW(gcurve11);
MX_ATTR_RW(gcurve12);
MX_ATTR_RW(gcurve13);
MX_ATTR_RW(gcurve14);
MX_ATTR_RW(gcurve15);
MX_ATTR_RW(gcurve16);
MX_ATTR_RW(gcurve17);
MX_ATTR_RW(gcurve18);
MX_ATTR_RW(gcurve19);
MX_ATTR_RW(gcurve20);
MX_ATTR_RW(gcurve21);
MX_ATTR_RW(gcurve22);
MX_ATTR_RW(gcurve23);
MX_ATTR_RW(gcurve24);

static struct attribute *gcurve_attrs[] = {
	&gcurve1_attr.attr,
	&gcurve2_attr.attr,
	&gcurve3_attr.attr,
	&gcurve4_attr.attr,
	&gcurve5_attr.attr,
	&gcurve6_attr.attr,
	&gcurve7_attr.attr,
	&gcurve8_attr.attr,
	&gcurve9_attr.attr,
	&gcurve10_attr.attr,
	&gcurve11_attr.attr,
	&gcurve12_attr.attr,
	&gcurve13_attr.attr,
	&gcurve14_attr.attr,
	&gcurve15_attr.attr,
	&gcurve16_attr.attr,
	&gcurve17_attr.attr,
	&gcurve18_attr.attr,
	&gcurve19_attr.attr,
	&gcurve20_attr.attr,
	&gcurve21_attr.attr,
	&gcurve22_attr.attr,
	&gcurve23_attr.attr,
	&gcurve24_attr.attr,
	NULL,
};

static struct attribute_group gcurve_attr_group = {
	.attrs = gcurve_attrs,
};

MX_ATTR_RW(cc_r1);
MX_ATTR_RW(cc_r2);
MX_ATTR_RW(cc_r3);
MX_ATTR_RW(cc_g1);
MX_ATTR_RW(cc_g2);
MX_ATTR_RW(cc_g3);
MX_ATTR_RW(cc_b1);
MX_ATTR_RW(cc_b2);
MX_ATTR_RW(cc_b3);

static struct attribute *cc_attrs[] = {
	&cc_r1_attr.attr,
	&cc_r2_attr.attr,
	&cc_r3_attr.attr,
	&cc_g1_attr.attr,
	&cc_g2_attr.attr,
	&cc_g3_attr.attr,
	&cc_b1_attr.attr,
	&cc_b2_attr.attr,
	&cc_b3_attr.attr,
	NULL,
};

static struct attribute_group cc_attr_group = {
	.attrs = cc_attrs,
};

static struct kobject *mdnie_control_kobj;
static struct kobject *override_kobj;
static struct kobject *offset_kobj;
static struct kobject *gcurve_kobj;
static struct kobject *cc_kobj;

static bool msd_initialized = false;
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

	if (device_create_file
		(tune_mdnie_dev, &dev_attr_sensorRGB) < 0)
		pr_err("Failed to create device file(%s)!=n",
			dev_attr_sensorRGB.attr.name);

	mdnie_control_kobj = kobject_create_and_add("mdnie_control", kernel_kobj);
	if (sysfs_create_group(mdnie_control_kobj, &mdnie_control_attr_group)) {
		pr_err("Failed to create mdnie_control kobject!\n");
		goto mdniefail;
	}

	override_kobj = kobject_create_and_add("override", mdnie_control_kobj);
	if (sysfs_create_group(override_kobj, &override_attr_group)) {
		pr_err("Failed to create override kobject!\n");
		goto overridefail;
	}

	offset_kobj = kobject_create_and_add("offset", mdnie_control_kobj);
	if (sysfs_create_group(offset_kobj, &offset_attr_group)) {
		pr_err("Failed to create offset kobject!\n");
		goto offsetfail;
	}

	gcurve_kobj = kobject_create_and_add("gcurve", mdnie_control_kobj);
	if (sysfs_create_group(gcurve_kobj, &gcurve_attr_group)) {
		pr_err("Failed to create gcurve kobject!\n");
		goto gcurvefail;
	}

	cc_kobj = kobject_create_and_add("cc", mdnie_control_kobj);
	if (sysfs_create_group(cc_kobj, &cc_attr_group)) {
		pr_err("Failed to create cc kobject!\n");
		goto ccfail;
	}

	goto success;

ccfail:
	kobject_put(cc_kobj);
	cc_kobj = NULL;
	sysfs_remove_group(gcurve_kobj, &offset_attr_group);

gcurvefail:
	kobject_put(gcurve_kobj);
	gcurve_kobj = NULL;
	sysfs_remove_group(offset_kobj, &offset_attr_group);

offsetfail:
	kobject_put(offset_kobj);
	offset_kobj = NULL;
	sysfs_remove_group(override_kobj, &override_attr_group);

overridefail:
	kobject_put(override_kobj);
	override_kobj = NULL;
	sysfs_remove_group(mdnie_control_kobj, &mdnie_control_attr_group);

mdniefail:
	kobject_put(mdnie_control_kobj);
	mdnie_control_kobj = NULL;

success:
	mdnie_tun_state.mdnie_enable = true;
	if (msd_initialized)
		mDNIe_Set_Mode();
}

void mdnie_lite_tuning_init(struct mipi_samsung_driver_data *msd)
{
	mdnie_msd = msd;
	msd_initialized = true;
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

#if 0
void coordinate_tunning(int x, int y)
{
	return;
}
#endif

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
