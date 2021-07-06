#!/bin/bash

LISTFILE="/root/mn3lite/initlist"
OUTFILE="/root/mn3lite/initout"
CHMDCMD=$(echo -n 'chmod')
CHWNCMD=$(echo -n 'chown')

[ -f "$OUTFILE" ] && rm "$OUTFILE"
touch "$OUTFILE"

while IFS= read -r ILINE
do
	MKDRCMD=$(echo -n "$ILINE" | cut -z -d ' ' -f1)
	TARG=$(echo -n "$ILINE" | cut -z -d ' ' -f2)
	MODE=$(echo -n "$ILINE" | cut -z -d ' ' -f3)
	OWNR=$(echo -n "$ILINE" | cut -z -d ' ' -f4-5)
	echo "    $ILINE" >> "$OUTFILE"
	echo "    $CHMDCMD $MODE $TARG" >> "$OUTFILE"
	echo "    $CHWNCMD $OWNR $TARG" >> "$OUTFILE"
done < "$LISTFILE"
