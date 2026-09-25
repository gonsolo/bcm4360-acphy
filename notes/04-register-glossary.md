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

## PHY registers, round 2 — TX tone/playback subsystem (fully understood)

| reg | role |
|-----|------|
| 0x140 | "classifier" control (`wlc_phy_classifier_acphy` is a plain RMW helper for it) — bits gate which signal types (OFDM/CCK/etc) the carrier-sense logic reacts to |
| 0x339 | carrier-search-related threshold, saved/restored around forced carrier-search windows (state struct offset `+0x904`) |
| 0x382 | bit 0x8000 = alternate tone-playback-enable path (used when `param_4` "some mode" is set); bit 0x4000 cleared when stopping playback if status showed a certain bit |
| 0x400 | saved/restored around playback start; bit 0 set to trigger something (read back to restore original value after) |
| 0x403 | playback-busy status register — polled (bit 0) with a ~40-iteration/10us-step timeout when stopping tone playback |
| 0x460 | tone playback control: bit 0 = enable (alternate path from 0x382), bits cleared (`&0xfffb`, `&0xfffe`) when stopping |
| 0x461, 0x462 | written `0xffff`/`0x3c` when starting playback — likely gain/repeat-count for the tone generator |
| 0x463 | sample-count-minus-1 for the tone table, written when starting playback |
| 0x464 | playback status, read at stop time to decide which cleanup path (bit0/bit1) |
| 0x471 | playback enable bits: bit0 = enable, bits 2/4/6 = per-bandwidth (20/40/80MHz) selector matching the `param_3 & 0x3800` bandwidth field seen elsewhere |

## Table IDs, round 2

| table_id | role |
|----------|------|
| 0x0e | **tone-playback sample table** — I/Q sample pairs (10-bit each, packed into a 32-bit word), written by `wlc_phy_tx_tone_acphy` from CORDIC-synthesized sine/cosine data. Width 0x20 (32-bit entries). |

## Subsystem now fully understood: TX calibration tone generation & playback

`wlc_phy_tx_tone_acphy(pi, freq_param, amplitude, mode4, mode5, stop_flag)`:
1. If starting a new tone (amplitude != 0): compute sample count from
   current channel bandwidth (20/40/80MHz -> 0x14/0x28/0x50 samples),
   synthesize I/Q pairs via `wlc_phy_cordic`, scale by amplitude, pack
   into table 0x0e.
2. Save (`FUN_00199491`) or restore (`FUN_0019d224`) the gain-table
   entries at table 0x0c positions {0x63,0x67,0x6b,0x6f}/
   {0x73,0x77,0x7b,0x7f} per chain — these are exactly the same
   positions used by `wlc_phy_stopplayback_acphy`, confirming
   playback start = "save gain, force known gain for tone test",
   playback stop = "restore original gain".
3. Optionally force carrier-search-suppressed state
   (`wlc_phy_stay_in_carriersearch_acphy`) so normal RX doesn't react
   to the injected tone.
4. Either start playback (`0x471`/`0x461`-`0x463` sequence) or stop it
   (`0x400`/`0x460`/`0x382` sequence with a busy-poll on `0x403`).

`wlc_phy_stopplayback_acphy` is the simplified "just stop, don't
reconfigure" version of step 4/2, and calls `wlc_phy_resetcca_acphy`
(clear-channel-assessment reset) afterward to resume normal RX.

`wlc_phy_stay_in_carriersearch_acphy` is a refcounted force-carrier-
search helper: on the 0->1 transition it disables normal classifier
response (`classifier_acphy` mask 7 -> narrowed value) and OFDM CRS
(`wlc_phy_ofdm_crs_acphy`); on 1->0 it restores them. This is standard
"don't let RX think a calibration transmission is a real received
frame" bookkeeping.

## PHY registers, round 3 — RF sequencer & RX-force helpers (fully understood)

| reg | role |
|-----|------|
| 0x400 | general enable/mode reg — bit 0/1 (`\|3`) set to kick off RF sequencer |
| 0x402 | RF-sequencer **trigger** bitmask (`wlc_phy_force_rfseq_acphy`'s `param_2` selects which of 6 canned bitmasks: 1,2,4,8,0x10,0x20) |
| 0x403 | RF-sequencer **busy/done** status — same register used by `wlc_phy_tx_tone_acphy`'s playback-stop poll; confirms 0x403 is a general "hardware sequencer busy" status shared by multiple sequencer types, polled with the same ~10us-step timeout pattern everywhere it's used |
| 0x6d4, 0x6da (+0x200/chain) | per-chain RX-force-known-state registers, toggled by `FUN_001986fc` when entering/leaving forced-carrier-search — for chip type 0 writes a saved/`0xffff` value to 0x6da, otherwise masks bit 0x4000 on 0x6d4 |

`wlc_phy_force_rfseq_acphy(pi, seq_id)`: generic "kick a canned RF
sequencer step and wait for it to finish" helper — saves/restores 0x400
and 0x19e around the operation, sets the trigger bit in 0x402, busy-polls
0x403. This is the same low-level primitive `wlc_phy_switch_radio_acphy`
and `wlc_phy_tx_tone_acphy` both build on top of, just exposed as a
reusable helper for 6 known sequences (radio warmup, TX/RX gain settle,
etc. — exact meaning of each `seq_id` not yet determined, would need
cross-referencing every call site).

## Open call-graph threads (not yet decompiled)

- `wlc_phy_cordic` — CORDIC sin/cos generator. Purpose is unambiguous
  from context; low priority to decompile (standard algorithm, can be
  reimplemented from any CORDIC reference rather than reverse-engineered
  bit-for-bit, unless exact rounding behavior matters).
- The remaining, not-yet-visited callees of `FUN_001ac9b6` beyond what
  we've covered (it's 837 lines; we've now covered most of its callee
  set but haven't re-read the full body against what's now known).
- `wlc_phy_cals_acphy`'s other phase cases (1, 2-12, 14-16, 18, 19) call
  additional `FUN_xxxxxxx` helpers we haven't pulled in yet.
- `wlc_phy_attach_acphy` — huge (~6KB) struct-init function, partially
  viewed via raw objdump early in the session, not yet re-examined via
  clean Ghidra decompilation.
- Embedded constant tables `DAT_00558d60`, `DAT_00558e00`,
  `DAT_00558e30` — not yet extracted as raw bytes.

## Fully-closed subsystems (safe to treat as "done" for a future port)

1. Bus access primitives (register primitives doc)
2. Radio power on/off sequence for chip 0x4360 (session log — TODO copy
   into a note file)
3. TX calibration tone generation & playback (this file, section above)
4. Generic RF-sequencer trigger/wait helper
5. Forced-carrier-search RX suppression helper

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
