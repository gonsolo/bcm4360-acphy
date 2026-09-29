# Status 2026-09-29 (part 8): phase-timing instrumentation confirms
`b43_mac_suspend()` genuinely is the connect-time bottleneck - notes/83's
retraction was about a different condition, not a refutation

Direct continuation of notes/83, same day, same boot. notes/83 correctly
showed that `b43_mac_suspend()` isn't the bottleneck for slow
`drv_config` calls **during steady-state scanning on an already-
associated link** - but that test never actually re-checked the
**fresh-reload/connect** condition notes/82's original theory was about.
This session closes that gap with direct measurement instead of more
inference.

## What was done

Added small, threshold-gated `ktime_get()` instrumentation to
`b43_op_config()` (`main.c`), bracketing: mutex-lock-through-
`b43_mac_suspend()`, the channel-switch call, TX-power check, antenna
setup, and `b43_mac_enable()`. Logs one `b43info` line
("`optiming: total=Xms lock+suspend=Xms chan=Xms txpwr=Xms
antenna=Xms mac_enable=Xms`") whenever the whole call exceeds
`optiming_thresh_ms` (new `0644` param, default 15ms). Rebuilt against
the running 7.2.7 kernel (`nix-shell -p gnumake gcc bc flex bison
elfutils --run make KDIR=.../linux-7.2.7-dev/.../build`, per
[[env-tooling]]), vermagic matched, reloaded via `connect_test.sh`.

## Result: unambiguous, 7/7 samples

Every slow `b43_op_config` call captured this session (7 total, during
one `connect_test.sh` attempt's pre-auth scan) showed the **same**
shape:

```
optiming: total=89-98ms lock+suspend=80-85ms chan=8-17ms txpwr=0ms antenna=0ms mac_enable=0ms
```

`lock+suspend` (mutex acquisition through `b43_mac_suspend()` returning)
accounts for **~90% of the total time in every single sample**, and
every one of these lines was immediately preceded in `dmesg` by a real
`b43-phy18 ERROR: MAC suspend failed (40ms)` line at the same moment.
`chan` (the actual channel retune) is a small, consistent 8-17ms;
`txpwr`/`antenna`/`mac_enable` are consistently 0ms.

**This directly confirms the connect-time slowness is genuinely
`b43_mac_suspend()` failing** - not a retry-doubling artifact (there is
no retry in the code, per notes/83), just the function's single 40ms
wait loop actually being exhausted, for real, on a large fraction of
scan-triggered channel switches during connect. notes/82's original
instinct was right for this condition; notes/83's retraction was
correct about a *different* condition (steady-state scanning) and
shouldn't have been read as invalidating the fresh-reload finding too -
clarifying that distinction is this note's main purpose.

## Reconciling with notes/83

Two genuinely distinct phenomena, now both real and evidenced:

1. **Fresh-reload/connect-time** (this note): `b43_mac_suspend()`
   itself fails routinely, eating a full ~40ms plus ~40ms more
   (likely `wl->mutex` contention with another op happening around the
   same time - not yet separately measured, `lock+suspend` bundles
   both). This matches the raw `dmesg` failure counts seen throughout
   notes/76-82 (8-20+ per connect attempt).
2. **Steady-state scanning on an already-associated link** (notes/83):
   `b43_mac_suspend()` does not fail (zero logged failures even with
   `suspend_ms=60`), yet `drv_config` can still take up to ~1.5s via an
   unlocalized mechanism elsewhere in the call chain. Not explained by
   this session's data - the `optiming` instrumentation wasn't run
   against this specific condition yet (next step).

## Also observed live: `netwatch` worked exactly as designed

Mid-capture, the channel-switching storm made the router briefly
unreachable long enough (10 consecutive ping failures, ~25s) that
`netwatch` auto-`rmmod`'d b43, per its own design (notes/78's
`postboot.sh` setup) - not a crash, not a hang, the safety net doing
its job on a real (if session-induced) network interruption. Restored
normal daily-use operation afterward via `tools/b43_boot.sh` (the same
path `b43-ac-load.service` uses at boot) - connected cleanly.

## Decision: keeping the `optiming` instrumentation in the tree

Unlike a one-off diagnostic, this is cheap (single `ktime_get()` calls,
threshold-gated logging, `0644` at runtime including full disable via
`-1`) and mirrors the pattern of existing permanent diagnostics already
in this codebase (`b43_mac_suspend_diag`, `suspend_ms`). Left in rather
than reverted - useful for the next session's steady-state-scanning
follow-up (next step below) without another rebuild.

## Next steps for a future session, in order

1. **Run the same `optiming`-instrumented build against the steady-
   state scanning condition** (already-associated link, `nmcli`
   rescan, no reload) - this is the direct, targeted way to answer what
   notes/83 left open: which phase (`chan`, `txpwr`, `antenna`,
   `mac_enable`, or something after `mac_enable` this instrumentation
   doesn't cover) eats the time when `lock+suspend` is *not* the culprit.
2. Split `lock+suspend` into two separate timestamps (mutex-acquire vs.
   the `b43_mac_suspend()` call itself) to quantify how much of the
   ~80-85ms is genuine suspend-wait vs. `wl->mutex` contention with a
   concurrent operation - the current bucket conflates them.
3. Now that the connect-time mechanism is precisely characterized (a
   real, ~50%+-of-attempts `b43_mac_suspend()` failure, not a race that
   "usually" succeeds), a *targeted* kernel bisect around whatever
   changed the ucode's suspend-acknowledgment timing margin (PCIe/bcma
   MMIO round-trip time, interrupt latency, or `wl->mutex` scheduling
   context) is more tractable than notes/77 Part 1's broad sweep.
4. notes/77 Part 6 (RX-blackout) and a 6.18.53 reference `optiming`
   capture (needs a user-initiated reboot, would directly show whether
   `lock+suspend` is ~9ms there instead of ~80ms) remain open.

## Current state at session end

Source change: `b43-src/main.c` gained the `optiming` instrumentation
(kept, see above) and an `#include <linux/ktime.h>`. Module rebuilt and
reloaded (18th-19th `rmmod`/`insmod` cycle today, cumulative across
notes/80-84). `netwatch` auto-unloaded b43 once mid-session (real,
correct safety-net behavior, not a fault) - manually restored via the
normal daily-use load path afterward, connection currently healthy.
`optiming_thresh_ms` left at its default (15ms).
