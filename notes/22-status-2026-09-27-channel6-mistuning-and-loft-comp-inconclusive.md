# Status 2026-09-27: a real channel-6 radio-mistuning bug found and partially fixed; the loft-comp calibration question is still unanswered

Direct follow-up to notes/20/21. Tonight's goal was to test the one
concrete, actionable finding left over from the calibration work: the
TX-LOFT compensation tables (PHY table 0x42/0x62) were completely zeroed
in `phy_ac_replay.h`, while the real wl trace
(`traces/wl-init-20260927-184726.trace`) showed wl computing and writing
genuine, uniform, non-zero correction values (`0xfdff` for table 0x42/
core0, `0x0201` for table 0x62/core1) right after its calibration sweep.
That data fix was applied via `sed` (128+128 entries corrected) before
this note was written. Testing it turned up two much bigger, unrelated
problems first, and the original question is still open.

## First finding: the AP's real channel changed since the last on-air test

`tools/probeack.sh` kept returning `txackfrm +0 txphyerr +0` with **zero**
probe responses ever captured, even after fixing an unrelated BSSID/CH
env-var passthrough bug (`sudo VAR=val cmd` doesn't reliably forward
through sudo; `sudo env VAR=val cmd` does). Scanning from the USB stick
found why: `Vodafone-2A84`'s 2.4 GHz BSSID (`8c:6a:8d:9e:2a:88`) is now on
**channel 6 (2437 MHz)**, not channel 1. notes/15's earlier successful
on-air test explicitly recorded "the stick's own AP association was
already on channel 1" - the AP has since moved channels (a real,
independent-of-this-project change, likely automatic channel selection on
the ISP's router), and every attempt tonight to force channel 1 to match
the old assumption was simply testing the wrong channel against the
current network.

## Second finding: channel 6 has been silently mistuned this whole time

Switching to the AP's *actual* current channel (6) still gave zero
responses. Passive monitor-mode capture confirmed why, directly and
reproducibly: with the standard baseline load
(`ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1`), requesting channel 6 via
`iw` correctly updates the driver's own reported state
(`channel 6 (2437 MHz)`), but the radio's **real** RX/TX frequency stays
locked at channel 1's frequency (every captured frame's radiotap header
reads `2412 MHz`, not `2437 MHz`). Channels 1, 3, 9, and 11 all retune
correctly when tested the same way - this is specific to channel 6.

Root cause, traced precisely: `phy_ac.c`'s `switch_channel()` calls, in
order, `b43_phy_ac_tune()` (the correct per-channel synthesizer tune,
which also does its own VCO calibration) and then, only for
`new_channel == 6`, `b43_phy_ac_replay_ch6()` and `b43_phy_ac_apply_por()`
- both described as replaying wl's captured post-attach state. This is
gated by `!b43_ac_init_state`, a module param that defaults to (and in
every load command this project uses, stays) false, so in practice this
"once" path runs on *every* switch to channel 6, not just the first.

`b43_phy_ac_apply_por()`'s radio-write table
(`b43_ac_por_radio[]` in `phy_ac_por.h`, generated from
`traces/wl-firstload-20260926-190438.trace` - wl's very first boot, which
associates on channel 1 before anything else runs) is essentially a full
copy of wl's channel-1 radio register state. Comparing it register-by-
register against `radio_2069.c`'s per-channel tuning table found 19
registers (`0x8e6, 0x8e7, 0x8c4, 0x8c5, 0x8c7, 0x8c8, 0x894-0x897,
0x899-0x89c, 0x112, 0x629, 0x65b, 0x65e, 0x668`) that are genuinely
channel-dependent and differ between channel 1 and channel 6, all with
channel-1 values baked into this "apply once on channel 6" table. Since
`apply_por()` runs *after* the correct tune, it silently overwrote the
correct channel-6 synthesizer state with channel-1's - a real, concrete,
fully-evidenced bug, unrelated to the loft-comp question this session set
out to test.

## Fix applied, and its limit

Marked all 19 conflicting entries as skipped (`0xffff` sentinel, the
existing convention this table already uses for disabled entries) in
`phy_ac_por.h`, keeping the original captured value in a comment for the
record. Rebuilt and retested: **this alone was not sufficient.** With the
register conflicts removed but `apply_por()`'s radio block still calling
`b43_radio_2069_vcocal(dev)` a second time (its own line, gated
separately, not per-entry), real RX was completely silent - zero packets,
even our own neighbors' beacons. Testing systematically:

- `ac_por=0` (por disabled entirely, `ac_replay=1` still on): **correct**
  - 74 real packets in 6s, all at 2437 MHz, including the AP's own beacons
    at a plausible-if-weak signal level.
- `ac_por=127` (`63 | 0x40`, an existing flag that skips the second
  `vcocal()` call): wrong again - 387 packets, but all at 2412 MHz.

