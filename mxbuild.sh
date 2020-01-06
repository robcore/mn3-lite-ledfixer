#!/bin/bash

export CCACHE_DIR="$HOME/.ccache"
export USE_CCACHE="1"
export CCACHE_NLEVELS="8"
env KCONFIG_NOTIMESTAMP=true &>/dev/null

RDIR="/root/mn3lite"
OLDVERFILE="$RDIR/.oldversion"
OLDVER="$(cat $OLDVERFILE)"
LASTZIPFILE="$RDIR/.lastzip"
LASTZIP="$(cat $LASTZIPFILE)"
RAMDISKFOLDER="$RDIR/mxramdisk"
ZIPFOLDER="$RDIR/mxzip"
MXCONFIG="$RDIR/arch/arm/configs/mxconfig"
QUICKMONTHDAY="$(date | awk '{print $2$3}')"
QUICKHOUR="$(date +%l | cut -d " " -f2)"
QUICKMIN="$(date +%S)"
QUICKAMPM="$(date +%p)"
QUICKTIME="$QUICKHOUR:$QUICKMIN${QUICKAMPM}"
QUICKDATE="$QUICKMONTHDAY-$QUICKTIME"
CORECOUNT="$(grep processor /proc/cpuinfo | wc -l)"
KDIR="$RDIR/build/arch/arm/boot"
TOOLCHAIN="/opt/toolchains/arm-cortex_a15-linux-gnueabihf_5.3/bin/arm-cortex_a15-linux-gnueabihf-"
echo -n "$(date +%s)" > "$RDIR/.starttime"
STARTTIME="$(cat $RDIR/.starttime)"

timerprint() {

	local DIFFMINS
	local DIFFSECS

	DIFFMINS=$(bc <<< "(${1}%3600)/60")
	DIFFSECS=$(bc <<< "${1}%60")
	echo -n "Build completed in: "
	printf "$DIFFMINS"
	if [ "$DIFFMINS" = "1" ]
	then
		echo -n " Minute and "
	else
		echo -n " Minutes and "
	fi
	printf "$DIFFSECS"
	if [ "$DIFFSECS" = "1" ]
	then
		echo " Second."
	else
		echo " Second."
	fi

}

