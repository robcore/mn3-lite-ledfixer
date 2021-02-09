#!/bin/bash

for ODIR in /root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.app_process \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.dex2oat \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.dexopt \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.vold \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.wpa_supplicant \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libSecFileServerUnit.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libandroid_runtime.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libart.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libc.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libcrypto.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libdirencryption.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libdvm.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libhsvtest.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libm.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsec_ecryptfs.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsec_ode_km.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsecure_storage.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsecure_storage_jni.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsqlite.so \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.policydm \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.intelligenceservice \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.personalpage.service \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.providers.context \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.securitylogagent \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.app.shealth.heartrate \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.service.health \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.signaturelock \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.spc \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.knox.store \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/system_server
do
	mkdir -p "$ODIR"
	chmod 755 "$ODIR"
	chown 0:0 "$ODIR"
done

for OFIL in /root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.app_process/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.dex2oat/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.dexopt/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.vold/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.bin.wpa_supplicant/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libSecFileServerUnit.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libandroid_runtime.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libart.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libc.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libcrypto.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libdirencryption.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libdvm.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libhsvtest.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libm.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsec_ecryptfs.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsec_ode_km.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsecure_storage.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsecure_storage_jni.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/.system.lib.libsqlite.so/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.policydm/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.intelligenceservice/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.personalpage.service/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.providers.context/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.samsung.android.securitylogagent/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.app.shealth.heartrate/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.service.health/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.signaturelock/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.android.spc/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/com.sec.knox.store/ss_id \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/ss_config \
/root/mn3lite/mxramdisk/overlay.d/system/etc/secure_storage/system_server/ss_id
do
	touch "$OFIL"
	chmod 644 "$OFIL"
	chown 0:0 "$OFIL"
done

for DDIR in /root/mn3lite/mxramdisk/overlay.d/data/system \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.sec.android.signaturelock \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.samsung.android.securitylogagent \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.sec.knox.store \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.sec.android.service.health \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/.system.bin.wpa_supplicant
do
    mkdir -p "$DDIR"
    chmod 775 "$DDIR"
    chown 1000:1000 "$DDIR"
done

for DFIL in /root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.sec.android.signaturelock/ss_id \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.samsung.android.securitylogagent/ss_id \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.samsung.android.securitylogagent/ss_data.db \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.sec.knox.store/ss_id \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/com.sec.android.service.health/ss_id \
/root/mn3lite/mxramdisk/overlay.d/data/system/secure_storage/.system.bin.wpa_supplicant/ss_data.db
do
    touch "$DFIL"
    chmod 644 "$DFIL"
    chown 1000:1000 "$DFIL"
done
