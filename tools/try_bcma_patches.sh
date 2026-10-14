#!/usr/bin/env bash
# Run as root. Replace the stock bcma by a build with Alessio's bcma patches (b43-src-builds/ale8-bcma-<uname -r>.ko),
# then load our b43 through the normal service. Does not touch the stick (wlp0s20u1).
#   sudo tools/try_bcma_patches.sh           swap in the patched bcma, restart our b43
#   sudo tools/try_bcma_patches.sh restore   back to the stock bcma
set -u
PROJ=/home/gonsolo/bcm4360-acphy
DEV=0000:03:00.0
rmmod b43 2>/dev/null
[ -e /sys/bus/pci/devices/$DEV/driver ] && echo $DEV > /sys/bus/pci/devices/$DEV/driver/unbind
rmmod bcma 2>/dev/null
if [ "${1:-}" = restore ]; then modprobe bcma; else insmod $PROJ/b43-src-builds/ale8-bcma-$(uname -r).ko || exit 1; fi
systemctl restart b43-ac-load.service
