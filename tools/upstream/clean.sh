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
