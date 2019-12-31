#!/bin/bash

export CCACHE_DIR="$HOME/.ccache"
export USE_CCACHE="1"
export CCACHE_NLEVELS="8"

RDIR="/root/mn3lite"
OLDVERFILE="$RDIR/.oldversion"
OLDVER="$(cat $OLDVERFILE)"
RAMDISKFOLDER="$RDIR/mxramdisk"
ZIPFOLDER="$RDIR/mxzip"
DEFCONFIG="$RDIR/arch/arm/configs/mxconfig"
QUICKDATE="$(date | awk '{print $2$3}')"

#export PATH="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin:$PATH"

export CROSS_COMPILE="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-"
TOOLCHAIN="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-"
env KCONFIG_NOTIMESTAMP=true &>/dev/null

#!/bin/sh

# Asuswrt-Merlin helper functions
# For use with Postconf scripts (and others)

_quote() {
	echo $1 | sed 's/[]\/()$*.^|[]/\\&/g'
}

# This function looks for a string, and inserts a specified string after it inside a given file
# $1: the line to locate, $2: the line to insert, $3: Config file where to insert
pc_insert() {
	local PATTERN;
	local CONTENT;
	PATTERN=$(_quote "$1")
	CONTENT=$(_quote "$2")
	sed -i "/$PATTERN/a$CONTENT" $3
}

# This function looks for a string, and replace it with a different string inside a given file
# $1: the line to locate, $2: the line to replace with, $3: Config file where to insert
pc_replace() {
	local PATTERN;
	local CONTENT;
	PATTERN=$(_quote "$1")
	CONTENT=$(_quote "$2")
	sed -i "s/$PATTERN/$CONTENT/" $3
}

# This function will append a given string at the end of a given file
# $1 The line to append at the end, $2: Config file where to append
pc_append() {
	echo "$1" >> $2
}

# This function will delete a line containing a given string inside a given file
# $1 The line to locate, $2: Config file where to delete
pc_delete() {
	local PATTERN;
	PATTERN=$(_quote "$1")
	sed -i "/$PATTERN/d" $2
}

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
		MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
		echo "Removing old zip files..."
		rm -f "$RDIR/$MX_KERNEL_VERSION.zip"
	elif [ "$USEOLD" = n ]
	then
		echo -n "Enter new version and hit enter: "
		read -r NEWVER
		if [ -z "$NEWVER" ]
		then
			echo "Nothing entered, using old"
			MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
			echo "Removing old zip files..."
			rm -f "$RDIR/$MX_KERNEL_VERSION.zip" &> /dev/null
		else
			MX_KERNEL_VERSION="machinexlite-Mark$NEWVER-hltetmo"
			echo -n "$NEWVER" > "$OLDVERFILE"
		fi
	fi
	echo "Kernel version is: $MX_KERNEL_VERSION"
	echo "--------------------------------"
}

handle_yes_existing() {
	echo "Using last version. Mark$OLDVER will be removed."
	MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
	echo "Removing old zip files..."
	rm -f "$RDIR/$MX_KERNEL_VERSION.zip"
	echo "Kernel version is: $MX_KERNEL_VERSION"
	echo "--------------------------------"
}

CLEAN_BUILD() {
	echo -ne "Cleaning build   \r"; \
	make clean &>/dev/null
	make distclean &>/dev/null
	echo -ne "Cleaning build.  \r"; \
	make mrproper &>/dev/null
	echo -ne "Cleaning build.. \r"; \
	# clean up leftover junk
	find . -type f \( -iname \*.rej \
					-o -iname \*.orig \
					-o -iname \*.bkp \
					-o -iname \*.ko \) \
						| parallel rm -fv {};
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	rm -rf "$RDIR/build" &>/dev/null
	rm "$ZIPFOLDER"/boot.img &>/dev/null
	echo -ne "Cleaning build...\r"; \
	make -C "$RDIR/scripts/mkqcdtbootimg" clean &>/dev/null
	rm -rf "$RDIR/scripts/mkqcdtbootimg/mkqcdtbootimg" &>/dev/null
	echo -ne "                 \r"; \
	echo -ne "Cleaned\r"; \
	echo -ne "\n"
}

configit() {

git add -u && git add . && git add -A && git commit -a -m 'Config updated by build script'

}

BUILD_MENUCONFIG() {
	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="dummyconfigbuild"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	echo -n "$MX_KERNEL_VERSION" > "$RDIR/localversion"
	chmod 644 "$RDIR/localversion"
	configit
	cp "$DEFCONFIG" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$RDIR/build" menuconfig
}
BUILD_SINGLE_CONFIG() {
	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="buildingsingledriver"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	echo -n "$MX_KERNEL_VERSION" > "$RDIR/localversion"
	chmod 644 "$RDIR/localversion"
	configit
	cp "$DEFCONFIG" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$RDIR/build" -j5 oldconfig || warnandfail "make oldconfig Failed!"
}

BUILD_SINGLE_DRIVER() {
	echo "Building Single Driver..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" -S -s -j5 O="$RDIR/build/" "$1"
}

