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

#ifndef _MDNIE_LITE_TUNING_H_
#define _MDNIE_LITE_TUNING_H_

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL)
#include "mdss_samsung_dsi_panel.h"
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)|| defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL)
#include "mdss_samsung_oled_cmd_hd_wqhd_panel.h"
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_TFT_VIDEO_WQXGA_PT_PANEL)
#include "mdss_samsung_tft_video_dual_dsi_panel.h"
#elif defined(CONFIG_FB_MSM_MIPI_JDI_TFT_VIDEO_FULL_HD_PT_PANEL) // JACTIVE
#include "mdss_jdi_dsi_panel.h"
#elif defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
#include "mdss_magna_octa_video_wxga_dual_panel.h"
#elif defined(CONFIG_FB_MSM_MDSS_MDP3) // MDP3
#include "dsi_v2.h"
#elif defined(CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
//do nothing
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)
#include "mdss_samsung_dual_oled_cmd_wqxga_s6e3ha1_panel.h"
#else
#include "mdss_samsung_dsi_panel.h"
#endif

#define LDI_COORDINATE_REG 0xA1

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)
#define MDNIE_TUNE_FIRST_SIZE 128
#define MDNIE_TUNE_SECOND_SIZE 22
/*temp*/
#define MDNIE_COLOR_BLIND_FIRST_SIZE 128
#define MDNIE_COLOR_BLIND_SECOND_SIZE 22
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL)  // H
#define MDNIE_TUNE_FIRST_SIZE 108
#define MDNIE_TUNE_SECOND_SIZE 5
#define MDNIE_COLOR_BLIND_FIRST_SIZE 118
#define MDNIE_COLOR_BLIND_SECOND_SIZE 5
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_FULL_HD_PT_PANEL) // KS01
#define MDNIE_TUNE_FIRST_SIZE 108
#define MDNIE_TUNE_SECOND_SIZE 5
#define MDNIE_COLOR_BLIND_FIRST_SIZE 118
#define MDNIE_COLOR_BLIND_SECOND_SIZE 5
#elif defined(CONFIG_FB_MSM_MIPI_JDI_TFT_VIDEO_FULL_HD_PT_PANEL) // Jactive
#define MDNIE_TUNE_FIRST_SIZE 108
#define MDNIE_TUNE_SECOND_SIZE 5
#define MDNIE_COLOR_BLIND_FIRST_SIZE 118
#define MDNIE_COLOR_BLIND_SECOND_SIZE 5
#define COORDINATE_DATA_NONE
#elif defined(CONFIG_FB_MSM_MIPI_SAMSUNG_YOUM_CMD_FULL_HD_PT_PANEL) // F
#define MDNIE_TUNE_FIRST_SIZE 108
#define MDNIE_TUNE_SECOND_SIZE 5
#elif defined(CONFIG_FB_MSM_MDSS_SAMSUNG_OCTA_VIDEO_720P_PT_PANEL) //FRESCO_KOR
#define MDNIE_TUNE_FIRST_SIZE 108
#define MDNIE_TUNE_SECOND_SIZE 5
#define MDNIE_COLOR_BLIND_FIRST_SIZE 118
#define MDNIE_COLOR_BLIND_SECOND_SIZE 5
#elif defined(CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL)|| \
		defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
#define MDNIE_TUNE_FIRST_SIZE 92
#define MDNIE_TUNE_SECOND_SIZE 5
#define MDNIE_COLOR_BLIND_FIRST_SIZE 92
#define MDNIE_COLOR_BLIND_SECOND_SIZE 5
#elif defined(CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
#define MDNIE_TUNE_FIRST_SIZE 92
#define MDNIE_TUNE_SECOND_SIZE 5
#define MDNIE_COLOR_BLIND_FIRST_SIZE 118
#define MDNIE_COLOR_BLIND_SECOND_SIZE 5
#elif defined(CONFIG_FB_MSM_MIPI_VIDEO_WVGA_NT35502_PT_PANEL) // KANAS
#define MDNIE_TUNE_FIRST_SIZE 17
#define MDNIE_TUNE_SECOND_SIZE 25
#define MDNIE_TUNE_THIRD_SIZE 49
#define MDNIE_TUNE_FOURTH_SIZE 19
#define MDNIE_TUNE_FIFTH_SIZE 5
#endif

