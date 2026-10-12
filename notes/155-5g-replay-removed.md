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

## RX level on 5 GHz (open)
Same router, same moment, scan RSSI: USB stick -47 dBm, b43 -75 dBm (2.4 GHz: stick -35, b43 -35 when connected there).
Live tests (debugfs, write wl's 5 GHz value, scan 4x, revert): of the 190 PHY words that differ from wl's state only
0x173b/0x073b/0x093b (0x18 -> 0x2c) moves it, +8 dB (-75 -> -67); the differing radio words (65, in four groups) and wl's table
ids in six groups change nothing. `b43_phy_ac_setup_5g()` now writes 0x173b = 0x2c (2.4 GHz restore puts 0x18 back).
About 20 dB against the stick remain unexplained (could be antennas; wl itself read -51 and -77 dBm in two earlier sessions at other places,
never next to the stick). TX: rate control sits at VHT-MCS 7 NSS 1 with 11% retries; RX reaches MCS 6 NSS 2.

## RX level: closed as antennas (2026-10-12)
Not a remaining init problem. Same explanation as notes/129 (stick: two large external antennas; MacBook: small internal ones,
and b43 shows the raw ucode power byte without SROM RSSI offsets). The 5 GHz gap (20 dB) is larger than 2.4 GHz (13 dB), as
expected for small antennas at higher frequency. The rate follows the level: next to the router (-50 dBm, notes/143) b43 ran
tx VHT-MCS 9 NSS 2; at -67 dBm MCS 7 NSS 1 is what minstrel picks. PHY 0x173b stays (+8 dB is real gain).

## Block 100-112 (router on automatic moved itself there), throughput vs stick (2026-10-12)
Server: iperf3 on pampelmuse (192.168.0.236, started by ssh via nix-shell, stopped after). b43 at -52..-56 dBm, 3 runs:
up 59-78, down 58-65 Mbit/s; TX retries 6-11 % (3460-4432 per 40-54k packets), failed 0.02-0.2 %; rate VHT-MCS 7 NSS 1 (tx) / MCS 6 NSS 2 (rx).
Stick on the same path, same minute: up 79-83, down 65-69. The path to pampelmuse tops out near 65-80 Mbit/s, so b43 is
at the ceiling on download and close on upload; link-rate numbers (292-780 Mbit/s) are not the limit here. Second 80 MHz block
confirmed (52-64 and 100-112), no router change needed.

## 5 GHz at 20 MHz (ac_5ghz=1 only, no ac_5g_80 / ac_vht), block 100-112 primary, -56 dBm (2026-10-12)
Cold-load, no replay: connects, HT20 on the 80 MHz AP's primary (tx MCS 13 at first, MCS 7 under load).
2 runs each: up 35-36, down 26-27 Mbit/s (pampelmuse path ceiling ~65-80); TX retries 27 % (6.5-6.8k per 24k packets), failed 1-2.
For comparison 2.4 GHz HT20: up 25, down 43-62. So 20 MHz on 5 GHz works as a fallback but has about 3x the retries of the
80 MHz mode (6-11 %). 40 MHz on 5 GHz untested (needs a router channel width setting).
