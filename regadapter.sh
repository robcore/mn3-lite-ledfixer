#!/bin/bash

[ -f "/root/mn3lite/regsysfs.c" ] && rm "/root/mn3lite/regsysfs.c"

MXDIR="/root/mn3lite"
CFILE="$MXDIR/regsysfs.c"
RAWFILE="$MXDIR/reglist_raw"

echo 'static ssize_t allregs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)' >> "$CFILE"
echo '{' >> "$CFILE"
echo '	return sprintf(buf,' >> "$CFILE"

while ifs= read -r REGLINE
do
	echo -n '				   "' >> "$CFILE"
	echo -n "$REGLINE" >> "$CFILE"
	if [ "$REGLINE" = "TAIKO_A_CDC_PA_RAMP_B4_CTL" ]
	then
		echo -n ': reg %d value %d\n"' >> "$CFILE"
		echo ',' >> "$CFILE"
	else
		echo ': reg %d value %d\n"' >> "$CFILE"
	fi
	
done < "$RAWFILE"

while ifs= read -r VALLINE
do
	echo -n "				   $VALLINE" >> "$CFILE"
	echo -n ', ' >> "$CFILE"
	echo -n '(int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, ' >> "$CFILE"
	echo -n "$VALLINE" >> "$CFILE"
	if [ "$VALLINE" = "TAIKO_A_CDC_PA_RAMP_B4_CTL" ]
	then
		echo ");" >> "$CFILE"
		echo '}' >> "$CFILE"
	else
		echo '),' >> "$CFILE"
	fi

done < "$RAWFILE"
