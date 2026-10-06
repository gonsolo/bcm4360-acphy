#!/usr/bin/env bash
# Run as root BEFORE tools/try_alessio_driver.sh: ship every kernel message live over UDP (netconsole,
# via the USB stick wlp0s20u1) to pampelmuse, so a hard hang still leaves the last lines there
# (receiver: ncat -u -l 6666 > /tmp/laptop-console.log on pampelmuse), plus panic-on-lockup sysctls.
set -u
SRC=$(ip -4 -o addr show dev wlp0s20u1 | awk '{print $4}' | cut -d/ -f1)
MAC=a8:a1:59:2a:46:1b   # pampelmuse
dmesg -n 8
sysctl -q kernel.softlockup_panic=1 kernel.hung_task_panic=1 kernel.panic_on_oops=1 kernel.nmi_watchdog=1 kernel.hardlockup_panic=1 \
	kernel.sysrq=1 kernel.printk_ratelimit=0
modprobe -r netconsole 2>/dev/null
modprobe netconsole netconsole="6665@$SRC/wlp0s20u1,6666@192.168.0.236/$MAC" || exit 1
sleep 1
echo "<0>ale_logging_setup: netconsole test message from $(hostname)" > /dev/kmsg
sync
echo "netconsole up ($SRC -> 192.168.0.236:6666); check pampelmuse:/tmp/laptop-console.log"
