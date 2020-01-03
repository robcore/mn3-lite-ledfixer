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
PATCHFOLDER="$(dirname $BIGPATCHNAME)"

rm "$PATCHFOLDER/currentpval" &> /dev/null
echo -n '0' > "$PATCHFOLDER/currentpval"

dothesplits() {

	while read -r PLINE
	do
		local SPLITFILENUM
		local SPLITFILEFORM
		local SPLITFILE
		local CURRENTPVALFILE
		local CURRENTPVAL
		CURRENTPVALFILE="$PATCHFOLDER/currentpval"
		CURRENTPVAL="$(cat $CURRENTPVALFILE)"
		if echo "$PLINE" | grep -q 'diff --git'
		then
			if [ "$CURRENTPVAL" -gt 0 ]
			then
				PREVIOUSFILEFORM=$(printf "%04d\n" $CURRENTPVAL)
				PREVIOUSFILE="$PATCHFOLDER/$PREVIOUSFILEFORM.patch"
				truncate -s -1 "$PREVIOUSFILE"
			fi
			SPLITFILENUM=$((CURRENTPVAL+1))
			echo -n "$SPLITFILENUM" > "$CURRENTPVALFILE"
		elif echo "$PLINE" | grep -q 'THISISTHEENDFAKEFAKEFAKEFAKE'
		then
			PREVIOUSFILEFORM=$(printf "%04d\n" $CURRENTPVAL)
			PREVIOUSFILE="$PATCHFOLDER/$PREVIOUSFILEFORM.patch"
			truncate -s -1 "$PREVIOUSFILE"
			echo -ne "                   \r"; \
			echo "Finished!"; \
			break
		else
			SPLITFILENUM="$CURRENTPVAL"
		fi
		SPLITFILEFORM=$(printf "%04d\n" $SPLITFILENUM)
		SPLITFILE="$PATCHFOLDER/$SPLITFILEFORM.patch"
		echo -ne "                   \r"; \
		echo -ne "Creating $SPLITFILE\r"; \
		echo "$PLINE" >> "$SPLITFILE"
	done < "$BIGPATCHNAME"

}

dothesplits

FINALPVALFILE="$PATCHFOLDER/currentpval"
FINALPVAL="$(cat $CURRENTPVALFILE)"
echo "$BIGPATCHNAME split into $FINALPVAL patch files!"
