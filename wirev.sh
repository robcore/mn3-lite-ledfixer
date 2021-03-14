#!/bin/bash

patch -F0 -p1 -R < "/root/mn3lite/patches/0015-mxconfig-updated-from-build.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0014-attempting-to-change-some-network-options-in-config.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0013-grabbed-a-couple-of-the-sensible-changes-from-arter-.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0012-mxconfig-updated-from-build.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0011-re-install-stock-wifi-config-files-and-binaries.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0010-disable-flow-control-again.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0009-net-wireless-bcmdhd-fix-use-after-free-in.patch"
patch -F0 -p1 -R < "/root/mn3lite/patches/0008-revert-arter-wifi-patches.patch"
