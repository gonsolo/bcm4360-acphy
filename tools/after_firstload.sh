#!/usr/bin/env bash
# After the first-load trace boot: decode the newest traces/wl-firstload-*.trace,
# report what it contains beyond the ifup trace, generate phy_ac_por.h, rebuild b43.
set -eu
PROJ=/home/gonsolo/bcm4360-acphy
cd "$PROJ"
T=$(ls -t traces/wl-firstload-*.trace 2>/dev/null | head -1)
[ -n "$T" ] || { echo "no first-load trace found"; exit 1; }
D=traces/decoded-firstload
I=traces/decoded-ifup
nix-shell -p python3 --run "python3 tools/decode_trace.py '$T' $D && \
	python3 tools/decode_trace.py traces/wl-init-20260926-132021.trace $I > /dev/null && \
	python3 tools/gen_replay.py $D b43-src/phy_ac_por.h '$T'"

echo "=== only in first load (not written during ifup) ==="
for f in phy radio; do
	n=$(join -v1 <(cut -d' ' -f1 $D/$f.txt | sort) <(cut -d' ' -f1 $I/$f.txt | sort) | wc -l)
	echo "$f: $n new registers"
done
n=$(join -v1 <(awk '{print $1"_"$2}' $D/tables.txt | sort) <(awk '{print $1"_"$2}' $I/tables.txt | sort) | wc -l)
echo "tables: $n new entries; new table ids: $(join -v1 <(awk '{print $1"_"$2}' $D/tables.txt | sort) <(awk '{print $1"_"$2}' $I/tables.txt | sort) | cut -d_ -f1 | sort -un | tr '\n' ' ')"
echo "=== differing final values (both traces) ==="
for f in phy radio; do
	n=$(join <(sort $D/$f.txt) <(sort $I/$f.txt) | awk '$2 != $3' | wc -l)
	echo "$f: $n registers differ"
done
echo "=== chipcommon / PMU ==="
cat $D/cc.txt; for k in chipctl regctl pllctl; do echo "pmu-$k:"; cat $D/pmu-$k.txt; done

cd b43-src
nix-shell -p gnumake gcc bc flex bison elfutils --run "make 2>&1 | grep -E ' error|b43.ko$'"
