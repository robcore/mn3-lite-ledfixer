#!/bin/bash
#shopt -s globstar

QUICKMONTHDAY="$(date | awk '{print $2$3}')"
QUICKHOUR="$(date +%l | cut -d " " -f2)"
QUICKMIN="$(date +%S)"
QUICKAMPM="$(date +%p)"
QUICKTIME="$QUICKHOUR:$QUICKMIN${QUICKAMPM}"
QUICKDATE="$QUICKMONTHDAY-$QUICKTIME"
echo -n "$QUICKDATE" > "/root/mn3lite/tmpdate"
STATICDATE="$(cat /root/mn3lite/tmpdate)"
STATICLOG="/root/mn3lite/$STATICDATE-patchinator.log"

echo "PATCHINATOR LOG" > "$STATICLOG"
echo "---------------" >> "$STATICLOG"
echo " " >> "$STATICLOG"

for PFILE in /root/113patches/*
do
	patch -p1 --dry-run < "$PFILE"
	if [ $? -ne 0 ]
	then
		patch -p1 < "$PFILE" | tee -a "$STATICLOG"
	else
	    patch -s -p1 < "$PFILE" &> /dev/null
	fi
done

echo "Failed entries have been saved to:"
echo "$STATICLOG"
rm "/root/mn3lite/tmpdate"
