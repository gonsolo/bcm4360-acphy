# Status 2026-09-29 (part 6): ftrace shows the *majority* of scan
channel-switches fail their first `b43_mac_suspend()` attempt on 7.2.7
- not an intermittent race, a near-constant tax

Direct continuation of notes/81, same day, same boot, no reboot. Per
the daily-use plan's Phase 1b, set up `ftrace` on the mac80211
`drv_*`/`api_*` tracepoint group (`/sys/kernel/debug/tracing`,
`trace_clock=mono` to match the monotonic timestamps used everywhere
else this project's tooling reads: `dmesg` without `-T`,
`journalctl -o short-monotonic`, `hw_timing`). Captured one full
`tools/connect_test.sh` attempt (fresh `rmmod`/reload, scan, connect) on
7.2.7, `dmesg -c` cleared first for a clean per-attempt count.

## The finding

Parsed all 171 `drv_config` (channel-switch) call/return pairs in the
trace by matching each `drv_config:` entry to its next `drv_return_int:`
and measuring the gap:

- **106/171 (62%) took ≥60ms** (mean ~90ms) - clustered extremely
  tightly around ~89-91ms, not a spread.
- **62/171 (36%) took <20ms** (mean ~9ms) - the "normal" fast retune.
- Only 3/171 fell in between.

**~90ms is ~2x `suspend_ms`'s default (40ms) plus ~10ms overhead** - the
signature of `b43_mac_suspend()` failing its first attempt (burning the
full 40ms timeout), then succeeding on a second attempt (another ~40ms
+ processing). This is not the occasional/random failure notes/77 Part
5 described ("most individual channel switches actually succeed
silently and only a handful randomly fail") - **in this capture, the
majority of channel switches during an active scan sweep hit this
extra ~80ms tax, essentially every single time a channel actually
changed** (the fast ones are almost all *repeated* `drv_config` calls
at the *same* frequency, e.g. `2412.000`->`2412.000`, not real retunes).

**dmesg only shows 21 `MAC suspend failed` lines for this same
capture, not ~106+** - `b43_mac_suspend_diag`'s error print is
rate-limited (`dmesg` elsewhere in this project's history shows "N
callbacks suppressed" from this exact source). The true first-attempt
failure rate is dramatically higher than any dmesg-line-counting method
used in notes/76-81 could see - **every failure-rate number in this
project's notes so far ("0/5 to ~40%", "8-18 per attempt") is a floor,
not the real count.**

## Why this matters more than a "sometimes it hangs" framing

A near-constant, tightly-clustered ~90ms cost per channel switch, versus
an occasional full ucode halt (notes/77 Part 4's "frozen at the
identical address across all 8 samples" finding), looks like two
different things:

1. **This session's finding**: a small, *fixed* amount of extra latency
   that consistently and narrowly exceeds the 40ms first-attempt budget
   - consistent with a timing-margin regression (something now
   routinely takes slightly longer than it used to, tipping a
   previously-comfortable 40ms budget into a near-miss almost every
   time), not a race or collision.
2. **notes/77 Part 4's finding**: the ucode is sometimes genuinely,
   completely halted (not slowly-progressing) for the *entire* extended
   90ms window they tested, which patience alone can't fix.

These may be the same underlying mechanism seen at different points (a
near-miss that mostly self-corrects by attempt 2, occasionally doesn't
correct at all), or two distinct things. Not resolved this session.

## Immediate implication for scan behavior

mac80211's active-scan per-channel dwell budget is typically on the
order of 100-120ms. An unconditional extra ~80ms tax on top of the
normal ~9ms retune, on 62% of channel switches, is a very plausible
direct explanation for scans running far slower/less reliably on 7.2.7
than 6.18.53, independent of any single suspend failure ever fully
"blocking" anything - it's death by a thousand near-misses, not one
dramatic collision.

## Next steps for a future session, in order

1. **Test whether raising `suspend_ms` past the near-miss margin
   eliminates the ~90ms tax.** If first attempts almost always fail by
   a small margin, giving the first attempt more headroom (e.g.
   `suspend_ms=60`) might make most of them succeed on attempt 1,
   which would be a real, measurable, and very cheap (`0644`
   runtime-settable, no reload) win - re-run this exact ftrace capture
   with `suspend_ms=60` and compare the fast/slow drv_config ratio.
   **Caution**: notes/77 Part 4 already tested `suspend_ms=90` during
   *actual connect attempts* and saw 0/5 with the ucode fully halted -
   so this may not transfer from the scan case to the auth-time case;
   test scan behavior and connect reliability separately, don't
   conflate them.
2. Get a real (not rate-limited) count of first-attempt suspend
   failures - either raise the `dev_err_ratelimited`-equivalent's burst
   limit for one test session, or add a per-attempt atomic counter
   surfaced via debugfs/sysfs, so future A/B tests (like notes/79-80)
   aren't measuring a floor.
3. If `suspend_ms` doesn't help: this ~90ms-tax pattern is now precise
   and reproducible enough to be worth a *targeted* kernel bisect
   specifically around "what would add a few ms of fixed latency to
   whatever `b43_mac_suspend()` is polling" (PCIe/bcma MMIO round-trip
   time, interrupt latency, or scheduler latency for the workqueue
   context `drv_config` runs in - the trace shows it running on
   `kworker/uN` threads) - a much narrower question than notes/77 Part
   1's broad commit search.
4. Re-run this same ftrace capture on 6.18.53 (reference only, needs a
   user-initiated reboot) for a direct fast/slow ratio comparison - the
   single most direct confirmation of "what changed," if the reboot is
   granted.

## Current state at session end

No source changes. `ftrace` events disabled and tracing left off after
capture (`tracing_on=0`); trace buffer not cleared (harmless, will be
overwritten). Raw trace + matching `dmesg` for the captured (failed)
connect attempt saved under `test-logs/ftrace_fail_172129.txt` and
`test-logs/dmesg_fail_172129.txt`. Connection was mid-autoconnect
(`connecting (configuring)`) as this note was being written, following
the captured attempt's own auth-timeout failure - not yet confirmed
recovered. 16 total `rmmod`/`insmod` cycles today (15 from notes/80-81
plus this session's one `connect_test.sh` capture run).
