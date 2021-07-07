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
MXNEWCFG="$MXCONFIG.new"
QUICKHOUR="$(date +%l | cut -d " " -f2)"
QUICKMIN="$(date +%S)"
QUICKAMPM="$(date +%p)"
QUICKDMY="$(date +%d-%m-%Y)"
QUICKTIME="$QUICKHOUR:$QUICKMIN-${QUICKAMPM}"
QUICKDATE="$QUICKDMY-$QUICKTIME"
#CORECOUNT="$(grep processor /proc/cpuinfo | wc -l)"
TOOLCHAIN="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-"
#TOOLCHAIN="/opt/toolchains/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-"
#TOOLCHAIN="/opt/arm-cortex_a15-linux-gnueabihf-linaro_4.9.4-2015.06/bin/arm-cortex_a15-linux-gnueabihf-"
#TOOLCHAIN="/root/mx_toolchains/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-"
#TOOLCHAIN="/opt/toolchains/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-"
#TOOLCHAIN="/opt/toolchains/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-"
#export ARCH="arm"
export CROSS_COMPILE="$TOOLCHAIN"

if [ "$2" = "noreboot" ] || [ "$1" = "-anr" ] || [ "$1" = "--allnoreboot" ]
then
    NOREBOOT="true"
    echo "Script will not reboot after recovery install!"
else
    NOREBOOT="false"
fi

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
    STARTTIME="$(cat $RDIR/.starttime)"
	DIFFTIME=$(( ENDTIME - STARTTIME ))

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

    rm "$RDIR/localversion" &> /dev/null
	rm "$RDIR/.starttime" &> /dev/null
	rm "$RDIR/.endtime" &> /dev/null
	rm "$RDIR/mxtempusb" &> /dev/null

	find . -type f \( -iname \*.rej \
			-o -iname \*.orig \
			-o -iname \*.bkp \
			-o -iname \*.ko \) \
			| parallel rm -fv {};

}

getmxrecent() {

	local NEEDCOMMIT;
	if [ -f "$BUILDIR/.config" ]
	then
		cp "$BUILDIR/.config" "$MXNEWCFG"
		diff "$MXCONFIG" "$MXNEWCFG"
		if [ "$?" -eq "1" ]
		then
			NEEDCOMMIT="true"
		fi
		[ -f "$MXCONFIG" ] && rm "$MXCONFIG"
		mv "$MXNEWCFG" "$MXCONFIG"
		if [ "$NEEDCOMMIT" = "true" ]
		then
			git add "$MXCONFIG"
			git commit -a -m 'mxconfig updated from build'
		fi
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
	rm "$ZIPFOLDER/boot.img" &>/dev/null
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

checkrecov() {
	lsusb > "$RDIR/mxtempusb"
	if grep -q '04e8:6860' mxtempusb;
	then
		echo "Ensuring System is ready for operations"
		adb "wait-for-device";
		echo "System is Ready"
		echo -n "Reboot into Recovery? [y|n]: "
		read -r RECREBOOT
		if [ "$RECREBOOT" = "y" ]
		then
			echo "Rebooting into TWRP Recovery"
			adb reboot recovery
		fi
	fi
	rm $RDIR/mxtempusb &> /dev/null
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
    echo "$MX_KERNEL_VERSION" > "$RDIR/localversion"

}

rebuild() {

	echo "Using last version. Mark$OLDVER will be removed."
	MX_KERNEL_VERSION="machinexlite-Mark$OLDVER-hltetmo"
    rm "$RDIR/localversion" &> /dev/null
    echo "$MX_KERNEL_VERSION" > "$RDIR/localversion"
	echo "Removing old zip files..."
	rm -f "$RDIR/$MX_KERNEL_VERSION.zip"
	echo "Kernel version is: $MX_KERNEL_VERSION"
	echo "--------------------------------"

}

build_new_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cat "$RDIR/arch/arm/configs/msm8974_sec_hlte_tmo_defconfig" "$RDIR/arch/arm/configs/msm8974_sec_defconfig" "$RDIR/arch/arm/configs/selinux_defconfig" > "$RDIR/arch/arm/configs/mxconfig"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$BUILDIR" menuconfig

}

build_menuconfig() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$BUILDIR" menuconfig

}

