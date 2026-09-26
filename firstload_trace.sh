#!/usr/bin/env bash
# One-shot boot: trace wl's very first load on an untouched chip (attach,
# power-on init, first calibrations), which the ifdown/ifup trace misses.
# wl is blacklisted in this generation; kprobe events defined on the
# not-yet-loaded module arm when we modprobe it. wl stays loaded afterwards,
# so the machine keeps working WiFi and doesn't need to reboot.
PROJ=/home/gonsolo/bcm4360-acphy
GOOD_GEN=/nix/store/9rhwm6526aq8nlilicalmjgsbvvvgv81-nixos-system-zitrone-26.05.10529.c508844df6c2
STAMP=$(date +%Y%m%d-%H%M%S)
mkdir -p "$PROJ/test-logs" "$PROJ/traces"
LOG="$PROJ/test-logs/firstload-5g-$STAMP.log"
OUT="$PROJ/traces/wl-firstload-5g-$STAMP.trace"
exec >"$LOG" 2>&1
set -x
date -u

# SAFETY FIRST: next boot goes to the normal generation whatever happens.
"$GOOD_GEN/bin/switch-to-configuration" boot
sync

if lsmod | grep -q "^wl "; then
	echo "wl already loaded at boot - blacklist failed; not tracing"
	exit 0
fi

T=/sys/kernel/tracing
echo 0 > $T/tracing_on
echo nop > $T/current_tracer
echo > $T/trace
echo 262144 > $T/buffer_size_kb
cat >> $T/kprobe_events <<'EOF'
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
EOF
cat $T/kprobe_events
echo 1 > $T/events/wlt/enable
echo 1 > $T/tracing_on
echo "wlfirst: === MODPROBE wl ===" > /dev/kmsg

modprobe wl
sleep 5
ip link

# Connect wl to the home network too (the USB stick may hold the main profile).
WLIF=$(for i in /sys/class/net/*; do readlink "$i/device/driver" 2>/dev/null | grep -q '/wl$' && basename "$i"; done | head -1)
echo "wl interface: $WLIF"
nmcli connection delete wl-trace 2>/dev/null
nmcli connection clone Vodafone-2A84 wl-trace
nmcli connection modify wl-trace connection.interface-name "$WLIF" connection.autoconnect no 802-11-wireless.band a ipv4.route-metric 900 ipv6.route-metric 900
nmcli connection up wl-trace ifname "$WLIF"
sleep 40
"$PROJ/tools/iw/bin/iw" dev "$WLIF" link || true
nmcli -f GENERAL.CONNECTION,WIFI-PROPERTIES.5GHZ dev show "$WLIF" || true

echo 0 > $T/tracing_on
echo "wlfirst: === TRACE STOP ===" > /dev/kmsg
cat $T/per_cpu/cpu*/stats | grep -E "entries|overrun" | paste - - | head
cat $T/trace > "$OUT"
echo 0 > $T/events/wlt/enable
echo > $T/kprobe_events
wc -l "$OUT"
xz -T0 -k "$OUT"
nmcli -t -f DEVICE,TYPE,STATE,CONNECTION device
chown -R gonsolo:users "$PROJ/traces" "$PROJ/test-logs"
sync
echo "===== DONE (no reboot; wl stays loaded) ====="