So the second `vcocal()` call is not simply redundant-and-safe to skip,
and the register-table fix alone does not explain the full picture -
there is evidently at least one more channel-dependent register in
`b43_ac_por_radio[]`'s "kept" (non-tuning-table) entries that this
project's simplified 50-register tuning table doesn't cover, and/or a
real ordering dependency around the two `vcocal()` calls that isn't
understood yet. **Not resolved tonight** - flagged honestly rather than
guessed at further. The `phy_ac_por.h` register fix is still correct and
worth keeping (those 19 values are objectively wrong for channel 6
regardless), but `ac_por`'s RADIO bit should be considered untrustworthy
for channel 6 until this is fully run down.

**Practical workaround used for tonight's actual test:** `ac_por=0` with
`ac_replay=1` gives verified-correct channel-6 tuning (the loft-comp fix
lives in `phy_ac_replay.h`, gated by `ac_replay`, entirely independent of
`ac_por`), so that's the config the loft-comp test below actually used.

## Third finding: a large, unexplained RX signal-strength gap

Once genuinely on channel 6, the AP's own beacons were receivable but
weak - **-95 to -96 dBm** on `b43`. At the same moment, the USB stick
(`wlp0s20u1`), physically part of the same laptop, showed **-60 dBm**
signal for the identical BSSID on the identical channel. A ~35 dB gap is
far more than antenna-placement differences would explain on their own.
notes/15's earlier (channel-1) on-air test described "strong signal for
both the AP and our own internal chip" with real, successful two-way ACK
exchange - a qualitatively different, healthy-looking link. Whether
tonight's weak reading reflects a genuine RX gain/sensitivity problem
specific to channel 6 (plausibly related to the same register-table gap
above), some other change since notes/15, or is confounded by not
actually knowing today's real physical distance/orientation to the AP, is
**not established** - noted honestly as open, not investigated further
given time already spent tonight.

## The original question: still unanswered

With the channel now genuinely correct (6, confirmed via real beacon
reception), `probeack.sh` returned `txackfrm +0 txphyerr +0 txallfrm
+49`, with no probe responses captured. **Caught a real mistake before
trusting that number, though: `phy_ac_replay.h`'s loft-comp fix (the
`0xfdff`/`0x0201` correction, applied via `sed` earlier this session) had
silently reverted to the original all-zero state in the working tree by
the time this test ran** - `git diff`/`git status` showed the file clean
against HEAD, with no commit of the fix ever made, meaning the `+49`
result above was measured *without* the fix active at all. A backup
happened to survive at `/tmp/phy_ac_replay.h.loftcomp_fix` (byte-for-byte
diffed to confirm it was exactly the intended 256-line change and nothing
else) and was restored, rebuilt, and retested: `txackfrm +0 txphyerr +0
txallfrm +46` - i.e. **unchanged**, now with the loft-comp fix genuinely
in place.

Given the ~35 dB weak-signal finding above, neither result can be
attributed to the loft-comp fix (or its absence) with any confidence - a
link this marginal may simply not sustain a full request/response round
trip regardless of calibration correctness. **This is not evidence
against the loft-comp fix; it's an inconclusive test that needs to be
redone once the signal-strength gap is understood**, ideally with the
user physically closer to the AP to remove that variable, or after
root-causing the RX gap itself.

The `phy_ac_replay.h` fix is now correctly restored and present in the
working tree (verified in place before committing) - future sessions
should confirm `git diff` is clean going forward and not assume a
mid-session working-tree edit survived without checking.

## What's genuinely established tonight, versus what isn't

Established, with direct hardware evidence:
- The AP's real 2.4 GHz channel changed (1 → 6) since notes/15.
- `phy_ac_por.h`'s channel-6 "apply once" radio table silently mistunes
  the synthesizer away from channel 6's real frequency; partially fixed,
  root cause not fully closed.
- `ac_por=0`/`ac_replay=1` gives genuinely correct channel-6 tuning right
  now.
- There's a real, unexplained ~35 dB RX signal gap between `b43` and a
  reference radio for the same AP on channel 6.

Not established:
- Whether the loft-comp calibration fix (`phy_ac_replay.h`) changes the
  firmware-autonomous ACK success rate at all - today's test conditions
  were too confounded to tell.
- Whether the RX signal gap is a real hardware/calibration defect or an
  artifact of tonight's specific test setup.
- The full root cause of `apply_por()`'s channel-6 problem beyond the 19
  registers already fixed.

## Next steps

1. Root-cause the remaining `apply_por()`/channel-6 mistuning fully
   (check the "kept" non-tuning-table entries in `b43_ac_por_radio[]` for
   ones that might still be channel-dependent, and understand why
   skipping the second `vcocal()` call alone reverts to channel 1 instead
   of holding channel 6).
2. Root-cause or at least characterize the ~35 dB RX signal gap - ideally
   with a controlled, close-range test to rule out simple distance/
   orientation confounds.
3. Only then, retest `probeack.sh`'s ACK/txphyerr rate with the loft-comp
   fix in place, under conditions that don't confound the result.
4. `wl` needs a reboot to come back, same as every previous round -
   ask the user before doing it themselves.
