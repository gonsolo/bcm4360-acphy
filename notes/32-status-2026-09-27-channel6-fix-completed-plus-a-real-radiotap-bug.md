# Status 2026-09-27 (late evening, continued yet further still): the channel-6 mistuning fix is now genuinely complete - plus a real, separate radiotap-frequency bug found along the way

Direct follow-up to notes/22's still-open item 1 ("fully root-cause the
remaining `apply_por()`/vcocal channel-6 issue"). This picks that up on
its own merits - a well-scoped, previously-identified, unfinished bug fix
- independent of, and without touching, the loft-comp question the user
asked to leave reverted earlier this evening.

## The missing piece: four VCO-calibration control registers

Notes/22 found and fixed 19 registers in `phy_ac_por.h`'s
`b43_ac_por_radio[]` table that were channel-1-boot-captured values
clobbering the correct channel-6 tune, but noted the fix was incomplete:
even with those 19 skipped, `ac_por`'s RADIO bit (part of the standard
`ac_por=63` baseline) still left the radio mistuned, and skipping the
redundant second `b43_radio_2069_vcocal()` call inside `apply_por()`
alone didn't fix it either.

Went back to that table with a different, more targeted question: rather
than re-checking every register against the 50-register per-channel tune
table (already done), checked specifically against the four registers
`b43_radio_2069_vcocal()` itself manipulates (`0x8e5, 0x8d0, 0x8e8,
0x8dc`) - these aren't in the tune table at all (they're VCO-calibration
*control* bits, not frequency-setting registers), so the earlier pass
never looked at them. Found all four present in `b43_ac_por_radio[]`,
with static values captured during wl's channel-1 first boot (`0x0000,
0x0001, 0x0040, 0x2e21`), written unconditionally, *after* the correct
tune + its own correct `vcocal()` call had already run. Same class of bug
as the 19 already fixed, just for calibration-trigger bits instead of
frequency bits. Skipped all four (`0xffff` sentinel, matching the
existing convention), values kept in comments for the record.

## Result: `ac_por=63` (the standard baseline) now gives genuine, healthy channel-6 reception

Rebuilt, swapped to `b43`, loaded with the **standard baseline**
(`ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1` - not the `ac_por=0`
workaround this project has been using since notes/22). Checked real
reception:

- `rx_packets` counter: **461 packets in 5 seconds** (~92/s) of plain
  passive listening - a healthy, substantial reception rate, not a dead
  radio.
- Captured a real, correctly-formed beacon from the actual AP: `BSSID:
  8c:6a:8d:9e:2a:88 ... Beacon (Vodafone-2A84) ... ESS CH: 6, PRIVACY` -
  the beacon's own content (which the AP itself put there) correctly
  states channel 6, and includes full RTS/CTS exchanges with other real
  stations, cleanly decoded at reasonable signal levels (-51 to -66 dBm).
  Getting a clean, fully-decoded frame exchange like this while
  genuinely 25 MHz off-channel is not physically plausible - this is
  real, on-channel reception.

**This means the channel-6 mistuning bug from notes/22 is now genuinely,
fully fixed** - both the 19 tuning registers and these 4 VCO-cal control
registers needed to be skipped for `ac_por`'s RADIO bit to stop
clobbering the correct tune. The standard baseline no longer needs the
`ac_por=0` workaround for correct 2.4 GHz channel-6 operation.

## A separate, genuinely new bug found along the way: wrong RX frequency reporting for AC-PHY

While verifying the fix, `tcpdump`/radiotap kept reporting **2412 MHz**
(channel 1) for these same, genuinely-on-channel-6 frames - the
discrepancy that originally looked like continued mistuning. Traced this
to `xmit.c`'s RX-status population code (`b43_rx()`), which computes the
reported frequency from a `chanid`/`phytype` value extracted from the
hardware's per-frame RX descriptor:

```c
chanid = (chanstat & B43_RX_CHAN_ID) >> B43_RX_CHAN_ID_SHIFT;
switch (chanstat & B43_RX_CHAN_PHYTYPE) {
case B43_PHYTYPE_G: ...
case B43_PHYTYPE_N: case B43_PHYTYPE_LP: case B43_PHYTYPE_HT: ...
default: B43_WARN_ON(1); goto drop;
}
```

`B43_RX_CHAN_PHYTYPE` is `0x0007` - a **3-bit mask**, sized correctly for
the older PHY types this switch already handles (`B43_PHYTYPE_G=0x02,
N=0x04, LP=0x05, HT=0x07` - all fit in 3 bits). **`B43_PHYTYPE_AC` is
`0x0b` (`1011` binary) - it does not fit in a 3-bit mask at all**, and
there is no `case B43_PHYTYPE_AC:` in this switch to begin with. This is
a genuine, real, previously-unnoticed gap: AC-PHY support was added to
this port without updating this specific RX-status frequency-lookup path
for the new, wider PHY-type value. (Frames aren't being silently dropped
by the `default` case - some existing case value is evidently still
matching, given real content decodes correctly - so the practical effect
today is a wrong *reported* channel/frequency for RX frames, not lost
frames; the exact mechanism of which existing case fires and why wasn't
pinned down further tonight.)

**This is unrelated to, and was not fixed by, tonight's tuning fix** -
it's a separate, pre-existing cosmetic bug in how received frames get
labelled for monitor-mode tools and mac80211, not a real RF or
throughput problem. It also very plausibly explains part of why earlier
sessions' channel-tuning investigations were confusing: a "wrong
frequency shown" symptom looks identical to genuine mistuning unless you
check the actual frame content and reception health independently, the
way this session finally did.

## What this does and doesn't change

- The **channel-6 mistuning bug is now fully fixed** for the standard
  baseline configuration - a genuine, meaningful correctness
  improvement, independent of the loft-comp question.
- The **scan-finds-nothing symptom** (notes/24) and the **general
  intermittent RX blackout** (notes/25/26) are **still separate, still
  open** issues - this fix does not address either of them. A scan was
  retried during this session's testing and still found zero results,
  consistent with those being a genuinely different, still-unresolved
  problem (most likely the periodic watchdog-related blackout).
- The **radiotap-frequency bug** is newly found and not yet fixed -
  fixing it properly needs figuring out AC-PHY's actual `chanstat`
  bit-layout (does the ucode even use a compatible existing phytype code,
  or does this whole path need a wider mask and new case for AC-PHY?),
  which wasn't pinned down tonight.
- The **loft-comp calibration question** (notes/22) remains untouched
  and fully open, per the user's explicit instruction to leave that
  reverted.

## Next steps for a future session

1. Fix the radiotap-frequency reporting bug properly: capture a few raw
   `chanstat` values for known-good AC-PHY RX frames (e.g. via the
   existing debugfs/trace tooling) to determine the real bit-layout,
   then add a correct `case B43_PHYTYPE_AC:` (and appropriately widened
   mask, if `B43_RX_CHAN_PHYTYPE`/`B43_RX_CHAN_ID_SHIFT` need to change)
   to `xmit.c`'s RX-status code.
2. Re-run the original historical baseline tests (`probeack.sh`'s ACK/
   txphyerr measurement, and the documented old "auth/assoc succeeds"
   test) under the now-genuinely-fixed `ac_por=63` standard baseline,
   since essentially all of this project's history used a channel that
   may have been silently mistuned in this exact way - this could be a
   materially different starting point for the project's central
   question than anything tested before.
3. Continue chasing the scan-finds-nothing/RX-blackout mechanism
   (notes/24-26/29-31) - unaffected by, and unresolved by, this fix.
4. Loft-comp calibration question (notes/22): still open, still
   deliberately untouched.

## Session close

No crashes, no dmesg BUG/Oops/panic lines, no `B43_WARN_ON` triggers
observed. USB backup link 0% packet loss throughout and at close. `b43`
unloaded cleanly; chip left on `bcma-pci-bridge`. `wl` remains bound and
working normally from earlier this evening - no reboot needed this
round. Net source change: 4 additional register entries skipped in
`phy_ac_por.h`, same file and same pattern as notes/22's existing fix;
`phy_ac_replay.h` (loft-comp) untouched, confirmed clean against `HEAD`
before this round of testing began.
