#!/bin/bash

export CCACHE_DIR="$HOME/.ccache"
export USE_CCACHE="1"
export CCACHE_NLEVELS="8"
env KCONFIG_NOTIMESTAMP=true &>/dev/null

RDIR="/root/mn3lite"
BUILDIR="$RDIR/build"
KDIR="$BUILDIR/arch/arm/boot"
OLDVERFILE="$RDIR/.oldversion"
OLDVER="$(cat $OLDVERFILE)"
LASTZIPFILE="$RDIR/.lastzip"
LASTZIP="$(cat $LASTZIPFILE)"
RAMDISKFOLDER="$RDIR/mxramdisk"
ZIPFOLDER="$RDIR/mxzip"
MXCONFIG="$RDIR/arch/arm/configs/mxconfig"
MXRECENT="$MXCONFIG.recent"
QUICKMONTHDAY="$(date | awk '{print $2$3}')"
QUICKHOUR="$(date +%l | cut -d " " -f2)"
QUICKMIN="$(date +%S)"
QUICKAMPM="$(date +%p)"
QUICKTIME="$QUICKHOUR:$QUICKMIN${QUICKAMPM}"
QUICKDATE="$QUICKMONTHDAY-$QUICKTIME"
#CORECOUNT="$(grep processor /proc/cpuinfo | wc -l)"
#TOOLCHAIN="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-"
TOOLCHAIN="/opt/toolchains/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-"
#TOOLCHAIN="/opt/arm-cortex_a15-linux-gnueabihf-linaro_4.9.4-2015.06/bin/arm-cortex_a15-linux-gnueabihf-"
#TOOLCHAIN="/opt/toolchains/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-"
#TOOLCHAIN="/opt/toolchains/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-"
#export ARCH="arm"
export CROSS_COMPILE="$TOOLCHAIN"
echo -n "$(date +%s)" > "$RDIR/.starttime"
STARTTIME="$(cat $RDIR/.starttime)"

timerprint() {

	local DIFFMINS
	local DIFFSECS

	DIFFMINS=$(bc <<< "(${1}%3600)/60")
	DIFFSECS=$(bc <<< "${1}%60")
	printf "%s" "Build completed in: "
	printf "%d" "$DIFFMINS"
	if [ "$DIFFMINS" = "1" ]
	then
		printf "%s" " Minute and "
	else
		printf "%s" " Minutes and "
	fi
	printf "%d" "$DIFFSECS"
	if [ "$DIFFSECS" = "1" ]
	then
		printf "%s\n" " Second."
	else
		printf "%s\n" " Seconds."
	fi
	rm $RDIR/.starttime &> /dev/null
	rm $RDIR/.endtime &> /dev/null
	printf "%s" "Finished!"

}

timerdiff() {

	printf "%s" "$(date +%s)" > "$RDIR/.endtime"
	ENDTIME="$(cat $RDIR/.endtime)"
	DIFFTIME=$(( ENDTIME - STARTTIME ))
	timerprint "$DIFFTIME"

}

cleanupfail() {

	echo -n "MX ERROR on Line ${BASH_LINENO[0]}"
	echo "!!!"
	local ISTRING
	ISTRING="$1"
	if [ -n "$ISTRING" ]
	then
		printf "%s\n" "$ISTRING"
	fi
	exit 1

}

takeouttrash() {

	rm $RDIR/.starttime &> /dev/null
	rm $RDIR/.endtime &> /dev/null

	find . -type f \( -iname \*.rej \
			-o -iname \*.orig \
			-o -iname \*.bkp \
			-o -iname \*.ko \) \
			| parallel rm -fv {};

}

getmxrecent() {

	if [ -f "$BUILDIR/.config" ]
	then
		[ -f "$MXRECENT" ] && rm "$MXRECENT"
		cp "$BUILDIR/.config" "$MXRECENT"
	fi
}

clean_build() {

	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	getmxrecent
	if [ "$1" = "standalone" ]
	then
		echo -ne "Cleaning build         \r"; \
		make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -j16 clean
		echo -ne "Cleaning build.        \r"; \
		make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -j16 distclean
		echo -ne "Cleaning build..       \r"; \
		make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -j16 mrproper
	else
		echo -ne "Cleaning build         \r"; \
		make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -j16 clean &>/dev/null
		echo -ne "Cleaning build.        \r"; \
		make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -j16 distclean &>/dev/null
		echo -ne "Cleaning build..       \r"; \
		make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -j16 mrproper &>/dev/null
	fi
	echo -ne "Cleaning build...      \r"; \
	takeouttrash &>/dev/null
	echo -ne "Cleaning build....     \r"; \
	rm -rf "$BUILDIR" &>/dev/null
	echo -ne "Cleaning build.....    \r"; \
	rm "$ZIPFOLDER/common/boot.img" &>/dev/null
	echo -ne "Cleaning build......   \r"; \
	make -C "$RDIR/scripts/mkqcdtbootimg" clean &>/dev/null
	echo -ne "Cleaning build.......  \r"; \
	rm -rf "$RDIR/scripts/mkqcdtbootimg/mkqcdtbootimg" &>/dev/null
	echo -ne "Cleaning build........ \r"; \
	echo -ne "                       \r"; \
	echo -ne "Cleaned                \r"; \
	echo -e "\n"

}

