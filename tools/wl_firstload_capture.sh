#!/usr/bin/env bash
# wlcap.sh : trace wl's first load of this boot, connecting to the 5 GHz BSS. Leaves wl loaded.
PROJ=/home/gonsolo/bcm4360-acphy; DEV=0000:03:00.0
WLKO=/nix/store/mjfzgpskpxa08b3q55rmk4ibfzc1kybp-broadcom-sta-6.30.223.271-63-7.2.9/lib/modules/7.2.9/kernel/net/wireless/wl.ko
STAMP=$(date +%Y%m%d-%H%M%S); OUT="$PROJ/traces/wl-firstload-5g-$STAMP.trace"; LOG="$PROJ/test-logs/wlcap-$STAMP.log"
exec >"$LOG" 2>&1; set -x; date -u
lsmod | grep -q "^wl " && { echo "wl already loaded"; exit 1; }
systemctl stop b43-autorecover 2>/dev/null
sync
rmmod b43 2>/dev/null
echo > /sys/bus/pci/devices/$DEV/driver_override
[ -e /sys/bus/pci/devices/$DEV/driver ] && echo $DEV > /sys/bus/pci/devices/$DEV/driver/unbind
modprobe -r bcma 2>/dev/null; lsmod | grep -E "^(bcma|b43|ssb) "
T=/sys/kernel/tracing
echo 0 > $T/tracing_on; echo nop > $T/current_tracer; echo > $T/trace; echo 131072 > $T/buffer_size_kb
cat >> $T/kprobe_events <<'EOK'
p:wlt/w32 wl:osl_writel val=%di:x32 addr=%si:x64
p:wlt/w16 wl:osl_writew val=%di:x16 addr=%si:x64
p:wlt/w8 wl:osl_writeb val=%di:x8 addr=%si:x64
p:wlt/r32 wl:osl_readl addr=%di:x64
r:wlt/r32r wl:osl_readl ret=$retval:x32
p:wlt/r16 wl:osl_readw addr=%di:x64
r:wlt/r16r wl:osl_readw ret=$retval:x16
p:wlt/r8 wl:osl_readb addr=%di:x64
r:wlt/r8r wl:osl_readb ret=$retval:x8
p:wlt/cfgw wl:osl_pci_write_config off=%si:x32 size=%dx:u32 val=%cx:x32
p:wlt/delay wl:osl_delay us=%di:u32
EOK
echo 1 > $T/events/wlt/enable; echo 1 > $T/tracing_on
echo "wlcap: === INSMOD wl ===" > /dev/kmsg; sync
modprobe cfg80211; insmod $WLKO || { echo "insmod failed"; dmesg | tail -5; }
sleep 6
WLIF=$(for i in /sys/class/net/*; do readlink "$i/device/driver" 2>/dev/null | grep -q '/wl$' && basename "$i"; done | head -1)
echo "wl interface: $WLIF"
if [ -n "$WLIF" ]; then
	nmcli connection delete wl-trace 2>/dev/null
	nmcli connection clone Vodafone-2A84 wl-trace
	nmcli connection modify wl-trace connection.interface-name "$WLIF" connection.autoconnect no 802-11-wireless.band a ipv4.route-metric 900 ipv6.route-metric 900
	nmcli -w 40 connection up wl-trace ifname "$WLIF"
	sleep 25
	"$PROJ/tools/iw/bin/iw" dev "$WLIF" link || true
fi
echo 0 > $T/tracing_on; echo "wlcap: === TRACE STOP ===" > /dev/kmsg
cat $T/per_cpu/cpu*/stats | grep -E "entries|overrun" | paste - - | head
cat $T/trace > "$OUT"; echo 0 > $T/events/wlt/enable; echo > $T/kprobe_events; echo 1408 > $T/buffer_size_kb
wc -l "$OUT"; chown gonsolo:users "$OUT" "$LOG"; sync
nmcli -t -f DEVICE,TYPE,STATE,CONNECTION device
echo "===== DONE (wl stays loaded) ====="
