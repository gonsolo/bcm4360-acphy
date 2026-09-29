# HOSTF2/HOSTF3 confirmed cause of NAP; auth still mostly fails without it

Direct follow-up to notes/60/61, same day. notes/60 found the ucode PSM
naps (sleeps) instead of staying awake to service TX/auth; notes/61 ruled
out the host-visible IRQ mask as the cause and left the real question as
"why does a woken PSM decide there's nothing to do."

## The bug: this port never writes HOSTF2/HOSTF3 at all

The idle loop's own predicate, right before it naps (ucode42.fw
0x000C/0x000D), reads SHM words 0x30/0x31 directly - `B43_SHM_SH_HOSTF2`
(byte 0x60) and `B43_SHM_SH_HOSTF3` (byte 0x62), b43's own long-standing
"hostflags" mechanism (`b43_hf_read`/`b43_hf_write`, main.c). If either
is nonzero, it skips NAP. `grep` across every `.c` file: `phy_g.c`,
`phy_n.c`, `phy_lp.c` all call `b43_hf_write` for their own feature bits;
**`phy_ac.c` calls it zero times.** These two SHM words sit at whatever
the firmware download left them (0).

Mined the real association value from the same wl trace used in notes/61
(`traces/wl-init-20260927-184726.trace`): a 32-bit SHM write to shared
word 0x30 (routing=SHARED, `B43_MMIO_SHM_CONTROL`=0x00010030, then
`B43_MMIO_SHM_DATA`=0x8c05, then the same control word again and
`B43_MMIO_SHM_DATA_UNALIGNED`=0xb051 - the standard b43 32-bit-SHM-write
idiom spanning two words). Decoded: HOSTF2=0x8c05, HOSTF3=0xb051, i.e.
bits 16-47 = `SKCFPUP | N40W | ANTSELEN | MLADVW | PR45960W` plus six
bits (16,18,31,38,44,45) that have no name anywhere in this driver's
`b43.h` - `wl` sets a fuller hostflags picture than b43's own header
enumerates, consistent with those bits being introduced for chips b43
never supported before AC.

## Fix, tested

Added `ac_hostflags` param (default off) to `b43_phy_ac_op_init()`:
`b43_hf_write(dev, b43_hf_read(dev) | 0xb0518c050000ULL)`.

**Causal result: NAP is completely eliminated.** Same PC-sampling method
as notes/60/61: without the fix, 88% of samples during a failed connect
sat at the NAP address (0x000F). With it, **0 of 3882 samples** over a
fresh attempt were at 0x000F - not "less", gone. This is about as clean
a confirmation as this kind of testing gets: the exact predicate the
disassembly named, doing exactly what the disassembly said it would.

**Auth reliability: not fixed.** 13 connect attempts with the fix active:
4 succeeded (~30%) - statistically indistinguishable from the historical
baseline rate without it. The ucode now spins continuously through the
same hot subroutine cluster identified in notes/58 (0107/11ba/11c2/11c4)
instead of napping between calls, but something else still keeps most
auth attempts from completing.

## Where this leaves things

Two independent, now-confirmed facts: (1) this port has a real, fixable
missing-hostflags bug, unrelated to b43-dev's use of the driver so far
just never mattering until AC's specific idle-loop predicate exposed it;
(2) fixing it doesn't fix the connection. The remaining failure mode is
still open - the busy subroutine at 0x1197-0x1210ish (called from 0x01C0/
0x027C) needs actual semantic decoding now that it's not a red herring
from napping, or a fresh wl trace diff focused on what happens inside an
actual auth exchange rather than at bring-up/IFUP (the existing trace
only covers ifdown/ifup, not a live auth captured mid-flow).

`ac_hostflags` left at default off pending that further work - it's a
real, wl-matching fix worth keeping, but "matches wl and demonstrably
changes ucode behavior" isn't the same as "fixes the user-visible bug",
and this project's own convention is not to flip a default until a fix
is shown to actually close the gap it was aimed at.
