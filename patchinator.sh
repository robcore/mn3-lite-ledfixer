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
echo "---------------" | tee -a "$STATICLOG"
echo | tee -a "$STATICLOG"

for PFILE in /root/113patches/*
do
	patch --dry-run -p1 < "$PFILE" > /dev/null 2>&1
	if [ $? -eq 0 ]
	then
	    patch --dry-run -p1 < "$PFILE" > /dev/null 2>&1
	else
		echo | tee -a "$STATICLOG"
		echo "$PFILE" | tee -a "$STATICLOG"
		patch --dry-run -p1 < "$PFILE" | tee -a "$STATICLOG"
	fi
done

trashman &>/dev/null

echo "Failed entries have been saved to:"
echo "$STATICLOG"
rm "/root/mn3lite/tmpdate"
