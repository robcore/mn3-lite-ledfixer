#!/system/bin/sh

./boot_patch.sh boot.img
dd if=mxpboot.img of=/dev/block/platform/msm_sdcc.1/by-name/boot
