#!/usr/bin/env bash
# Tests for tools/b43_load_until_connected.sh with mocked load/unload/nmcli/dmesg: touches no real
# interface, module or network. usage: bash tools/test_b43_load_until_connected.sh
set -u
SUT=$(dirname "$0")/b43_load_until_connected.sh
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
fail=0

# A scenario is a list of per-try outcomes: "ok" (connects at once), "bad" (3+ PHY TX errors, never
# connects), "quiet" (no errors, never connects), "loadfail" (load command fails).
run() { # name expected_loads expected_rmmods expected_exit outcomes...
	local name=$1 el=$2 er=$3 ee=$4; shift 4
	: > "$T/loads"; : > "$T/rmmods"; echo 0 > "$T/try"; printf '%s\n' "$@" > "$T/outcomes"
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
[ "\$(sed -n \$(cat $T/try)p $T/outcomes)" = ok ] && echo "wlp3s0b1:connected" || echo "wlp3s0b1:disconnected"
EOS
	cat > "$T/dmesg" <<EOS
#!/usr/bin/env bash
# cumulative error lines: 3 per "bad" try so far
bad=\$(head -n \$(cat $T/try) $T/outcomes | grep -c '^bad\$')
for i in \$(seq 1 \$(( bad * 3 ))); do echo "b43-phy0 ERROR: PHY transmission error"; done
EOS
	chmod +x "$T"/load "$T"/rmmod "$T"/nmcli "$T"/dmesg
	B43_LOAD="$T/load" B43_RMMOD="$T/rmmod" B43_NMCLI="$T/nmcli" B43_DMESG="$T/dmesg" \
		B43_SLEEP=true B43_TRIES=6 B43_WAIT=6 B43_POLL=2 B43_MAX_ERRS=3 bash "$SUT" > "$T/out" 2>&1
	local ex=$?
	local gl gr; gl=$(wc -l < "$T/loads"); gr=$(wc -l < "$T/rmmods")
	if [ "$gl" = "$el" ] && [ "$gr" = "$er" ] && [ "$ex" = "$ee" ]; then
		echo "PASS $name"
	else
		echo "FAIL $name: loads=$gl (want $el) rmmods=$gr (want $er) exit=$ex (want $ee)"; sed 's/^/    /' "$T/out"; fail=1
	fi
}

run first_try_connects      1 0 0 ok
run third_try_connects      3 2 0 bad bad ok
run all_bad_gives_up        6 5 1 bad bad bad bad bad bad
run quiet_is_not_a_failure  1 0 0 quiet
run load_failure_retries    3 2 0 loadfail bad ok
exit $fail
