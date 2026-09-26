#!/usr/bin/env bash
# Network watchdog for b43 experiments: if the router stops answering pings
# (10 failures in a row, ~25 s; ignores short reconnect blips), unload b43 and remove the stick's monitor interfaces.
# Run detached: sudo systemd-run --unit=netwatch --setenv=PATH="$PATH" bash tools/netwatch.sh
LOG=/home/gonsolo/bcm4360-acphy/test-logs/netwatch.log
fails=0
echo "$(date) netwatch start" >> "$LOG"
while true; do
	if ping -c1 -W2 192.168.0.1 > /dev/null 2>&1; then
		fails=0
	else
		fails=$((fails + 1))
		echo "$(date) ping failed ($fails)" >> "$LOG"
	fi
	if [ $fails -ge 10 ]; then
		echo "$(date) network down: unloading b43, removing monitor vifs" >> "$LOG"
		echo "netwatch: network down, unloading b43" > /dev/kmsg
		rmmod b43 2>> "$LOG"
		for m in mon0 mon1; do iw dev $m del 2>/dev/null || ip link del $m 2>/dev/null; done
		fails=0
		sleep 20
	fi
	sleep 2
done