timerdiff() {

	echo -n "$(date +%s)" > "$RDIR/.endtime"
	ENDTIME="$(cat $RDIR/.endtime)"
	DIFFTIME=$(( $ENDTIME - $STARTTIME ))
	timerprint "$DIFFTIME"

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

if [ ! -f "$MXCONFIG" ]
then
	warnandfail "$MXCONFIG not found in arm configs!"
fi

if [ ! -d "$RAMDISKFOLDER" ]
then
	warnandfail "$RAMDISKFOLDER not found!"
fi

shortprog() {

	echo -ne "#####               (25%)\r"; \
	sleep 0.4; \
	echo -ne "##########          (50%)\r"; \
	sleep 0.4; \
	echo -ne "###############     (75%)\r"; \
	sleep 0.4; \
	echo -ne "####################(100%)\r"; \
	echo -ne "                          \r"; \
	#echo -ne "\n"

}

longprog() {

	echo -ne "#                       \r"; \
	sleep 0.4; \
	echo -ne "##                      \r"; \
	sleep 0.4; \
	echo -ne "###                     \r"; \
	sleep 0.4; \
	echo -ne "####                    \r"; \
	sleep 0.4; \
	echo -ne "#####                   \r"; \
	sleep 0.4; \
	echo -ne "######                  \r"; \
	sleep 0.4; \
	echo -ne "#######                 \r"; \
	sleep 0.4; \
	echo -ne "########                \r"; \
	sleep 0.4; \
	echo -ne "#########               \r"; \
	sleep 0.4; \
	echo -ne "##########              \r"; \
	sleep 0.4; \
	echo -ne "###########             \r"; \
	sleep 0.4; \
	echo -ne "############            \r"; \
	sleep 0.4; \
	echo -ne "#############           \r"; \
	sleep 0.4; \
	echo -ne "##############          \r"; \
	sleep 0.4; \
	echo -ne "###############         \r"; \
	sleep 0.4; \
	echo -ne "################        \r"; \
	sleep 0.4; \
	echo -ne "#################       \r"; \
	sleep 0.4; \
	echo -ne "##################      \r"; \
	sleep 0.4; \
	echo -ne "###################     \r"; \
	sleep 0.4; \
	echo -ne "####################    \r"; \
	sleep 0.4; \
	echo -ne "#####################   \r"; \
	sleep 0.4; \
	echo -ne "######################  \r"; \
	sleep 0.4; \
	echo -ne "####################### \r"; \
	sleep 0.4; \
	echo -ne "########################\r"; \
	sleep 0.4; \
	echo -ne "                        \r"; \

}

test_funcs() {

	echo "This is a test of the emergency broadcast system."
	echo "This is only a test."
	shortprog
	longprog
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
		NEWVER="$(echo $(expr $(( $OLDVER + 1 ))))"
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
			NEWVER="$(echo $(expr $(( $OLDVER + 1 ))))"
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

takeouttrash() {
	rm $RDIR/.starttime &> /dev/null
	rm $RDIR/.endtime &> /dev/null

	find . -type f \( -iname \*.rej \
			-o -iname \*.orig \
			-o -iname \*.bkp \
			-o -iname \*.ko \) \
			| parallel rm -fv {};

}

clean_build() {


	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	echo -ne "Cleaning build         \r"; \
	make clean &>/dev/null
	echo -ne "Cleaning build.        \r"; \
	make distclean &>/dev/null
	echo -ne "Cleaning build..       \r"; \
	make mrproper &>/dev/null
	echo -ne "Cleaning build...      \r"; \
	takeouttrash &>/dev/null
	echo -ne "Cleaning build....     \r"; \
	rm -rf "$RDIR/build" &>/dev/null
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

build_menuconfig() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="dummyconfigbuild"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	cp "$MXCONFIG" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$RDIR/build" menuconfig

}

build_single_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	MX_KERNEL_VERSION="buildingsingledriver"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	cp "$MXCONFIG" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$RDIR/build" -j "$CORECOUNT" oldconfig || warnandfail "make oldconfig Failed!"

}

build_single_driver() {

	echo "Building Single Driver..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" -S -s -j "$CORECOUNT" O="$RDIR/build/" "$1"

}

build_kernel_config() {

	echo "Creating kernel config..."
	cd "$RDIR" || warnandfail "Failed to cd to $RDIR!"
	mkdir -p "$RDIR/build" || warnandfail "Failed to make $RDIR/build directory!"
	cp "$MXCONFIG" "$RDIR/build/.config" || warnandfail "Config Copy Error!"
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -C "$RDIR" O="$RDIR/build" -j "$CORECOUNT" oldconfig || warnandfail "make oldconfig Failed!"

}

build_kernel() {

	echo "Backing up .config to config.$QUICKDATE"
	cp "build/.config" "config.$QUICKDATE"
	echo "Snapshot of current environment variables:"
	env
	echo "Starting build..."
	make ARCH="arm" CROSS_COMPILE="$TOOLCHAIN" LOCALVERSION="$MX_KERNEL_VERSION" -S -s -C "$RDIR" O="$RDIR/build" -j "$CORECOUNT" || warnandfail "Kernel Build failed!"

}

build_ramdisk() {

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

create_zip() {

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
		/bin/bash /root/google-drive-upload/upload.sh "$RDIR/$MX_KERNEL_VERSION.zip" || warnandfail "$RDIR/$MX_KERNEL_VERSION.zip failed to upload!"
		echo -n "$MX_KERNEL_VERSION.zip" > "$RDIR/.lastzip"
		/bin/bash /bin/robmail "$MX_KERNEL_VERSION.zip uploaded!"
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

usage: ./mx-build.sh [OPTION]
Common options:
 -a|--all            Do a complete build (starting at the beginning)
 -r|--rebuildme      Same as -all but defaults to rebuilding previous version
 -b|--bsd            Build single driver (path/to/folder/ | path/to/file.o)
 -c|--clean          Remove everything this build script has done
 -m|--menu           Setup an environment for and enter menuconfig
 -k|--kernel         Try the build again starting at compiling the kernel
 -o|--kernel-only    Recompile only the kernel, nothing else
 -r|--ramdisk        Try the build again starting at the ramdisk
 -t|--tests          Testing playground
EOF

	exit 1

}

build_ramdisk_continue() {

	build_ramdisk && build_boot_img && create_zip

}

build_kernel_continue() {

	build_kernel && build_ramdisk_continue

}

build_all() {

	clean_build && build_kernel_config && build_kernel_continue && clean_build

}

bsdwrapper() {

	[ -z "$1" ] && warnandfail "Build Single Driver: Missing path/to/folder/ or path/to/file.o"
	clean_build && build_single_config && build_single_driver "$1"
	clean_build

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
	key="$1"
	extrargs="$2"

	case $key in
	     -a|--all)
			handle_existing
			build_all
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
	    	clean_build
	    	break
	    	;;

		 -m|--menu)
			build_mc
			break
			;;

	     -k|--kernel)
			handle_existing
	    	build_kernel_continue
	    	break
	    	;;

	    -o|--kernel-only)
			handle_existing
	    	build_kernel
	    	break
	    	;;

	     -r|--ramdisk)
			handle_existing
	     	build_ramdisk_continue
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
