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

	while IFS= read -r PLINE
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
			SPLITFILENUM=$((CURRENTPVAL+1))
			echo -n "$SPLITFILENUM" > "$CURRENTPVALFILE"
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
FINALPVAL="$(cat $FINALPVALFILE)"
echo -ne "                   \r"; \
echo "Finished!"; \
echo "$BIGPATCHNAME split into $FINALPVAL patch files!"
