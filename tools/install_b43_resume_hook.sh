#!/usr/bin/env bash
# Add the b43-resume unit to /etc/nixos/configuration.nix and rebuild (run with sudo).
# After every resume it restarts b43-ac-load.service (reload b43 until an init connects, notes/111).
#   sudo tools/install_b43_resume_hook.sh            install + nixos-rebuild switch
#   sudo tools/install_b43_resume_hook.sh --remove   restore the backup + nixos-rebuild switch
# Test without touching the system:  CONF=/path/copy.nix REBUILD=true tools/install_b43_resume_hook.sh
set -eu
CONF=${CONF:-/etc/nixos/configuration.nix}
BAK=$CONF.bak-before-b43-resume
REBUILD=${REBUILD:-nixos-rebuild switch}
ANCHOR='  # MacBookAir6,1 internal ISO keyboard'
IFS= read -r -d '' BLOCK <<'NIX' || true
  # notes/111: resume re-initialises the chip core, which is the same ~21 % coin flip as a fresh load,
  # so after every resume run the reload-until-connected wrapper again.
  # (tools/install_b43_resume_hook.sh --remove undoes this; backup: configuration.nix.bak-before-b43-resume)
  systemd.services.b43-resume = {
    description = "Reload b43 after resume until an init connects";
    wantedBy = [ "suspend.target" "hibernate.target" "hybrid-sleep.target" "suspend-then-hibernate.target" ];
    after = [ "suspend.target" "hibernate.target" "hybrid-sleep.target" "suspend-then-hibernate.target" ];
    unitConfig.ConditionKernelVersion = "7.2.7";
    serviceConfig = {
      Type = "oneshot";
      ExecStart = "/run/current-system/sw/bin/systemctl restart --no-block b43-ac-load.service";
    };
  };

NIX
if [ "${1:-}" = --remove ]; then
	[ -f "$BAK" ] || { echo "no backup $BAK"; exit 1; }
	cp "$BAK" "$CONF"; echo "restored $CONF from backup"
else
	grep -q 'b43-resume' "$CONF" && { echo "already installed in $CONF"; exit 0; }
	grep -qF "$ANCHOR" "$CONF" || { echo "anchor line not found in $CONF; add the block by hand"; exit 1; }
	[ -f "$BAK" ] || cp "$CONF" "$BAK"
	awk -v blk="$BLOCK" -v anc="$ANCHOR" 'index($0, anc) == 1 && !done { print blk; print ""; done = 1 } { print }' "$CONF" > "$CONF.new"
	mv "$CONF.new" "$CONF"; echo "added b43-resume to $CONF (backup: $BAK)"
fi
$REBUILD