warnandfail() {

	echo -n "MX ERROR on Line ${BASH_LINENO[0]}"
	echo "!!!"
	local ISTRING
	ISTRING="$1"
	if [ -n "$ISTRING" ]
	then
		printf "%s\n" "$ISTRING"
	fi
	clean_build
	exit 1

}

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

if [ "$1" != "-nc" ] && [ "$1" != "--newconfig" ]
then
	if [ ! -f "$MXCONFIG" ]
	then
		warnandfail "$MXCONFIG not found in arm configs!"
	fi
fi

if [ ! -d "$RAMDISKFOLDER" ]
then
	warnandfail "$RAMDISKFOLDER not found!"
fi

shortprog() {

	printf "%s\r" "-----------------------------------"; \
	sleep 0.4; \
	printf "%s\r" "----------------- -----------------"; \
	sleep 0.4; \
	printf "%s\r" "---------------     ---------------"; \
	sleep 0.4; \
	printf "%s\r" "----------               ----------"; \
	sleep 0.4; \
	printf "%s\r" "-------                     -------"; \
	sleep 0.4; \
	printf "%s\r" "-----                         -----"; \
	sleep 0.4; \
	printf "%s\r" "---                             ---"; \
	sleep 0.4; \
	printf "%s\r" "-                                 -"; \
	sleep 0.4; \
	printf "%s\r" "---                             ---"; \
	sleep 0.4; \
	printf "%s\r" "-----                         -----"; \
	sleep 0.4; \
	printf "%s\r" "-------                     -------"; \
	sleep 0.4; \
	printf "%s\r" "----------               ----------"; \
	sleep 0.4; \
	printf "%s\r" "---------------     ---------------"; \
	sleep 0.4; \
	printf "%s\r" "----------------- -----------------"; \
	sleep 0.4; \
	printf "%s\r" "-----------------------------------"; \
	sleep 0.4; \
	printf "%s\r" "                                   "; \
	printf "%s\n"
	#echo -ne "\n"

}

test_funcs() {

	echo "This is a test of the emergency broadcast system."
	echo "This is only a test."
	shortprog
	echo "This has been a test of the emergency broadcast system."
	echo "This was only a test"

}

handle_existing() {

	if [ -z "$OLDVER" ]
	then
		warnandfail "FATAL ERROR! Failed to read version from .oldversion"
	fi

	if [ ! -f "$RDIR/machinexlite-Mark$OLDVER-hltetmo.zip" ]
	then
		echo "Version Override!"
		echo "Previous version was not completed!"
		echo "Rebuilding old version"
		MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
	elif [ "$LASTZIP" = "machinexlite-Mark$OLDVER-hltetmo.zip" ]
	then
		echo "Version Override"
		echo "Previous version completed successfully!"
		echo "Building new version!"
		NEWVER="$(echo $(( OLDVER + 1 )))"
		if [ -z "$NEWVER" ]
		then
			warnandfail "FATAL ERROR! Failed to raise version number by one!"
		fi
		MX_KERNEL_VERSION="machinexlite-Mark$NEWVER-hltetmo"
		echo -n "$NEWVER" > "$OLDVERFILE"
	else
		echo -n "Rebuilding (o)ld version? Or building (n)ew version? Please specify [o|n]: "
		read -r WHICHVERSION
		if [ "$WHICHVERSION" = "n" ]
		then
			CURVER="new"
		elif [ "$WHICHVERSION" = "o" ]
		then
			CURVER="old"
		else
			CURVER="invalid"
		fi
		if [ -z "$CURVER" ]
		then
			warnandfail "You MUST choose a version for the kernel"
		elif [ "$CURVER" = "invalid" ]
		then
			warnandfail "versioning failed.  please fix"
		elif [ "$CURVER" = "old" ]
		then
			echo "Rebulding old version has been selected"
			echo "Removing old zip files..."
			MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
			rm -f "$RDIR/$MX_KERNEL_VERSION.zip"
		elif [ "$CURVER" = "new" ]
		then
			echo "Building new version has been selected"
			NEWVER="$(echo $(( OLDVER + 1 )))"
			if [ -z "$NEWVER" ]
			then
				warnandfail "FATAL ERROR! Failed to raise version number by one!"
			fi
			MX_KERNEL_VERSION="machinexlite-Mark$NEWVER-hltetmo"
			echo -n "$NEWVER" > "$OLDVERFILE"
		fi
	fi
	echo "Kernel version is: $MX_KERNEL_VERSION"
	echo "--------------------------------"

}

