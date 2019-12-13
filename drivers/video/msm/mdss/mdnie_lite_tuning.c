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

#define MDNIE_VERSION "Version: 1.3 (by Wootever)"
#include "mdnie_lite_tuning_data_hlte.h"
#define DPRINT(x...)
#define MAX_LUT_SIZE	256
static struct mipi_samsung_driver_data *mdnie_msd;

/*#define MDNIE_LITE_TUN_DATA_DEBUG*/

#define PAYLOAD1 mdni_tune_cmd[3]
#define PAYLOAD2 mdni_tune_cmd[2]

#define INPUT_PAYLOAD1(x) PAYLOAD1.payload = x
#define INPUT_PAYLOAD2(x) PAYLOAD2.payload = x

char CONTROL_1[] = {0xEB, 0x01, 0x00, 0x33, 0x01,};
char CONTROL_2[107];
int override = 0, copy_mode = 0, gamma_curve = 0;

int play_speed_1_5;

struct dsi_buf dsi_mdnie_tx_buf;

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
};

const
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
};

const char background_name[MAX_BACKGROUND_MODE][10] = {
	"DYNAMIC",
#ifndef	MDNIE_LITE_MODE
	"STANDARD",
	"NATURAL",
	"MOVIE",
	"AUTO",
#endif /* MDNIE_LITE_MODE */
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
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL)
	"SCREEN_CURTAIN_MODE",
#endif
#endif /* NEGATIVE_COLOR_USE_ACCESSIBILLITY */
};

static char level1_key[] = {
	0xF0,
	0x5A, 0x5A,
};

static char level2_key[] = {
	0xF0,
	0x5A, 0x5A,
};

static char tune_data1[MDNIE_TUNE_FIRST_SIZE] = {0,};
static char tune_data2[MDNIE_TUNE_SECOND_SIZE] = {0,};

static struct dsi_cmd_desc mdni_tune_cmd[] = {
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0,
		sizeof(level1_key)}, level1_key},
	{{DTYPE_DCS_LWRITE, 0, 0, 0, 0,
		sizeof(level2_key)}, level2_key},

	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(tune_data1)}, tune_data1},
	{{DTYPE_DCS_LWRITE, 1, 0, 0, 0,
		sizeof(tune_data2)}, tune_data2},
};

void update_mdnie_copy_mode(void)
{
	char *source;
	int i;

	if (copy_mode == 0) {
		source = STANDARD_UI_2;
		DPRINT("(mode: Standard)\n");
	}
	else if (copy_mode == 1) {
		source = NATURAL_UI_2;
		DPRINT("(mode: Natural)\n");
	}
	else if (copy_mode == 2) {
		source = MOVIE_UI_2;
		DPRINT("(mode: Movie)\n");
	}

	for (i = 0; i < 41; i++)
	CONTROL_2[i] = source[i];
}

void update_mdnie_gamma_curve(void)
{
	char *source;
	int i;

	if (gamma_curve == 0) {
		source = MOVIE_UI_2;
		DPRINT("(gamma: Movie)\n");
	}
	else if (gamma_curve == 1) {
		source = DYNAMIC_UI_2;
		DPRINT("(gamma: Dynamic)\n");
	}

	for (i = 42; i < 107; i++)
	CONTROL_2[i] = source[i];
}

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

void free_tun_cmd(void)
{
	memset(tune_data1, 0, MDNIE_TUNE_FIRST_SIZE);
	memset(tune_data2, 0, MDNIE_TUNE_SECOND_SIZE);
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

    if (override) {
	    DPRINT(" = CONTROL MODE =\n");
	    INPUT_PAYLOAD1(CONTROL_1);
	    INPUT_PAYLOAD2(CONTROL_2);
    } else
	if (mdnie_tun_state.accessibility) {
		DPRINT(" = ACCESSIBILITY MODE =\n");
		INPUT_PAYLOAD1(blind_tune_value[mdnie_tun_state.accessibility][0]);
		INPUT_PAYLOAD2(blind_tune_value[mdnie_tun_state.accessibility][1]);

	} else {
		if (!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0] ||
			!mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]) {
			pr_err("mdnie tune data is NULL!\n");
			return;
		} else {
			INPUT_PAYLOAD1(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][0]);
			INPUT_PAYLOAD2(
				mdnie_tune_value[mdnie_tun_state.scenario][mdnie_tun_state.background][mdnie_tun_state.outdoor][1]);
		}
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
 * #	1. Standard
 * #	2. Video
 * #	3. Natural
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
	if(mdnie_tun_state.background == value)
		return size;
	mdnie_tun_state.background = value;

	if (mdnie_tun_state.accessibility == NEGATIVE) {
		DPRINT("already negative mode(%d), do not set background(%d)\n",
			mdnie_tun_state.accessibility, mdnie_tun_state.background);
	} else {
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
	if(mdnie_tun_state.scenario == value)
		return size;
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
static DEVICE_ATTR(scenario, 0664, scenario_show,
		   scenario_store);

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
	if(mdnie_tun_state.outdoor == value)
		return size;
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
	if(mdnie_tun_state.accessibility == value)
		return size;
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
	mDNIe_Set_Mode();
}

