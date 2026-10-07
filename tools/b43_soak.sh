#!/usr/bin/env bash
# Soak test for the b43 link (plan 2c): ping the gateway through wlp3s0b1 every 10 s, log outages,
# reconnects and kernel counters. usage: sudo tools/b43_soak.sh <seconds> [logfile]
set -u
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1; GW=${GW:-192.168.0.1}
DUR=${1:?seconds}; LOG=${2:-$P/test-logs/soak_$(date +%m%d_%H%M).log}
sysctl -q net.ipv4.conf.$IF.rp_filter=0
echo "# soak start $(date) dur=${DUR}s module=$(sudo cat /sys/module/b43/parameters/ac_phyreset 2>/dev/null)" | tee "$LOG"
end=$(( $(date +%s) + DUR )); n=0; lost=0; run=0; maxrun=0; recon=0; last=
dm0=$(dmesg | grep -c -E "PHY transmission error|MAC suspend failed|ac_selfheal: bad init")
while [ "$(date +%s)" -lt "$end" ]; do
	n=$((n+1))
	if ping -I $IF -c 1 -W 2 $GW >/dev/null 2>&1; then run=0; r=ok; else lost=$((lost+1)); run=$((run+1)); r=LOST; [ $run -gt $maxrun ] && maxrun=$run; fi
	st=$(nmcli -t -f DEVICE,STATE dev | grep "^$IF:" | cut -d: -f2)
	[ -n "$last" ] && [ "$st" != "$last" ] && { recon=$((recon+1)); echo "$(date +%T) state $last -> $st" | tee -a "$LOG"; }
	last=$st
	[ "$r" = LOST ] && echo "$(date +%T) LOST (run $run) state=$st" >> "$LOG"
	if [ $((n % 30)) -eq 0 ]; then
		dm=$(dmesg | grep -c -E "PHY transmission error|MAC suspend failed|ac_selfheal: bad init")
		echo "$(date +%T) n=$n lost=$lost maxrun=$maxrun transitions=$recon kerr=$((dm-dm0)) $(iw dev $IF station dump 2>/dev/null | awk '/tx retries/{r=$3}/tx packets/{p=$3}END{print "txpk="p" retries="r}')" | tee -a "$LOG"
	fi
	sleep 10
done
echo "# soak end $(date): pings=$n lost=$lost maxrun=$maxrun transitions=$recon" | tee -a "$LOG"
