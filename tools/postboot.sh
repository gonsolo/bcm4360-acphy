#!/usr/bin/env bash
# After every reboot, before any b43 experiment: runtime udev override that
# stops wpa_supplicant restarts on wlan add/remove, plus the ping watchdog.
# usage: sudo tools/postboot.sh
P=/home/gonsolo/bcm4360-acphy
mkdir -p /run/udev/rules.d
cat > /run/udev/rules.d/99-zz-no-wpa-restart.rules <<'R'
# Runtime-only (b43 experiments): do not restart wpa_supplicant when WiFi
# interfaces come and go; it drops the USB stick connection every time.
ACTION=="add|remove", SUBSYSTEM=="net", ENV{DEVTYPE}=="wlan", RUN:="/run/current-system/sw/bin/true"
R
udevadm control --reload
systemctl is-active --quiet netwatch || systemd-run --unit=netwatch --collect \
	--setenv=PATH="$PATH:$P/tools/iw/bin" /run/current-system/sw/bin/bash $P/tools/netwatch.sh
sleep 1
echo "udev override: $(ls /run/udev/rules.d/99-zz-no-wpa-restart.rules)  netwatch: $(systemctl is-active netwatch)"
