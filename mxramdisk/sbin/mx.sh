#!/system/bin/sh
# Copyright (c) 2009-2012, The Linux Foundation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of The Linux Foundation nor
#       the names of its contributors may be used to endorse or promote
#       products derived from this software without specific prior written
#       permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Removed Generalized BULLSHIT and kept our device specific props

export PATH=${PATH}:/sbin:/system/bin:/system/xbin
#export PATH=/sbin:/system/bin:/system/xbin:/res/synapse/actions:$PATH

#Supersu
#if [ -e /system/xbin/daemonsu ]; then
#	/system/xbin/daemonsu --daemon &
#fi

#if [ ! -L "/sbin/ueventd" ] && [ ! -L "/root/ueventd" ] || [ ! -L "/sbin/watchdogd" ] && [ ! -L "/root/watchdogd" ]
if [ ! -L "/root/ueventd" ] || [ ! -L "/root/watchdogd" ]
then
	mount -o remount,rw -t auto /
fi

if [ ! -L "/root/ueventd" ]
then
	#ln -s /init /sbin/ueventd
	ln -s /init /root/ueventd
fi

if [ ! -L "/root/watchdogd" ]
then
	#ln -s /init /sbin/watchdogd
	ln -s /init /root/watchdogd
fi
#mount -o remount,rw -t auto /
#mount -t rootfs -o remount,rw rootfs
#mount -o remount,rw /system

chown 0:0 "/sbin/sqlite3"
chmod 755 "/sbin/sqlite3"
chown 0:0 "/sbin/zip"
chmod 755 "/sbin/zip"
#busybox ln -sf $(pwd)/sbin/uci $(pwd)/res/synapse/uci

#if [ -e /system/robcore ]; then
#	if [ -e /cache/recovery/openrecoveryscript ]; then
#		rm -f /cache/recovery/openrecoveryscript
#	fi
#fi

# Set correct r/w permissions for LMK parameters
chmod 666 /sys/module/lowmemorykiller/parameters/cost
chmod 666 /sys/module/lowmemorykiller/parameters/adj
chmod 666 /sys/module/lowmemorykiller/parameters/minfree
setprop ro.ril.enable.amr.wideband 1
#echo 32 > /sys/module/lowmemorykiller/parameters/cost;

#echo 0 > /sys/module/subsystem_restart/parameters/enable_ramdumps;

# Synapse
#chown -R 0:0 /data/.machinex
#chmod -R 777 /data/.machinex
#chown -R 0:0 /sdcard/machinex
#chmod -R 777 /sdcard/machinex


#echo 5120 > /proc/sys/vm/min_free_kbytes;
#Insecure adb...shhhh
#stop adbd
#cat /system/bin/sh > /sbin/adbdsh
#chown 0.0 /sbin/adbdsh
#chmod 0750 /sbin/adbdsh
#if [ -e /system/xbin/supolicy ]; then
#	/system/xbin/supolicy --live "permissive init_shell" "allow adbd adbd process setcurrent" "allow adbd init process dyntransition" "allow servicemanager { init_shell zygote } dir search" "allow servicemanager { init_shell zygote } file { read open }" "allow servicemanager { init_shell zygote } process getattr" "allow system_server init_shell binder { transfer call }" "allow zygote { servicemanager system_server } binder call"
#fi
#start adbd

#what's the point of building your own kernel if you don't treat yourself?
#if [ -e /system/robcore ]; then
#	echo 2 > /sys/kernel/fast_charge/force_fast_charge;
#	echo 0 > /sys/kernel/fast_charge/failsafe;
#	echo 0 > /sys/kernel/fast_charge/screen_on_current_limit;
#	echo 2100 > /sys/kernel/fast_charge/ac_charge_level;
#	echo 1 > /sys/class/mdnie/mdnie/locked;

#fi