static ssize_t playspeed_show(struct device *dev,
			struct device_attribute *attr,
			char *buf)
{
	return snprintf(buf, 256, "%d\n", play_speed_1_5);
}

static ssize_t playspeed_store(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t size)
{
	int value;
	sscanf(buf, "%d", &value);

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
		if(mdnie_tun_state.accessibility == NEGATIVE)
			return size;
		mdnie_tun_state.accessibility = NEGATIVE;
	}
#ifndef	NEGATIVE_COLOR_USE_ACCESSIBILLITY
	else if (cmd_value == COLOR_BLIND) {
		mdnie_tun_state.accessibility = COLOR_BLIND;
		memcpy(&COLOR_BLIND_2[MDNIE_COLOR_BLINDE_OFFSET],
				buffer, MDNIE_COLOR_BLINDE_CMD);
	}
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL)
	else if (cmd_value == SCREEN_CURTAIN) {
		if(mdnie_tun_state.accessibility == SCREEN_CURTAIN)
			return size;
		mdnie_tun_state.accessibility = SCREEN_CURTAIN;
	}
#endif
#endif /* NEGATIVE_COLOR_USE_ACCESSIBILLITY */
	else if (cmd_value == ACCESSIBILITY_OFF) {
		if(mdnie_tun_state.accessibility == ACCESSIBILITY_OFF)
			return size;
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

/* override */
static ssize_t override_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", override);
}

static ssize_t override_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int val;
	sscanf(buf, "%d", &val);

	if (val != override) {
		if (val < 0 || val > 1)
			return -EINVAL;
		DPRINT("(override: %d)\n", val);
		override = val;
		mDNIe_Set_Mode();
	}
    return size;
}

/* copy_mode */
static ssize_t copy_mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", copy_mode);
}

static ssize_t copy_mode_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
   int val;
	sscanf(buf, "%d", &val);

	if (val != copy_mode) {
		if (val < 0 || val > 2)
			return -EINVAL;
		copy_mode = val;
		update_mdnie_copy_mode();
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* gamma_curve */
static ssize_t gamma_curve_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", gamma_curve);
}

static ssize_t gamma_curve_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int val;
	sscanf(buf, "%d", &val);

	if (val != gamma_curve) {
		if (val < 0 || val > 1)
			return -EINVAL;
		gamma_curve = val;
		update_mdnie_gamma_curve();
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* sharpen */
static ssize_t sharpen_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", CONTROL_1[4]);
}

static ssize_t sharpen_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int val;
	sscanf(buf, "%d", &val);

	if (val != CONTROL_1[4]) {
		if (val < 0 || val > 11)
			return -EINVAL;
		DPRINT("(sharpen: %d)\n", val);
		CONTROL_1[4] = val;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* red */
static ssize_t red_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[19], CONTROL_2[21], CONTROL_2[23]);
}

static ssize_t red_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[19] || green != CONTROL_2[21] || blue != CONTROL_2[23]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[RED] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[19] = red;
		CONTROL_2[21] = green;
		CONTROL_2[23] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* green */
static ssize_t green_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[25], CONTROL_2[27], CONTROL_2[29]);
}

static ssize_t green_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[25] || green != CONTROL_2[27] || blue != CONTROL_2[29]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[GREEN] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[25] = red;
		CONTROL_2[27] = green;
		CONTROL_2[29] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* blue */
static ssize_t blue_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[31], CONTROL_2[33], CONTROL_2[35]);
}

static ssize_t blue_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[31] || green != CONTROL_2[33] || blue != CONTROL_2[35]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[BLUE] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[31] = red;
		CONTROL_2[33] = green;
		CONTROL_2[35] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* cyan */
static ssize_t cyan_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[18], CONTROL_2[20], CONTROL_2[22]);
}

