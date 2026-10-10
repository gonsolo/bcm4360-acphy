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

## Same day: wl once, and b43 receives on 5 GHz

wl builds for 7.2.9 with the broadcom-sta of nixpkgs master (rpmfusion patches 036–038 for kernels 7.1/7.2); the local nixpkgs stops at 035. `tools/wl_firstload_capture.sh` unbinds b43/bcma, traces wl's first load of the boot with tracefs kprobes and connects it to the 5 GHz BSS: wl links at 5560 MHz, -45 dBm, 780 Mbit/s. Trace: `traces/wl-firstload-5g-20261010-175159.trace.xz`, decoded in `traces/decoded-firstload-5g-cold/`.

Then `rmmod wl`, b43 again, monitor on 5560 MHz, tcpdump 8 s:

| b43 load | frames on 5560 |
|---|---|
| cold boot (all variants, table above) | 0 |
| after wl, 20 MHz path | 68 |
| after wl, 80 MHz path | 68 |
| after wl and one more plain b43 reload (`ac_por=7`) | 69 |

So one wl run puts the chip into a state in which our unchanged driver receives on 5 GHz, and the state survives b43 reloads.

What it is not:
- Not a register wl writes only on a first load: the final PHY/radio/table/SHM/chipcommon/PMU/wrapper state of the new trace has the same register set as the 2026-09-26 trace (323 PHY, 163 radio, 3142 table entries, 18 chipcommon), values differ only in calibration results.
- Not PMU regctl[0] bit 21 (the only chipcommon difference debugfs shows): clearing it live, with a retune, keeps 5 GHz RX; and `apply_por5g` writes it and chipcontrol on every 5 GHz switch anyway.
- Not visible in the radio on 2.4 GHz: registers 0x000–0x3ff on channel 11 are the same before and after wl except 0x04e, 0x050, 0x241.

Saved for the comparison after the next cold boot (`traces/5g-state-after-wl/`): radio 0x000–0x9ff, PHY, tables and chipcommon of b43 on channel 11 in the working state. Next: the same dumps from a cold boot, diff, and then set the differing state by hand until 5 GHz receives.

## After the next cold boot: what the residue is not

Cold boot again: 5560 MHz 0 frames. wl once more (`tools/wl_firstload_capture.sh`, second trace `wl-firstload-5g-20261010-19*.trace`, linked at 702 Mbit/s), then b43: 69 frames. Reproducible.

Compared, working state against cold state:

- **Radio 0x000–0x9ff on channel 11**: equal except 0x028/0x228/0x428 (3601 working, 2601 cold), 0x035/0x235/0x435 (0241, 0141), 0x050, 0x241, 0x414. Neither wl nor b43 ever writes 0x028/0x035. Writing the cold values into them in the working state (on 5560) does not stop reception: read-only results or irrelevant.
- **Chipcommon, full** (debugfs `cc` now dumps raw 0x000–0x1fc and 0x600–0x6fc, PMU chipctl/regctl/pllctl 0–15, resource tables, wrapper 0x160/0x164/0x408/0x500/0x800): during working 5 GHz reception against cold, only status-like words differ: 0x018 (0 against 0x80f), 0x060 GPIO in, 0x078, 0x168/0x16c (ECI input/event, 0x9060/0 against 0x9063/0xbf00), 0x1e0 clock status, timers. PMU resource tables, pllctl, chipctl are equal.
- **cc 0x140/0x144** is a strobed pair: wl writes 0x140=0, 0x144=data, 0x140=0x40000000, with data 0x200, 0x200, 0x1000, 0x1200 (before radio power-up) and 0xf200 (on 5 GHz). `phy_ac_por5g.h` replays the final values in address order, strobe before data, so nothing is latched. Latching 0xf200 by hand from the cold state did not bring 5 GHz RX back, so this is not sufficient alone; the replay order is still wrong.
- **cc 0x088/0x08c** (GPIO timer value and timer output mask): `apply_por5g` writes 0x000a0000 and 7, a blink state of wl captured as "final". After wl unloads they are 0x00ff00ff and 0. Reception works with the replayed values after wl, so not the cause either, but it should not be replayed.

Also learned: PHY registers survive a b43 reload. A 2.4 GHz dump taken after 5 GHz tests in the same boot still shows 0x073b = 0x2c from the 5 GHz table (0x18 straight after boot). Our load does not reset the PHY, so the order of experiments within one boot matters, and "clean init" is not clean.

Not compared yet: PHY and radio state while tuned to 5 GHz, working against cold. Reading them there hung the machine once (notes/112).
