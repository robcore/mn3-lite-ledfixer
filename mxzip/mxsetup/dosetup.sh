#!/system/bin/sh

[ ! -d /system/etc/init.d ] && mkdir /system/etc/init.d;
chmod -R 755 /system/etc/init.d;
chown -R 0:2000 /system/etc/init.d;

rm -rf /data/magisk_backup*

chmod 755 /data/synapse
chown -R 0:0 /data/synapse
chmod 644 /data/synapse/config.*
chmod -R 755 /data/synapse/actions
chmod 755 /data/synapse/stemp
chmod 644 /data/synapse/stemp/*

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

if [ -d "/system/etc/secure_storage" ] && [ ! -d "/system/etc/secure_storage.bak" ]
then
    mv "/system/etc/secure_storage" "/system/etc/secure_storage.bak"
    mkdir "/system/etc/secure_storage"
fi

chmod 755 "/system/etc/secure_storage"
chown 0:0 "/system/etc/secure_storage"

if [ -d "/data/system/secure_storage" ] && [ ! -d "/data/system/secure_storage.bak" ]
then
    mv "/data/system/secure_storage" "/data/system/secure_storage.bak"
    mkdir "/data/system/secure_storage"
fi

chmod 775 "/data/system/secure_storage"
chown 1000:1000 "/data/system/secure_storage"

chown -R 0:0 /system/etc/wifi
chmod 755 /system/etc/wifi
chmod 644 /system/etc/wifi/bcmdhd_apsta.bin
chmod 644 /system/etc/wifi/bcmdhd_ibss.bin
chmod 644 /system/etc/wifi/bcmdhd_mfg.bin
chmod 644 /system/etc/wifi/bcmdhd_sta.bin
chmod 644 /system/etc/wifi/nvram_mfg.txt
chmod 644 /system/etc/wifi/nvram_mfg.txt_murata
chmod 644 /system/etc/wifi/nvram_mfg.txt_muratafem1
chmod 644 /system/etc/wifi/nvram_net.txt
chmod 644 /system/etc/wifi/nvram_net.txt_murata
chmod 644 /system/etc/wifi/nvram_net.txt_muratafem1
chmod 644 /system/etc/wifi/p2p_supplicant_overlay.conf
chmod 644 /system/etc/wifi/WCNSS_qcom_cfg.ini
chmod 644 /system/etc/wifi/wpa_supplicant.conf
chmod 644 /system/etc/wifi/wpa_supplicant_overlay.conf
