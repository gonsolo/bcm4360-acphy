# Register access primitives — CONFIRMED ground truth

Decompiled directly from `wl.ko` (see `decompiled/phy_reg_write.c`,
`phy_reg_mod.c`, `write_radio_reg.c`, `read_radio_reg.c`,
`mod_radio_reg.c`). All addresses below are `<core MMIO base> + offset`,
where the base is `*(long *)(phy_or_dev_struct + 0x148)`.

## PHY register access — byte-for-byte matches b43's existing constants

- `phy_reg_write(pi, regnum, val)`:
  `osl_writel((val << 16) | (regnum & 0xffff), base + 0x3fc)`
  — **one 32-bit write**, combined control+data, to `base+0x3fc` ==
  `B43_MMIO_PHY_CONTROL` in `reference/b43/b43.h`.
- `phy_reg_mod(pi, regnum, mask, set)`:
  write `regnum` (16-bit) to `base+0x3fc` (`PHY_CONTROL`), then
  read-modify-write `base+0x3fe` (`PHY_DATA`) — separate control/data
  steps, same two addresses as above.
- This fully explains the MMIO trace: `0x3fc` was the single busiest
  address captured (tens of thousands of hits) because *every* PHY
  register access funnels through it.

**Conclusion: `b43`'s existing generic `b43_write16`/`b43_read16`
infrastructure and the `B43_MMIO_PHY_CONTROL`/`PHY_DATA` constants are
directly reusable for ACPHY, unchanged.** No new low-level bus code is
needed — only the higher-level calibration/init logic that decides *what*
to write.

## Radio register access — reveals a bug in the current b43 stub

`write_radio_reg`/`read_radio_reg` pick between **two different legacy
register pairs** based on core revision (`corerev = *(int*)(dev+0x28)`):

```c
if ((corerev == 0x1b || corerev < 0x18) &&
    (corerev != 0x16 || phy->something(offset 0x160) == 6)) {
    // "old" pair
    control = base + 0x3f6;   // B43_MMIO_RADIO_CONTROL
    data    = base + 0x3fa;   // B43_MMIO_RADIO_DATA_LOW
} else {
    // "new" pair
    control = base + 0x3d8;   // B43_MMIO_RADIO24_CONTROL
    data    = base + 0x3da;   // B43_MMIO_RADIO24_DATA
}
```

`reference/b43/phy_ac.c`'s current stub (`b43_phy_ac_op_radio_read/write`)
**unconditionally** uses `RADIO24_CONTROL`/`RADIO24_DATA` — it never
checks core revision. That's a real, fixable bug relative to what the
proprietary driver actually does: on core revisions where the "old" pair
applies, the stub would read/write the wrong hardware registers entirely.
This is a concrete, actionable correction for whenever `phy_ac.c` gets
real logic.

## Radio-core (chain) selection bits — `read_radio_reg`

The struct field at offset `+0x160` off the phy struct holds a "current
radio core index" (0/2/4/5/6/7/8/10 seen as cases), which gets OR'd into
the register number before addressing:

```c
switch (radio_core_idx) {
  case 0:            regnum |= 0x40;  break;
  case 2:             regnum |= 0x80;  break;
  case 4: case 5:      regnum |= (some_count < threshold) ? 0x100 : 0x200; break;
  case 6: case 7: case 8: case 10: regnum |= 0x200; break;
}
```

This is a per-radio-chain addressing scheme for the multi-core (up to
3-chain MIMO) radio attached to ACPHY — not discoverable without seeing
this code. Needed for any multi-antenna-chain register access.

**Caveat on struct offsets**: offsets like `+0x148`, `+0x160`, `+0x226`,
`+0x228` are into wl.ko's own private struct layouts, not b43's. They'll
need to be re-derived/renamed as real fields once we understand more of
the struct (attach function - see `decompiled/wlc_phy_attach_acphy.c` -
is the best source for figuring out the struct layout, since it
initializes most fields with named-looking constants).