rebuild() {

	echo "Using last version. Mark$OLDVER will be removed."
	MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
	echo "Removing old zip files..."
	rm -f "$RDIR/$MX_KERNEL_VERSION.zip"
	echo "Kernel version is: $MX_KERNEL_VERSION"
	echo "--------------------------------"

}

build_new_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="dummyconfigbuild"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cat "$RDIR/arch/arm/configs/msm8974_sec_hlte_tmo_defconfig" "$RDIR/arch/arm/configs/msm8974_sec_defconfig" "$RDIR/arch/arm/configs/selinux_defconfig" > "$RDIR/arch/arm/configs/mxconfig"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$BUILDIR" menuconfig

}

build_menuconfig() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="dummyconfigbuild"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$BUILDIR" menuconfig

}

build_single_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="buildingsingledriver"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$BUILDIR" -j16 oldconfig || warnandfail "make oldconfig Failed!"

}

build_kernel_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$BUILDIR" -j16 oldconfig || warnandfail "make oldconfig Failed!"
	getmxrecent

}

build_single_driver() {

	echo "Building Single Driver..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" -S -s -j16 O="$BUILDIR/" "$1"

}

build_kernel() {
	OLDCFG="/root/mn3-oldconfigs"
	echo "Backing up .config to $OLDCFG/config.$QUICKDATE"
	cp "$BUILDIR/.config" "$OLDCFG/config.$QUICKDATE"
	echo "Snapshot of current environment variables:"
	env
	echo "Starting build..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -S -s -C "$RDIR" O="$BUILDIR" -j16 || warnandfail "Kernel Build failed!"

}

