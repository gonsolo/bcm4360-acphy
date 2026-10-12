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
# development-time log chatter: info -> debug in the added code; no emergency-level prints or delays
perl -0pi -e 's/b43info\(dev->wl, "phy_ac:/b43dbg(dev->wl, "phy_ac:/g' phy_ac.c
perl -0pi -e 's/b43info\((ring->dev->wl, "DMA (?:tx|rx)%d: ctl)/b43dbg($1/g; s/b43info\((dev->wl, "DMA: %u-bit engine)/b43dbg($1/; s/b43info\((ring->dev->wl, "RX slot)/b43dbg($1/' dma.c
perl -0pi -e 's/b43info\((dev->wl, "RX: DECERR passed up)/b43dbg($1/' xmit.c
perl -0pi -e 's/b43info\((dev->wl, "AC FIFO init)/b43dbg($1/; s/\t\tb43info\(dev->wl, "intrcvlazy0 was %08x\\n", b43_read32\(dev, 0x100\)\);\n//' main.c
perl -0pi -e 's/\tpr_emerg\("b43 ac_selfheal: bad init \(%u PHY TX errors\), restart %u\/%u\\n",\n\t\t d, restarts, B43_AC_SELFHEAL_MAX\);\n\tmdelay\(30\);\n/\tb43err(dev->wl, "AC-PHY: bad init (%u PHY TX errors), restart %u\/%u\\n",\n\t       d, restarts, B43_AC_SELFHEAL_MAX);\n/' phy_ac.c
grep -n "pr_emerg\|mdelay(30)" phy_ac.c main.c dma.c xmit.c || true
# development switches: the RX frame dump, dma32, the ignored command-line parameters
perl -0pi -e 's/\tif \(ring->dev->phy.type == B43_PHYTYPE_AC\) \{\n\t\tstatic atomic_t dumped = ATOMIC_INIT\(0\);\n.*?\n\t\}\n(\tif \(len == 0\) \{)/$1/s' dma.c
perl -0pi -e 's/static bool b43_dma32;\nmodule_param_named\(dma32, b43_dma32, bool, 0444\);\nMODULE_PARM_DESC\(dma32, [^\n]*\n\n//; s/DMA_BIT_MASK\(b43_dma32 \? 32 : type\)/DMA_BIT_MASK(type)/' dma.c
perl -0pi -e 's/static bool b43_ac_replay;\nmodule_param_named\(ac_replay[^\n]*\nMODULE_PARM_DESC\(ac_replay[^\n]*\n//; s/\/\* Accepted and ignored:[^\n]*\*\/\nstatic uint b43_ac_por = 7;\n//; s/module_param_named\(ac_por, b43_ac_por, uint, 0444\);\nMODULE_PARM_DESC\(ac_por[^\n]*\n\n?//' phy_ac.c
grep -n "dma32\|ac_replay\|ac_por\|atomic_t dumped" dma.c phy_ac.c || true
nix-shell -p python3 --run "python3 -I $HERE/tools/upstream/polish.py $D"
