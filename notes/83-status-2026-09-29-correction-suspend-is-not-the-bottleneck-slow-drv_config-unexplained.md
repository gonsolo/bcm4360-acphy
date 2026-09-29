# Status 2026-09-29 (part 7): correction to notes/82 - `b43_mac_suspend`
is not actually the bottleneck; the ~90ms/~900ms slow `drv_config` calls
happen with zero suspend failures logged, real cause still unknown

Direct, same-session correction to notes/82. Testing notes/82's proposed
mitigation (raise `suspend_ms` to close the "near-miss" margin) exposed
that notes/82's causal model was wrong, via mismatched test conditions
and then a same-condition re-test. Recording this precisely because it
reverses a specific, confident claim from an hour ago.

## What was tested and what it showed

Bumped `suspend_ms` to 60 live (`0644`, no reload) and re-ran the same
`ftrace` capture, but on an **already-associated, steady-state** link
(a plain `nmcli` rescan) - not the **fresh-reload** condition notes/82's
baseline used. Result: 42/~117 `drv_config` calls took **~1511ms**
(tightly clustered, 1511.6-1511.8ms), with **zero** `MAC suspend failed`
or `MAC suspend took ~Xms` lines in `dmesg`.

That "zero failures logged" detail matters: reading `b43_mac_suspend()`
itself (`main.c` ~line 3154) shows there is **no retry loop** in it at
all - it's a single `for (i = 0; i < b43_suspend_ms; i++) { ...;
msleep(1); }`, and the informational "took ~Xms" line only fires if
`i > 40` on eventual success, which is structurally unreachable at the
default `suspend_ms=40` (the loop bound *is* 40, so `i` never exceeds
40 - it either succeeds at `i <= 40` silently, or exhausts to the
`b43err` failure path). notes/82's "~90ms is ~2x the 40ms timeout,
therefore two failed suspend attempts" theory does not match this code
- **there is no such retry**, and this session's zero-failures-logged
result confirms `b43_mac_suspend` itself was not even close to failing
in either the `suspend_ms=40` or `=60` runs that showed multi-hundred-
to-1500ms `drv_config` calls.

**Re-tested `suspend_ms=40` under the exact same scan-only, already-
associated condition** (to get an apples-to-apples baseline, which
notes/82 never actually had): also found slow outliers - four calls at
~700-925ms, out of ~30 - again with **zero** suspend failures logged.
So the slow-`drv_config` phenomenon is real at both `suspend_ms` values,
happens without `b43_mac_suspend` ever reporting trouble, and is
**not** proportional to `suspend_ms` in the way notes/82 assumed (going
40ms->60ms did not shift the slow cluster from ~90ms to ~120ms, it
produced ~1500ms - a scale change too large to be "the same wait loop,
1.5x longer").

## Conclusion: retract notes/82's "2x suspend_ms retry" explanation

**What's still true from notes/82**: the underlying observation (a
large fraction of `drv_config` calls during scanning take dramatically
longer than the ~9ms baseline) is real and reproduced again today, in
multiple conditions. **What's retracted**: the specific mechanism
("`b43_mac_suspend` fails once, retries, succeeds" = ~2x timeout). The
real slow path is somewhere else inside `b43_op_config`'s call chain
(channel retune / calibration / `b43_mac_enable` / table writes) and
does not correlate with `suspend_ms` in the simple way assumed - it may
not correlate with it at all; the `suspend_ms=60` test may simply have
hit a worse instance of the same underlying rare event, not a caused-
by-the-parameter-change one.

## Attempted localization: inconclusive

Tried `ftrace`'s `function_graph` tracer, scoped to `b43_op_config`'s
call subtree (`set_graph_function`) with a duration threshold
(`tracing_thresh`, tried 5ms then 2ms) to catch which specific inner
function eats the time on a slow call, without reload. **Didn't catch a
single slow event across 4 more scan attempts** - the phenomenon seen
moments earlier (4/~30 calls, ~700-925ms) didn't reproduce in this
follow-up window at all. This is consistent with "real but comparatively
rare in steady-state scanning" (unlike notes/82's fresh-reload capture,
where 62% of calls were slow) - or, possibly, `function_graph`'s own
overhead perturbs the timing enough to mask it. Not resolved.

## Where this leaves the investigation

The precise, reproducible ~90ms/62%-slow pattern from notes/82's
**fresh-reload** capture is still real and still unexplained -
correcting the *mechanism*, not the *observation*. Separately, this
session found that even steady-state scanning (no reload) has rarer but
much larger (~700-1500ms) slow-`drv_config` outliers that also don't
implicate `b43_mac_suspend`. Both point at the same next step: **find
what inside `b43_op_config`'s call chain (beyond `b43_mac_suspend`
itself) can take hundreds of ms to over a second**, likely via finer-
grained manual timestamping inside `b43_phy_ac_op_switch_channel` /
`b43_mac_enable` / the calibration helpers (`b43_radio_2069_vcocal`,
`b43_radio_2069_rccal`, both already `ftrace`-visible by name per this
session's `available_filter_functions` check) rather than another
blind parameter sweep.

## Next steps for a future session, in order

1. Add real internal timestamps (e.g. temporary `ktime_get()` +
   `b43dbg` prints, or a non-thresholded `function_graph` run scoped
   more narrowly, accepting the volume) around each major sub-step of
   `b43_phy_ac_op_switch_channel` and `b43_mac_enable`, then capture
   during both a known-fast and (by running enough scans) a known-slow
   `drv_config`, to localize which specific sub-step is responsible.
2. Do **not** re-attempt the `suspend_ms` mitigation idea from notes/82
   as previously framed - it was based on a now-retracted mechanism.
   `ac_state_once`'s status (notes/79/80, still genuinely untested
   under the right condition) is unaffected by this correction.
3. notes/77 Part 6 (RX-blackout re-check) and a real reference capture
   on 6.18.53 (needs a user-initiated reboot) remain open and still the
   most direct ways to confirm what's different, independent of this
   thread.

## Current state at session end

No source changes. `ftrace`: tracing off, `current_tracer=nop`,
`tracing_thresh=0`, `set_graph_function`/`set_event` cleared - back to
its idle default. `suspend_ms` back at its default (`40`). Connection
currently up and stable (`Vodafone-2A84`), no reload this session (all
of notes/82-83's testing was ftrace + scan-only, except the one
`connect_test.sh` capture in notes/82 - 1 additional `rmmod`/`insmod`
cycle today, 17 total across notes/80-83).
