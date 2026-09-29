# Status 2026-09-29 (part 12): the "present but stuck" auto-recovery
path live-tested and fixed - trigger threshold was too tight, plus two
smaller refinements found

Direct continuation of notes/87, same day, same boot. Tested the one
path notes/87 flagged as not yet separately verified: `wlp3s0b1`
present but stuck disconnected (rather than the interface being fully
gone), with the AP's SSID visible.

## First attempt found a real bug: 60s trigger too tight

Disabled `connection.autoconnect` on the `Vodafone-2A84` profile
(so NetworkManager wouldn't reconnect on its own and mask the test),
then `nmcli device disconnect wlp3s0b1`. The watchdog correctly detected
"SSID visible" and reloaded (attempt 3/6) - but then kept re-triggering
every ~75-90s (attempts 4, 5, 6, hitting the hourly cap) because,
with autoconnect off, each reload brought the module back up with **no
connection attempt at all**, which the watchdog correctly (if
unhelpfully, given the test setup) kept seeing as "still not connected."

Worse: while manually restoring `autoconnect yes` and issuing
`nmcli connection up`, my own in-flight, legitimate (if slow) connection
attempt got interrupted mid-`connecting` by the watchdog's own next
reload (attempt 6/6) - the original `DISCONNECTED_POLLS_TRIGGER=4`
(~60s) is tighter than `connect_test.sh`'s own 70s connect timeout, so
a real, still-working attempt can get pre-empted. **Fixed**: raised the
threshold to 6 polls (~90s), comfortably past the 70s ceiling, with a
comment explaining why.

## Rate limiter worked exactly as intended

Once the 6/hour cap was hit, the watchdog correctly stopped reloading
and logged "cap reached, not reloading" on every subsequent stuck-poll
- it got out of the way and let NetworkManager's own retry logic
eventually get a connection through on its own. This is the safety
backstop (notes/59/77 degradation caution) working as designed, even
though it surfaced during what was really a self-inflicted test loop
rather than a genuine daily-use failure storm.

## Clean re-test with the fix: works as designed

Restarted the watchdog (fresh rate-limit window), repeated the same
disconnect-with-autoconnect-off test. This time: 6 consecutive
"disconnected" polls (90s), SSID confirmed genuinely visible (spot-
checked directly with `nmcli dev wifi list`), reload triggered exactly
once (attempt 1/6), no interruption of anything since nothing was
attempting to connect during that window. Restored `autoconnect yes`
afterward; a *second* trigger did fire once more (attempt 2/6) because
the poll counter had already accumulated most of its 90s budget across
several of my own manual actions before autoconnect was re-enabled -
but this didn't prevent the connection from eventually succeeding
(NetworkManager's own retry got through a few polls later, confirmed
connected with real RX traffic flowing).

## Two smaller refinements found, not fixed live

1. **Stale SSID scan cache**: at one point the watchdog logged "SSID
   not visible, leaving alone" when the AP was, confirmed moments
   later, genuinely broadcasting and visible via a fresh
   `nmcli dev wifi list` - `nmcli`'s cached scan results while the
   interface has been cycling disconnected/connecting can be stale,
   causing the watchdog to skip a legitimate recovery opportunity. A
   more robust check would force a fresh scan (`nmcli dev wifi rescan`)
   before checking visibility, rather than trusting the cache.
2. **Cumulative vs. per-attempt counting**: the poll counter counts
   consecutive non-`connected` polls regardless of *which* substate
   (`disconnected` or `connecting`) and regardless of whether a *new*
   attempt just started - so a sequence of several individually-
   reasonable attempts, each a bit slow, can still accumulate enough
   non-connected time to trigger a reload that interrupts whichever
   attempt happens to be in flight when the threshold is crossed, even
   if that specific attempt is still young. A more precise design would
   reset the counter specifically when a **new** attempt begins
   (`disconnected` -> `connecting` transition), giving each attempt its
   own fresh budget, and only count uninterrupted time within one
   state. Left as-is for now - the 90s fix already substantially
   reduces how often this matters, and over-engineering the heuristic
   live under time pressure seemed like the wrong trade-off tonight.

## Current state at session end

`tools/b43_autorecover.sh`: `DISCONNECTED_POLLS_TRIGGER` raised from 4
to 6 (~60s -> ~90s), with a comment explaining why. Service restarted
with the fix; currently active, 2/6 reload attempts used this hour (both
from this session's own testing, not a real daily-use failure).
`connection.autoconnect` on `Vodafone-2A84` restored to `yes` (was
toggled off for testing). Connection currently healthy and stable, real
traffic flowing. `netwatch` also still active.

## Next steps for a future session, in order

1. If the stale-scan-cache or cumulative-counting refinements above
   turn out to matter in real daily use (not just deliberately
   engineered test conditions), implement them: a forced rescan before
   the visibility check, and a per-attempt-scoped counter.
2. The daily-use plan's remaining items (promoting `b43-autorecover` to
   a persistent NixOS service, 2b suspend/resume, 2c 24h soak, Phase 3
   throughput/HT) are all still open.
3. The steady-state-scanning anomaly (notes/82/83, parked in notes/85/
   86) and the deeper kernel-side root cause (notes/84's remaining
   items: splitting `lock+suspend`, a targeted bisect) remain available
   whenever there's appetite for more root-cause work.
