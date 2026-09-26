#!/usr/bin/env bash
# Capture wl's complete register-access sequence for a full device init.
# Unbinds and rebinds 0000:03:00.0 while wl.ko stays loaded (unloading the
# module would remove the probes). Run as root via systemd-run:
#
#   sudo systemd-run --unit=wltrace --collect --no-block \
#     --setenv=PATH="$PATH" /run/current-system/sw/bin/bash trace_wl.sh
#
# If WiFi is not back afterwards, the script reboots.

PROJ=/home/gonsolo/bcm4360-acphy
DEV=0000:03:00.0
STAMP=$(date +%Y%m%d-%H%M%S)
mkdir -p "$PROJ/traces"
TRACE="$PROJ/traces/wl-init-$STAMP.trace"
exec >"$PROJ/traces/wl-init-$STAMP.meta" 2>&1
set -x

# Give the Claude session time to send its reply before WiFi drops.
sleep 5

sysctl -w kernel.panic_on_oops=1 kernel.panic=10 \
	kernel.hung_task_panic=1 kernel.hung_task_timeout_secs=30 \
	kernel.softlockup_panic=1

BPFTRACE_PERF_RB_PAGES=16384 bpftrace "$PROJ/wl_full_trace.bt" >"$TRACE" 2>&1 &
BT=$!
# Wait until the probes are attached.
for i in $(seq 1 30); do
	grep -q "wl trace start" "$TRACE" && break
	sleep 1
done
grep -q "wl trace start" "$TRACE" || { echo "bpftrace did not start"; kill $BT; exit 1; }

echo "wltrace: === UNBIND ===" > /dev/kmsg
echo "$DEV" > /sys/bus/pci/drivers/wl/unbind
sleep 2
echo "wltrace: === BIND ===" > /dev/kmsg
echo "$DEV" > /sys/bus/pci/drivers/wl/bind

# Let NetworkManager reassociate so the trace covers the channel set too.
sleep 20
echo "wltrace: === STOP ===" > /dev/kmsg
kill -INT $BT
wait $BT
sync

readlink -f /sys/bus/pci/devices/$DEV/driver
nmcli -t -f DEVICE,STATE device
dmesg | sed -n '/wltrace: === UNBIND ===/,$p'

if readlink /sys/bus/pci/devices/$DEV/driver | grep -q '/wl$' &&
   nmcli -t -f STATE general | grep -q '^connected'; then
	echo "===== WiFi is back ====="
	sysctl -w kernel.panic_on_oops=0 kernel.panic=0 \
		kernel.hung_task_panic=0 kernel.hung_task_timeout_secs=120 \
		kernel.softlockup_panic=0
	sync
else
	echo "===== WiFi NOT back, rebooting ====="
	journalctl --sync
	sync
	systemctl reboot
fi
