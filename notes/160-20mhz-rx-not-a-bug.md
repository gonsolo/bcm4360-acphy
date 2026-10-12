# notes/160: the "20 MHz RX problem" on 5 GHz was the test setup (2026-10-12)

Notes/141/142/156 recorded a slow download (18-24 Mbit/s, AP sending MCS 0) for a 20 MHz client on 5 GHz while the router ran an 80 MHz BSS.
With the router set to 20 MHz (channel 140, 5700 MHz) the same measurements, b43 against the USB stick in alternating 6 s downloads:

| PHY mode | b43 down | stick down | b43 up |
|---|---|---|---|
| default (block 132-144, 80 MHz mode, AP 20 MHz, VHT-MCS 8 x2) | 39.0-41.2 (mean 39.6) | 40.4-41.6 (one 7.5) | 42-55 |
| real 20 MHz PHY (debug `ac_force20=1`, HT20, MCS 15) | 20.6-24.1 (mean 22.8) | 21.0-25.7 (mean 24.0) | 52.7, 52.8 |

So b43 receives as fast as the stick in both modes; the absolute numbers move with the air (the stick fell from 40 to 24 between the two runs).
Ucode counters over one 6 s download (default mode): 15444 PPDUs started, 19633 good unicast data frames, 270 bad FCS (1.8 %),
11 bad PLCP, 2410 RTS to us (answered with 2387 CTS). The AP aggregates little (1.3 frames per PPDU), which it does for the stick as well.
What looked like a receive fault was an HT20-only client on an 80 MHz BSS (the AP's RTS and rate control with such a client). The 35 PHY
words and groups that differ from wl's 5 GHz 20 MHz hops (0x2d1/2d2/2e4, 0x727-729, 0x42, 0xec-0xf4, 0x140/164, 0x31c-31f, 0x6dd-6f9/0x8dd-8f9,
0x725/73a) changed nothing when applied live there. Nothing to fix; 20, 40 (not measured), 80 MHz APs all work.
Tools: debug build only (`AC_DEBUG=1`), `ac_force20` to run 5 GHz as HT20, `ms.sh`-style macstat deltas through debugfs `shm` (SHM 0xe0).

## 40 MHz (router at 40 MHz, channel 132, centre 5670, 2026-10-12)
b43 in the default mode (block 132-144, PHY 80 MHz mode) associates at VHT 40 MHz, rx VHT-MCS 9 x2 (360 Mbit/s), tx MCS 8-9 x2.
Sequential 6 s runs against pampelmuse: b43 down 39.1, 39.5 / stick down 39.1, 39.3; b43 up 48.7-56.3 (six runs, retries 11-14 %, 0-13 failed per
~27k frames) / stick up 51.9, 52.5. Parity again. The test scripts, not the driver, produced some empty or stuck runs: a client run racing a
server restart and a stick run bound to an address while the b43 host route was installed (use separate sequential runs).
