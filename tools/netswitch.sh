#!/usr/bin/env bash
# Switch the main connection between the internal b43 (wlp3s0b1) and the USB stick (wlp0s20u1).
#
#   sudo tools/netswitch.sh stick     b43 stops being used: the stick becomes the only default route
#                                     (b43 stays loaded but idle and unmanaged, so it cannot grab the route)
#   sudo tools/netswitch.sh b43       give b43 back to NetworkManager and connect it (stick stays as backup)
#   sudo tools/netswitch.sh b43 --reload   same, but reload b43 until a clean init connects (the boot
#                                     service's logic; the stick blinks at every reload)
#   tools/netswitch.sh status         interfaces, default route, and a ping through each wlan
#
# DRY=1 sudo tools/netswitch.sh stick   only prints the commands.
set -u
B43=${B43_IF:-wlp3s0b1}
STICK=${STICK_IF:-wlp0s20u1}
P=${B43_PROJ:-/home/gonsolo/bcm4360-acphy}
run() { if [ "${DRY:-0}" = 1 ]; then echo "+ $*"; else "$@"; fi; }
dev_state() { nmcli -t -f DEVICE,STATE device 2>/dev/null | grep "^$1:" | cut -d: -f2; }
gw_of() { ip -4 route show default dev "$1" 2>/dev/null | awk '{print $3; exit}'; }

status() {
	echo "== devices";  nmcli -t -f DEVICE,STATE,CONNECTION device | grep -E "^($B43|$STICK):" | sed 's/^/   /'
	echo "== default routes"; ip -4 route show default | sed 's/^/   /'
	primary=$(ip -4 route show default | awk '{print $5; exit}')
	for i in "$B43" "$STICK"; do
		if [ "$i" != "$primary" ] && [ -n "$primary" ]; then
			echo "== $i: standby (not pingable while $primary holds the default route: the kernel drops the replies, rp_filter)"
			continue
		fi
		gw=$(gw_of "$i"); [ -z "$gw" ] && gw=$(ip -4 route show default | awk '{print $3; exit}')
		if [ -n "$(ip -4 addr show "$i" 2>/dev/null | grep inet)" ] && [ -n "$gw" ]; then
			printf "== ping via %s -> %s: " "$i" "$gw"
			ping -I "$i" -c 3 -W 2 "$gw" 2>/dev/null | awk -F'/' '/rtt/{print "ok, avg " $5 " ms"} /packet loss/{l=$0} END{if (!seen) print l}' | head -1
			ping -I "$i" -c 1 -W 2 "$gw" >/dev/null 2>&1 || echo "   (no reply)"
		else
			echo "== $i: no IPv4 address"
		fi
	done
	echo "== b43 module: $(lsmod | grep -c '^b43') loaded; recent suspend failures: $(dmesg 2>/dev/null | grep -c 'MAC suspend failed')"
}

[ "${1:-status}" = status ] && { status; exit 0; }
[ "$(id -u)" = 0 ] || [ "${DRY:-0}" = 1 ] || { echo "run with sudo"; exit 1; }

case "$1" in
stick)
	[ "$(dev_state "$STICK")" = connected ] || run nmcli device connect "$STICK"
	run nmcli device disconnect "$B43"
	run nmcli device set "$B43" managed no
	[ "${DRY:-0}" = 1 ] || sleep 3
	echo "now using the stick ($STICK); b43 is idle. Back to b43: sudo $0 b43"
	[ "${DRY:-0}" = 1 ] || status
	;;
b43)
	run nmcli device set "$B43" managed yes
	if [ "${2:-}" = --reload ] || [ "$(lsmod | grep -c '^b43')" = 0 ]; then
		run rmmod b43 2>/dev/null
		run systemctl restart b43-ac-load.service
		echo "reloading b43 until it connects (a few minutes at most; follow with: journalctl -fu b43-ac-load)"
	else
		run nmcli device connect "$B43"
	fi
	[ "${DRY:-0}" = 1 ] || { sleep 5; status; }
	;;
*)
	sed -n 2,13p "$0"; exit 1;;
esac
