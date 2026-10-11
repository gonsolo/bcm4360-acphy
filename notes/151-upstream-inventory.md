# 151: what stands between the tree and an upstream submission (inventory, written while the owner was away)

Facts from the tree at c645ca8 (b43-src: phy_ac.c 3908 lines, xmit.c +1253, dma.c +2017, main.c +6431 incl. stock code, tables_phy_ac.c 985, radio_2069.c 241).

## 1. Data derived from wl traces (must go or be re-derived)
| File / item | Lines | Used by default? | Plan |
|---|---|---|---|
| `phy_ac_por5g.h` (wl's 5 GHz first-load state: radio 163, PHY 318, tables 3142, SHM 798, cc/pmu) | 4464 | 5 GHz only (`ac_5ghz=1`) | notes/149: only PHY words up to index ~136 are needed (radio words, tables, SHM, cc/pmu are not). Finish the ablation, write the 4-10 essential writes as init code, delete the file. |
| `phy_ac_replay.h` (wl's channel-6 state) | 1550 | no (`ac_replay=0` since the 2.4 GHz init is real code, notes/130-135) | delete with the `ac_replay`/`ac_state_once` parameters. |
| `phy_ac_win116.h` | 801 | no (test `ac_win116`) | delete. |
| `phy_ac_alx.o`, `phy_ac_farrow.h` | 131 | farrow.h only for `ac_farrow`/`ac_fr_*` tests | check; farrow_80() is computed code. |
| `tables_phy_ac.c` (TX gain 128x2 wide, rpcal) | 985 | yes | values come from wl traces; compare with Alessio's tables, keep what he published or derive. |

Clean-room status: the register map and tables were obtained by tracing wl's register access and from Alessio Ferri's published work (credited in comments), not from wl source. The EU interoperability question (decompilation for interoperability) is separate and still needs legal advice before anyone sends this to the mailing list under the owner's name.

## 2. Diagnostic and test parameters (~60, all `ac_*`)
phy_ac.c 43, main.c 9, xmit.c 5, dma.c 2. Keep as real features: `ac_ht`, `ac_vht` (until 5 GHz is on by default), `ac_ampdu`, `ac_ampdu_mpdus`, `ac_ampdu_requeue`, `ac_ampdu_rx`, `ac_dmaburst`, `ac_txpwrctl`, `ac_5ghz`. Remove: the 12 `ac_txcal_*` test flags (untested drafts of TX calibration, notes/16), `ac_rfkick`, `ac_rfseq`, `ac_fr_*`, `ac_win116`, `ac_replay`, `ac_state_once`, `ac_init_state`, `ac_por*`, `ac_diag`, `ac_hostflags`, `ac_hostf1`, `ac_5g_ctr`, `ac_selfheal` (or make it a fixed behaviour).

## 3. Code that works but is not upstream quality
- A-MPDU requeue in dma.c and the counter in the private TX info (fixed, notes/146): a hack around TX status of aggregated frames; needs a clean description.
- SHM chanspec, 80 MHz chanspec/subband mapping in xmit.c, `b43_phy_ac_chanspec()`.
- Hardcoded 2-of-3 chain assumption (chipcontrol bit 3), board-specific; needs the SROM/board flag or a probe.
- No hardware crypto (`nohwcrypt` is required today), no power save, no suspend/resume test.
- checkpatch: phy_ac.c/xmit.c clean of errors; dma.c has legacy style from stock code (not ours).

## 4. Proposed series
1. bcma/ssb: BCM4360 ids, SPROM rev 11 decode (Alessio's patch 0001).
2. b43: AC-PHY identification, PHY ops skeleton, radio 2069 rev 4 tables.
3. b43: AC-PHY init (2.4 GHz), channel switch, RX.
4. b43: DMA 64-bit engine setup for core rev 42 (burst/prefetch bits).
5. b43: TX header v2/AC, TX status v2, rates/HT.
6. b43: A-MPDU TX/RX.
7. b43: 5 GHz, 80 MHz/VHT (after the ablation).
Each needs real hardware test notes; the firmware (832.127, 2014) is not redistributable and must stay a user-supplied blob.

## 5. Constraint on removing parameters
The boot service in /etc/nixos passes `ac_replay=0 dma32=1 ac_por=7 nohwcrypt=1`. Removing `ac_replay` or `ac_por` from the module makes the load fail ("Unknown parameter"), so those two must stay (as no-ops) until the owner changes the service. A cleanup branch that deleted them was started and dropped for that reason.
