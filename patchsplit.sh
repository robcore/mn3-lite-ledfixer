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

rm "$PATCHFOLDER/currentpval"
echo -n '0' > "$PATCHFOLDER/currentpval"
CURRENTPVALFILE="$PATCHFOLDER/currentpval"
CURRENTPVAL="$(cat $CURRENTPVALFILE)"

dothesplits() {

	local SPLITFILENUM
	local SPLITFILEFORM
	local SPLITFILE

	while IFS=$'\n' read -r PLINE
	do
		if echo "$PLINE" | grep -q 'THISISTHEENDFAKEFAKEFAKEFAKE'
		then
			echo -ne "                   \r"; \
			echo "Finished!"; \
			break
		fi

		if echo "$PLINE" | grep -q 'diff --git'
		then
			SPLITFILENUM="$(echo $(expr $(( $CURRENTPVAL + 1 ))))"
			echo -n "$SPLITFILENUM" > CURRENTPVALFILE
			SPLITFILEFORM=$(printf "%04d\n" "$CURRENTPVAL")
			SPLITFILE="$PATCHFOLDER/$SPLITFILEFORM.patch"
			echo -ne "                   \r"; \
			echo -ne "Creating $SPLITFILE\r"; \
		fi
		echo "$PLINE" >> "$SPLITFILE"
	done < "$BIGPATCHNAME"

}

dothesplits
