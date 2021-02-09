#!/system/bin/sh

[ ! -d /system/etc/init.d ] && mkdir /system/etc/init.d;
chmod -R 755 /system/etc/init.d;
chown -R 0:2000 /system/etc/init.d;

rm -rf /data/magisk_backup*

chmod 755 /data/synapse
chown -R 0:0 /data/synapse
chmod 644 /data/synapse/config.*
chmod -R 755 /data/synapse/actions

if [ -f "/data/synapse/config.json" ]
then
    rm /data/synapse/config.json
fi

if [ -f "/data/dalvik-cache/arm/data@app@com.topjohnwu.magisk-1@base.apk@classes.dex" ]
then
    rm "/data/dalvik-cache/arm/data@app@com.topjohnwu.magisk-1@base.apk@classes.dex"
fi

if [ -f "/data/dalvik-cache/profiles/com.topjohnwu.magisk" ]
then
    rm "/data/dalvik-cache/profiles/com.topjohnwu.magisk"
fi

chown 0:0 /system/priv-app/synapse
chmod 755 /system/priv-app/synapse

chown 0:0 /system/priv-app/synapse/synapse.apk
chmod 644 /system/priv-app/synapse/synapse.apk

chmod 644 /system/etc/permissions/no_secure_storage.xml
chown 0:0 /system/etc/permissions/no_secure_storage.xml
