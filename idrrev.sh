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

myppr /root/mn3lite/patches/0020-remove-MAX_ID_MASK-from-spmi.patch
myppr /root/mn3lite/patches/0019-remove-MAX_ID_MASK-or-whatever-from-slimbus.patch
myppr /root/mn3lite/patches/0018-idr-implement-lookup-hint.patch
myppr /root/mn3lite/patches/0017-idr-add-idr_layer-prefix.patch
myppr /root/mn3lite/patches/0016-idr-make-idr_layer-larger.patch
myppr /root/mn3lite/patches/0015-idr-remove-length-restriction-from-idr_layer-bitmap.patch
myppr /root/mn3lite/patches/0014-idr-remove-MAX_IDR_MASK-and-move-left-MAX_IDR_.patch
myppr /root/mn3lite/patches/0013-idr-fix-top-layer-handling.patch
myppr /root/mn3lite/patches/0012-idr-implement-idr_preload-_end-and-idr_alloc.patch
myppr /root/mn3lite/patches/0011-idr-refactor-idr_get_new_above.patch
myppr /root/mn3lite/patches/0010-idr-remove-_idr_rc_to_errno-hack.patch
myppr /root/mn3lite/patches/0009-idr-relocate-idr_for_each_entry-and-reorganize.patch
myppr /root/mn3lite/patches/0008-idr-cosmetic-updates-to-struct-initializer-def.patch

echo "$0 is complete!"
