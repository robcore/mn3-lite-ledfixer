#!/bin/bash

printusage() {

	echo "Usage:"
	echo "$0 /path/to/example.patch"
}

if [ $# -ne 1 ]
then
	printusage
	exit 1
fi

if [ -z "$1" ] || [ ! -f "$1" ]
then
	printusage
	exit 1
fi

BIGPATCHNAME="$1"
PATCHFOLDER="$(dirname "$BIGPATCHNAME")"
PATCHCOUNT=$(grep -c "diff --git " "$BIGPATCHNAME")
FINALPATCHFORM=$(printf "%04d\n" "$PATCHCOUNT")
FINALPATCHFILE="$PATCHFOLDER/$FINALPATCHFORM.patch"
rm "$PATCHFOLDER/currentpval" &> /dev/null
echo -n '0' > "$PATCHFOLDER/currentpval"
echo "Splitting into $PATCHCOUNT patches"

dothesplits() {
	local CHECKLINE
	CHECKLINE="diff --git ";
	while IFS= read -r PLINE
	do
		local SPLITFILENUM
		local SPLITFILEFORM
		local SPLITFILE
		local CURRENTPVALFILE
		local CURRENTPVAL
		CURRENTPVALFILE="$PATCHFOLDER/currentpval"
		CURRENTPVAL="$(cat "$CURRENTPVALFILE")"
		SPLITLINE="$(echo "$PLINE" | cut --bytes=1-11)"
		if [ "$SPLITLINE" = "$CHECKLINE" ]
		then
			SPLITFILENUM=$((CURRENTPVAL+1))
			echo -n "$SPLITFILENUM" > "$CURRENTPVALFILE"
			SPLITFILEFORM="$(printf "%04d\n" $SPLITFILENUM)"
			SPLITFILE="$PATCHFOLDER/$SPLITFILEFORM.patch"
			echo -ne "                                            \r"; \
			echo -ne "Creating patch $SPLITFILE out of $PATCHCOUNT\r"; \
		else
			SPLITFILENUM="$CURRENTPVAL"
			SPLITFILEFORM=$(printf "%04d\n" "$SPLITFILENUM")
			SPLITFILE="$PATCHFOLDER/$SPLITFILEFORM.patch"
		fi
		if [ "$SPLITFILE" = "$FINALPATCHFILE" ] && [ "$PLINE" = "-- " ]
		then
			break;
		else
			echo "$PLINE" >> "$SPLITFILE"
		fi
	done < "$BIGPATCHNAME"

}

dothesplits
echo -ne "                                            \r"; \
echo
echo
FINALPVALPATH="$PATCHFOLDER/currentpval"
FINALPVAL="$(cat "$FINALPVALPATH")"
SHORTPATCHNAME="$(basename "$BIGPATCHNAME")"
echo "Succesful Split!"
echo "$SHORTPATCHNAME split into $FINALPVAL patch files!"
echo "Doing some cleanup..."
echo "Removing $SHORTPATCHNAME"
rm "$BIGPATCHNAME" &>/dev/null
echo "Removing currentpval"
rm "$FINALPVALPATH" &>/dev/null
echo "Finished!"
