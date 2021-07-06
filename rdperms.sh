#!/bin/bash

KROOT="/root/mn3lite"
chmod 750 "$KROOT/mxramdisk/init"
chmod 750 "$KROOT/mxramdisk/init.carrier.rc"
chmod 750 "$KROOT/mxramdisk/init.class_main.sh"
chmod 750 "$KROOT/mxramdisk/init.container.rc"
chmod 750 "$KROOT/mxramdisk/init.environ.rc"
chmod 750 "$KROOT/mxramdisk/init.mdm.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.class_core.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.early_boot.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.factory.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.rc"
chmod 750 "$KROOT/mxramdisk/init.qcom.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.ssr.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.syspart_fixup.sh"
chmod 750 "$KROOT/mxramdisk/init.qcom.usb.rc"
chmod 750 "$KROOT/mxramdisk/init.qcom.usb.sh"
chmod 750 "$KROOT/mxramdisk/init.rc"
chmod 750 "$KROOT/mxramdisk/init.target.rc"
chmod 750 "$KROOT/mxramdisk/init.trace.rc"
chmod 750 "$KROOT/mxramdisk/init.usb.rc"
chmod 750 "$KROOT/mxramdisk/init.zygote32.rc"

echo "Permissions fixed!"