# 120: in-driver self-heal of a bad init (ac_selfheal)

Per-init coin flip (notes/105): only ~30 % of fresh inits can transmit. `ac_selfheal=N` polls the ucode txphyerr counter (SHM 0xFE)
in the 15 s work; >= 3 errors in a window -> restart the core, at most N times (budget refills after 10 quiet minutes).

Findings (2026-10-06):
- IRQ-driven variant (unmask B43_IRQ_PHY_TXERR) hung the machine twice (no log, hard freeze) -> abandoned. Polling is safe.
- b43_controller_restart_full (ieee80211_restart_hw) leaves the interface dead: mac80211 WARNs (ieee80211_reconfig, sta_info, del_chanctx),
  no scan/auth afterwards, 0/3. Not usable.
- b43_controller_restart (quiet chip reset: core exit/init/start + config reload) works because a bad init is never associated:
  3/3 attempts connected, each after exactly 1 restart (detected 15-30 s after load).
- Test harness: heal_test.sh (success = connected within ~80 s of load, no NetworkManager kicking).
Next: N=10 for statistics, then enable by default in b43_boot.sh / the service params.
Earlier root-cause negatives (kicks, op-stream replay, ucode identical): notes/118, 119.

## N=10 result and default
heal10 (ac_selfheal=3): 9/10 connected (6 of 10 needed one restart, 4 none, the failure had used its restart). With the first 3/3: 12/13 vs ~30 % before.
Made ac_selfheal=3 the module default so the boot service (params in /etc/nixos, not edited by us) gets it; takes effect on the next load of the rebuilt b43-7.2.9.ko.
