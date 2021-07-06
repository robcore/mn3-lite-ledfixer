#!/bin/bash

myppr() {
    local PFILE
    if [ -n "$1" ]
    then
        PFILE="$1"
    else
        echo "ERROR! No Patch File Supplied! Exiting!"
        exit 1
    fi

    if patch -F0 -p1 -R < "$PFILE"
    then
        echo "Patch Successfully applied"
    else
        echo "Patch Failed! Exiting!"
        exit 1
    fi
}

myppr /root/mn3lite/patches/0020-workqueue-use-mutex-for-global_cwq-manager-exclusion.patch
myppr /root/mn3lite/patches/0019-workqueue-ROGUE-workers-are-UNBOUND-workers.patch
myppr /root/mn3lite/patches/0018-workqueue-drop-CPU_DYING-notifier-operation.patch
myppr /root/mn3lite/patches/0017-workqueue-reimplement-WQ_HIGHPRI.patch
myppr /root/mn3lite/patches/0016-workqueue-introduce-NR_WORKER_POOLS-and.patch
myppr /root/mn3lite/patches/0015-workqueue-separate-out-worker_pool-flags.patch
myppr /root/mn3lite/patches/0014-workqueue-use-pool-instead-of-gcwq-or-cpu.patch
myppr /root/mn3lite/patches/0013-workqueue-factor-out-worker_pool-from-global_cwq.patch
echo "$0 is complete!"
