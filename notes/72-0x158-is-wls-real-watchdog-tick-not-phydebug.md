# 0x158 is wl's real 1.024s watchdog tick; "phydebug"/"CRS|TXF" was an unverified label

Direct follow-up to notes/71, prompted by the user asking "does this
lead anywhere?" - checked rather than answered from confidence alone.

## The label was never verified

`main.c`'s suspend-failure diagnostic (added tonight, notes/58) labeled
MMIO 0x158 "phydebug" and its bits "CRS"/"TXF", borrowed from
`brcmsmac`'s naming convention for a *different* Broadcom driver
family - never checked against real documentation or a real trace for
this specific chip. Separately, mainline b43.h has its own, also-
unverified label for the same address: `B43_MMIO_RADIO_HWENABLED_HI`,
with its one documented meaningful bit at position 16 (`1<<16`) - never
matching any value actually observed (everything seen has been in the
low byte). That constant isn't read by any code path this port
exercises either. Two competing guesses, neither grounded - worth
checking against `wl`'s real behavior before trusting either.

## What wl actually does

Grepped both captured wl traces for reads of offset `0x158` (the same
`raw_va & 0xfff` addressing convention validated repeatedly this
session). `wl` reads it as a genuine 32-bit MMIO register
(`b43_read32`-equivalent), and the read is periodic:

```
2141127137196 R32 ...158 00000040
2142151242361 R32 ...158 00000040   (+1.024105165s)
2143175177649 R32 ...158 00000040   (+1.023935288s)
2144199208874 R32 ...158 00000040   (+1.024031225s)
2145223190686 R32 ...158 00000040   (+1.023981812s)
```

**Precisely 1.024 seconds apart, every time.** This is the exact cadence
`phy_ac.c`'s own old comment (notes/27-31/34) has described as wl's real
periodic watchdog ("wlc_bmac_watchdog/wlc_phy_watchdog... a ~1.024s
cycle doing DMA-error recovery and PHY/ACI recalibration") - a comment
this project has had for days without ever locating the actual
mechanism. This is that mechanism, found by accident while chasing an
unrelated symptom.

The surrounding pattern is identical on every cycle:
```
R32 MACCTL (0x120)
R32 0x158                              <- the tick
W32 SHM_CONTROL = 0x0001058a           <- routing=SHARED, arg=0x58a
R32 SHM_CONTROL (readback/verify)
R16 SHM_DATA_UNALIGNED (0x166)         <- the actual value read
```

Same three-step shape every single time: check MAC state, check 0x158,
read one specific SHM location. Not yet resolved precisely which SHM
word `0x58a` (as the *post-internal-shift* control argument) corresponds
to in plain word/byte terms - the SHARED-routing unaligned-access
arithmetic has already bitten this session once (notes/69's `full_
snapshot.c` bug) and deserves a careful, separate, double-checked pass
rather than a quick guess appended here.

## What this means for the CRS|TXF thread

The *raw, live, reproducibly-measured* correlation from notes/58-71
(this register's value differs tightly between failure and success) is
real and doesn't go away - it's just data, unaffected by what anything
calls it. But the interpretation ("carrier sense", "TX frame pending")
should be treated as unconfirmed from here on, not as established fact
the way earlier notes implicitly did. What IS now confirmed: this
address is genuinely significant - it's the one wl itself polls, on the
clock, as its real watchdog check.

## Next step

Decode the exact SHM word wl reads after 0x158 (careful arithmetic,
cross-check against a live `shm` debugfs read rather than computing
blind), then watch *that* word plus 0x158 together, live, through real
success/failure attempts with `tools/hw_timing.c` - now with the
question reframed correctly: not "what does CRS|TXF mean" but "what is
wl's real watchdog actually checking, and does our port's answer to
that same check differ between success and failure."
