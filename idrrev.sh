#!/bin/bash

myppr() {
    local PFILE
    if [ -n "$1" ]
    then
        PFILE="$1"
    else
        echo "ERROR! No Patch File Supplied! Exiting!"
        exit 1
    fi

    if patch -F0 -p1 -R < "$PFILE"
    then
        echo "Patch Successfully applied"
    else
        echo "Patch Failed! Exiting!"
        exit 1
    fi
}

myppr /root/mn3lite/patches/0010-wait-nevermind.patch
myppr /root/mn3lite/patches/0009-idr-rename-MAX_LEVEL-to-MAX_IDR_LEVEL.patch
myppr /root/mn3lite/patches/0008-revert-to-real-stock-3.4.patch
myppr /root/mn3lite/patches/0006-return-idr-to-stock-3.4.patch

echo "$0 is complete!"
