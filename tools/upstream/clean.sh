#!/usr/bin/env bash
# clean.sh [<series-repo>]: turn the merged tree (tools/upstream/merge.sh) into the tree the series is cut from:
# no b43ac debugfs / development switches, no references to the private notes/ directory, no TX header hex dump.
set -eu
R=${1:-$HOME/b43-upstream}; D=$R/drivers/net/wireless/broadcom/b43
HERE=$(cd "$(dirname "$0")/../.." && pwd)
cd $D
nix-shell -p python3 --run "python3 -I $HERE/tools/upstream/strip_debug.py phy_ac.c phy_ac.h main.c"
# "(notes/NNN)", "(see notes/NNN-name.md)", "notes/NNN: " prefixes
perl -0pi -e 's/[ \t]*\((?:see |cf\. )?notes\/[^)\n]*\)//g; s/\bSee notes\/[0-9-]+(?:\/[0-9]+)*:\s*//g; s/,? ?notes\/[0-9]+(?:[-\/][0-9]+)*(?:-[a-z0-9-]+\.md)?\.?//g' phy_ac.c main.c dma.c xmit.c b43.h tables_phy_ac.c radio_2069.c
# the TX header hex dump block in xmit.c
perl -0pi -e 's/\n\t\{\n\t\tstatic atomic_t dumped = ATOMIC_INIT\(0\).*?\n\t\}\n(\treturn 0;)/\n$1/s' xmit.c
grep -n "notes/" *.c *.h || true
# decompiler function names and private trace paths in comments
perl -0pi -e 's/\(vendor FUN_[0-9a-f]+(?:, [^)]*)?\)/(as the vendor driver does it)/g; s/ \(vendor FUN_[0-9a-f]+\)/ (as the vendor driver does it)/g' phy_ac.c main.c
perl -0pi -e 's/\(traces\/decoded-firstload-5g-cold\/tables-wide.txt\), same entry format\./captured from the vendor driver, same entry format./' tables_phy_ac.c
perl -0pi -e 's/\(traces\/wl-init-20260927-184726.trace\) - Names are/captured from the vendor driver. Names are/' b43.h
perl -0pi -e 's/acphychipid == 0x4360 \(this chip - see notes\/session log\)\./acphychipid == 0x4360 (the BCM4360)./' phy_ac.c
echo "--- remaining odd references:"
grep -n "traces/\|FUN_\|notes/\|decompil\|ghidra" *.c *.h || true
