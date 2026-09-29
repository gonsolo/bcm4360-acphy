# wl's extra IRQ mask bits: real diff found, tested, does NOT fix the NAP problem

Direct follow-up to notes/60, same day.

## The diff

Mined the existing real wl association trace
(`traces/wl-init-20260927-184726.trace` - full ifdown/ifup cycle, already
captured for notes/19-22) for `B43_MMIO_GEN_IRQ_MASK` (offset 0x12C)
writes. Trace addresses are raw ioremap'd VAs whose low 12 bits are the
MMIO offset directly (confirmed: `...8120`/`...8128` match
MACCTL/IRQ_REASON). wl's steady-state mask is `0xb0e7a860` (it toggles to
0 and back periodically, ~100ms apart - looks like a beacon-driven
critical-section guard, not relevant here).

Our `B43_IRQ_MASKTEMPLATE` is `0x38058A64`. Bit-diffed:
- wl has, we don't: `0x80e22000` - `B43_IRQ_TIMER0` (bit13),
  `B43_IRQ_CCA_MEASURE_OK` (bit17), three bits with **no name anywhere in
  b43.h** (21/22/23 - `0x00200000`/`0x00400000`/`0x00800000`), and
  `B43_IRQ_TIMEOUT` (bit31).
- we have, wl doesn't: `0x8000204` - `TBTT_INDI`, `MAC_TXERR`,
  `UCODE_DEBUG` (all generically plausible, not investigated further).

Added `ac_irq_extra` module param (default off) that ORs wl's extra bits
into `dev->irq_mask` for AC only (`B43_IRQ_AC_EXTRA_MASK` in b43.h).

## Test: negative

Loaded with `ac_irq_extra=1`. 5/5 connect attempts still failed. Sampled
the live PSM PC (same method as notes/60) during one of the failures:
1729/1958 samples (88%) still at `0x000F` (NAP) - if anything a *higher*
NAP fraction than notes/60's baseline sample, not lower. The extra
unmasked sources made no visible difference to the sleep/wake pattern.

## Why this makes sense in hindsight

`B43_MMIO_GEN_IRQ_MASK` gates which IRQ_REASON bits the **host** CPU gets
interrupted for - it's downstream of whatever wakes the D11 core's own
PSM from NAP, not the same gate. The PSM's own wake-source mask is a
separate, ucode-internal thing: notes/60 already found the loop writes
`IHR[0x40] = 0xFFFF` (arm-everything) right before every NAP, which this
result is consistent with - the PSM was already listening broadly, so
widening the host's separate IRQ mask couldn't have changed what wakes
it. Ruled out; reverted to default (`ac_irq_extra=0`).

## Open question, revised

If the PSM already wakes on (near-)anything, the gap isn't "not enough
wake sources armed" - it's either (a) the event that should fire (e.g.
the DMA TX-post actually reaching the D11 core as a wake pulse) isn't
happening, or (b) it wakes, re-checks its own dispatch predicate at
0x0000-0x000E, finds nothing it considers actionable, and naps straight
back down - a "wakes but decides there's nothing to do" bug, not a
"doesn't wake" bug. (b) is more consistent with notes/60's own data:
several of the observed wakes (10e2, 0045, 00de, 0105) lasted exactly one
~10ms sample before returning to NAP, rather than running for the many
instructions a real dispatch (0x0105 CALLS target, 0x11xx block) would
take.

Next: trace what SHM/SCR flags the 0x0000-0x000E predicate actually
reads (`17AC`/`17AD` SCR bits, `ShmDir 0x30`/`0x31`), and what sets them
in wl's real trace right after each DMA TX-post, vs what (if anything)
this port's `b43_dma_tx()` / TX-post path sets today.
