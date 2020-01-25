#!/bin/bash

cleaner () {

	make clean;
	make distclean;
	make mrproper;
	# clean up leftover junk
	find . -type f \( -iname \*.rej \
					-o -iname \*.orig \
					-o -iname \*.bkp \
					-o -iname \*.ko \) \
						| parallel rm -fv {};
	rm -rf /root/mn3-lite/build
	rm -f /root/mn3-lite/mx.zip/boot.img
	make -C /root/mn3-lite/scripts/mkqcdtbootimg clean &>/dev/null
	rm -rf /root/mn3-lite/scripts/mkqcdtbootimg/mkqcdtbootimg &>/dev/null
}

cd /root/mn3-lite
export PATH=/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin:$PATH
export ARCH=arm
export CROSS_COMPILE=/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-
env KCONFIG_NOTIMESTAMP=true &>/dev/null
cleaner &>/dev/null
[ ! -d "/root/mn3-lite/build" ] && mkdir /root/mn3-lite/build
cp $(pwd)/arch/arm/configs/mxconfig $(pwd)/build/.config;
make ARCH=arm -j7 O=$(pwd)/build oldconfig;
make ARCH=arm -S -s -j7 O=$(pwd)/build $(pwd)/$1;
cleaner &>/dev/null
