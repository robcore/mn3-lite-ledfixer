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

trashman() {

	find . -type f \( -iname \*.rej \
					-o -iname \*.orig \
					-o -iname \*.bkp \
					-o -iname \*.ko \) \
						| parallel rm -fv {};

}

echo "PATCHINATOR LOG" > "$STATICLOG"
echo "---------------" >> "$STATICLOG"
echo >> "$STATICLOG"

for PFILE in /root/113patches/*
do
	patch --dry-run -p1 < "$PFILE" > /dev/null 2>&1
	if [ $? -eq 0 ]
	then
	    patch -s -p1 < "$PFILE" > /dev/null 2>&1
	else
		echo "$PFILE" >> "$STATICLOG"
		patch -p1 < "$PFILE" >> "$STATICLOG"
		echo " " >> "$STATICLOG"
	fi
done

trashman &>/dev/null

echo "Failed entries have been saved to:"
echo "$STATICLOG"
rm "/root/mn3lite/tmpdate"
