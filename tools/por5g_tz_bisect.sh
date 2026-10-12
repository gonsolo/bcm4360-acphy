#!/usr/bin/env bash
# por5g_tz_bisect.sh LO HI : find the essential words of wl's 5 GHz table replay (notes/153).
# A test zeroes table words [a,b) (everything else as wl wrote it, the 318 PHY words reset and
# replaced by the one explicit write), so the state does not depend on earlier runs. A range is
# "essential" when zeroing it breaks the link. Recursive halving; result lines go to stdout.
# Run as root, router on a 5 GHz 80 MHz channel at a good signal level.
P=/home/gonsolo/bcm4360-acphy
tests=0
ok() {	# ok a b : 0 when the link works with [a,b) zeroed
	local out down
	tests=$((tests + 1))
	[ $tests -gt 80 ] && { echo "too many tests" >&2; exit 1; }
	out=$(RESET=1 bash $P/tools/por5g_chain.sh "163,0,3142,0,$1,$2" 2>&1 | grep "^step" | tail -1)
	echo "test [$1,$2): ${out:0:200}" >&2
	down=$(sed -n 's/.*down \([0-9]*\)\..*/\1/p' <<< "$out")
	grep -q "Connected" <<< "$out" && [ "${down:-0}" -ge 40 ]
}
split() {	# split a b : [a,b) is known to break the link
	local m
	local a=$1 b=$2
	if [ $((b - a)) -le 1 ]; then echo "ESSENTIAL table word $a"; return; fi
	m=$(((a + b) / 2))
	local lo_ok=0 hi_ok=0
	ok $a $m && lo_ok=1
	ok $m $b && hi_ok=1
	[ $lo_ok = 1 ] && [ $hi_ok = 1 ] && echo "INTERACTION in [$a,$b): both halves pass alone"
	[ $lo_ok = 0 ] && split $a $m
	[ $hi_ok = 0 ] && split $m $b
}
if ok 0 0; then echo "control ok"; else echo "control FAILED, aborting"; exit 1; fi
if ok $1 $2; then echo "zeroing [$1,$2) does not break the link: nothing essential there"; else split $1 $2; fi
echo "done after $tests tests"
