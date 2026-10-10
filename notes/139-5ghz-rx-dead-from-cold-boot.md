# 139: 5 GHz RX is dead from a cold boot, also with the 2026-09-26 driver that received then

Notebook next to the router, AP on channel 112 (5560 MHz, 80 MHz block centre 106), stick sees it at -42 dBm. Generation 30, cold boot, wl never loaded in this boot.

| driver / parameters | test | result |
|---|---|---|
| master, `ac_por=7 ac_5ghz=1` (20 MHz path) | 3 passive scans of 5560 | no BSS |
| master, `ac_por=7 ac_5ghz=1 ac_5g_80=1` | 3 passive scans | no BSS |
| master, `ac_por=63 ...ac_5g_80=1` (with SHM, chipcommon, PMU) | 3 passive scans | no BSS |
| master, `ac_replay=1 ac_por=63 ac_init_state=0 ...ac_5g_80=1` | 3 passive scans | no BSS |
| commit 6b399f0 (2026-09-26, "5 GHz: receives", 88/100 beacons then), `ac_replay=1 ac_por=63 ac_5ghz=1 ac_5g_80=1` | monitor, tcpdump 8 s | 2462: 115 frames, 5560: 0 frames |
| master, 20 MHz path, `ac_diag=1`, monitor on 5560 for 30 s | ucode macstat | rxstrt and rxcrsglitch do not move at all (on 2462 in 17 s: 568 rxstrt, 1481 glitches) |

- The receiver is deaf on 5 GHz, not merely failing to decode: not one frame start in 15 s next to the AP.
- The commit that received on 2026-09-26 does not receive today. That evening wl had been loaded in the same boot (the 5 GHz trace was taken 40 minutes before). So the result depended on state wl left in the chip and our tables do not contain, exactly like the chipcontrol bit of notes/136. `phy_ac_por5g.h` is the last-write state of one wl load that was itself not the first in its boot, so anything wl set up only once per boot is missing.
- Chipcommon as far as debugfs shows it matches wl's 5 GHz capture after an `ac_por=63` load (chipcontrol 0x01000008, GPIO, pllctl 2/3); pmucontrol differs in bits 9/10 (ours 0x...0181/0381, wl 0x...0581), regctl[0] is 0 here against 0x00200000 without the PMU class.

Ways forward:
1. A wl reference from a cold boot that goes straight to 5 GHz (MMIO trace plus a final radio/PHY/table dump). Needs the user: wl has to be loaded.
2. Alessio's driver has a validated 5 GHz bring-up on routers; port its 5 GHz radio/PHY init blocks as was done for 2.4 GHz.
3. Before either: on a cold boot, diff what our 5 GHz radio list covers against the full 2.4 GHz wl radio dump (`traces/wl-final-radio-2g-ch6.txt`) to list radio registers wl touches but our 5 GHz table lacks.
