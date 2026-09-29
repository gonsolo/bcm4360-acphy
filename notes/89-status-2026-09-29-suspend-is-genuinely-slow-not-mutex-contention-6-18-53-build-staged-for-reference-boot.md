# Status 2026-09-29 (part 13): `lock=0ms suspend=81ms` - genuinely
inside `b43_mac_suspend()`, not mutex contention; a msleep(1)-rounding
correction; mixed frozen/moving psmdebug signatures in one capture;
6.18.53 reference build staged for a future reboot

Direct continuation of notes/88, same day, same boot, explicit user
ask: fix the actual 7.2.7 regression, not just work around it via
auto-recovery. Picks up notes/84's flagged next step: split the
`optiming` instrumentation's `lock+suspend` bucket into mutex-acquire
time vs. the `b43_mac_suspend()` call itself.

## What was done

Added a second `ktime_get()` timestamp in `b43_op_config()`
(`main.c`), taken right after `mutex_lock(&wl->mutex)` returns and
before `b43_mac_suspend(dev)` is called, splitting the old
`lock+suspend` bucket into separate `lock` and `suspend` fields.
Rebuilt against 7.2.7, reloaded via `connect_test.sh`.

## Result: it's genuinely the suspend call, not the mutex

```
optiming: total=90ms lock=0ms suspend=81ms chan=8ms txpwr=0ms antenna=0ms mac_enable=0ms
optiming: total=91ms lock=0ms suspend=81ms chan=9ms txpwr=0ms antenna=0ms mac_enable=0ms
```

`lock=0ms` in every sample - `wl->mutex` was never contended. The full
~80ms is spent inside the single call to `b43_mac_suspend()`. This
rules out mutex contention as even a partial explanation (notes/84 had
left this open).

## Correction: ~81ms is not "2x a 40ms retry" - it's msleep(1) rounding,
and this is expected behavior, not itself a regression

