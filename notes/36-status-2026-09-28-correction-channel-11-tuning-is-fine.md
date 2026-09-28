# Status 2026-09-28 (cont'd): CORRECTION - channel 11 tuning is fine; notes/35's hypothesis was wrong

Direct, immediate correction to notes/35. Before treating "generalize the
channel-6-specific tuning fix to other channels" as the new top priority, I
should have first checked whether this project already had an answer -
it did.

**notes/22 already established, explicitly and directly**: "Channels 1, 3,
9, and 11 all retune correctly when tested the same way - this is specific
to channel 6." The channel-6 mistuning bug (notes/22-32's whole subject)
happened because `phy_ac.c`'s `switch_channel()` only runs the extra
`b43_ac_replay`/`b43_ac_por` reapplication for `new_channel == 6`
specifically - and that reapplication itself was the *source* of the
clobbering (it replays wl's channel-1-boot state *after* the correct
per-channel tune, for channel 6 only). Channel 11 was never subject to that
reapplication at all (gated out), and was independently confirmed, back in
notes/22, to tune correctly via the regular `b43_phy_ac_tune()` path alone
- there was never a channel-11-specific bug to find.

Verified this directly, live, right now (chip currently parked on channel
11 since that's the AP's real current channel):

```
tcpdump -i wlp3s0b1 -n -e ...
Beacon (Vodafone-2A84) ... ESS CH: 11, PRIVACY   -68 to -70 dBm signal
```

Beacons decode correctly, self-report the right channel, and land at a
consistent, reasonable (not exceptionally weak) signal level. Passive RX
rate (~29 pkt/s over 5s) is healthy. This is what "genuinely well-tuned
reception" looks like elsewhere in this project's history - there is no
sign of a channel-11 mistuning problem.

## What this means

notes/35's core observation stands (the AP silently moved to channel 11,
and tonight's 10-trial stability batch plus the zombie-connection finding
were captured there, not on channel 6) - that part is real and worth
knowing. But **the specific explanation offered ("channel 11 needs its own
notes/22-32-equivalent fix") was wrong**, contradicted by evidence this
project already had before I speculated, which I should have checked
first rather than reasoning from an incomplete mental model of how
`switch_channel()` works.

**Restoring the original priority**: the zombie-connection symptom (a
`nmcli`-"connected" session with 100% ping loss and ~50% of outgoing
unicast frames unacked, RX still incrementing) observed on channel 11
tonight is most likely just another manifestation of the same
already-known, still-unresolved intermittent RX-reliability issue
(notes/25/26's ~11% abnormal-gap baseline, the still-unidentified
`wlc_bmac_watchdog` vtable calls investigated in notes/34) - which was
never expected to be channel-specific in the first place (it's plausibly a
periodic PHY/ACI maintenance routine, or similar, that would misbehave the
same way regardless of which channel the radio happens to be tuned to).
The channel-6-vs-11 confound doesn't invalidate this connection; if
anything, seeing the same symptom class on a *known-well-tuned* channel is
mild additional evidence *against* a channel-tuning explanation and *for*
the watchdog/RX-reliability one.

## Corrected priority list

1. The `wlc_bmac_watchdog` vtable resolution (notes/34) is back to being
   the most concrete lead for the disconnect/zombie-connection symptom -
   not superseded by a channel-tuning explanation.
2. The channel-6-vs-11 distinction is still worth keeping in mind for
   *future* testing (know which channel a given test ran on, since the AP
   can move at any time) but is not itself an actionable bug to fix.
3. Everything else on notes/34's list (confirm `wlc_hw+0x80`'s ACI-gate
   bits, the lifetime-expiry-on-second-probe oddity, loft-comp) is
   unchanged.

**Process lesson**: before proposing a new root-cause hypothesis, grep this
project's own notes for whether the specific question was already answered
- notes/22 had the answer to "does channel 11 tune correctly" sitting
right there, and I lost close to an hour of session time (write-up, memory
update, a live re-verification) before checking. The existing README-style
consolidated-summary notes (notes/17) and per-topic searches
(`grep -rn <topic> notes/`) are cheap; re-deriving an already-answered
question from first principles is not.

No hardware changes beyond the read-only channel-11 verification just
performed (a monitor-mode channel set + passive capture, no association).
Chip left on channel 11 in monitor mode (matches the AP's actual current
channel; harmless idle state), USB backup link unaffected.
