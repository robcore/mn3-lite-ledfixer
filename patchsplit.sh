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
		echo "$PLINE" | grep -q 'diff --git'
		if [ "$?" -eq 0 ]
		then
			SPLITFILENUM=$((CURRENTPVAL+1))
			echo -n "$SPLITFILENUM" > "$CURRENTPVALFILE"
			SPLITFILEFORM=$(printf "%04d\n" $SPLITFILENUM)
			SPLITFILE="$PATCHFOLDER/$SPLITFILEFORM.patch"
			echo -ne "                   \r"; \
			echo -ne "Creating $SPLITFILE\r"; \
		else
			SPLITFILEFORM=$(printf "%04d\n" $CURRENTPVAL)
			SPLITFILE="$PATCHFOLDER/$SPLITFILEFORM.patch"
			echo -ne "                   \r"; \
			echo -ne "Creating $SPLITFILE\r"; \
		fi

		echo "$PLINE" | grep -q 'THISISTHEENDFAKEFAKEFAKEFAKE'
		if [ "$?" -eq 0 ]
		then
			echo -ne "                   \r"; \
			echo "Finished!"; \
			break
		else
			echo "$PLINE" >> "$SPLITFILE"
		fi
	done < "$BIGPATCHNAME"

}

dothesplits