static ssize_t cyan_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[18] || green != CONTROL_2[20] || blue != CONTROL_2[22]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[CYAN] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[18] = red;
		CONTROL_2[20] = green;
		CONTROL_2[22] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* magenta */
static ssize_t magenta_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[24], CONTROL_2[26], CONTROL_2[28]);
}

static ssize_t magenta_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[24] || green != CONTROL_2[26] || blue != CONTROL_2[28]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[MAGENTA] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[24] = red;
		CONTROL_2[26] = green;
		CONTROL_2[28] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* yellow */
static ssize_t yellow_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[30], CONTROL_2[32], CONTROL_2[34]);
}

static ssize_t yellow_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[30] || green != CONTROL_2[32] || blue != CONTROL_2[34]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[YELLOW] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[30] = red;
		CONTROL_2[32] = green;
		CONTROL_2[34] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* white */
static ssize_t white_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[36], CONTROL_2[38], CONTROL_2[40]);
}

static ssize_t white_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[36] || green != CONTROL_2[38] || blue != CONTROL_2[40]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[WHITE] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[36] = red;
		CONTROL_2[38] = green;
		CONTROL_2[40] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

/* black */
static ssize_t black_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d %d %d\n", CONTROL_2[37], CONTROL_2[39], CONTROL_2[41]);
}

static ssize_t black_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int red, green, blue;
	sscanf(buf, "%d %d %d", &red, &green, &blue);

	if (red != CONTROL_2[37] || green != CONTROL_2[39] || blue != CONTROL_2[41]) {
		if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
			return -EINVAL;
		DPRINT("[BLACK] (red: %d) (green: %d) (blue: %d)\n", red, green, blue);
		CONTROL_2[37] = red;
		CONTROL_2[39] = green;
		CONTROL_2[41] = blue;
		if (override)
			mDNIe_Set_Mode();
	}
    return size;
}

static ssize_t version_show(struct device *dev, struct device_attribute *attr, char *buf)
{
        return sprintf(buf, "%s\n", MDNIE_VERSION);
}

static DEVICE_ATTR(override, 0664, override_show, override_store);
static DEVICE_ATTR(copy_mode, 0664, copy_mode_show, copy_mode_store);
static DEVICE_ATTR(gamma_curve, 0664, gamma_curve_show, gamma_curve_store);
static DEVICE_ATTR(sharpen, 0664, sharpen_show, sharpen_store);
static DEVICE_ATTR(red, 0664, red_show, red_store);
static DEVICE_ATTR(green, 0664, green_show, green_store);
static DEVICE_ATTR(blue, 0664, blue_show, blue_store);
static DEVICE_ATTR(cyan, 0664, cyan_show, cyan_store);
static DEVICE_ATTR(magenta, 0664, magenta_show, magenta_store);
static DEVICE_ATTR(yellow, 0664, yellow_show, yellow_store);
static DEVICE_ATTR(white, 0664, white_show, white_store);
static DEVICE_ATTR(black, 0664, black_show, black_store);
static DEVICE_ATTR(version, 0444, version_show, NULL);

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

	device_create_file(tune_mdnie_dev, &dev_attr_override);
	device_create_file(tune_mdnie_dev, &dev_attr_copy_mode);
	device_create_file(tune_mdnie_dev, &dev_attr_gamma_curve);
	device_create_file(tune_mdnie_dev, &dev_attr_sharpen);
	device_create_file(tune_mdnie_dev, &dev_attr_red);
	device_create_file(tune_mdnie_dev, &dev_attr_green);
	device_create_file(tune_mdnie_dev, &dev_attr_blue);
	device_create_file(tune_mdnie_dev, &dev_attr_cyan);
	device_create_file(tune_mdnie_dev, &dev_attr_magenta);
	device_create_file(tune_mdnie_dev, &dev_attr_yellow);
	device_create_file(tune_mdnie_dev, &dev_attr_white);
	device_create_file(tune_mdnie_dev, &dev_attr_black);
	device_create_file(tune_mdnie_dev, &dev_attr_version);

	mdnie_tun_state.mdnie_enable = true;

	DPRINT("end!\n");

	update_mdnie_copy_mode();
	update_mdnie_gamma_curve();
}

void mdnie_lite_tuning_init(struct mipi_samsung_driver_data *msd)
{
	mdnie_msd = msd;
}

#ifndef COORDINATE_DATA_NONE
#define coordinate_data_size 6

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_FULL_HD_PT_PANEL)
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
#else
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
	tune_number = 0;

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
#endif /* COORDINATE_DATA_NONE */

