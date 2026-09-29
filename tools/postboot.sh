#!/usr/bin/env bash
# After every reboot, before any b43 experiment (or just for daily use):
# runtime udev override that stops wpa_supplicant restarts on wlan
# add/remove, plus the ping watchdog and the connect-failure auto-recovery
# watchdog (notes/86 Phase 2a).
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
systemctl is-active --quiet b43-autorecover || systemd-run --unit=b43-autorecover --collect \
	--setenv=PATH="$PATH:$P/tools/iw/bin" /run/current-system/sw/bin/bash $P/tools/b43_autorecover.sh
sleep 1
echo "udev override: $(ls /run/udev/rules.d/99-zz-no-wpa-restart.rules)  netwatch: $(systemctl is-active netwatch)  b43-autorecover: $(systemctl is-active b43-autorecover)"
