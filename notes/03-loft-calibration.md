# LOFT (LO feedthrough) calibration table — real calibration math, decoded

`decompiled/wlc_phy_populate_tx_loft_comp_tbl_acphy.c` is the clearest
example yet of the actual *calibration algorithm* (not just register
plumbing). It builds a 128-entry LOFT (Local Oscillator Feedthrough)
compensation table per TX chain and writes it via
`wlc_phy_table_write_acphy(pi, table_id, count, offset, width, data)`
with `table_id` = `0x42`/`0x62`/`0x82` for the 3 possible chains.

The correction values come from small hardcoded lookup tables
(`local_68`/`local_78`/`local_88` in the decompiled output — literal
magic-number arrays baked into the function). These are genuine
factory/lab-derived calibration constants for this exact
chip/radio combination, not computed at runtime — i.e. this is exactly
the kind of thing that has to be carried over rather than re-derived.

## What this confirms about scope

- The actual calibration *math* layer, not just bus access, is present
  as ordinary (if dense, optimizer-mangled) C and is readable with
  enough effort — this derisks the project further: it's not hiding
  behind firmware or anything unreachable.
- Call graph keeps branching: `wlc_phy_cals_acphy` (dispatcher) →
  `FUN_001ac9b6` (837-line phase-execution engine) →
  `wlc_phy_populate_tx_loft_comp_tbl_acphy` + 8 more anonymous
  `FUN_xxxxxxx` helpers at the same level (IQ cal, TX-tone-based
  measurement, carrier-search handling, etc. — not yet pulled in).
- Each level reveals roughly as many new functions as it resolves —
  this is a real, multi-week decompilation project done honestly, not
  a one-session task, even though every individual piece so far has
  turned out to be tractable.

## Confirmed layer map so far

1. **Bus access primitives** (`phy_reg_write`, `phy_reg_mod`,
   `read/write_radio_reg`) — CONFIRMED, byte-identical to b43's existing
   constants (see `notes/02-register-primitives.md`). Zero new work
   needed here.
2. **Radio power on/off sequence** (`wlc_phy_switch_radio_acphy`) —
   resolved for our exact chip (`acphychipid == 0x4360`), clean register
   list extracted (see chat/session log — not yet copied into a note
   file, TODO).
3. **Calibration dispatcher** (`wlc_phy_cals_acphy`) — phase state
   machine, orchestration only.
4. **Calibration phase engine** (`FUN_001ac9b6`, 837 lines) — real
   calibration steps: TX tone generation, carrier search, LOFT table
   population, IQ-related sub-steps. Partially explored.
5. **Individual calibration algorithms** (LOFT table confirmed; IQ
   imbalance, TX power detector cal, etc. still to pull in) — this is
   where the bulk of remaining work lives.

## Next session should

- Pull in the 8 unnamed `FUN_xxxxxxx` callees of `FUN_001ac9b6`
  (addresses visible via `grep -oE "FUN_[0-9a-f]+" decompiled/FUN_001ac9b6.c`)
  the same way we did for this batch (add to `explicitAddrs` in
  `decompile_acphy.java`, rerun with `-process wl.ko -noanalysis`).
- Start a `notes/registers.md` glossary mapping confirmed PHY register
  numbers (0x19e, 0x40f, 0x408, 0x416, 0x417, 0x1720-0x173e family, etc.)
  to what we've observed them controlling, as they accumulate — don't
  wait until the end.
- Consider whether to attempt actually writing `b43` code yet (start
  with the radio on/off sequence, which is already fully resolved for
  this chip) vs. continuing pure decompilation first.
