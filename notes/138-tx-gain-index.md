# 138: TX gain: we sit at index 64 of the stock table; more gain is not clearly better at 1 m

Scoping of TX calibration (Alessio's driver, his capture notes, our notes 16–21, 108):

- Our fixed TX gain (table 7 `ff00/07cf/00a7`, bbmult 0x3f) is exactly **index 64** of `acphy_txgain_epa_2g_2069rev4`, the table wl loads on 2.4 GHz. It is the reset value, nothing in our init sets it. Index 0 is the highest gain (`ff00/ffff/00a7`, bbmult 0x44).
- wl's power loop ran at index 0x26/0x19 (ch6) and 0x16/0x14 (ch1) on this machine (notes/136): more gain than we use.
- A TX IQ/LO calibration exists in Alessio's driver only as part of his RX-IQ chain (~1000 lines, results in table 0xc 0x60+4*core), validated on 5 GHz routers only; his driver refuses 2.4 GHz. Our own txcal experiments (notes/16–21) ran safely but the candidate sweep read flat. Not a small step.

New: `b43_phy_ac_txpwr_by_index()` and the table (`b43_phy_ac_txgain_2g`), behind `ac_txidx` (default -1 = unchanged, applied on a channel switch). Live without reload: scratchpad `gi.sh` writes an entry through debugfs.

Upload next to the router, A-MPDU on, 8 s runs:

| index | 32 MPDUs per aggregate | 4 MPDUs |
|---|---|---|
| 112 | 0.13 | |
| 96 | 3.5 | |
| 80 | 10.0 | |
| 64 (ours) | 21.8, 14.5, 23.7, 21.6, 22.4 | 23.5, 32.1 (36–43 earlier) |
| 48 | 31.3 | |
| 32 | 33.0, 33.4, 33.7, 31.2, 25.9 | 32.8, 27.8, 25.3 |
| 24 | 35.1, 31.3 | |
| 20 | 14.0, 38.7, 28.0, 32.0 | 20.8, 19.5, 29.4, 30.0 |
| 16 | 42.7, 26.3 | 11.5 |
| 8 | 36.4 | |
| 0 | 15.2 | |

- **Less gain than index 64 collapses the link at 1 m** (index 96: 3.5 Mbit/s). The signal is weak, not too strong: 8–16 index steps of margin.
- More gain lowers the retry share with long aggregates (55 % at 64, 20–30 % at 16–32).
- But at index 16–20, and later at 32 too, runs with 50–390 failed frames appear (frames that fail all 4 requeues), next to runs with none. The spread between runs is larger than the difference between indices, so 1 m from the AP does not decide this.

Conclusion: no default change. The gain index, and after it power control, have to be tuned at a distance where the link is rate-limited by signal, not next to the router.
