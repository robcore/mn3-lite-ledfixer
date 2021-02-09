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

chown 0:0 /overlay.d
chmod 700 /overlay.d

chown 0:0 /overlay.d/system
chmod 755 /overlay.d/system

chown 1000:1000 /overlay.d/data
chmod 771 /overlay.d/data

for DDIR in /overlay.d/data/system \
/overlay.d/data/system/secure_storage \
/overlay.d/data/system/secure_storage/com.sec.android.signaturelock \
/overlay.d/data/system/secure_storage/com.samsung.android.securitylogagent \
/overlay.d/data/system/secure_storage/com.sec.knox.store \
/overlay.d/data/system/secure_storage/com.sec.android.service.health \
/overlay.d/data/system/secure_storage/.system.bin.wpa_supplicant
do
    chmod 775 "$DDIR"
    chown 1000:1000 "$DDIR"
done

for DFIL in /overlay.d/data/system/secure_storage/com.sec.android.signaturelock/ss_id \
/overlay.d/data/system/secure_storage/com.samsung.android.securitylogagent/ss_id \
/overlay.d/data/system/secure_storage/com.samsung.android.securitylogagent/ss_data.db \
/overlay.d/data/system/secure_storage/com.sec.knox.store/ss_id \
/overlay.d/data/system/secure_storage/com.sec.android.service.health/ss_id \
/overlay.d/data/system/secure_storage/.system.bin.wpa_supplicant/ss_data.db
do
    chmod 644 "$DFIL"
    chown 1000:1000 "$DFIL"
done

for ODIR in /overlay.d/system/preloadedkiosk \
/overlay.d/system/preloadedkiosk/kioskdefault \
/overlay.d/system/preloadedsso \
/overlay.d/system/etc \
/overlay.d/system/etc/secure_storage \
/overlay.d/system/etc/secure_storage/.system.bin.app_process \
/overlay.d/system/etc/secure_storage/.system.bin.dex2oat \
/overlay.d/system/etc/secure_storage/.system.bin.dexopt \
/overlay.d/system/etc/secure_storage/.system.bin.vold \
/overlay.d/system/etc/secure_storage/.system.bin.wpa_supplicant \
/overlay.d/system/etc/secure_storage/.system.lib.libSecFileServerUnit.so \
/overlay.d/system/etc/secure_storage/.system.lib.libandroid_runtime.so \
/overlay.d/system/etc/secure_storage/.system.lib.libart.so \
/overlay.d/system/etc/secure_storage/.system.lib.libc.so \
/overlay.d/system/etc/secure_storage/.system.lib.libcrypto.so \
/overlay.d/system/etc/secure_storage/.system.lib.libdirencryption.so \
/overlay.d/system/etc/secure_storage/.system.lib.libdvm.so \
/overlay.d/system/etc/secure_storage/.system.lib.libhsvtest.so \
/overlay.d/system/etc/secure_storage/.system.lib.libm.so \
/overlay.d/system/etc/secure_storage/.system.lib.libsec_ecryptfs.so \
/overlay.d/system/etc/secure_storage/.system.lib.libsec_ode_km.so \
/overlay.d/system/etc/secure_storage/.system.lib.libsecure_storage.so \
/overlay.d/system/etc/secure_storage/.system.lib.libsecure_storage_jni.so \
/overlay.d/system/etc/secure_storage/.system.lib.libsqlite.so \
/overlay.d/system/etc/secure_storage/com.policydm \
/overlay.d/system/etc/secure_storage/com.samsung.android.intelligenceservice \
/overlay.d/system/etc/secure_storage/com.samsung.android.personalpage.service \
/overlay.d/system/etc/secure_storage/com.samsung.android.providers.context \
/overlay.d/system/etc/secure_storage/com.samsung.android.securitylogagent \
/overlay.d/system/etc/secure_storage/com.sec.android.app.shealth.heartrate \
/overlay.d/system/etc/secure_storage/com.sec.android.service.health \
/overlay.d/system/etc/secure_storage/com.sec.android.signaturelock \
/overlay.d/system/etc/secure_storage/com.sec.android.spc \
/overlay.d/system/etc/secure_storage/com.sec.knox.store \
/overlay.d/system/etc/secure_storage/system_server
do
    chown 0:0 "$ODIR"
    chmod 755 "$ODIR"
done

for OFIL in /overlay.d/system/preloadedkiosk/kioskdefault/kioskdefault.apk \
/overlay.d/system/preloadedsso/samsungsso.apk_ \
/overlay.d/system/preloadedsso/ssoservice.apk_ \
/overlay.d./system/etc/secure_storage/.system.bin.app_process/ss_id \
/overlay.d./system/etc/secure_storage/.system.bin.dex2oat/ss_id \
/overlay.d./system/etc/secure_storage/.system.bin.dexopt/ss_id \
/overlay.d./system/etc/secure_storage/.system.bin.vold/ss_id \
/overlay.d./system/etc/secure_storage/.system.bin.wpa_supplicant/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libSecFileServerUnit.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libandroid_runtime.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libart.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libc.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libcrypto.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libdirencryption.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libdvm.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libhsvtest.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libm.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libsec_ecryptfs.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libsec_ode_km.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libsecure_storage.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libsecure_storage_jni.so/ss_id \
/overlay.d./system/etc/secure_storage/.system.lib.libsqlite.so/ss_id \
/overlay.d./system/etc/secure_storage/com.policydm/ss_id \
/overlay.d./system/etc/secure_storage/com.samsung.android.intelligenceservice/ss_id \
/overlay.d./system/etc/secure_storage/com.samsung.android.personalpage.service/ss_id \
/overlay.d./system/etc/secure_storage/com.samsung.android.providers.context/ss_id \
/overlay.d./system/etc/secure_storage/com.samsung.android.securitylogagent/ss_id \
/overlay.d./system/etc/secure_storage/com.sec.android.app.shealth.heartrate/ss_id \
/overlay.d./system/etc/secure_storage/com.sec.android.service.health/ss_id \
/overlay.d./system/etc/secure_storage/com.sec.android.signaturelock/ss_id \
/overlay.d./system/etc/secure_storage/com.sec.android.spc/ss_id \
/overlay.d./system/etc/secure_storage/com.sec.knox.store/ss_id \
/overlay.d./system/etc/secure_storage/ss_config \
/overlay.d./system/etc/secure_storage/system_server/ss_id
do
    chown 0:0 "$OFIL"
    chmod 644 "$OFIL"
done
