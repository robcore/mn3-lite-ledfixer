#!/bin/bash
export PATH=/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin:$PATH
#export PATH=/opt/toolchains/arm-cortex-linux-gnueabi-linaro_4.9.4-2015.06/bin:$PATH
#export CROSS_COMPILE=/opt/toolchains/arm-cortex-linux-gnueabi-linaro_4.9.4-2015.06/bin/arm-cortex-linux-gnueabi-

# kernel build script for Samsung Galaxy Note 3.
#
# Originally written by jcadduono @ xda
#
# Updated by frequentc @ xda
# - Modified to support command line arguments
# - Made script more generic and customizable
# - Other minor changes
#
# Updated by robcore
# -really just specific stuff for my needs

################### BEFORE STARTING ################
#
# download a working toolchain and extract it somewhere and configure this file
# to point to the toolchain's root directory.
# I highly recommend Christopher83's Linaro GCC 4.9.x Cortex-A15 toolchain.
# Download it here: http://forum.xda-developers.com/showthread.php?t=2098133
#
# once you've set up the config section how you like it, you can simply run
# ./dl-build.sh
#
###################### CONFIG ######################
export CCACHE_DIR="$HOME/.ccache"
export USE_CCACHE="1"
export CCACHE_NLEVELS="8"

# root directory of kernel's git repo (default is this script's location)
RDIR="/root/mn3lite"

#[ -z $VARIANT ] && \
# device variant/carrier, possible options:
#	can = N900W8	(Canadian, same as T-Mobile)
#	eur = N9005	(Snapdragon International / hltexx / Europe)
#	spr = N900P	(Sprint)
#	tmo = N900T	(T-Mobile, same as Canadian)
#	kor = N900K/L/S	(Unified Korean / KT Corporation, LG Telecom, South Korea Telecom)
# not currently possible options (missing cm12.1 support!):
#	att = N900A	(AT&T)
#	usc = N900R4	(US Cellular)
#	vzw = N900V	(Verizon)
#VARIANT=tmo
#[ -z $VER ] && \
# version number
# KERNEL_NAME should NOT contain any spaces
# kernel version string appended to 3.4.x-${KERNEL_NAME}-kernel-hlte-
# (shown in Settings -> About device)
OLDVER="$(cat .oldversion)"

############## SCARY NO-TOUCHY STUFF ###############

# Used as the prefix for the ramdisk and zip folders. Also used to prefix the defconfig files in arch/arm/configs/.
RAMDISKFOLDER="$RDIR/mxramdisk"
ZIPFOLDER="$RDIR/mxzip"
DEFCONFIG="$RDIR/arch/arm/configs/mxconfig"
QUICKDATE="$(date | awk '{print $2$3}')"

export ARCH="arm"
export PATH="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin:$PATH"
export CROSS_COMPILE="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-"

env KCONFIG_NOTIMESTAMP=true &>/dev/null

warnandfail() {
	echo -n "MX ERROR on Line ${BASH_LINENO[0]}"
	echo "!!!"
	local ISTRING
	ISTRING="$1"
	if [ -n "$ISTRING" ]
	then
		echo "$ISTRING"
	fi
	exit 1
}

if [ ! -f "$DEFCONFIG" ]
then
	echo "$DEFCONFIG not found in arm configs!"
	exit 1
fi

if [ ! -d "$RAMDISKFOLDER" ]
then
	echo "$RAMDISKFOLDER not found!"
	exit 1
fi

KDIR="$RDIR/build/arch/arm/boot"

handle_existing() {
	echo -n "Use last version? Mark$OLDVER will be removed [y/n/Default y] ENTER: "
	read -r USEOLD
	if [ -z "$USEOLD" ]
	then
		warnandfail "You MUST choose a version for the kernel"
	elif [ "$USEOLD" = y ]
	then
		KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
		echo "Removing old zip files..."
		rm -f "$RDIR/$KERNEL_VERSION.zip"
	elif [ "$USEOLD" = n ]
	then
		echo -n "Enter new version and hit enter: "
		read -r NEWVER
		if [ -z "$NEWVER" ]
		then
			echo "Nothing entered, using old"
			KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
			echo "Removing old zip files..."
			rm -f "$RDIR/$KERNEL_VERSION.zip" &> /dev/null
		else
			KERNEL_VERSION="machinexlite-Mark$NEWVER-hltetmo"
			echo "$NEWVER" > .oldversion
		fi
	fi
	echo "Kernel version is: $KERNEL_VERSION"
	echo "--------------------------------"
}

CLEAN_BUILD() {
	echo "Cleaning build..."
	make clean &>/dev/null
	make distclean &>/dev/null
	make mrproper &>/dev/null
	# clean up leftover junk
	find . -type f \( -iname \*.rej \
					-o -iname \*.orig \
					-o -iname \*.bkp \
					-o -iname \*.ko \) \
						| parallel rm -fv {};
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	rm -rf "$RDIR/build" &>/dev/null
	rm -f "$ZIPFOLDER/boot.img" &>/dev/null
	make -C "$RDIR/scripts/mkqcdtbootimg" clean &>/dev/null
	rm -rf "$RDIR/scripts/mkqcdtbootimg/mkqcdtbootimg" &>/dev/null
	echo "Cleaned"
}

BUILD_KERNEL_CONFIG() {
	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	sed -i '/CONFIG_LOCALVERSION/d' "$RDIR/arch/arm/configs/mxconfig"
	echo -n 'CONFIG_LOCALVERSION="' >> "$RDIR/arch/arm/configs/mxconfig"
	echo -n "$KERNEL_VERSION" >> "$RDIR/arch/arm/configs/mxconfig"
	echo '"' >> "$RDIR/arch/arm/configs/mxconfig"
	echo 'CONFIG_LOCALVERSION_AUTO=y' >> "$RDIR/arch/arm/configs/mxconfig"
	cp "$RDIR/arch/arm/configs/mxconfig" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" -C "$RDIR" O="$RDIR/build" -j5 oldconfig || warnandfail "make oldconfig Failed!"
}