build_single_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$BUILDIR" oldconfig || warnandfail "make oldconfig Failed!"

}

build_kernel_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$BUILDIR" || warnandfail "Failed to make $BUILDIR directory!"
	cp "$MXCONFIG" "$BUILDIR/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" O="$BUILDIR" oldconfig || warnandfail "make oldconfig Failed!"
	getmxrecent

}

build_single_driver() {

	echo "Building Single Driver..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -C "$RDIR" -S -s -j16 O="$BUILDIR/" "$1"

}

build_kernel() {
	OLDCFG="/root/mn3-oldconfigs"
	echo "Backing up .config to $OLDCFG/config.$QUICKDATE"
	cp "$BUILDIR/.config" "$OLDCFG/config.$QUICKDATE"
	#echo "Snapshot of current environment variables:"
	#env
	echo -n "$(date +%s)" > "$RDIR/.starttime"
	echo "Starting build..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" -S -s -j16 -C "$RDIR" O="$BUILDIR" || warnandfail "Kernel Build failed!"

}

build_ramdisk() {

	echo "Building ramdisk structure..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
	rm -rf "$BUILDIR/ramdisk" &>/dev/null
	cp -par "$RAMDISKFOLDER" "$BUILDIR/ramdisk" || warnandfail "Failed to create $BUILDIR/ramdisk!"
	cd "$BUILDIR/ramdisk" || warnandfail "Failed to cd to $BUILDIR/ramdisk!"
	mkdir -pm 755 dev proc sys system
	mkdir -pm 771 data
	if [ -f "$KDIR/ramdisk.cpio.gz" ]
	then
		rm "$KDIR/ramdisk.cpio.gz"
	fi
#	find | fakeroot cpio -v -H newc -o | lzop -9 > "$KDIR/ramdisk.cpio.gz"
	echo "Building ramdisk img"
	find | fakeroot cpio -v -o -H newc | gzip -v -9 > "$KDIR/ramdisk.cpio.gz"
	[ ! -f "$KDIR/ramdisk.cpio.gz" ] && warnandfail "NO ramdisk!"
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"

}

