#!/bin/bash

SPFILE="/root/mn3lite/sndrevfile"
while read -r SPLINE
do
	patch -F0 -p1 -R < "$SPLINE"
	if [ "$?" -ne "0" ]
	then
		echo "PATCH FAILED! ABORT!"
		exit 1
	fi
done < "$SPFILE"
