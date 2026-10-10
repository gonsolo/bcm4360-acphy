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

## At range (basement, -65..-68 dBm, AP on channel 1): index 64 is nearly dead for HT

Same test, A-MPDU on, 4 MPDUs per aggregate, upload Mbit/s per 8 s run:

| index | runs |
|---|---|
| 64 (old) | 0 (22 packets, all failed), 0 (173 packets, 155 failed) |
| 48 | 7.7, 5.9 |
| 32 | 22.5, 15.5, 8.7 |
| 24 | 14.3, 21.0 |
| 20 | 27.8, 3.8, 22.5 |
| 16 | 3.9, 26.9 |
| 12 | 7.3, 29.4 |
| 8 | 29.5, 4.6, 30.1 |
| 0 | 19.3, 13.2 (90 failed) |

The runs spread widely (one whole round was slow at every index; both adapters share channel 1 here), but the order is clear: 64 does not carry HT at this range, 8–24 does, 0 is past the optimum.

Legacy rates at the same spot do not care: index 20 gives 8.5 / 15.9 up and 9.8 / 8.7 down, index 64 gives 15.3 / 13.4 up and 10.6 / 10.2 down.

**Default now `ac_txidx=20`**, inside the range the stock power loop used here (0x14–0x26). Next to the router index 20 showed some runs with failed frames (above); a fixed index is a compromise until there is real power control.

## 15-minute soak at range, HT + A-MPDU, index 20

Basement, -62..-70 dBm, 26 rounds of 20 s upload + 10 s download, stick pinged every 0.5 s on the same channel.

- Upload 6.1–28.5 Mbit/s, mean 21.4 (legacy here: 8.5–15.9).
- Download 2.6–11.2 Mbit/s, mean 7.5 (legacy here: 8.7–10.6). Worse than legacy: the AP sends us HT frames one by one because we decline its block ack sessions (RX aggregation is not implemented).
- total: pkts 1039014 retries 377763 failed 1481
- No b43 error, no deauth. Stick: 1701 of 1704 pings.

HT + A-MPDU is stable at range and faster up, slower down. Not the default until RX aggregation works.
