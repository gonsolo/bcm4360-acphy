# Status 2026-09-29 (part 10): aging the module (16 more scans, same
instance) still didn't reproduce the steady-state slow outliers - second
clean result in a row

Direct continuation of notes/85, same day, same boot, **same module
instance** (no reload since notes/84's `connect_test.sh` load). Tested
notes/85's own first suggestion: run more operations on the same
long-lived module instance before re-checking steady-state scanning,
to see whether the earlier slow outliers (notes/82/83) need an "aged"
module to reproduce.

## What was done

Ran 16 more `nmcli` rescans (no reload) to accumulate runtime/operation
count on top of notes/85's already-tested instance (12 scans there),
then re-ran the `optiming` capture (threshold lowered to 5ms again) for
8 more scans: **90/90 samples clean**, total times 8-13ms, nothing
above 13ms. Combined with notes/85, that's **174 consecutive clean
samples across 28 scans on the same module instance**, and still zero
reproduction of the ~90ms-1.5s outliers notes/82/83 found.

## Where this leaves the "session-history" hypothesis

Weakened, but not eliminated. Simple scan-count/runtime accumulation on
an otherwise-idle, stable connection does not appear to be the trigger.
What's still different between this session's clean tests and notes/83's
slow captures, and untested: notes/83's slow captures happened on a
module instance that had **also** just been through several `suspend_ms`/
`ac_state_once` sysfs parameter changes and, further back in that same
session, real connect-time `b43_mac_suspend` failures (notes/78-82) -
this session's clean tests instead ran on modules freshly loaded via
`connect_test.sh`/`b43_boot.sh` with only scans afterward, no parameter
churn, no preceding suspend failures on *this* instance. Whether the
trigger is "the module has seen real suspend failures at some point,"
"sysfs parameters were changed live," pure environmental luck, or
something else entirely remains genuinely open.

## Assessment: not worth chasing further without a reliable repro

Two clean 80+/90+-sample rounds in a row is a real signal that blind
"do more of the same" isn't going to reproduce this on demand. Further
attempts along the same lines (more scans, more waiting) have
diminishing expected value. The phenomenon is real (directly observed
twice, with hard timestamped evidence, notes/82/83) but currently
un-reproducible-on-demand, which makes it a poor use of further live
session time right now compared to acting on what **is** solidly
established: the connect-time `b43_mac_suspend` failure (notes/84),
which alone plausibly explains most of the day-to-day unreliability
(every fresh connect/reconnect goes through the connect-time path;
steady-state scanning while already connected is comparatively rare in
normal use).

## Recommendation: pivot to Phase 2a (auto-recovery)

Per the project's daily-use plan, Phase 2a (automatic reload-and-retry
on a failed/stuck connection) doesn't require solving either open
mechanism - it directly compensates for the connect-time failure rate
notes/84 quantified, and makes the driver usable *today* regardless of
whether the steady-state mystery or the deep kernel-side root cause are
ever fully explained. Recommending this as the next concrete piece of
work, rather than continuing to hunt for a repro of an elusive secondary
phenomenon.

## Next steps for a future session, in order

1. **Build Phase 2a**: a small watcher (systemd service or NetworkManager
   dispatcher script) that detects a stuck/failed `wlp3s0b1` (disconnected
   with the SSID visible for >~60s, or ≥2 consecutive auth timeouts) and
   does `rmmod b43` + `tools/b43_boot.sh`, with backoff and a cap on
   attempts per hour (chip-degradation caution, notes/59/77).
2. If the steady-state mystery becomes actively relevant again (e.g. it
   causes a real user-visible stall during daily use): capture the
   *exact* conditions at that moment (recent parameter changes? recent
   suspend failures? time since load?) rather than trying to
   deliberately reproduce it in the abstract.
3. notes/84's other open items (splitting `lock+suspend`, a targeted
   bisect, the RX-blackout re-check, a 6.18.53 reference capture) remain
   available whenever there's appetite for more kernel-side archaeology.

## Current state at session end

No source changes. `optiming_thresh_ms` reset to default (`15`).
Connection healthy, same module instance loaded since notes/84 (no
reload this session - 28 scans total on it now, zero suspend failures,
zero slow outliers). `netwatch` still active.
