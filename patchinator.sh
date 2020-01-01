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
	if patch -s -p1 --dry-run < "$PFILE"
	then
	    patch -s -p1 < "$PFILE" &> /dev/null
	else
		patch -p1 < "$PFILE" | tee -a "$STATICLOG"
	fi
done

find . -type f \( -iname \*.rej \
				-o -iname \*.orig \
				-o -iname \*.bkp \
				-o -iname \*.ko \) \
					| parallel rm -fv {};

echo "Failed entries have been saved to:"
echo "$STATICLOG"
rm "/root/mn3lite/tmpdate"
