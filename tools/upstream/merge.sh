#!/usr/bin/env bash
# merge.sh [<linux-repo> [<theirs-tag> [<series-repo>]]]
# Rebase b43-src (which started from v6.18) onto a newer mainline b43: revert comment-only reflows against the v6.18 base
# (tools/upstream/norm.py), three-way merge every file with <theirs-tag>, and write the result into the working tree of
# <series-repo> (default ~/b43-upstream, branch "all"). Exits non-zero if a file has conflicts.
set -eu
P=drivers/net/wireless/broadcom/b43
L=${1:-$HOME/src/linux}; THEIRS=${2:-v7.3-rc5}; R=${3:-$HOME/b43-upstream}
HERE=$(cd "$(dirname "$0")/../.." && pwd)
W=$(mktemp -d); trap 'rm -rf "$W"' EXIT
mkdir -p $W/base $W/theirs $W/normed $W/out
git -C "$L" archive v6.18 $P | tar -x -C $W/base
git -C "$L" archive "$THEIRS" $P | tar -x -C $W/theirs
B=$W/base/$P; T=$W/theirs/$P
for f in $(cd "$HERE/b43-src" && ls *.c *.h Makefile Kconfig 2>/dev/null); do
	case $f in b43.mod.c) continue;; esac
	if [ -e $B/$f ]; then
		nix-shell -p python3 --run "python3 -I $HERE/tools/upstream/norm.py $B/$f $HERE/b43-src/$f $W/normed/$f" >/dev/null
	else
		cp "$HERE/b43-src/$f" $W/normed/$f
	fi
done
bad=0
cp $T/* $W/out/
for f in $(cd $W/normed && ls); do
	[ "$f" = Makefile ] && continue		# the stock Makefile plus the AC objects, below
	if [ -e $B/$f ] && [ -e $T/$f ]; then
		cp $W/normed/$f $W/out/$f
		(cd $W/out && git merge-file $f $B/$f $T/$f) || { echo "CONFLICT in $f"; bad=1; }
	else
		cp $W/normed/$f $W/out/$f
	fi
done
sed -i 's/^b43-\$(CONFIG_B43_PHY_AC)\t+= phy_ac.o$/b43-$(CONFIG_B43_PHY_AC)\t+= phy_ac.o radio_2069.o tables_phy_ac.o/' $W/out/Makefile
rm -f $R/$P/*; cp $W/out/* $R/$P/
echo "merged b43-src onto $THEIRS into $R/$P ($(ls $W/out | wc -l) files)"
exit $bad