Re-read `b43_mac_suspend()`'s actual wait loop (`main.c` ~3168-3190):
a 350us fast-poll (35 x `udelay(10)`), then `for (i = 0; i <
b43_suspend_ms; i++) { ...; msleep(1); }` with `b43_suspend_ms=40`.
Naively this caps at ~40.35ms - but `msleep(1)` on a `HZ=1000` kernel is
well-known to actually sleep for **2 jiffies (~2ms)**, not 1
(`schedule_timeout` rounds up to guarantee "at least" the requested
delay). 40 iterations x ~2ms/iteration = ~80ms, matching the observed
~81ms almost exactly. **This is not new or 7.2.7-specific** - `HZ=1000`
is identical on both kernels (confirmed in notes/81's `.config` diff),
so this rounding has presumably always made the *real* wall-clock
timeout ~80ms, not the ~40ms the parameter name and log message
("`MAC suspend failed (40ms)`") suggest. A real, if cosmetic, finding
(the log message is misleading), but **not** itself evidence of a
kernel-version regression - retracting my own momentary excitement
mid-session that "2x the expected time" meant something was newly
broken.

## The real open question, sharpened but not answered: why does the
wait fail at all on 7.2.7 (in ~80ms) when 6.18.53 apparently succeeds
quickly (per notes/76's 5/5 clean result)?

Captured `b43_mac_suspend_diag()`'s output for all 3 failures in one
`connect_test.sh` attempt (this diagnostic, already in the driver, dumps
8 samples of the PSM program counter across the wait):

- **Failure 1**: `psmdebug 00ff800f` **repeated identically 8/8 times** -
  matches notes/77 Part 4's "frozen, not slow" signature exactly.
- **Failure 2**: `psmdebug 00ff8013 00ff919f 00ff80c4 00c991c2 00ff800b
  00c980c8 00ff8041 00ec8107` - **all 8 samples different**, real
  movement across a wide address range. This does **not** match a
  "frozen ucode" story - the PSM is actively executing something, just
  not reaching whatever state sets `B43_IRQ_MAC_SUSPENDED` within the
  window.
- **Failure 3**: `psmdebug 00fe804e 00ec8014 00ff9198 ...` - also moving,
  similar to failure 2.

**Three failures in one attempt, two different signatures** (one
frozen, two moving). This had not been observed together before -
notes/77 Part 4 only reported the frozen case. Whatever's happening on
7.2.7 is not a single uniform mechanism ("the ucode always halts at one
spot") - it looks more like the ucode is under some kind of general
timing/scheduling pressure that sometimes manifests as a genuine halt
and sometimes as just running long/elsewhere, both failing to reach the
suspend-acknowledged state inside the ~80ms window either way.

## Why this needs a real 6.18.53 reference capture to go further

Everything gathered so far (this note plus notes/82-84) characterizes
the 7.2.7 *symptom* in detail but still has zero *direct* comparison
point - all of notes/76's 6.18.53 evidence is from before this
`optiming`/diag instrumentation existed. Without a same-instrumentation
6.18.53 capture, it's not possible to tell whether 6.18.53 has the same
`msleep`-rounding-driven ~80ms ceiling but reliably succeeds well within
it (e.g. suspend acknowledged in ~2-5ms every time), or whether
something else entirely differs. This is the single most direct
remaining lever - a true apples-to-apples timing comparison, not more
7.2.7-only archaeology.

**Pre-staged for this**: built the exact same instrumented `b43-src`
against the 6.18.53 kernel headers (already in the Nix store from
notes/76's original A/B testing, no download needed) and saved the
result at `b43-src-builds/b43-6.18.53.ko` - **not** the live
`b43-src/b43.ko` (which was immediately rebuilt back to 7.2.7 afterward
so daily-use tooling, `b43-autorecover` included, isn't left pointing at
a vermagic-mismatched module). Whenever a 6.18.53 reference boot happens
(user-initiated, per standing project rule), the capture is just:
`sudo cp b43-src-builds/b43-6.18.53.ko b43-src/b43.ko` (or point
`b43_live.sh`/`connect_test.sh` at it directly), then the same
`connect_test.sh` + `dmesg -T | grep -E "optiming|suspend diag"` this
note used on 7.2.7.

## Next steps for a future session, in order

1. **The reference boot** (user-initiated): boot 6.18.53, load the
   pre-staged instrumented module, run `connect_test.sh` a few times,
   compare `optiming`/`suspend diag` output directly against this
   note's 7.2.7 numbers. This is now genuinely a 5-minute capture, not
   a rebuild-from-scratch effort.
2. If 6.18.53 shows suspend consistently fast (a few ms): the question
   becomes *why* the ucode takes longer to reach the suspended state on
   7.2.7 specifically after a channel switch - worth checking whether
   the *fast* 6.18.53 psmdebug samples land at a completely different
   PC than either of 7.2.7's two signatures, which would at least say
   something about *where* the ucode's execution differs.
3. If 6.18.53 *also* sometimes takes ~80ms but still eventually
   succeeds (e.g. within a longer window than 7.2.7 allows): the
   difference might be more about pure margin than mechanism - revisits
   `suspend_ms` as a lever, but this time informed by real comparative
   data instead of the flawed A/B from notes/79-80.
4. Fix the misleading `b43err` log message ("MAC suspend failed
   (%dms)`, `b43_suspend_ms`") to report the actual elapsed wall-clock
   time (already available via `optiming`'s `suspend` field) instead of
   just echoing the nominal parameter - a small, independently-useful
   correctness fix regardless of the bigger investigation.

## Current state at session end

Source change: `b43-src/main.c` gained the `lock`/`suspend` timestamp
split (extends notes/84's `optiming` instrumentation, same param).
Live module rebuilt and confirmed back on 7.2.7 vermagic. New file
`b43-src-builds/b43-6.18.53.ko` (not tracked in git - a build artifact,
matches this project's existing `.gitignore` policy for
firmware/extracted material; rebuildable any time from source +
`KDIR=.../linux-6.18.53-dev/...`). Connection currently healthy
(`b43-test` profile, from this session's `connect_test.sh` run). No
reboot performed this session.
