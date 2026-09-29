# wl's real watchdog counter identified from decompiled source: macstat[60]

Direct follow-up to notes/72, same session. Went to do what notes/72
said was the honest next step - read wl's actual decompiled code -
instead of more live guessing, and it resolved cleanly.

## Correction: notes/72's "0x158" and this note's "0x158" are different things

`decompiled-si/wlc_bmac_watchdog.c` -> `wlc_bmac_fifoerrors` (a different
function, checks DMA ring status, not related) -> `wlc_phy_watchdog`
(605 lines, already decompiled, covers many PHY types' calibration/ACI
logic in one function). It contains:

```c
sVar10 = wlapi_bmac_read_shm(dev, 0x158);
```

This is a **SHM read**, reached specifically when the PHY type is 4
(N), 7 (HT), or **0xb (AC - confirmed by tracing the branch condition,
`iVar14==0xb` falls through to the same code path as 4/7)** - applies to
our chip. It is a *different, coincidentally-same-numbered* thing from
notes/72's finding: that was a raw MMIO register read at hardware
offset 0x158 (confirmed via the trace's own `raw_va & 0xfff` addressing,
no preceding SHM_CONTROL write). This is an *argument* to a SHM-read
wrapper function, in a completely different address space. Two
unrelated 0x158s. notes/72's 1.024s MMIO-register finding stands
unaffected; it's just not the same thing as this note's discovery.

## Decoding it: falls inside the already-decoded macstat block

`wlapi_bmac_read_shm`'s argument convention matches b43.h's established
byte-offset convention (cross-checked: the same code block's other read,
`wlapi_bmac_read_shm(dev, 0x10c)`, sits right next to `B43_SHM_SH_
BCMCFIFOID` at byte `0x108` - a real, plausible neighbor, not noise).
Byte `0x158` / 2 = word `0xAC`. The macstat block (`tools/
macstat_decode.pl`, from notes/12 weeks ago) starts at byte `0xE0`
(`txallfrm`) and is 64 words long - `(0x158-0xE0)/2 = 60`. **Word 0xAC
is macstat index 60** - inside the already-known counter block, but
past the 50 names this project's decoder currently has (`macstat_
decode.pl`'s `@n` array only goes to index 49/`pmqovfl`; 50-63 were
never named).

## It's live, already-captured data - not a new test needed

`phy_ac.c`'s existing 15-second diagnostic (`b43_phy_ac_log_macstat`)
has been dumping all 64 macstat words to dmesg all session. Pulled
index 60 straight from tonight's already-logged output:

```
1caa
1ce6   (+0x3c, ~15s later)
1d00   (+0x1a)
1d23   (+0x23)
1d57   (+0x34)
```

A real, actively incrementing counter on our own port - roughly +55
every 15 seconds (~3.7/s), not stalled, not zero. Whatever this counts,
our AC port is producing it continuously.

## What wl does with it

```c
sVar10 = wlapi_bmac_read_shm(dev, 0x158);      // read macstat[60]
sVar7 = *(short *)(param_1 + 0x3f0);            // previous tick's value
*(short *)(param_1 + 0x3f0) = sVar10;
iVar13 = (int)sVar10 - (int)sVar7;              // delta since last tick
...
iVar14 = iVar20 - iVar13;                       // iVar20 = delta of ANOTHER
                                                 // counter (SHM byte 0x20)
```

`iVar14` (the difference between two counters' deltas) feeds into a
circular-buffer moving-average computation further down (storing into
`param_1+0x492+idx*2`, shift-based averaging) that's part of this
function's ACI (adjacent-channel-interference) / noise-engine logic for
AC/N/HT PHY types. Not yet traced to full semantic clarity - macstat
index 60 has no name anywhere in mainline b43 (unsurprising - AC PHY
support never existed there), and 600 lines of dense, multi-PHY-type
interleaved decompiled code is more than this session has budget to
fully unravel.

## Honest status

Real, concrete, source-grounded finding, not a guess: identified the
exact counter (macstat[60]) wl's real periodic watchdog reads for our
chip's PHY type, confirmed it's a real, active, already-logged value on
our own port. Its exact meaning and whether our port's *rate* of
incrementing it (not just "nonzero") matches what wl's ACI-averaging
logic expects is still open. Next step for whoever continues: name it
properly in `macstat_decode.pl` (indices 50-63 are all still unnamed,
worth decoding the surrounding context of `wlc_phy_watchdog`'s other
SHM reads at 0x10c/0x20 the same way, and correlating index 60's rate,
not just presence, against real success/failure attempts).
