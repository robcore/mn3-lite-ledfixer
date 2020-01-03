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

warnandfail() {

	echo -n "ERROR on Line ${BASH_LINENO[0]}"
	echo "!!!"
	local ISTRING
	ISTRING="$1"
	if [ -n "$ISTRING" ]
	then
		echo "$ISTRING"
	fi
	exit 1

}

echo "PATCHINATOR LOG" > "$STATICLOG"
echo "---------------" >> "$STATICLOG"
echo >> "$STATICLOG"

realpatch() {

	if [ -z "$1" ]
	then
		warnandfail "Error! No patch file provided!"
	fi

	IFILE="$1"
	patch -p1 < "$IFILE"

}

for PFILE in /root/113patches/*.patch
do
	if ! patch --dry-run -p1 < "$PFILE" &> /dev/null
	then
		echo "$PFILE" >> "$STATICLOG"
		patch --dry-run -p1 < "$PFILE" >> "$STATICLOG"
		echo -e "\n" >> "$STATICLOG"
	fi
	realpatch "$PFILE" &> /dev/null
done

trashman &>/dev/null

echo "Failed entries have been saved to:"
echo "$STATICLOG"
rm "/root/mn3lite/tmpdate"
