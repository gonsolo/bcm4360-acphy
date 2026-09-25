# Register/table glossary (running, confirmed-from-decompile only)

All PHY register numbers below are arguments to `phy_reg_read/write/mod`
(see `notes/02-register-primitives.md` for how those map to actual MMIO
addresses — this file only tracks the *logical* register numbers).
Per-chain registers use a `+ chain_index*0x200` stride (confirmed in
multiple functions).

## PHY registers (base numbers, chain 0)

| reg  | seen in | apparent role |
|------|---------|----------------|
| 0x19e | many | a "mute/config" control reg — bit 2 toggled around nearly every table read/write (looks like "freeze ADC/pause pipeline while touching tables") |
| 0x408 | switch_radio | cleared (bits &~2) during radio power-down |
| 0x40f | switch_radio, FUN_001982a2 | bit 0x200 cleared on power-down; loaded from state struct on cal-apply |
| 0x416, 0x417 | switch_radio | written 1/0 late in power-down sequence |
| 0x1720-0x173e (chip 0x4360 family, "high" bank) | switch_radio | TX/RX path gate registers, zeroed/maxed during power-down (see notes on session finding) |
| 0x721/0x724/0x725/0x727/0x728/0x729/0x735/0x736/0x737/0x738/0x739/0x73a/0x73c/0x73e (+0x200/chain) | FUN_00193d3a, FUN_001982a2 | per-chain TX gain-control register bank — muted (OR 0x80/0x204) before cal, restored after; also the destination of a large calibration-coefficient load from the state struct |

## Radio registers (chip 0x4360 branch specifically)

| reg | seen in | role |
|-----|---------|------|
| 0x1a, 0x1b, 0x1c, 0x1e, 0x1f, 0x24, 0x29, 0x170/0x184 (+chain*0x200 via `<<9`) | FUN_0019454f (save), FUN_00195603 (restore) | a block of per-chain radio synth/gain-path registers saved before and restored after some cal measurement — likely LNA/mixer gain and filter settings |
| 0x80b/0x80c, 0x8ea/0x8f2, 0x8ed/0x8f5, 0x60c, 0xb/0x20b (chip 0x4335/other-chip branches only — NOT our chip's path) | switch_radio | radio power sequencing for *other* chip variants; chip 0x4360 skips most of this block entirely (see session log) |

## Table IDs (`wlc_phy_table_write/read_acphy(pi, table_id, count, offset, width, data)`)

| table_id | seen in | role |
|----------|---------|------|
| 0x0c | wlc_phy_cals_acphy, FUN_0019d65d, FUN_0019ccd9 (param_4<0xc case) | gain/gain-curve table — 0x0c entries written scaled by a percentage in FUN_0019d65d using embedded constant curves (`DAT_00558e00`, `DAT_00558e30`) |
| 0x07 | FUN_0019d3ac, FUN_0019d550 | per-chain, 3-entry-wide sub-table at offset `chain*10 + {0x100,0x103,0x106}` — read/written together with a per-chain 8-byte extra field via `FUN_00199491`/`FUN_0019d224` (not yet decompiled) — likely LOFT or IQ coefficient storage |
| 0x42, 0x62, 0x82 | wlc_phy_populate_tx_loft_comp_tbl_acphy | per-chain (chain 0/1/2) LOFT comp table, 128 entries, built from embedded correction-offset tables |

## Embedded constant tables found so far (not yet extracted)

- `DAT_00558d60` — 15×4-byte (60 byte) table read by `FUN_0019ccd9`; looks like a `{count, base, stride}`-style descriptor array for 15 different "data classes" used across the table-read/write dispatcher. Worth extracting in full — would explain a lot of the indexing scheme at once.
- `DAT_00558e00`, `DAT_00558e30` — two 9×4-byte gain-curve tables used by `FUN_0019d65d`.

## Open call-graph threads (not yet decompiled)

- `FUN_00199491`, `FUN_0019d224` — called per-chain from the table-7
  read/write pair (`FUN_0019d3ac`/`FUN_0019d550`).
- `wlc_phy_tx_tone_acphy`, `wlc_phy_stopplayback_acphy`,
  `wlc_phy_stay_in_carriersearch_acphy`, `wlc_phy_classifier_acphy` —
  already decompiled (present in `decompiled/`) but not yet read/
  written up.
- Everything else `FUN_001ac9b6` calls beyond the 8 pulled this round.

## Process note for continuing

Pattern that's working well: grep a decompiled function for
`FUN_[0-9a-f]+` and named-but-unpulled callees, add addresses/names to
`explicitAddrs`/`patterns` in `decompile_acphy.java`, rerun with:

```
analyzeHeadless ghidra_proj AcphyProj -process wl.ko -noanalysis \
  -scriptPath . -postScript decompile_acphy.java ./decompiled
```

(fast — auto-analysis is cached, only decompilation reruns, ~seconds to
a couple minutes even for 100+ functions).
