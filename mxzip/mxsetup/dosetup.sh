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

#rm -rf /system/app/SecurityLogAgent &> /dev/null
#rm -rf /system/priv-app/DiagMonAgent &> /dev/null
#rm -rf /system/priv-app/FotaClient &> /dev/null
#rm -rf /system/app/LocalFOTA &> /dev/null
#rm -rf /system/app/SecKidsModeInstaller &> /dev/null
#rm -rf /system/priv-app/SPDClient &> /dev/null
#rm -rf /system/container/* &> /dev/null
#rm -rf /system/app/Bloomberg &> /dev/null
#rm -rf /system/app/ChatON_MARKET_Canada &> /dev/null
#rm -rf /system/app/Hangouts &> /dev/null
#rm -rf /system/app/Peel_L &> /dev/null
#rm -rf /system/app/PlusOne &> /dev/null
#rm -rf /system/app/BellMobileTVStub_New_Icon &> /dev/null
#rm -rf /system/app/BellMobileTVStub_New_Icon &> /dev/null
#rm -rf /system/app/BellWallet_1.0_stub_new_icon &> /dev/null
#rm -rf /system/app/Fido-Ringtones &> /dev/null
#rm -rf /system/app/Fido-Shop &> /dev/null
#rm -rf /system/app/FidoAppZone_v1.0.25.2-ZA &> /dev/null
#rm -rf /system/app/Generic_citytv-stub-signed-aligned &> /dev/null
#rm -rf /system/app/Koodo_SelfServe_Virtual_PreLoad_Signed &> /dev/null
#rm -rf /system/app/MyAccountStub_v2.0 &> /dev/null
#rm -rf /system/app/MyAccount_v3.2.1 &> /dev/null
#rm -rf /system/app/MyBellStub &> /dev/null
#rm -rf /system/app/My_Account-android-fido-prod-ZA &> /dev/null
#rm -rf /system/app/BellMobileTVStub_New_Icon &> /dev/null
#rm -rf /system/app/BellWallet_1.0_stub_new_icon &> /dev/null
#rm -rf /system/app/Fido-Ringtones &> /dev/null
#rm -rf /system/app/Fido-Shop &> /dev/null
#rm -rf /system/app/FidoAppZone_v1.0.25.2-ZA &> /dev/null
#rm -rf /system/app/Generic_citytv-stub-signed-aligned &> /dev/null
#rm -rf /system/app/Koodo_SelfServe_Virtual_PreLoad_Signed &> /dev/null
#rm -rf /system/app/MyAccountStub_v2.0 &> /dev/null
#rm -rf /system/app/MyAccount_v3.2.1 &> /dev/null
#rm -rf /system/app/MyBellStub &> /dev/null
#rm -rf /system/app/My_Account-android-fido-prod-ZA &> /dev/null
#rm -rf /system/app/Navigator_Stub &> /dev/null
#rm -rf /system/app/Push_To_Talk &> /dev/null
#rm -rf /system/app/Rogers-Navigator &> /dev/null
#rm -rf /system/app/Rogers-OneNumber &> /dev/null
#rm -rf /system/app/Rogers-Ringtones &> /dev/null
#rm -rf /system/app/Rogers-Shop &> /dev/null
#rm -rf /system/app/RogersAppZone_v1.0.25.2-ZA &> /dev/null
#rm -rf /system/app/Samsung_Note_3_KitKat_AnyplaceTV &> /dev/null
#rm -rf /system/app/Samsung_Note_3_KitKat_Fido_Navigator &> /dev/null
#rm -rf /system/app/TELUSFeaturedApps_v1.0_Signed_Prod_App &> /dev/null
#rm -rf /system/app/Telus_MyAccount_Virtual_PreLoad_Singed_May10 &> /dev/null
#rm -rf /system/app/TopHDGames_HUB_SamsungH_EN_Rogers_CA_100 &> /dev/null
#rm -rf /system/app/TopHDGames_HUB_SamsungH_EN_Rogers_CA_100/lib &> /dev/null
#rm -rf /system/app/TopHDGames_HUB_SamsungH_EN_Rogers_CA_100/lib/arm &> /dev/null
#rm -rf /system/app/videotron-android &> /dev/null