#chown -h system.system /sys/devices/virtual/sec/sec_misc/drop_caches
#chown -h root.root /sys/devices/virtual/sec/sec_misc/mx_drop_caches
#chmod 644 /sys/devices/virtual/sec/sec_misc/mx_drop_caches

#echo 0 > /sys/module/pm_8x60/modes/cpu0/retention/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu1/retention/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu2/retention/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu3/retention/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu0/power_collapse/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu0/standalone_power_collapse/suspend_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu1/standalone_power_collapse/suspend_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu2/standalone_power_collapse/suspend_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu3/standalone_power_collapse/suspend_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu0/standalone_power_collapse/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu1/standalone_power_collapse/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu2/standalone_power_collapse/idle_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu3/standalone_power_collapse/idle_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu0/power_collapse/suspend_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu1/power_collapse/suspend_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu2/power_collapse/suspend_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu3/power_collapse/suspend_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu0/wfi/suspend_enabled;
#echo 0 > /sys/module/pm_8x60/modes/cpu0/wfi/idle_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu1/wfi/idle_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu2/wfi/idle_enabled;
#echo 1 > /sys/module/pm_8x60/modes/cpu3/wfi/idle_enabled;
##emmc_boot=`getprop ro.boot.emmc`
#case "$emmc_boot"
#    in "true")
#        chown -h system /sys/devices/platform/rs300000a7.65536/force_sync
#        chown -h system /sys/devices/platform/rs300000a7.65536/sync_sts
#        chown -h system /sys/devices/platform/rs300100a7.65536/force_sync
#       chown -h system /sys/devices/platform/rs300100a7.65536/sync_sts
#    ;;
#esac

#fastrpc permission setting
#insmod /system/lib/modules/adsprpc.ko
#chown -h system.system /dev/adsprpc-smd
#chmod -h 666 /dev/adsprpc-smd

#echo "[MACHINEX] Machinex Post-Init Finishing Up" | tee /dev/kmsg
#echo 20 > /sys/devices/platform/msm_sdcc.3/idle_timeout
#echo 1 > /sys/module/rpm_resources/enable_low_power/L2_cache;
#echo 1 > /sys/module/rpm_resources/enable_low_power/pxo;
#echo 1 > /sys/module/rpm_resources/enable_low_power/vdd_dig;
#echo 1 > /sys/module/rpm_resources/enable_low_power/vdd_mem;

#echo electrodemand > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor;
#echo 80 > /sys/module/vmpressure/parameters/allocstall_threshold;
#echo 1 > /sys/module/msm_thermal/core_control/enabled;
#echo 1 > /sys/kernel/sound_control_3/gpl_sound_control_enabled;
#if [ -e /system/robcore ]; then
#	echo 10 > /sys/kernel/sound_control_3/gpl_speaker_gain;
#	echo 10 > /sys/kernel/sound_control_3/gpl_headphone_gain;
#else
#	echo 0 > /sys/kernel/sound_control_3/gpl_speaker_gain;
#	echo 0 > /sys/kernel/sound_control_3/gpl_headphone_gain;
#fi

#sed -i 's/\x0//g' /data/.cid.info

#echo 0 > /sys/block/mmcblk0/queue/iostats
#if [ -e /sys/block/mmcblk1/queue/iostats ]; then
#	echo 0 > /sys/block/mmcblk1/queue/iostats
#fi
#chown -R 0:0 /res/synapse
#chmod -R 775 /res/synapse
#
#if [ ! -e /res/synapse/config.json ]; then
#	if [ -e /system/mxdevflag ]; then
#		if [ -d /sys/block/mmcblk1 ]; then
#		    source /res/synapse/config.json.generate_dev > /$config
#		else
#		    source /res/synapse/config.json.xenerate_dev > /$config
#		fi
#	else
#		if [ -d /sys/block/mmcblk1 ]; then
#		    source /res/synapse/config.json.generate > /$config
#		else
#		    source /res/synapse/config.json.xenerate > /$config
#		fi
#	fi
#fi