BUILD_KERNEL() {
	echo "Starting build..."
	make ARCH="arm" -S -s -C "$RDIR" O="$RDIR/build" -j5 || warnandfail "Kernel Build failed!"
	cp "build/.config" "config.$QUICKDATE"
}

BUILD_RAMDISK() {
	echo "Building ramdisk structure..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
	rm -rf "$RDIR/build/ramdisk" &>/dev/null
	cp -par "$RAMDISKFOLDER" "$RDIR/build/ramdisk" || warnandfail "Failed to create $RDIR/build/ramdisk!"
	echo "Building ramdisk img"
	cd "$RDIR/build/ramdisk" || warnandfail "Failed to cd to $RDIR/build/ramdisk!"
	mkdir -pm 755 dev proc sys system
	mkdir -pm 771 data
	if [ -f "$KDIR/ramdisk.cpio.gz" ]
	then
		rm "$KDIR/ramdisk.cpio.gz"
	fi
	find | fakeroot cpio -v -o -H newc | gzip -v -9 > "$KDIR/ramdisk.cpio.gz"
	[ ! -f "$KDIR/ramdisk.cpio.gz" ] && warnandfail "NO ramdisk!"
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
}

BUILD_BOOT_IMG() {
	echo "Generating boot.img..."
	rm -f "$ZIPFOLDER/boot.img"
	if [ ! -f "$RDIR/scripts/mkqcdtbootimg/mkqcdtbootimg" ]
	then
		make -C "$RDIR/scripts/mkqcdtbootimg" || warnandfail "Failed to make dtb tool!"
	fi

	$RDIR/scripts/mkqcdtbootimg/mkqcdtbootimg --kernel "$KDIR/zImage" \
		--ramdisk "$KDIR/ramdisk.cpio.gz" \
		--dt_dir "$KDIR" \
		--cmdline "console=null androidboot.hardware=qcom user_debug=23 msm_rtb.filter=0x37 ehci-hcd.park=3" \
		--base "0x00000000" \
		--pagesize "2048" \
		--ramdisk_offset "0x02000000" \
		--tags_offset "0x01e00000" \
		--output "$ZIPFOLDER/boot.img"

	echo -n "SEANDROIDENFORCE" >> "$ZIPFOLDER/boot.img"
}

CREATE_ZIP() {
	echo "Compressing to TWRP flashable zip file..."
	cd "$ZIPFOLDER" || warnandfail "Failed to cd to $ZIPFOLDER"
	rm -f "$ZIPFOLDER"/system/lib/modules/*
	for MXMODS in $(find "$RDIR/build/" -iname '*.ko')
	do
		echo "Copying $MXMODS to zip"
		cp -pa "$MXMODS" "$ZIPFOLDER/system/lib/modules/" || warnandfail "Failed to copy new modules to zip!"
	done
	zip -r -9 - * > "$RDIR/$KERNEL_VERSION.zip"
	echo "Kernel $KERNEL_VERSION.zip finished"
	echo "Filepath: "
	echo "$RDIR/$KERNEL_VERSION.zip"
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
}

#CREATE_TAR()
#{
#	if [ $MAKE_TAR != 1 ]; then return; fi
#
#	echo "Compressing to Odin flashable tar.md5 file..."
#	cd $RDIR/$ZIPFOLDER
#	tar -H ustar -c boot.img > $RDIR/$KERNEL_VERSION.tar
#	cd $RDIR
#	md5sum -t $KERNEL_VERSION.tar >> $KERNEL_VERSION.tar
#	mv $KERNEL_VERSION.tar $KERNEL_VERSION.tar.md5
#	cd $RDIR
#}

SHOW_HELP() {
	cat << EOF
Machinexlite by robcore. To configure this script for your build, edit the top of mx-build.sh before continuing.

usage: ./mx-build.sh [OPTION]

Common options:
  -a|--all		Do a complete build (starting at the beginning)
  -c|--clean		Remove everything this build script has done
  -m|--clean_make	Perform make proper|clean|distclean in one sweep
  -k|--kernel		Try the build again starting at compiling the kernel
  -r|--ramdisk		Try the build again starting at the ramdisk

Other options that only complete 1 part of the build:
 -ko|--kernel-only	Recompile only the kernel

Build script by jcadduono, frequentc & robcore
EOF

	exit 1
}

BUILD_RAMDISK_CONTINUE() {
	BUILD_RAMDISK && BUILD_BOOT_IMG && CREATE_ZIP
}

BUILD_KERNEL_CONTINUE() {
	BUILD_KERNEL && BUILD_RAMDISK_CONTINUE
}

BUILD_ALL() {
	CLEAN_BUILD && handle_existing && BUILD_KERNEL_CONFIG && BUILD_KERNEL_CONTINUE
}

if [ $# = 0 ] ; then
	SHOW_HELP
fi

while [[ $# -gt 0 ]]
	do
	key="$1"

	case $key in
	     -a|--all)
			BUILD_ALL
			break
	    	;;

	     -c|--clean)
	    	CLEAN_BUILD
	    	break
	    	;;

	     -k|--kernel)
	    	BUILD_KERNEL_CONTINUE
	    	break
	    	;;

	    -ko|--kernel-only)
	    	BUILD_KERNEL
	    	break
	    	;;

	     -r|--ramdisk)
	     	BUILD_RAMDISK_CONTINUE
	    	break
	    	;;

	    *)
	    	SHOW_HELP
	    	break;
	    	;;
	esac
	shift # past argument or value
done
