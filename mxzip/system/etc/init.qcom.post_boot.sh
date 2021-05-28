#!/system/bin/sh
# Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
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

target=`getprop ro.board.platform`

case "$target" in
    "msm8974")
        # Permissions for Camera to flush cache buffers
        chown -h system.system /sys/devices/virtual/sec/sec_misc/drop_caches
        echo 4 > /sys/module/lpm_levels/enable_low_power/l2
        echo 1 > /sys/module/msm_pm/modes/cpu0/power_collapse/suspend_enabled
        echo 1 > /sys/module/msm_pm/modes/cpu1/power_collapse/suspend_enabled
        echo 1 > /sys/module/msm_pm/modes/cpu2/power_collapse/suspend_enabled
        echo 1 > /sys/module/msm_pm/modes/cpu3/power_collapse/suspend_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu0/power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu1/power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu2/power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu3/power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu0/standalone_power_collapse/suspend_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu1/standalone_power_collapse/suspend_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu2/standalone_power_collapse/suspend_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu3/standalone_power_collapse/suspend_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu0/standalone_power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu1/standalone_power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu2/standalone_power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu3/standalone_power_collapse/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu0/retention/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu1/retention/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu2/retention/idle_enabled
        echo 0 > /sys/module/msm_pm/modes/cpu3/retention/idle_enabled
        echo 0 > /sys/module/msm_thermal/core_control/enabled
        echo 1 > /sys/devices/system/cpu/cpu1/online
        echo 1 > /sys/devices/system/cpu/cpu2/online
        echo 1 > /sys/devices/system/cpu/cpu3/online
        echo "interactive" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
        echo "interactive" > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
        echo "interactive" > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor
        echo "interactive" > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor

        echo 0 > /proc/sys/kernel/sched_wake_to_idle
        if [ -f /sys/devices/soc0/soc_id ]; then
            soc_id=`cat /sys/devices/soc0/soc_id`
        else
            soc_id=`cat /sys/devices/system/soc/soc0/id`
        fi

        # Change msm_pm sysfs permission
        chmod -h 0664 /sys/module/msm_pm/modes/cpu0/power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu1/power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu2/power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu3/power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu0/retention/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu1/retention/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu2/retention/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu3/retention/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu0/standalone_power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu1/standalone_power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu2/standalone_power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu3/standalone_power_collapse/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu0/wfi/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu1/wfi/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu2/wfi/*
        chmod -h 0664 /sys/module/msm_pm/modes/cpu3/wfi/*

        if [ "$soc_id" != "0" ]; then
            # Set default governor as interactive
            # Change governor to interactive
            echo "interactive" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
            echo "interactive" > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
            echo "interactive" > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor
            echo "interactive" > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor
            # Change interactive sysfs permission
            # Change cpu-boost sysfs permission
			echo 0 > /sys/module/cpu_boost/parameters/input_boost_ms
			echo 0 > /sys/module/cpu_boost/parameters/input_boost_freq
			echo 0 > /sys/module/cpu_boost/parameters/sync_threshold
			echo 0 > /sys/module/cpu_boost/parameters/boost_ms
            product_name=`getprop ro.product.name`
        else
            echo "interactive" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
            echo "interactive" > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
            echo "interactive" > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor
            echo "interactive" > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor
        fi

	case "$soc_id" in
	"208" | "211" | "214" | "217" | "209" | "212" | "215" | "218" | "194" | "210" | "213" | "216")
		echo cpubw_hwmon > /sys/class/devfreq/0.qcom,cpubw/governor

		# Change cpubw sysfs permission
		chown radio.system /sys/class/devfreq/0.qcom,cpubw/available_frequencies
		chown radio.system /sys/class/devfreq/0.qcom,cpubw/available_governors
		chown radio.system /sys/class/devfreq/0.qcom,cpubw/governor
		chown radio.system /sys/class/devfreq/0.qcom,cpubw/max_freq
		chown radio.system /sys/class/devfreq/0.qcom,cpubw/min_freq
		chown -h system.system /sys/class/devfreq/0.qcom,cpubw/cpubw_hwmon/guard_band_mbps
		chown -h system.system /sys/class/devfreq/0.qcom,cpubw/cpubw_hwmon/io_percent
		chmod -h 0664 /sys/class/devfreq/0.qcom,cpubw/available_frequencies
		chmod -h 0664 /sys/class/devfreq/0.qcom,cpubw/available_governors
		chmod -h 0664 /sys/class/devfreq/0.qcom,cpubw/governor
		chmod -h 0664 /sys/class/devfreq/0.qcom,cpubw/max_freq
		chmod -h 0664 /sys/class/devfreq/0.qcom,cpubw/min_freq
		chmod -h 0660 /sys/class/devfreq/0.qcom,cpubw/cpubw_hwmon/guard_band_mbps
		chmod -h 0660 /sys/class/devfreq/0.qcom,cpubw/cpubw_hwmon/io_percent
	esac

        chown system /sys/class/kgsl/kgsl-3d0/min_pwrlevel
        chown system /sys/class/kgsl/kgsl-3d0/max_pwrlevel
        chmod 664 /sys/class/kgsl/kgsl-3d0/min_pwrlevel
        chmod 664 /sys/class/kgsl/kgsl-3d0/max_pwrlevel

        echo 300000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
        echo 300000 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq
        echo 300000 > /sys/devices/system/cpu/cpu2/cpufreq/scaling_min_freq
        echo 300000 > /sys/devices/system/cpu/cpu3/cpufreq/scaling_min_freq
        chown -h system /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
        chown -h system /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
        chown -h root.system /sys/devices/system/cpu/mfreq
        chmod -h 220 /sys/devices/system/cpu/mfreq
        chown -h root.system /sys/devices/system/cpu/cpu1/online
        chown -h root.system /sys/devices/system/cpu/cpu2/online
        chown -h root.system /sys/devices/system/cpu/cpu3/online
        chmod -h 664 /sys/devices/system/cpu/cpu1/online
        chmod -h 664 /sys/devices/system/cpu/cpu2/online
        chmod -h 664 /sys/devices/system/cpu/cpu3/online
        echo 1 > /dev/cpuctl/apps/cpu.notify_on_migrate

        # Change PM debug parameters permission
        chown -h system.system /sys/module/qpnp_power_on/parameters/reset_enabled
        chown -h system.system /sys/module/qpnp_power_on/parameters/wake_enabled
        chown -h system.system /sys/module/qpnp_int/parameters/debug_mask
        chown -h system.system /sys/module/lpm_levels/parameters/secdebug
        chmod -h 664 /sys/module/qpnp_power_on/parameters/reset_enabled
        chmod -h 664 /sys/module/qpnp_power_on/parameters/wake_enabled
        chmod -h 664 /sys/module/qpnp_int/parameters/debug_mask
        chmod -h 664 /sys/module/lpm_levels/parameters/secdebug
        chmod -h 444 /sys/kernel/wakeup_reasons/last_resume_reason

        # Permissions for Audio
        chown system.system /sys/devices/fe12f000.slim/es705-codec-gen0/keyword_grammar_path
        chown system.system /sys/devices/fe12f000.slim/es705-codec-gen0/keyword_net_path

        # control daemon for xosd
        factory_mode=`getprop ro.factory.factory_binary`
        if [ "$factory_mode" != "factory" ]; then
            case "$product_name" in
                hlte* | klte* | slte*)
                    jig_mode=`cat /sys/class/switch/uart3/state`
                    case "$jig_mode" in
                    1)
                        echo "PM: JIG UART" > /dev/kmsg
                    ;;
                    0)
                        echo "PM: stop at_distributor" > /dev/kmsg
                        stop at_distributor
                    ;;
                    esac
                ;;
            esac
        fi

    ;;
esac

emmc_boot=`getprop ro.boot.emmc`
case "$emmc_boot"
    in "true")
        chown -h system /sys/devices/platform/rs300000a7.65536/force_sync
        chown -h system /sys/devices/platform/rs300000a7.65536/sync_sts
        chown -h system /sys/devices/platform/rs300100a7.65536/force_sync
        chown -h system /sys/devices/platform/rs300100a7.65536/sync_sts
    ;;
esac

case "$target" in
    "msm8226" | "msm8974" | "msm8610" | "apq8084" | "mpq8092" | "msm8610")
        # Let kernel know our image version/variant/crm_version
        image_version="10:"
        image_version+=`getprop ro.build.id`
        image_version+=":"
        image_version+=`getprop ro.build.version.incremental`
        image_variant=`getprop ro.product.name`
        image_variant+="-"
        image_variant+=`getprop ro.build.type`
        oem_version=`getprop ro.build.version.codename`
        echo 10 > /sys/devices/soc0/select_image
        echo $image_version > /sys/devices/soc0/image_version
        echo $image_variant > /sys/devices/soc0/image_variant
        echo $oem_version > /sys/devices/soc0/image_crm_version
        ;;
esac
