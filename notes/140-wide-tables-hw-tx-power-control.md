# 140: the 48-bit PHY tables on 2.4 GHz: hardware TX power control works, download triples

Follow-up to notes/139. wl loads three PHY tables through the third data port (PHY 0x011, three words per entry). The trace decoder missed them, so b43 never wrote them; `tools/decode_trace.py` now decodes them (width 48 in tables.txt).

On 2.4 GHz (`b43_phy_ac_wide_tables_2g()`, called from phyinit):

- table 0x20, 128 entries: the TX gain table `acphy_txgain_epa_2g_2069rev4`, the same words as `b43_phy_ac_txgain_2g`. Hardware TX power control picks its gain from this table. It was empty on a cold boot, or held whatever wl had left.
- table 0x14, entry 0x33: `e800 0084 d351` (RF sequencer extension).
- table 0x11, 464 entries: 12 fixed cells, 448 cells `d602 007e 4002`, 4 zero cells. In Alessio's driver this is the SROM rpcal coefficient table; the fill value here is the one wl computed for this board on 2.4 GHz.

Next to the router (-36..-40 dBm), HT20 + A-MPDU, 4 MPDUs per aggregate, iperf3 8 s:

| | upload | retries | failed |
|---|---|---|---|
| before, fixed index 20 (notes/138) | 20–30 | 15–20 % | 27–67 per run |
| wide tables, fixed index 20 | 37.0, 33.3, 26.7 | 1.5–2 % | 0–1 |
| wide tables, hardware power control (`ac_txpwrctl=1`) | 48.5, 50.8, 50.5 | 2 % | 0 |

Download with power control: 54.7, 56.4 Mbit/s (before: 17–20).

Aggregate size with power control: 4: 51.6, 8: 52.3, 16: 49.9 / 50.6, 32: 39.7 / 41.8, stock (0): 47.7. The "later MPDUs of a long aggregate are lost" effect of notes/137 is gone; 4 stays the default.

The 28 % TX failures with the power loop (notes/136) were the missing table 0x20, not the loop.

12-minute soak with power control, same spot:

- 22 rounds. Upload 49.5-51.3 Mbit/s, mean 50.5. Download 40.7-58.5 Mbit/s, mean 52.6.
- total: pkts 2373911 retries 82954 failed 9
- stick: 1424 packets transmitted, 1424 received, 0% packet loss, time 719715ms
- b43 errors: 0  stick deauths: 0  b43 deauth/disassoc: 0

`ac_txpwrctl` is now on by default. Not yet tested at range; `ac_txidx` only matters with `ac_txpwrctl=0`.
