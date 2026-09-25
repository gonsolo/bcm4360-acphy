# MMIO trace findings

## Method

`wl.ko`'s low-level register accessors (`osl_writel`/`osl_readl`/etc.) are
real, ftrace-instrumented, kprobe-attachable functions — unlike the
higher-level wrappers (`phy_reg_write`, `si_corereg`, ...) which exist as
symbols but are NOT ftrace-instrumented and can't be kprobed directly.
`bpftrace` scripts: `wl_trace2.bt` (radio toggle only) and
`wl_reload_trace.bt` (full `rmmod`/`modprobe` reload — more
representative of cold init). Raw logs: `wl_trace2.log`,
`wl_reload_trace.log`.

## Finding 1: writes cluster into a small, fixed address set

Both captures (radio-toggle-only and full module reload) hit only ~24-32
distinct 32-bit addresses, all within a narrow ~0x3000-byte window based
around `0xffffcabb012c0000` (the ioremap'd kernel VA for this boot;
will differ next boot). One address dominates all others by 1-2 orders
of magnitude (75k / 13k hits in ~20s in the two captures respectively).

This does **not** mean there are only ~24 real hardware registers in use
— it means most PHY/radio register access goes through **indirect
control+data addressing**: write the logical register number to one fixed
MMIO address, then read/write the value through another fixed address.
The logical register identity lives in the *value*, not the address.

## Finding 2: this matches b43's own known legacy indirect-register idiom

`reference/b43/b43.h` defines (for older, already-supported chips):

```
#define B43_MMIO_RADIO24_CONTROL   0x3D8
#define B43_MMIO_RADIO24_DATA      0x3DA
#define B43_MMIO_PHY_CONTROL       0x3FC
#define B43_MMIO_PHY_DATA          0x3FE
```

Assuming the observed addresses sit in a register window based at
`0xffffcabb012c4000` (i.e. treating `0x4000` as this core's window base —
inferred, not confirmed), the busiest address in both captures,
`...43fc`, lands at relative offset **exactly 0x3FC** — the same value as
`B43_MMIO_PHY_CONTROL` in the legacy map. That's a strong, non-coincidental
match: the base D11 MAC-core register block appears to have kept the same
layout across chip generations (only the PHY-specific table contents and
radio chip differ), which is plausible since this low-level block predates
the AC-PHY/radio split.

Other addresses in the capture, treated the same way (offset = addr -
0x4000):

| offset | notes |
|--------|-------|
| 0x3fc  | dominant register, thousands of hits — matches `B43_MMIO_PHY_CONTROL` |
| 0x160/0x164/0x166 | control+data pair, written in immediate WR32/WR16 succession — plausible newer-generation PHY_CONTROL/PHY_DATA equivalent |
| 0x120/0x124/0x128/0x12c | triple, written close together — plausible RADIO_CONTROL/DATA analogue |
| 0x020, 0x1e0, 0x224, 0x240/0x244, 0x2c0/0x2c4/0x280/0x284, 0x5408, 0x7064, 0x7140 | seen less often, not yet correlated |

**Caveat**: the `0x4000` base assumption is inferred from clustering, not
verified against an actual `osl_reg_map()` call (none was captured — the
mapping already existed before our trace started). Treat all of the above
as a working hypothesis, to be checked against the decompiled
`phy_reg_write`/`si_corereg`/`ai_corereg` call sites once Ghidra output is
available — those functions will show the *actual* constant offset used
in the `mov`/`lea` immediately before the call, which is ground truth.

## Next
- Cross-reference decompiled `phy_reg_write` (and friends) call sites
  against these offsets to confirm or correct the mapping.
- Re-run a reload trace with an `osl_reg_map` breakpoint hit captured
  (e.g. trace during a cold boot rather than post-hoc rmmod/modprobe) to
  nail the true BAR-relative base.
