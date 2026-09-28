# "MAC suspend failed" tracks the auth failures

Follow-up to notes/56. Boot auto-load now works: the service loads b43,
firmware comes from hardware.firmware, NetworkManager manages wlp3s0b1,
and the USB stick's firmware is fine. But b43 mostly can't connect.
Symptom: auth frames go out, the AP's reply never arrives ("authentication
... timed out"), and every so often it associates on the first try.

## Finding

`b43_mac_suspend()` failing ("MAC suspend failed") lines up with the failures.
Per-minute counts, boot 2a8576dd (gen 16, 16:22-16:44):

- every minute with auth timeouts also had suspend failures (8-63/min)
- 16:28:44-16:33:15, b43 associated and carried a Claude Code session with
  0% loss to router and internet: zero suspend failures
- 16:42 association: zero suspend failures in that minute
- boot -7 (the manual swap+load session where everything worked): zero
  suspend failures all boot; the auto-load boots have hundreds

The same holds for chip re-inits (`replayed vendor ch6 state`): a clean one
(no suspend failures around it) was followed by auth + assoc + WPA in the
same second at 16:46:04; re-inits surrounded by suspend failures were
followed by timeouts.

While in this state, SHM 0x40 (UCODESTAT) reads 2 = ACTIVE: the ucode runs
and isn't asleep, it just never answers the suspend request.

## Ruled out

- **USB stick interference:** fails with the stick physically unplugged.
- **Suspend timeout too short:** new `suspend_ms` param (main.c). At 250ms
  it's still "failed", and no "took ~Xms" (>40ms) success was logged even
  once. Suspend is either instant or never. Default is back to 40.
- **`verbose=3` (the manual path's extra logging/timing):** 64 failures
  and 1/3 connects, same as without.
- **MAC 00:01:00:00:84:38 / channel 11:** both used successfully before
  (notes/15, 36).

## Side findings

- NixOS restarts wpa_supplicant whenever a wlan interface is added or
  removed (USB stick plug, `iw ... interface add`, rmmod/insmod b43). That
  drops every WiFi connection. It killed the one good b43 connection of
  boot 5ea38cb1 when the stick was replugged.
- `systemd-run` units also lack bash in PATH: use an absolute
  `#!/run/current-system/sw/bin/bash` and export PATH.
- Added NM profile `stick-backup` (stick only, autoconnect, metric 700),
  so the stick and b43 can both hold a connection to the same SSID.

## Next

Find where the ucode sits when it ignores suspend: read the PSM PC (the
register isn't documented anywhere in these notes yet), map it in the
d11emu disassembly of ucode42, and compare with a state where suspend
works. Candidates: stuck in a TX/wait loop (TX lifetime 0x7C?), or a
path entered via the ac_replay state replay that never polls MACCTL.
