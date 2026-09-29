# Status 2026-09-29 (part 4): the reload A/B was flawed by design -
`ac_state_once` cannot affect a single fresh connect attempt; regression
reconfirmed (4/10, 40%) but says nothing new about the flag

Direct continuation of notes/79, same day, same boot, with explicit user
sign-off to run the higher-risk test notes/79 flagged (repeated
`rmmod`/`insmod` + fresh reconnect cycles, notes/76 methodology).
`kernel.panic_on_oops=1`/`hung_task_panic=1`/`softlockup_panic=1` set
first (project's own standard practice for this kind of test,
`tools/test_7.2.7.sh`), netwatch already active from notes/78. Backup
link (`wlp0s20u1`) initially looked dead by `ping -I` (100% loss) but
`tcpdump` confirmed real ICMP replies arriving correctly - the same
dual-default-route-on-one-subnet reporting artifact notes/76 already
documented, not a real backup failure. Data path genuinely up
throughout (confirmed by capture, not just ARP).

## What was run

Wrote a wrapper (`ab_reload_test.sh`, scratchpad, not in repo) around
the existing `tools/connect_test.sh` (fresh `rmmod` + `b43_live.sh load`
+ managed-mode + `nmcli con up b43-test`, 70s timeout, exactly notes/76's
proven sequence): 5 attempts with default module params (Arm A), then 5
with `ac_state_once=1` passed as an extra `insmod` param (Arm B),
counting `MAC suspend failed` lines (`dmesg -c` cleared between
attempts) and final `nmcli` connection state each time.

- **Arm A** (default): 3/5 connected, suspend-failure counts per
  attempt: 14, 9, 8, 8, 11.
- **Arm B** (`ac_state_once=1`): 1/5 connected, suspend-failure counts:
  12, 11, 14, 10, 12.

At first glance this looks like `ac_state_once=1` made things *worse*.
**It didn't - the test couldn't have shown a real difference either
way, by construction.**

## Why: `ac_state_once` cannot affect a single fresh connect attempt

Checked `phy_ac.c` (line ~1169) and `phy_ac.h` (line 40) again, this
time for exactly when `phy_ac->wl_state_applied` becomes true: **only**
inside the same `if` block the flag guards (line 1175), never
initialized elsewhere - so on a freshly-allocated `phy_ac` struct (every
`rmmod`/`insmod`, zero-initialized), it starts `false`. The guard is
`!(b43_ac_state_once && phy_ac->wl_state_applied)`; with
`wl_state_applied` false, this is `true` **regardless of
`b43_ac_state_once`**. The flag only changes behavior on the *second and
later* returns to channel 6 within the same module load (e.g. scan
hops while already associated - exactly what notes/78/79 tested). A
test built entirely out of fresh `rmmod`+single-connect-attempt cycles
(this session's reload test) puts both arms through the **identical**
code path on their one and only channel-6 switch - the flag is a no-op
in that specific test shape.

So: the 3/5 vs 1/5 split is two independent samples of the same
underlying ~40-60%-variable failure process notes/76 already
characterized, not a real effect of the flag. Combined, this session's
reload testing saw **4/10 (40%) successful fresh connections** on
7.2.7, which is itself a clean, unsurprising reconfirmation that the
regression is alive and well on this boot/kernel - just not evidence
about `ac_state_once` either way.

## Where the actual differential test stands

notes/79 already ran the *only* test shape that actually exercises the
flag's difference (repeated scans on an already-connected link, no
reload) - and found 0/10 vs 0/10, i.e. no failures in either arm, so
also inconclusive, just for the opposite reason (no stress, rather than
no differential code path).

**The test that would actually answer the question** ("does suppressing
the repeated channel-6 replay reduce suspend failures?") needs *both*
elements at once: connect once (arm-independent, replay happens either
way), *then*, while still connected on the same module load, run
repeated scans/rescans (where `ac_state_once` actually changes what
runs) for long enough to accumulate a real sample of scan-triggered
suspend failures - comparing the *scan-triggered* failure count between
`ac_state_once=0` and `=1` on top of an already-successful association,
not the initial-connect success rate. Neither this session's reload test
nor notes/79's scan-only test was built that way; notes/79 was closer in
shape but happened to hit zero failures either way.

## Current state at session end

No source changes. Module currently loaded with `ac_state_once=1`
still set from Arm B's last `insmod`, but the runtime `0644` sysfs
parameter was flipped back to `0` (its documented default) immediately
after - future channel-6 switches on this boot behave as default again.
Connection self-recovered to `Vodafone-2A84` (NetworkManager autoconnect,
`managed=yes` was left set by `connect_test.sh`) after the last reload
attempt, unprompted - confirmed healthy. `kernel.panic_on_oops=1` and
related panic sysctls, set at the start of this session's reload
testing, were **left enabled** (matches `tools/test_7.2.7.sh`'s own
intent as standing test-session state, not reverted between notes/76-80
historically either). 10 total `rmmod`/`insmod` cycles this session (5
per arm) - noted per the standing chip-degradation caution
(notes/59/77): `wl`'s own historical known-good attach was not
re-checked this session, only b43's.

## Next steps for a future session, in order

1. Build the actually-differential test described above (connect once,
   then N repeated scans while associated, same module load, comparing
   `ac_state_once=0` vs `=1` scan-triggered-only suspend-failure counts)
   if `ac_state_once` is still considered a live lead.
2. Independently: 4/10 (40%) this session is itself a useful, fresh data
   point for the underlying regression's base rate - consistent with
   notes/76's original range, on a clean-ish boot, not degrading further.
3. notes/77's settle-time-vs-scan-dwell measurement and the RX-blackout
   re-check (notes/77 Part 6) remain untouched across notes/78-80 now -
   genuinely the most-neglected open threads.
4. If chasing `ac_state_once` further doesn't pan out, notes/77 Part 3's
   conclusion stands: a real `git bisect` in `~/src/linux` is the honest
   next step for the kernel-side root cause, at the cost of real local
   kernel builds per step.
