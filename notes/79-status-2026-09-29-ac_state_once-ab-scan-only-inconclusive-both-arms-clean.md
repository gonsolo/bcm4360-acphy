# Status 2026-09-29 (part 3): `ac_state_once` A/B on scan-triggered
suspend failures - both arms clean, inconclusive, and why that's itself
informative

Direct continuation of notes/78, same day, same boot (kernel 7.2.7,
still no reboot/reload since session start). Ran the A/B test notes/78
flagged as the top next step: 10x `nmcli dev wifi rescan` with
`ac_state_once=0` (Arm A, the default), then 10x more with
`ac_state_once=1` (Arm B), counting `b43-phy1 ERROR: MAC suspend failed`
lines in `dmesg` for each arm. `sudo dmesg -c` was used to clear the
ring buffer once before Arm A for clean counting.

## Results

- **Arm A** (`ac_state_once=0`): 10/10 rescans, 10/10 triggered a
  `replayed vendor ch6 state` line (confirms the 1:1 rescan-to-replay
  correlation from notes/78 again), **0** suspend failures.
- **Arm B** (`ac_state_once=1`): 10/10 rescans, **0** new
  `replayed vendor ch6 state` lines (confirms the knob reliably
  suppresses the replay across a real 10-sample run, not just the one
  spot-check in notes/78), **0** suspend failures.
- Connection stayed up and RX packets climbed normally throughout both
  arms (~800 new packets each arm) - no regression, no instability,
  from either setting.

**This is inconclusive on the actual question** (does suppressing the
replay reduce the 7.2.7 suspend-failure rate?) - you cannot show an
improvement over a baseline of zero. Reverted `ac_state_once` to `0`
(default) at session end, as before.

## Why zero failures in 20 scans is itself worth noting

notes/76's "0/5 to ~40%" failure-rate figures were measured across
**full reload-and-reconnect** attempts (`b43_live.sh`/`connect_test.sh`
style: `rmmod`, replay ch6 state fresh, associate from scratch, 4-way
handshake, DHCP) - i.e. `b43_mac_suspend()` calls happening during
initial association/key-negotiation timing pressure. This session's test
was different: the interface was **already associated and stable** the
whole time, and only *scan-triggered* `b43_mac_suspend()` calls (from an
otherwise-idle, already-working connection) were exercised - no
`rmmod`/reload, no fresh association, no key negotiation. notes/77 Part
5 did trace scan-triggered suspend failures back to real `dmesg`
evidence from a *live, connected* session, so this failure mode does
happen without a fresh reload - but this particular 20-scan sample, on
this particular boot, didn't hit it either way.

Net effect: this test doesn't contradict notes/76 or notes/77, but it
does mean **`ac_state_once` has still not been tested under the
condition that actually produces high failure rates** (fresh
reload+reconnect, per notes/76's own methodology) - only under a milder
condition (scan on an already-stable link) that turned out to be clean
in both arms this session regardless of the setting.

## Next steps for a future session, in order

1. The real test of `ac_state_once`'s effect needs notes/76's own
   methodology (`connect_test.sh`-style fresh reload + reconnect, N
   attempts each arm, counting suspend failures) - not scan-on-a-
   stable-link. This is a materially bigger step up in risk (repeated
   `rmmod`/`insmod` cycling, the exact pattern notes/59/77 flag for
   chip-degradation caution) and probably warrants explicit user sign-off
   before running many cycles, rather than doing it unprompted.
2. Barring that: keep opportunistically watching for a *naturally
   occurring* scan-triggered suspend failure during normal daily use
   with `ac_state_once=1` left on for a while (it's runtime-settable,
   `0644`, safe per notes/78+this note) - a real-world data point costs
   nothing extra, even if it's slower to accumulate than a deliberate
   A/B.
3. notes/77's settle-time-vs-scan-dwell measurement and notes/77 Part
   6's RX-blackout re-check remain open and untouched this session.

## Current state at session end

No source changes. `ac_state_once` reverted to its default (`0`) after
being exercised live in both arms. `netwatch`/postboot overrides still
active from notes/78 (unchanged, no need to redo per boot once set).
b43 remained loaded and associated the entire session (this note plus
notes/78) - no `rmmod`/`insmod` at any point today.
