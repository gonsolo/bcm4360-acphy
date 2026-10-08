#!/usr/bin/env bash
# Switch the b43-ac-load service to the minimal replay config and rebuild for next boot.
# Run as root:  sudo bash tools/nixos_update_b43_args.sh [extra nixos-rebuild options]
# e.g. --option builders "" to build everything locally (no copying to the remote builder).
# Only prints file names and the changed line, never other contents of /etc/nixos.
set -eu

OLD='ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1'
NEW='ac_replay=0 dma32=1 ac_por=7 nohwcrypt=1'

[ "$(id -u)" = 0 ] || { echo "run with sudo" >&2; exit 1; }

files=$(grep -rlF -- "$OLD" /etc/nixos || true)
if [ -z "$files" ]; then
	if grep -rqF -- "$NEW" /etc/nixos; then
		echo "already updated, nothing to change"
	else
		echo "could not find '$OLD' in /etc/nixos; edit the b43-ac-load args by hand to: $NEW" >&2
		exit 1
	fi
else
	for f in $files; do
		cp -a "$f" "$f.bak-b43args"
		sed -i "s|$OLD|$NEW|" "$f"
		echo "updated $f (backup: $f.bak-b43args)"
		grep -nF -- "$NEW" "$f"
	done
fi

nixos-rebuild boot "$@"
echo "done. Reboot when convenient; the new module and args apply at next boot."
