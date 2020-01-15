#!/system/bin/sh

for FD in $(ls /proc/$$/fd); do
  if readlink /proc/$$/fd/$FD | grep -q pipe; then
    if ps | grep -v grep | grep -q " 3 $FD "; then
      OUTFD=$FD
      break
    fi
  fi
done

ui_print() {
  echo -e "ui_print $1\nui_print" >> /proc/self/fd/$OUTFD
}

cd /tmp || 	ui_print "mxmagisk ERROR! Failed to switch directories!"

if [ ! -f "/tmp/boot_patch.sh" ] || \
[ ! -f "/tmp/magiskboot" ] || \
[ ! -f "/tmp/magiskinit" ] || \
[ ! -f "/tmp/mxmagisk.sh" ] || \
[ ! -f "/tmp/util_functions.sh" ]; then
	ui_print "mxmagisk ERROR! Missing files!"
	exit 1
fi

ui_print "mxmagisk - running magisk boot patch script"

./boot_patch.sh "boot.img"

if [ ! -f "new-boot.img" ]; then
	ui_print "mxmagisk ERROR! Failed to patch boot.img!"
	exit 1
fi

ui_print "mxmagisk - flashing patched boot.img"

dd if="new-boot.img" of="/dev/block/platform/msm_sdcc.1/by-name/boot"

ui_print "Finished! Back to the main process!"