BUILD_KERNEL_CONFIG() {
	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	echo -n "$MX_KERNEL_VERSION" > "$RDIR/localversion"
	chmod 644 "$RDIR/localversion"
	configit
	cp "$DEFCONFIG" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$RDIR/build" -j5 oldconfig || warnandfail "make oldconfig Failed!"
}

BUILD_KERNEL() {
	echo "Backing up .config to config.$QUICKDATE"
	cp "build/.config" "config.$QUICKDATE"
	echo "Snapshot of current environment variables:"
	env
	echo "Starting build..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -S -s -C "$RDIR" O="$RDIR/build" -j5 || warnandfail "Kernel Build failed!"
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
#	find | fakeroot cpio -v -H newc -o | lzop -9 > "$KDIR/ramdisk.cpio.gz"
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
	if [ "$?" -eq 0 ]
	then
		echo "mkqcdtbootimg appears to have succeeded in building an image"
	else
		warnandfail "mkqcdtbootimg appears to have failed in building an image!"
	fi
	[ -f "$ZIPFOLDER/boot.img" ] || warnandfail "$ZIPFOLDER/boot.img does not exist!"
	echo -n "SEANDROIDENFORCE" >> "$ZIPFOLDER/boot.img"
}

CREATE_ZIP() {
	echo "Compressing to TWRP flashable zip file..."
	cd "$ZIPFOLDER" || warnandfail "Failed to cd to $ZIPFOLDER"
	rm -f "$ZIPFOLDER"/system/lib/modules/*
	for MXMODS in $(find "$RDIR/build/" -iname '*.ko')
	do
		if [ -f "$MXMODS" ]
		then
			echo "Copying $MXMODS to zip"
			cp -pa "$MXMODS" "$ZIPFOLDER/system/lib/modules/" || warnandfail "Failed to copy new modules to zip!"
		fi
	done
	zip -r -9 - * > "$RDIR/$MX_KERNEL_VERSION.zip"
	echo "Kernel $MX_KERNEL_VERSION.zip finished"
	echo "Filepath: "
	echo "$RDIR/$MX_KERNEL_VERSION.zip"
	if [ ! -f "$RDIR/$MX_KERNEL_VERSION.zip" ]
	then
		warnandfail "$RDIR/$MX_KERNEL_VERSION.zip does not exist!"
	fi
	if [ -s "$RDIR/$MX_KERNEL_VERSION.zip" ]
	then
		echo "Uploading $MX_KERNEL_VERSION.zip to Google Drive"
		/bin/bash /root/google-drive-upload/upload.sh "$RDIR/$MX_KERNEL_VERSION.zip"
	else
		warnandfail "$RDIR/$MX_KERNEL_VERSION.zip is 0 bytes, something is wrong!"
	fi
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
}

#CREATE_TAR()
#{
#	if [ $MAKE_TAR != 1 ]; then return; fi
#
#	echo "Compressing to Odin flashable tar.md5 file..."
#	cd $RDIR/$ZIPFOLDER
#	tar -H ustar -c boot.img > $RDIR/$MX_KERNEL_VERSION.tar
#	cd $RDIR
#	md5sum -t $MX_KERNEL_VERSION.tar >> $MX_KERNEL_VERSION.tar
#	mv $MX_KERNEL_VERSION.tar $MX_KERNEL_VERSION.tar.md5
#	cd $RDIR
#}

SHOW_HELP() {
	cat << EOF
Machinexlite by robcore. To configure this script for your build, edit the top of mx-build.sh before continuing.

usage: ./mx-build.sh [OPTION]

Common options:
  -a|--all			Do a complete build (starting at the beginning)
  -b|--bsd			Build single driver (/path/to/folder/ | /path/to/file.o)
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
	CLEAN_BUILD && BUILD_KERNEL_CONFIG && BUILD_KERNEL_CONTINUE
}

BSDWRAPPER() {
	[ -z "$1" ] && warnandfail "Build Single Driver: Missing /path/to/folder/ or /path/to/file.o"
	CLEAN_BUILD && BUILD_SINGLE_CONFIG && BUILD_SINGLE_DRIVER "$1"
	CLEAN_BUILD
}

BUILD_MC() {
	BUILD_MENUCONFIG
}

if [ $# = 0 ] ; then
	SHOW_HELP
fi

while [[ $# -gt 0 ]]
	do
	key="$1"
	extrargs="$2"

	case $key in
	     -a|--all)
			handle_existing
			BUILD_ALL
			break
	    	;;

	     -y|--allyesrebuild)
			handle_yes_existing
			BUILD_ALL
			break
	    	;;

	     -b|--bsd)
			BSDWRAPPER "$extrargs"
			break
	    	;;

	     -c|--clean)
	    	CLEAN_BUILD
	    	break
	    	;;

		 -m|--menu)
			BUILD_MC
			break
			;;

	     -k|--kernel)
			handle_existing
	    	BUILD_KERNEL_CONTINUE
	    	break
	    	;;

	    -ko|--kernel-only)
			handle_existing
	    	BUILD_KERNEL
	    	break
	    	;;

	     -r|--ramdisk)
			handle_existing
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
