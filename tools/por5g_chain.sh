#!/usr/bin/env bash
# por5g_chain.sh : ablation of wl's 5 GHz first-load replay (notes/149). Run as root right after a COLD boot
# (+ postboot.sh), router on a 5 GHz 80 MHz channel. Each step applies only the first N radio/phy/table words;
# the steps are nested (each applies a superset of the previous one), so state left by earlier steps never
# makes a later one pass that would not pass alone. One line per step: link state and throughput.
S=${SCRATCH:-/tmp/claude-1000/-home-gonsolo-bcm4360-acphy/6879bedf-950a-4f9d-8c2e-6754577630e0/scratchpad}
P=/home/gonsolo/bcm4360-acphy
steps="0,0,0 163,0,0 163,318,0 163,318,100 163,318,300 163,318,600 163,318,1200 163,318,2000 163,318,3142"
[ -n "$1" ] && steps="$*"
for st in $steps; do
	IFS=, read r p t p0 <<< "$st"
	sync
	nmcli connection delete b43-5g >/dev/null 2>&1
	bash $S/ld.sh ac_5ghz=1 ac_5g_80=1 ac_vht=1 ac_por5g_nr=$r ac_por5g_np=$p ac_por5g_nt=$t ac_por5g_p0=${p0:-0} >/dev/null 2>&1
	[ -n "$RESET" ] && bash $P/tools/phy5g_reset.sh
	l=$(bash $S/c5.sh 2>&1 | grep -E "Connected|Not connected|rx bitrate" | tr '\n\t' '  ' | cut -c1-110)
	if ip -4 -br a show wlp3s0b1 | grep -q 192; then
		u=$(bash $S/up.sh 2>&1 | tail -1 | cut -c1-40); d=$(bash $S/ud.sh 2>&1 | tail -1 | cut -c1-40)
	else u=; d=; fi
	echo "step $st: $l | $u | $d"
	sleep 30
done
nmcli connection delete b43-5g >/dev/null 2>&1
