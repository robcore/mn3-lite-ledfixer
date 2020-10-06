#!/bin/bash

for MXACDB in Bluetooth_cal.acdb \
General_cal.acdb \
Global_cal.acdb \
Handset_cal.acdb \
Hdmi_cal.acdb \
Headset_cal.acdb \
Speaker_cal.acdb
do
    adb pull "/system/etc/$MXACDB" "/root/mn3lite/mx-audcal/mx_device_acdb/system/etc/$MXACDB"
done