build_boot_img() {

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

ADBPUSHLOCATION="/sdcard/Download"
MAGISKFILE="Magisk-v23.0.zip"

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
	if [ ! -f "$RDIR/$MX_KERNEL_VERSION.zip" ]
	then
		warnandfail "$RDIR/$MX_KERNEL_VERSION.zip does not exist!"
	fi
	echo "Kernel $MX_KERNEL_VERSION.zip finished"
	echo "Filepath: "
	echo "$RDIR/$MX_KERNEL_VERSION.zip"
	timerdiff
	if [ -s "$RDIR/$MX_KERNEL_VERSION.zip" ]
	then
		echo -n "$MX_KERNEL_VERSION.zip" > "$RDIR/.lastzip"
		echo "Starting ADB as root."
		adb root
		echo "Checking if Device is Connected..."
		local SAMSTRING
		SAMSTRING="$(lsusb | grep '04e8:6860')"
		RECOVSTRING="$(lsusb | grep '18d1:4ee2')"
		if [ -n "$SAMSTRING" ]
		then
			echo "Device is Connected via Usb in System Mode!"
			echo "$SAMSTRING"
			echo "Ensuring System is ready for operations"
			adb "wait-for-device";
			echo "System is Ready"
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
		elif [ -n "$RECOVSTRING" ]
		then
			echo "Device is Connected via Usb in Recovery Mode!"
			echo "$RECOVSTRING"
			#adb shell input keyevent KEYCODE_WAKEUP
			#adb shell input touchscreen swipe 930 880 930 380
			echo "Ensuring Recovery is ready for operations"
			adb "wait-for-recovery";
			echo "Recovery is Ready"
			echo "Transferring installer via adb to $ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip"
			adb push "$RDIR/$MX_KERNEL_VERSION.zip" "$ADBPUSHLOCATION"
			if [ "$?" -eq "0" ]
			then
				echo "Successfully pushed $RDIR/$MX_KERNEL_VERSION.zip to $ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip over ADB!"
				echo "Installing $ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip via open recovery script"
				adb shell twrp install "$ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip"
                echo "Pushing Magisk to $ADBPUSHLOCATION/$MAGISKFILE"
                adb push "$RDIR/$MAGISKFILE" "$ADBPUSHLOCATION"
				echo "Installing $ADBPUSHLOCATION/$MAGISKFILE via open recovery script"
				adb shell twrp install "$ADBPUSHLOCATION/$MAGISKFILE"
                echo "Removing leftovers"
                adb shell rm "/data/dalvik-cache/arm/dev@tmp@install@common@magisk.apk@classes.dex" &> /dev/null
                adb shell rm "/data/dalvik-cache/arm/data@app@com.topjohnwu.magisk-1@base.apk@classes.dex" &> /dev/null
                adb shell rm "/data/dalvik-cache/profiles/com.topjohnwu.magisk" &> /dev/null
                if [ "$NOREBOOT" = "false" ]
                then
    				echo "Rebooting Device"
        			adb reboot
                else
                    echo "Skipping Reboot due to command line option!"
                fi
			else
				echo "FAILED to push $RDIR/$MX_KERNEL_VERSION.zip to $ADBPUSHLOCATION/$MX_KERNEL_VERSION.zip over ADB!"
			fi
		else
			echo "Device not Connected.  Skipping adb transfer."
			echo "Uploading $MX_KERNEL_VERSION.zip to Google Drive Instead."
			/bin/bash /root/google-drive-upload/upload.sh "$RDIR/$MX_KERNEL_VERSION.zip"
			if [ "$?" -eq "0" ]
			then
				echo "$RDIR/$MX_KERNEL_VERSION.zip upload SUCCESS!"
			else
				echo "$RDIR/$MX_KERNEL_VERSION.zip upload FAILED!"
			fi
		fi
	else
		warnandfail "$RDIR/$MX_KERNEL_VERSION.zip is 0 bytes, something is wrong!"
	fi
	adb kill-server || echo "Failed to kill ADB server!"
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR"
	timerprint "$DIFFTIME"
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

show_help() {

cat << EOF
Machinexlite kernel by robcore
Script written by jcadduono, frequentc & robcore

usage: ./mxbuild.sh [OPTION]
Common options:
 -a|--all            Do a complete build (starting at the beginning)
 -anr|--allnoreboot  Do a complete build (starting at the beginning), do not reboot
 -d|--debug          Same as --all but skips final cleanup
 -r|--rebuildme      Same as --all but defaults to rebuilding previous version
 -b|--bsd            Build single driver (path/to/folder/ | path/to/file.o)
 -c|--clean          Remove everything this build script has done
-nc|--newconfig      Concatecate samsung defconfigs & enter menuconfig
 -m|--menuconfig     Setup an environment for and enter menuconfig
 -k|--kernel         Try the build again starting at compiling the kernel
 -o|--kernel-only    Recompile only the kernel, nothing else
-rd|--ramdisk        Try the build again starting at the ramdisk
 -t|--tests          Testing playground

Extra command line options are possible, with more to be added in the future:
Currently, it is just the one.
Appending "noreboot" as the second option will keep the device from rebooting.
Or, just use the -anr option that is the same as -a to build all,
but skips the reboot.
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
			checkrecov
			handle_existing
			build_all
			break
	    	;;

	     -anr|--allnoreboot)
			checkrecov
			handle_existing
			build_all
			break
	    	;;

	     -d|--debug)
			checkrecov
			handle_existing
			build_debug
			break
	    	;;

	     -r|--rebuildme)
			checkrecov
            handle_existing
			rebuild
			build_all
			break
	    	;;

	     -b|--bsd)
            handle_existing
			bsdwrapper "$extrargs"
			break
	    	;;

	     -c|--clean)
	    	clean_build "standalone"
	    	break
	    	;;
		 -nc|--newconfig)
            handle_existing
			build_new_config
			break
			;;
		 -m|--menuconfig)
            handle_existing
			build_menuconfig
			break
			;;

	     -k|--kernel)
			checkrecov
			handle_existing
	    	build_kernel_and_package
	    	break
	    	;;

	    -o|--kernel-only)
			checkrecov
			handle_existing
	    	build_kernel
	    	break
	    	;;

	     -rd|--ramdisk)
			checkrecov
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