#define MDNIE_COLOR_BLINDE_CMD 18

/* blind setting value offset (ascr_Cr ~ ascr_Bb) */
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_CMD_HD_PT_PANEL) || \
	defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6E3HA1_PT_PANEL)
#define MDNIE_COLOR_BLINDE_OFFSET 104
#else
#define MDNIE_COLOR_BLINDE_OFFSET 18
#endif

#define SIG_MDNIE_UI_MODE				0
#define SIG_MDNIE_VIDEO_MODE			1
#define SIG_MDNIE_VIDEO_WARM_MODE		2
#define SIG_MDNIE_VIDEO_COLD_MODE		3
#define SIG_MDNIE_CAMERA_MODE			4
#define SIG_MDNIE_NAVI					5
#define SIG_MDNIE_GALLERY				6
#define SIG_MDNIE_VT					7
#define SIG_MDNIE_BROWSER				8
#define SIG_MDNIE_eBOOK					9
#define SIG_MDNIE_EMAIL					10

#define SIG_MDNIE_DYNAMIC				0
#define SIG_MDNIE_STANDARD				1
#define SIG_MDNIE_MOVIE				2

#if defined(CONFIG_TDMB)
#define SIG_MDNIE_DMB_MODE			20
#define SIG_MDNIE_DMB_WARM_MODE	21
#define SIG_MDNIE_DMB_COLD_MODE	22
#endif

#define SIG_MDNIE_ISDBT_MODE		30
#define SIG_MDNIE_ISDBT_WARM_MODE	31
#define SIG_MDNIE_ISDBT_COLD_MODE	32

enum SCENARIO {
	mDNIe_UI_MODE = 0,
	mDNIe_VIDEO_MODE = 1,
	mDNIe_VIDEO_WARM_MODE = 2,
	mDNIe_VIDEO_COLD_MODE = 3,
	mDNIe_CAMERA_MODE = 4,
	mDNIe_NAVI = 5,
	mDNIe_GALLERY = 6,
	mDNIe_VT_MODE = 7,
	mDNIe_BROWSER_MODE = 8,
	mDNIe_eBOOK_MODE = 9,
	mDNIe_EMAIL_MODE = 10,
	MAX_mDNIe_MODE = 11,
};

enum BACKGROUND {
	DYNAMIC_MODE = 0,
	STANDARD_MODE = 1,
	NATURAL_MODE = 2,
	MOVIE_MODE = 3,
	AUTO_MODE = 4,
	MAX_BACKGROUND_MODE = 5,
};

enum OUTDOOR {
	OUTDOOR_OFF_MODE = 0,
	OUTDOOR_ON_MODE = 1,
	MAX_OUTDOOR_MODE = 2,
};

enum ACCESSIBILITY {
    ACCESSIBILITY_OFF = 0,
	NEGATIVE = 1,
	COLOR_BLIND = 2,
	SCREEN_CURTAIN = 3,
	ACCESSIBILITY_MAX = 4,
};

#if defined(CONFIG_TDMB)
enum DMB {
	DMB_MODE_OFF = -1,
	DMB_MODE,
	DMB_WARM_MODE,
	DMB_COLD_MODE,
	MAX_DMB_MODE,
};
#endif

struct mdnie_lite_tun_type {
	bool mdnie_enable;
	enum SCENARIO scenario;
	enum BACKGROUND background;
	enum OUTDOOR outdoor;
	enum ACCESSIBILITY accessibility;
//	int scr_white_red;
//	int scr_white_green;
//	int scr_white_blue;
};

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
void mdnie_lite_tuning_init(struct mdss_dsi_driver_data *msd);
#else
void mdnie_lite_tuning_init(struct mipi_samsung_driver_data *msd);
#endif

void init_mdnie_class(void);
void is_negative_on(void);
void coordinate_tunning(int x, int y);
void mDNIe_Set_Mode(void);

#endif /*_MDNIE_LITE_TUNING_H_*/
