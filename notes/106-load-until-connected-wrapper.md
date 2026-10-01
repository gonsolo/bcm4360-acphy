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
