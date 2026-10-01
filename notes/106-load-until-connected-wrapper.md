# 106 - reload-until-connected wrapper for the boot service (test-driven, not yet enabled)

Why: only ~25-35 % of fresh b43 inits can transmit (notes/57, 103-105); a bad init stays bad until
the next reload, and a scan cannot tell (notes/105: 23/24 bad inits had 0 TX errors during the scan
phase). So an init has to be judged by its first connect attempt.

`tools/b43_load_until_connected.sh [module params]` wraps `tools/b43_boot.sh`: per try it loads b43 and
watches up to 30 s: `connected` -> keep; >= 3 new "PHY transmission error" lines -> unload and retry
(max 6 tries, then exit 1 leaving the last init loaded); no connect attempt and no errors -> keep (nothing
to judge). Tests (`bash tools/test_b43_load_until_connected.sh`, all external commands mocked via
`B43_*` env vars, touches no real interface): first-try success, success on the third try, give up after
6, quiet is not a failure, a failing load counts as a bad try. All pass.

Not enabled: to use it, `b43-ac-load.service` (/etc/nixos/configuration.nix) must call this script
instead of `tools/b43_boot.sh` with the same params (`ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1`), then
`nixos-rebuild switch`. Each reload restarts wpa_supplicant on NixOS, so do it at boot. Expected cost:
~4 tries on average, <= ~3 min worst case. Untested on the real hardware (the USB-stick wlan must not be
disturbed while working); first real test = next boot after the service change.

## Live results (2026-10-01, three batches of 4 runs with the final logic, USB stick guarded)
- Evidence per rejected init is logged (`phy= susp= auth=`); in production `phy` is always 0 (the driver
  masks the PHY TX error IRQ below verbose=3), so decisions rest on suspend failures and mac80211 auth
  timeouts. Typical bad init: auth=2 (two failed auth rounds, ~17 s apart) plus 4-9 suspend failures.
- Fixes found live (each test-first): the wrapper starts the connect itself (NM autoconnect does not
  reliably pick up the b43 interface); "connected" must hold 25 s because NixOS restarts wpa_supplicant a
  few seconds after the interface appears and drops a fresh link (success then re-checked 40 s later in
  all live runs); evidence is counted after a per-try kmsg marker (the dmesg ring buffer rotates, totals
  gave negative deltas).
- 43 tries, 9 judged clean (~21 % per try, the same as the plain base rate). With 6 tries the give-up
  chance is ~24 % (3 of 12 runs gave up); default raised to 12 tries (~6 %). Worst case ~12 x 55 s.
- Every successful run was still connected 40 s after the wrapper exited.

## IMPORTANT when enabling it: do NOT keep Type=oneshot
`b43-ac-load.service` is `Type = "oneshot"` with `Before=multi-user.target` (systemctl show), so the
graphical login waits for it; with the retry loop inside it, boot could stall up to ~12 min (typically
3-4 min). Use a non-blocking unit instead:

    systemd.services.b43-ac-load.serviceConfig = {
      Type = "simple";          # started immediately, login does not wait for the retries
      ExecStart = "/home/gonsolo/bcm4360-acphy/tools/b43_load_until_connected.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1";
    };   # drop RemainAfterExit; ideally also after = [ "NetworkManager.service" ];

The USB-stick wlan keeps working throughout, but blinks at every b43 reload (wpa_supplicant restart),
about once a minute while retries last.

## Enabled (2026-10-01) and first boot test
`b43-ac-load.service` now runs the wrapper (`Type = "simple"`, `after = NetworkManager.service`, via
/etc/nixos/configuration.nix; backup at /etc/nixos/configuration.nix.bak-before-b43-wrapper; undo = restore it
and `nixos-rebuild switch`). First reboot (kernel 7.2.7): service 11:44:29-11:45:21 (52 s), try 1 rejected
(susp=8 auth=0), try 2 connected and held 25 s, Result=success; b43 and the stick both connected, graphical
login not delayed. One boot is one sample of a ~21 %-per-try process (mean ~4 tries). Stick behaviour: every
b43 (re)load restarts the shared wpa_supplicant via a NixOS udev rule, which disconnects the stick too (seen
in the journal: ~20 s drop at 11:36).