#chown 0:0 /res/synapse/config.json
#chmod 755 /res/synapse/config.json
#chmod -R 775 /res/synapse
#chmod 775 /sbin/uci

#chown -R 0:0 /data/.machinex
#chmod -R 775 /data/.machinex
#for i in /sys/dev/block/*/queue/read_ahead_kb; do
#	echo 128 > $i;
#	status=$?;
#	if [ $status != 0 ]; then
#	   echo "[MACHINEX] READAHEAD: $status - Unsuccessful" | tee /dev/kmsg;
#	fi;
#done;

#####################################################################
#supolicy --live "allow system_server system_file { get_property list_property set_property x_property \
#property_service get_property list_property set_property domain_no_set_prop property_type km_fips_prop \
#drs_date_prop tlc_mgmt_prop policy_mgmt_prop prop_device property_data_file	 knox_kap_prop system_prop \
#mobicore_prop bt_prop container_mgmt_prop csc_prop nfc_prop vpn_prop debug_prop pan_result_prop security_prop \
#bluetooth_prop ctl_rildaemon_prop system_radio_prop denial_prop ctl_dhcp_pan_prop ctl_bootanim_prop net_radio_prop \
#freq_prop dhcp_prop audio_prop boot_prop ctl_bugreport_prop logd_prop kies_prop vold_prop user_prop tzdaemon_prop rild_prop \
#perf_prop digitalpen_prop recovery_prop ctl_fuse_prop good_mgmt_prop seclevel_prop ctl_mdnsd_prop setupwizard_prop \
#property_socket ctl_default_prop ctl_dumpstate_prop default_prop debuggerd_prop powerctl_prop sdcard_prop radio_prop \
#properties_device secmm_prop shell_prop camera_prop }"

#supolicy --live "allow untrusted_app debugfs file { open read getattr }"
#supolicy --live "allow untrusted_app sysfs_lowmemorykiller file { open read getattr }"
#supolicy --live "allow untrusted_app sysfs_devices_system_iosched file { open read getattr }"
#supolicy --live "allow untrusted_app persist_file dir { open read getattr }"
#supolicy --live "allow debuggerd gpu_device chr_file { open read getattr }"
#supolicy --live "allow netd netd capability fsetid"
#supolicy --live "allow netd { hostapd dnsmasq } process fork"
#supolicy --live "allow { system_app shell } dalvikcache_data_file file write"
#supolicy --live "allow system_server { rootfs resourcecache_data_file } dir { open read write getattr add_name setattr create remove_name rmdir unlink link }"
#supolicy --live "allow system_server resourcecache_data_file file { open read write getattr add_name setattr create remove_name unlink link }"
#supolicy --live "allow system_server dex2oat_exec file rx_file_perms"
#supolicy --live "allow mediaserver mediaserver_tmpfs file execute"
#supolicy --live "allow drmserver theme_data_file file r_file_perms"
#supolicy --live "allow zygote system_file file write"
#supolicy --live "allow atfwd property_socket sock_file write"
#supolicy --live "allow untrusted_app sysfs_display file { open read write getattr add_name setattr remove_name }"
#supolicy --live "allow debuggerd app_data_file dir search"
#supolicy --live "allow sensors diag_device chr_file { read write open ioctl }"
#supolicy --live "allow sensors sensors capability net_raw"
#supolicy --live "allow netmgrd netmgrd netlink_xfrm_socket nlmsg_write"
#supolicy --live "allow netmgrd netmgrd socket { read write open ioctl }"

# Init.d
chown -R 0:0 /system/etc/init.d/
chmod -R 755 /system/etc/init.d/
chmod 755 /sys
supolicy --live "permissive audioserver"
supolicy --live "permissive default_prop"
supolicy --live "permissive *"
#supolicy --live "allow s_untrusted_app default_prop property_service { set }"
#/system/xbin/busybox run-parts /system/etc/init.d/
#echo "[MACHINEX] INIT.D EXECUTED" | tee /dev/kmsg
