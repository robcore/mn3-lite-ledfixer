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

myppr /root/mn3lite/patches/0007-locking-Various-static-lock-initializer-fixes.patch
myppr /root/mn3lite/patches/0006-idr-deprecate-idr_remove_all.patch
myppr /root/mn3lite/patches/0005-idr-make-idr_destroy-imply-idr_remove_all.patch
myppr /root/mn3lite/patches/0004-idr-fix-a-subtle-bug-in-idr_get_next.patch
myppr /root/mn3lite/patches/0003-idr-rename-MAX_LEVEL-to-MAX_IDR_LEVEL.patch

echo "$0 is complete!"
