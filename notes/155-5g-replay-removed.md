# 155: wl's 5 GHz first-load replay removed

Cold boot (reboot, postboot, no 5 GHz use before), router on channel 52 / 80 MHz, nested chain of radio words with
PHY words and tables off (`por5g_chain.sh 0,0,0 40,0,0 80,0,0 120,0,0 163,0,0`, our PHY 0x18b write, AGC and rfseq2 tables in source):

| radio words applied | result |
|---|---|
| 0 | connected, VHT-MCS 6, 57 up / 76 down |
| 40 | VHT-MCS 7, 69 / 61 |
| 80 | VHT-MCS 4, 45 / 71 |
| 120 | VHT-MCS 6, 69 / 65 |
| 163 | VHT-MCS 3, 34 / 24 (signal/air dependent, not worse by design) |

None of wl's 163 radio words is needed. With that the whole replay is gone: `phy_ac_por5g.h` (radio, PHY, tables, SHM,
chipcommon, PMU; 4464 lines) deleted, the `ac_por5g_*` test parameters dropped; `b43_phy_ac_setup_5g()` keeps what our own code does
(rfseq extension entries, 5 GHz TX gain table and rpcal fill, rfseq2 command lists, AGC tables, vcocal).
Build without any replay: connects, VHT-MCS 4-7, 62-83 up / 56-66 down.

Observed: TX retries 8-15% in this build against 1-4% in the chain steps; signal read -69 dBm at the time. To check.
Still open: 5 GHz is opt-in (`ac_5ghz=1 ac_5g_80=1 ac_vht=1`), other 80 MHz blocks untested, 20/40 MHz on 5 GHz, calibration
still channel 106's.
