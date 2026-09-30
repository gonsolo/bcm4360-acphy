#!/usr/bin/env bash
# Build+stage "good mainline + a prefix of a pulled branch" (notes/103).
#
# Why: the first-parent bisect ended on Linus's KVM-pull merge 51d90a15fedf
# (first parent 399ead3a6d76 good, second parent e0c26d47def7 good *alone*),
# so the regression is an interaction. Test trees are made by merging a
# prefix of the pulled branch into the good first parent.
#
# usage: tools/bisect_merge_test.sh <base-good-commit> <branch-prefix-commit>
# e.g.   tools/bisect_merge_test.sh 399ead3a6d76 de8e8ebb1a7c
#
# The temporary merge commit only exists locally, so it is pushed to a
# scratch branch on pampelmuse before tools/bisect_build.sh (which checks
# out HEAD there by hash) runs. Run via Bash run_in_background, never a
# detached remote process (pampelmuse's logind kills those, notes/93).
set -eu
BASE=$1
X=$2
KEY=~/.ssh/id_ed25519_builder
REMOTE=gonsolo@192.168.0.236
cd ~/src/linux
git -c user.name=gonsolo -c user.email=gonsolo@gmail.com bisect reset >/dev/null 2>&1 || true
git checkout -qf --detach "$BASE"
if ! git -c user.name=gonsolo -c user.email=gonsolo@gmail.com merge --no-edit -q "$X" >/dev/null 2>&1; then
	echo "MERGE CONFLICT merging $X into $BASE:"
	git diff --name-only --diff-filter=U
	git merge --abort || true
	exit 2
fi
HEAD_SHORT=$(git rev-parse --short=12 HEAD)
echo "=== test tree $HEAD_SHORT = merge($BASE, $X) ==="
GIT_SSH_COMMAND="ssh -i $KEY" git push -q -f "ssh://$REMOTE/home/gonsolo/src/linux" "HEAD:refs/heads/mergetest-$HEAD_SHORT"
exec bash ~/bcm4360-acphy/tools/bisect_build.sh
