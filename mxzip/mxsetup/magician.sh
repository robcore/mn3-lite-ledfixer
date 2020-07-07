#!/system/bin/sh

rm -rf /data/magisk_backup*
chown 0:2000 /system/etc/permissions
chmod 755 /system/etc/permissions
chown 0:0 /system/etc/permissions/platform.xml
chmod 644 /system/etc/permissions/platform.xml
twrp install /tmp/Magisk-v20.4.zip
