# Status 2026-09-29 (part 9): `optiming` on steady-state scanning found
nothing - 84/84 samples clean, suggesting notes/82-83's slow outliers may
depend on session history, not just "scanning while associated"

Direct continuation of notes/84, same day, same boot, same freshly-
reloaded (`optiming`-instrumented) module. Ran the follow-up notes/84
flagged: pointed the new phase-timing instrumentation at the steady-
state-scanning condition (already-associated link, `nmcli` rescan, no
reload) that notes/82-83's `ftrace` captures found slow (~90ms to
~1.5s) outliers in, with zero suspend failures.

## Result: no outliers at all

12 `nmcli` rescans, `optiming_thresh_ms` lowered to 5 (from the default
15) to catch anything above the noise floor: **84/84 samples were
"normal"** - total 8-18ms, `chan` 8-17ms, `lock+suspend` 0-2ms in every
single case. Not one sample came anywhere close to the ~90ms-1.5s
outliers notes/82/83 found doing the same kind of thing (scanning on an
already-associated link) earlier tonight.

## A real methodological difference, not (necessarily) a contradiction

The key difference between this test and notes/82/83's: **this module
had just been freshly `rmmod`/`insmod`'d** (via `connect_test.sh` in
notes/84, then `b43_boot.sh`), with only a handful of prior operations
on it. notes/83's scan-only captures ran on a module that had already
been through a long session of testing (10 reload cycles, multiple
`ac_state_once`/`suspend_ms` sysfs changes, prior scans, notes/78-83
tonight) before those particular captures. **This raises a real
possibility that hadn't been considered before**: the slow-`drv_config`
phenomenon during steady-state scanning may correlate with *how long a
module instance has been running / how many prior operations it's been
through*, not purely with "is this a scan on an already-associated
link" as notes/83 framed it. Equally possible: it's genuinely
intermittent/rare and 12 scans (84 samples) just didn't happen to catch
it this time, matching the earlier `function_graph` attempt in notes/83
which also came up empty across a few tries. **Not distinguished by
this session's data** - both are live hypotheses.

## What this does and doesn't change

Doesn't touch notes/84's connect-time finding (`b43_mac_suspend`
genuinely failing, ~80-90% of a slow call's time, 7/7 clean samples) -
that used the same instrumentation, on the same kind of freshly-loaded
module, and was unambiguous. This session's null result is specifically
about the *separate*, steady-state-scanning phenomenon, which remains
real (directly observed twice tonight, notes/82 and notes/83) but is
now additionally shown to be harder to reproduce on demand than initially
assumed - not "sometimes happens during scanning," possibly "sometimes
happens after a module has accumulated enough runtime/operations," or
just genuinely rare.

## Next steps for a future session, in order

1. **Test the "session-history-dependent" hypothesis directly**: run
   the same `optiming`-on-scanning capture again, but late in a long
   session (after many operations/reload cycles), rather than right
   after a fresh reload, and see if outliers reappear. If they do,
   that's a real, useful clue (something state-dependent accumulates -
   a leak, a fragmenting resource, thermal, or genuinely unrelated
   session/RF drift); if they still don't, lean toward "rare/
   intermittent" instead.
2. Alternatively, extend the capture window dramatically (dozens of
   scans over many minutes, not 12 over ~3 minutes) on a fresh module,
   to distinguish "rare but present from the start" from "only appears
   after accumulated runtime."
3. notes/84's still-open items remain: split `lock+suspend` into
   mutex-wait vs. suspend-call time for the connect-time case; a
   targeted bisect around whatever changed the ucode's suspend-
   acknowledgment margin; notes/77 Part 6's RX-blackout re-check; a
   6.18.53 reference `optiming` capture (needs a user-initiated reboot).

## Current state at session end

No further source changes (`optiming` instrumentation from notes/84
unchanged). `optiming_thresh_ms` reset to its default (`15`) after
testing at `5`. Connection healthy and stable throughout (no reload this
session - purely `nmcli` rescans on the already-loaded module from
notes/84). `netwatch` still active. No new `rmmod`/`insmod` cycles this
session (still 18-19 total today, unchanged from notes/84).
