# Status 2026-09-29 (part 11): Phase 2a (auto-recovery) built and
live-tested - a stuck/unloaded b43 now reloads itself within ~60-75s

Direct continuation of notes/86, same day, same boot. Per notes/86's
recommendation (the connect-time `b43_mac_suspend` failure, notes/84,
plausibly explains most daily-use pain, and doesn't need to be root-
caused before making the driver more usable), built the daily-use
plan's Phase 2a: automatic detection and reload of a stuck/failed
`wlp3s0b1`, instead of requiring the user to notice and reload by hand.

## What was built

`tools/b43_autorecover.sh` - a polling watchdog (15s interval, same
style as the existing `tools/netwatch.sh`):

- Tracks consecutive polls where `wlp3s0b1` isn't in NetworkManager's
  `connected` state. After ~60s (4 polls) of that:
  - If the interface is **entirely gone** (`/sys/class/net/wlp3s0b1`
    missing - b43 unloaded, by netwatch or otherwise) - reload
    unconditionally, since there's nothing to scan with to check the AP
    first.
  - Otherwise, only reload if the AP's SSID (`Vodafone-2A84`,
    overridable via `B43_AUTORECOVER_SSID`) is **actually visible** in a
    scan - a real AP outage or being out of range won't be fixed by
    reloading and shouldn't burn an attempt.
- Recovery action: `rmmod b43` (harmless no-op if already unloaded) +
  `tools/b43_boot.sh` with the same params `b43-ac-load.service` uses -
  the normal daily-use load path, not the monitor-mode test path
  (`b43_live.sh`).
- **Rate-limited**: at most 6 reloads/hour (`/run/b43_autorecover_attempts`,
  a rolling 1-hour timestamp log), matching the chip-degradation caution
  already standing in this project (notes/59/77) - won't reload-loop
  indefinitely if something is persistently broken.
- Logs to `test-logs/b43_autorecover.log`.

Wired into `tools/postboot.sh` alongside `netwatch`, both started (if
not already running) via `systemd-run`, idempotently.

## Live test: worked exactly as designed

Started it (`sudo systemd-run --unit=b43-autorecover ...`), confirmed
polling, then forced the interface-absent case directly: `sudo rmmod
b43` while connected. Result:

- 4 consecutive "state=absent" polls logged (~60s: `18:00:50` through
  `18:01:35`).
- At `18:01:35`, triggered recovery ("interface absent", attempt 1/6),
  ran the harmless no-op `rmmod` + `b43_boot.sh`.
- `wlp3s0b1` came back up and reconnected to `Vodafone-2A84`
  **unattended** - confirmed via `nmcli` and climbing RX packet counts
  a few seconds later.

Total unattended recovery time from the forced failure to a working
connection: roughly 60-75s (the fixed ~60s detection window plus reload
time) - not instant, but fully automatic, with no user action needed.

## Not yet tested

The other trigger path (interface present but stuck `disconnected`
with the SSID visible - the actual failure mode notes/84 characterized,
where auth repeatedly times out) wasn't separately live-tested this
session, only code-reviewed - the forced-`rmmod` test exercises the
"interface absent" branch, not the "present but stuck" branch. Both
share the same detection/rate-limit/reload logic, so this is a lower-
risk gap than it might sound, but worth a real test (e.g. deliberately
triggering repeated auth timeouts via `connect_test.sh` failures while
the watchdog is running, without manually reloading in between) in a
future session.

## What this does and doesn't fix

Doesn't fix the underlying kernel-7.2.7 regression (notes/76-84) or
explain the still-unreproduced steady-state-scanning anomaly (notes/82/
83/85/86) - it papers over failures automatically instead of requiring
manual intervention, which is a real, meaningful step toward "usable for
daily work" independent of ever fully root-causing either mechanism.
With the ~30-40% connect failure rate this project has measured, and a
~60-75s automatic recovery, a user should in practice see the interface
come back within roughly a minute or two of any given failure, rather
than staying down until someone notices.

## Next steps for a future session, in order

1. Test the "present but stuck, SSID visible" trigger path directly
   (not just the interface-absent path).
2. Consider promoting `b43-autorecover` from a `postboot.sh`/
   `systemd-run` runtime service to a persistent NixOS-defined service
   (`/etc/nixos/configuration.nix`, alongside `b43-ac-load.service`) so
   it starts automatically on every boot without needing `postboot.sh`
   run by hand first - this needs a `nixos-rebuild switch`, a real
   system-level change, so should be a user decision, not made
   unprompted.
3. Longer soak: leave it running across normal daily use for a day or
   more and see how often it actually fires, and whether the 6/hour cap
   is ever actually hit (would indicate a persistent, not transient,
   problem worth escalating rather than auto-recovering from).
4. The daily-use plan's remaining items (2b suspend/resume, 2c 24h soak,
   Phase 3 throughput/HT) are all still open, independent of this.

## Current state at session end

New file: `tools/b43_autorecover.sh` (executable). Modified:
`tools/postboot.sh` (starts the new watchdog alongside `netwatch`).
`b43-autorecover.service` currently active (started this session, one
successful recovery logged). `netwatch` also still active. Connection
currently healthy. No further `rmmod`/`insmod` cycles beyond the one
the watchdog itself performed as part of this test.
