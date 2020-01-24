#!/sbin/busybox sh
    mkdir /data/dontpanic 0750 root log
    chown root log /data/dontpanic/apanic_console
    chmod 0640 /data/dontpanic/apanic_console
    chown root log /data/dontpanic/apanic_threads
    chmod 0640 /data/dontpanic/apanic_threads
    mkdir /data/misc 01771 system misc
    mkdir /data/misc/adb 02750 system shell
    mkdir /data/misc/audit 02775 audit system
    mkdir /data/misc/bluedroid 0770 bluetooth net_bt_stack
    mkdir /data/misc/bluedroiddump 0770 system system
    mkdir /data/misc/bluetooth 0770 system system
    mkdir /data/misc/keystore 0700 keystore keystore
    mkdir /data/misc/keychain 0771 system system
    mkdir /data/misc/net 0750 root shell
    mkdir /data/misc/radio 0771 system radio
    mkdir /data/misc/sms 0770 system radio
    mkdir /data/misc/zoneinfo 0775 system system
    mkdir /data/misc/vpn 0770 system vpn
    mkdir /data/misc/shared_relro 0771 shared_relro shared_relro
    mkdir /data/misc/systemkeys 0700 system system
    mkdir /data/misc/wifi 0770 wifi wifi
    mkdir /data/misc/wifi/sockets 0770 wifi wifi
    mkdir /data/misc/wifi/wpa_supplicant 0770 wifi wifi
    mkdir /data/misc/wifi_share_profile 0771 wifi system
    mkdir /data/misc/ethernet 0770 system system
    mkdir /data/misc/dhcp 0770 dhcp dhcp
    mkdir /data/misc/user 0771 root root
    mkdir /data/misc/jack 0770 jack system
    chmod 0660 /data/misc/wifi/wpa_supplicant.conf
    chown system wifi /data/misc/wifi/wpa_supplicant.conf
    mkdir /data/local 0751 root root
    mkdir /data/misc/media 0700 media media
    mkdir /data/misc/radio/hatp 0755 radio system
    mkdir /data/local/tmp 0771 shell shell
    mkdir /data/data 0771 system system
    mkdir /data/app-private 0771 system system
    mkdir /data/app-asec 0700 root root
    mkdir /data/app-lib 0771 system system
    mkdir /data/app 0771 system system
    mkdir /data/property 0700 root root
    mkdir /data/log 0775 system log
    chown system log /data/log
    mkdir /data/anr 0775 system system
    chown system system /data/anr
    chmod 0775 /data/log
    chmod 0775 /data/anr
    restorecon /data/log
    restorecon /data/anr
    mkdir /data/dalvik-cache 0771 root root
    mkdir /data/dalvik-cache/profiles 0711 system system
    mkdir /data/resource-cache 0771 system system
    chown system system /data/resource-cache
    chmod 0771 /data/resource-cache
    mkdir /data/lost+found 0770 root root
    restorecon /data/lost+found
    mkdir /data/drm 0770 drm drm
    mkdir /data/mediadrm 0770 mediadrm mediadrm
    mkdir /data/system/databases 0775
    chown system system /data/system/databases
    chmod 0775 /data/system/databases
    mkdir /data/data/.drm 0775
    chown drm system /data/data/.drm
    chmod 0775 /data/data/.drm
    mkdir /data/data/.drm/.playready 0775
    chown drm system /data/data/.drm/.playready
    chmod 0775 /data/data/.drm/.playready
    mkdir /data/security 0700 system system
    mkdir /data/DownFilters       0775 system system
    mkdir /data/DownFilters/Lib   0775 system system
    mkdir /data/DownFilters/Lib64 0775 system system
    mkdir /data/app/mcRegistry 0775 system system
    mkdir /data/bcmnfc 0700 nfc nfc
    mkdir /data/bcmnfc/param 0700 nfc nfc
    mkdir /data/nfc 0700 nfc nfc
    mkdir /data/nfc/param 0700 nfc nfc