build_ramdisk() {

	echo "Building ramdisk structure..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
	rm -rf "$BUILDIR/ramdisk" &>/dev/null
	cp -par "$RAMDISKFOLDER" "$BUILDIR/ramdisk" || warnandfail "Failed to create $BUILDIR/ramdisk!"
	echo "Building ramdisk img"
	cd "$BUILDIR/ramdisk" || warnandfail "Failed to cd to $BUILDIR/ramdisk!"
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

build_boot_img() {

	echo "Generating boot.img..."
	rm -f "$ZIPFOLDER/common/boot.img"
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
		--output "$ZIPFOLDER/common/boot.img"
	if [ "$?" -eq 0 ]
	then
		echo "mkqcdtbootimg appears to have succeeded in building an image"
	else
		warnandfail "mkqcdtbootimg appears to have failed in building an image!"
	fi
	[ -f "$ZIPFOLDER/common/boot.img" ] || warnandfail "$ZIPFOLDER/common/boot.img does not exist!"
	#echo -n "SEANDROIDENFORCE" >> "$ZIPFOLDER/common/boot.img"

}

ADBPUSHLOCATION="/sdcard/Download"

create_zip() {

	echo "Compressing to TWRP flashable zip file..."
	cd "$ZIPFOLDER" || warnandfail "Failed to cd to $ZIPFOLDER"
	#[ -d "$ZIPFOLDER/system/lib/modules" ] && rm -rf "$ZIPFOLDER/system/lib/modules"
	#for MXMODS in $(find "$BUILDIR/" -iname '*.ko')
	#do
	#	if [ -f "$MXMODS" ]
	#	then
	#		echo "Copying $MXMODS to zip"
	#		cp -pa "$MXMODS" "$ZIPFOLDER/system/lib/modules/" || warnandfail "Failed to copy new modules to zip!"
	#	fi
	#done
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
		if [ "$?" -eq "0" ]
		then
			echo "$RDIR/$MX_KERNEL_VERSION.zip upload SUCCESS!"
		else
			echo "$RDIR/$MX_KERNEL_VERSION.zip upload FAILED!"
		fi
		echo -n "$MX_KERNEL_VERSION.zip" > "$RDIR/.lastzip"
		echo "Checking if Device is Connected..."
		local SAMSTRING
		SAMSTRING="$(lsusb | grep '04e8:6860')"
		RECOVSTRING="$(lsusb | grep '18d1:4ee2')"
		if [ -n "$SAMSTRING" ]
		then
			echo "Device is Connected via Usb in System Mode!"
			echo "$SAMSTRING"
			adb shell input keyevent KEYCODE_WAKEUP
			#adb shell input touchscreen swipe 930 880 930 380
			echo "Transferring via adb to $ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip"
			adb push "$RDIR/$MX_KERNEL_VERSION.zip" "$ADBPUSHLOCATION"
			if [ "$?" -eq "0" ]
			then
				echo "Successfully pushed $RDIR/$MX_KERNEL_VERSION.zip to $ADBPUSHLOCATION over ADB!"
				#echo "Rebooting Device into Recovery"
				#adb reboot recovery
			else
				echo "Failed to push $RDIR/$MX_KERNEL_VERSION.zip to $ADBPUSHLOCATION over ADB!"
			fi
			adb kill-server || echo "Failed to kill ADB server!"
		elif [ -n "$RECOVSTRING" ]
		then
			echo "Device is Connected via Usb in Recovery Mode!"
			echo "$RECOVSTRING"
			#adb shell input keyevent KEYCODE_WAKEUP
			#adb shell input touchscreen swipe 930 880 930 380
			echo "Transferring via adb to $ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip"
			adb push "$RDIR/$MX_KERNEL_VERSION.zip" "$ADBPUSHLOCATION"
			if [ "$?" -eq "0" ]
			then
				echo "Successfully pushed $RDIR/$MX_KERNEL_VERSION.zip to $ADBPUSHLOCATION over ADB!"
			else
				echo "Failed to push $RDIR/$MX_KERNEL_VERSION.zip to $ADBPUSHLOCATION over ADB!"
			fi
			adb kill-server || echo "Failed to kill ADB server!"
		else
			echo "Device not Connected.  Skipping adb transfer."
		fi
		timerdiff
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
#	tar -H ustar -c common/boot.img > $RDIR/$MX_KERNEL_VERSION.tar
#	cd $RDIR
#	md5sum -t $MX_KERNEL_VERSION.tar >> $MX_KERNEL_VERSION.tar
#	mv $MX_KERNEL_VERSION.tar $MX_KERNEL_VERSION.tar.md5
#	cd $RDIR
#}

show_help() {

	cat << EOF
Machinexlite kernel by robcore
Script written by jcadduono, frequentc & robcore

usage: ./mxbuild.sh [OPTION]
Common options:
 -a|--all            Do a complete build (starting at the beginning)
 -d|--debug          Same as --all but skips final cleanup
 -r|--rebuildme      Same as --all but defaults to rebuilding previous version
 -b|--bsd            Build single driver (path/to/folder/ | path/to/file.o)
 -c|--clean          Remove everything this build script has done
-nc|--newconfig)     Concatecate samsung defconfigs & enter menuconfig
 -m|--menu           Setup an environment for and enter menuconfig
 -k|--kernel         Try the build again starting at compiling the kernel
 -o|--kernel-only    Recompile only the kernel, nothing else
-rd|--ramdisk        Try the build again starting at the ramdisk
 -t|--tests          Testing playground
EOF

	exit 1

}

package_ramdisk_and_zip() {

	build_ramdisk && build_boot_img && create_zip

}

build_kernel_and_package() {

	build_kernel && package_ramdisk_and_zip

}

build_all() {

	clean_build && build_kernel_config && build_kernel_and_package && clean_build

}

build_debug() {

	clean_build && build_kernel_config && build_kernel_and_package

}

bsdwrapper() {

	[ -z "$1" ] && warnandfail "Build Single Driver: Missing path/to/folder/ or path/to/file.o"
	clean_build && build_single_config && build_single_driver "$1"
	clean_build

}

build_nc() {

	build_new_config

}

build_mc() {

	build_menuconfig

}

runtest() {

test_funcs && exit 0

}

if [ $# = 0 ] ; then
	show_help
fi

while [[ $# -gt 0 ]]
do
	extrargs="$2"
	case "$1" in
	     -a|--all)
			handle_existing
			build_all
			break
	    	;;

	     -d|--debug)
			handle_existing
			build_debug
			break
	    	;;

	     -r|--rebuildme)
			rebuild
			build_all
			break
	    	;;

	     -b|--bsd)
			bsdwrapper "$extrargs"
			break
	    	;;

	     -c|--clean)
	    	clean_build "standalone"
	    	break
	    	;;
		 -nc|--newconfig)
			build_nc
			break
			;;
		 -m|--menu)
			build_mc
			break
			;;

	     -k|--kernel)
			handle_existing
	    	build_kernel_and_package
	    	break
	    	;;

	    -o|--kernel-only)
			handle_existing
	    	build_kernel
	    	break
	    	;;

	     -rd|--ramdisk)
			handle_existing
	     	package_ramdisk_and_zip
	    	break
	    	;;

	     -t|--tests)
			runtest
	    	break
	    	;;

	    *)
	    	show_help
	    	break;
	    	;;
	esac
	shift # past argument or value
done
