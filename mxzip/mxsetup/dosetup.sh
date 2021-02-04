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

chmod 755 /system/priv-app/synapse
chown 0:0 /system/priv-app/synapse

chmod 644 /system/priv-app/synapse/synapse.apk
chown 0:0  /system/priv-app/synapse/synapse.apk

rm -rf /system/app/SecurityLogAgent
rm -rf /system/priv-app/DiagMonAgent
rm -rf /system/priv-app/FotaClient
rm -rf /system/app/LocalFOTA
rm -rf /system/app/SecKidsModeInstaller
rm -rf /system/priv-app/SPDClient
rm -rf /system/container/*
rm -rf /system/app/Bloomberg
rm -rf /system/app/ChatON_MARKET_Canada
rm -rf /system/app/Hangouts
rm -rf /system/app/Peel_L
rm -rf /system/app/PlusOne
rm -rf /system/app/BellMobileTVStub_New_Icon
rm -rf /system/app/BellMobileTVStub_New_Icon
rm -rf /system/app/BellWallet_1.0_stub_new_icon
rm -rf /system/app/Fido-Ringtones
rm -rf /system/app/Fido-Shop
rm -rf /system/app/FidoAppZone_v1.0.25.2-ZA
rm -rf /system/app/Generic_citytv-stub-signed-aligned
rm -rf /system/app/Koodo_SelfServe_Virtual_PreLoad_Signed
rm -rf /system/app/MyAccountStub_v2.0
rm -rf /system/app/MyAccount_v3.2.1
rm -rf /system/app/MyBellStub
rm -rf /system/app/My_Account-android-fido-prod-ZA
rm -rf /system/app/BellMobileTVStub_New_Icon
rm -rf /system/app/BellWallet_1.0_stub_new_icon
rm -rf /system/app/Fido-Ringtones
rm -rf /system/app/Fido-Shop
rm -rf /system/app/FidoAppZone_v1.0.25.2-ZA
rm -rf /system/app/Generic_citytv-stub-signed-aligned
rm -rf /system/app/Koodo_SelfServe_Virtual_PreLoad_Signed
rm -rf /system/app/MyAccountStub_v2.0
rm -rf /system/app/MyAccount_v3.2.1
rm -rf /system/app/MyBellStub
rm -rf /system/app/My_Account-android-fido-prod-ZA
rm -rf /system/app/Navigator_Stub
rm -rf /system/app/Push_To_Talk
rm -rf /system/app/Rogers-Navigator
rm -rf /system/app/Rogers-OneNumber
rm -rf /system/app/Rogers-Ringtones
rm -rf /system/app/Rogers-Shop
rm -rf /system/app/RogersAppZone_v1.0.25.2-ZA
rm -rf /system/app/Samsung_Note_3_KitKat_AnyplaceTV
rm -rf /system/app/Samsung_Note_3_KitKat_Fido_Navigator
rm -rf /system/app/TELUSFeaturedApps_v1.0_Signed_Prod_App
rm -rf /system/app/Telus_MyAccount_Virtual_PreLoad_Singed_May10
rm -rf /system/app/TopHDGames_HUB_SamsungH_EN_Rogers_CA_100
rm -rf /system/app/TopHDGames_HUB_SamsungH_EN_Rogers_CA_100/lib
rm -rf /system/app/TopHDGames_HUB_SamsungH_EN_Rogers_CA_100/lib/arm
rm -rf /system/app/videotron-android
