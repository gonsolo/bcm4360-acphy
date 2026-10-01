#!/usr/bin/env bash
# Tests for tools/b43_load_until_connected.sh with mocked load/unload/nmcli/dmesg: touches no real
# interface, module or network. usage: bash tools/test_b43_load_until_connected.sh
set -u
SUT=$(dirname "$0")/b43_load_until_connected.sh
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
fail=0

# A scenario is a list of per-try outcomes: "ok" (connects at once), "bad" (3+ PHY TX errors, never
# connects), "badauth" (3 mac80211 auth timeouts, never connects), "quiet" (no errors, never connects), "loadfail" (load command fails).
run() { # name expected_loads expected_rmmods expected_exit outcomes (also: >= one "nmcli device connect" per load)...
	local name=$1 el=$2 er=$3 ee=$4; shift 4
	: > "$T/loads"; : > "$T/rmmods"; : > "$T/nmcli_calls"; echo 0 > "$T/try"; printf '%s\n' "$@" > "$T/outcomes"
	cat > "$T/load" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat $T/try) + 1 )); echo \$n > $T/try; echo load >> $T/loads
[ "\$(sed -n \${n}p $T/outcomes)" = loadfail ] && exit 1; exit 0
EOS
	cat > "$T/rmmod" <<EOS
#!/usr/bin/env bash
echo rmmod >> $T/rmmods
EOS
	cat > "$T/nmcli" <<EOS
#!/usr/bin/env bash
echo "\$*" >> $T/nmcli_calls
if [ "\$(sed -n \$(cat $T/try)p $T/outcomes)" = blip ]; then
	# link drops once right after the first "connected" (NixOS restarts wpa_supplicant), then holds
	case "\$*" in *DEVICE,STATE*) n=\$(( \$(cat $T/stq 2>/dev/null || echo 0) + 1 )); echo \$n > $T/stq
		[ \$(( n % 3 )) -eq 2 ] && echo "wlp3s0b1:disconnected" || echo "wlp3s0b1:connected";; *) echo "wlp3s0b1:x";; esac
	exit 0
fi
[ "\$(sed -n \$(cat $T/try)p $T/outcomes)" = ok ] || [ "\$(sed -n \$(cat $T/try)p $T/outcomes)" = midok ] && echo "wlp3s0b1:connected" || echo "wlp3s0b1:disconnected"
EOS
	cat > "$T/dmesg" <<EOS
#!/usr/bin/env bash
# cumulative error lines: 3 per "bad" try so far
bad=\$(head -n \$(cat $T/try) $T/outcomes | grep -c "^bad\$")
badauth=\$(head -n \$(cat $T/try) $T/outcomes | grep -c "^badauth\$")
for i in \$(seq 1 \$(( bad * 3 ))); do echo "b43-phy0 ERROR: PHY transmission error"; done
midok=\$(head -n \$(cat $T/try) $T/outcomes | grep -c "^midok\$")
badmild=\$(head -n \$(cat $T/try) $T/outcomes | grep -c "^badmild\$")
for i in \$(seq 1 \$(( midok * 4 ))); do echo "b43-phy0 ERROR: MAC suspend failed (40ms)"; done
for i in \$(seq 1 \$(( badmild * 1 ))); do echo "b43-phy0 ERROR: MAC suspend failed (40ms)"; done
for i in \$(seq 1 \$badmild); do echo "wlp3s0b1: authentication with 8c:6a:8d:9e:2a:88 timed out"; done
badsusp=\$(head -n \$(cat $T/try) $T/outcomes | grep -c "^badsusp\$")
for i in \$(seq 1 \$(( badauth * 3 ))); do echo "wlp3s0b1: authentication with 8c:6a:8d:9e:2a:88 timed out"; done
for i in \$(seq 1 \$(( badsusp * 3 ))); do echo "b43-phy0 ERROR: MAC suspend failed (40ms)"; done
EOS
	chmod +x "$T"/load "$T"/rmmod "$T"/nmcli "$T"/dmesg
	B43_LOAD="$T/load" B43_RMMOD="$T/rmmod" B43_NMCLI="$T/nmcli" B43_DMESG="$T/dmesg" \
		B43_SLEEP=true B43_TRIES=6 B43_WAIT=30 B43_SETTLE=1 B43_POLL=2 B43_MAX_ERRS=3 bash "$SUT" > "$T/out" 2>&1
	local ex=$?
	local gl gr; gl=$(wc -l < "$T/loads"); gr=$(wc -l < "$T/rmmods")
	local gc nf; gc=$(grep -c "device connect" "$T/nmcli_calls"); nf=$(head -n "$gl" "$T/outcomes" | grep -c "^loadfail\$")
	if [ "$gl" = "$el" ] && [ "$gr" = "$er" ] && [ "$ex" = "$ee" ] && [ "$gc" -ge $(( gl - nf )) ]; then
		echo "PASS $name"
	else
		echo "FAIL $name: loads=$gl (want $el) rmmods=$gr (want $er) exit=$ex (want $ee) connect_calls=$gc"; sed 's/^/    /' "$T/out"; fail=1
	fi
}

run first_try_connects      1 0 0 ok
run third_try_connects      3 2 0 bad bad ok
run all_bad_gives_up        6 5 1 bad bad bad bad bad bad
run quiet_is_not_a_failure  1 0 0 quiet
run load_failure_retries    3 2 0 loadfail bad ok
run auth_timeouts_count     2 1 0 badauth ok
grep -q "auth=3" "$T/out" || { echo "FAIL evidence_is_logged: no auth=3 in output"; sed "s/^/    /" "$T/out"; fail=1; }
run suspend_failures_count  2 1 0 badsusp ok
run mild_failure_not_connected 2 1 0 badmild ok
run few_suspend_failures_then_connects 1 0 0 midok
: > "$T/stq"
run link_drops_then_holds    1 0 0 blip
grep -q "dropped" "$T/out" || { echo "FAIL link_drop_logged: no dropped in output"; fail=1; }
exit $fail
