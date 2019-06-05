/*
 * WCD93xx Sound Engine
 *
 * Copyright (C) 2013, Paul Reioux
 * Copyright (C) 2016, The Linux Foundation. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/bitops.h>
#include <linux/kallsyms.h>
#include <linux/export.h>
#include <linux/mfd/wcd9xxx/core.h>
#include <linux/mfd/wcd9xxx/wcd9320_registers.h>
#include "wcd9320.h"

#define SOUND_CONTROL_MAJOR_VERSION	6
#define SOUND_CONTROL_MINOR_VERSION	0

#define taiko_err() pr_err("%s: failed to write to taiko driver\n", __func__)

extern struct snd_soc_codec *snd_engine_codec_ptr;
static unsigned int cached_regs[3];

unsigned int snd_ctrl_enabled = 0;
unsigned int snd_ctrl_locked = 1;
extern unsigned int taiko_read(struct snd_soc_codec *codec, unsigned int reg);
extern int taiko_write(struct snd_soc_codec *codec, unsigned int reg,
		unsigned int value);

static unsigned int simpleclamp(int val)
{
	unsigned int clampedval;
	if (val <= 0)
		val = 0;
	if (val >= 1)
		val = 1;
	clampedval = val;
	return clampedval;
}

static unsigned int *cache_select(unsigned int reg)
{
	unsigned int *out = NULL;

	switch (reg) {
		case TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL:
			out = &cached_regs[0];
			break;
		case TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL:
			out = &cached_regs[1];
			break;
		case TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL:
			out = &cached_regs[2];
			break;
		default:
			break;
	}

	return out;
}

void snd_cache_write(unsigned int reg, unsigned int value)
{
	unsigned int *tmp = cache_select(reg);

	if (tmp != NULL)
		*tmp = value;
}
EXPORT_SYMBOL(snd_cache_write);

int snd_cache_read(unsigned int reg)
{
	if (cache_select(reg) != NULL)
		return *cache_select(reg);
	else
		return -1;
}
EXPORT_SYMBOL(snd_cache_read);

int snd_reg_access(unsigned int reg)
{
	int ret = 1;

	if (!snd_ctrl_locked)
		return ret;

	switch (reg) {
		/* Digital Headphones/Speaker Gain */
		case TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL:
		case TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL:
		case TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL:
			ret = 0;
			break;
		default:
			break;
	}

	return ret;
}
EXPORT_SYMBOL(snd_reg_access);

static int show_sound_value(int val)
{
	if (val > 50)
	val -= 256;

	return taiko_read(snd_engine_codec_ptr, val);
}

static int human_readable(unsigned int regval)
{
 return show_sound_value(taiko_read(snd_engine_codec_ptr, regval));
}

static ssize_t sound_control_enabled_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", snd_ctrl_enabled);
}

static ssize_t sound_control_enabled_store(struct kobject *kobj,
        struct kobj_attribute *attr, const char *buf, size_t count)
{
    unsigned int val;

    sscanf(buf, "%u", &val);
	snd_ctrl_enabled = simpleclamp(val);

    return count;
}

static ssize_t speaker_gain_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", human_readable(TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL));
}

static ssize_t speaker_gain_store(struct kobject *kobj,
		struct kobj_attribute *attr, const char *buf, size_t count)
{
	int val, addval, checksum;

	sscanf(buf, "%d", &val);

	if (!snd_ctrl_enabled)
		return count;

/*	addval = val + val;
	checksum = 255 - addval;
	if (checksum > 255) {
		checksum -=256;
		val += 256;
	} */
	if (255 - (val + val) > 255)
		val += 256;
	snd_ctrl_locked = 0;
	taiko_write(snd_engine_codec_ptr, TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL, val);
	taiko_write(snd_engine_codec_ptr, TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL, val);
	snd_ctrl_locked = 1;
	return count;
}

static ssize_t headphone_gain_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", human_readable(TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL));
}

static ssize_t headphone_gain_store(struct kobject *kobj,
		struct kobj_attribute *attr, const char *buf, size_t count)
{
	int val, addval, checksum;

	sscanf(buf, "%d", &val);

	if (!snd_ctrl_enabled)
		return count;

	addval = val + val;
	checksum = 255 - addval;
	if (checksum > 255) {
		checksum -=256;
		val += 256;
	}
	snd_ctrl_locked = 0;
	taiko_write(snd_engine_codec_ptr, TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL, val);
	taiko_write(snd_engine_codec_ptr, TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL, val);
	snd_ctrl_locked = 1;
	return checksum;
}

static ssize_t sound_control_version_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "Sound Control Engine: %u.%u\n",
			SOUND_CONTROL_MAJOR_VERSION,
			SOUND_CONTROL_MINOR_VERSION);
}

static struct kobj_attribute sound_control_enabled_attribute =
	__ATTR(gpl_sound_control_enabled,
		0664,
		sound_control_enabled_show,
		sound_control_enabled_store);

static struct kobj_attribute headphone_gain_attribute =
	__ATTR(gpl_headphone_gain,
		0664,
		headphone_gain_show,
		headphone_gain_store);

static struct kobj_attribute speaker_gain_attribute =
	__ATTR(gpl_speaker_gain,
		0664,
		speaker_gain_show,
		speaker_gain_store);

static struct kobj_attribute sound_control_version_attribute =
	__ATTR(gpl_sound_control_version,
		0444,
		sound_control_version_show, NULL);

static struct attribute *sound_control_attrs[] =
{
	&sound_control_enabled_attribute.attr,
	&headphone_gain_attribute.attr,
	&speaker_gain_attribute.attr,
	&sound_control_version_attribute.attr,
	NULL,
};

static const struct attribute_group sound_control_attr_group =
{
	.attrs = sound_control_attrs,
};

static struct kobject *sound_control_kobj;

static int sound_control_init(void)
{
	sound_control_kobj =
		kobject_create_and_add("sound_control_3", kernel_kobj);

	if (!sound_control_kobj) {
		pr_err("%s sound_control_kobj create failed!\n",
			__FUNCTION__);
		return -ENOSYS;
	}

	if (sysfs_create_group(sound_control_kobj, &sound_control_attr_group)) {
		pr_err("%s sysfs create failed!\n", __FUNCTION__);
		kobject_put(sound_control_kobj);
		return -ENOMEM;
	}

	pr_info("Sound Control Engine: %u.%u Initialized!\n",
			SOUND_CONTROL_MAJOR_VERSION,
			SOUND_CONTROL_MINOR_VERSION);

	return 0;
}

late_initcall_sync(sound_control_init);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Paul Reioux <reioux@gmail.com>");
MODULE_AUTHOR("Rob Patershuk <robpatershuk@gmail.com>");
MODULE_DESCRIPTION("WCD93xx Sound Engine v5.x");
