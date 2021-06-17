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

myppr /root/mn3lite/patches/0050-fix-i2c-core.patch
myppr /root/mn3lite/patches/0049-fix-from-removal-of-MAX_IDR_MASK.patch
myppr /root/mn3lite/patches/0048-rename-MAX_LEVEL-to-MAX_IDR_LEVEL.patch
myppr /root/mn3lite/patches/0047-idr-deprecate-idr_pre_get-and-idr_get_new-_above.patch
myppr /root/mn3lite/patches/0046-dox.patch
myppr /root/mn3lite/patches/0045-idr-implement-lookup-hint.patch
myppr /root/mn3lite/patches/0044-idr-add-idr_layer-prefix.patch
myppr /root/mn3lite/patches/0043-idr-remove-length-restriction-from-idr_layer-bitmap.patch
myppr /root/mn3lite/patches/0042-idr-remove-MAX_IDR_MASK-and-move-left-MAX_IDR_-into-.patch
myppr /root/mn3lite/patches/0039-idr-fix-top-layer-handling.patch
myppr /root/mn3lite/patches/0038-idr-implement-idr_preload-_end-and.patch
myppr /root/mn3lite/patches/0037-idr-refactor-idr_get_new_above.patch
myppr /root/mn3lite/patches/0036-idr-remove-_idr_rc_to_errno-hack.patch
myppr /root/mn3lite/patches/0035-idr-relocate-idr_for_each_entry-and-reorganize.patch
myppr /root/mn3lite/patches/0034-idr-deprecate-idr_remove_all.patch
myppr /root/mn3lite/patches/0033-idr-make-idr_destroy-imply-idr_remove_all.patch

echo "$0 is complete!"
