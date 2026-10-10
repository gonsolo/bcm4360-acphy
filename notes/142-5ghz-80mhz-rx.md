# 142: 80 MHz on 5 GHz, receive only: the PHY decodes the stick's VHT80 traffic

Cold boot (generation 31), b43 in monitor mode on 5560 MHz, no transmit. The USB stick is associated with the same AP on 5 GHz (VHT-MCS 9, 80 MHz, 2 streams, 866.7 Mbit/s) and downloads with iperf3 for 33 s; `ac_diag=1` logs the microcode statistics every 15 s (`tools/rx5g_80_listen.sh`).

Deltas over one 15 s window:

| counter | 20 MHz path (`ac_5ghz=1`) | 80 MHz path (`ac_5g_80=1`) |
|---|---|---|
| rxstrt | 31515 | 31396 |
| rxrtsocast / rxctsocast | 12732 / 24989 | 12925 / 25213 |
| rxdfrmocast (data for others, FCS ok) | 32 | 16353 |
| rxbadfcs | 60 | 35355 |
| rxbadplcp | 80 | 5 |
| rxcrsglitch | 1518 | 1 |

- In both paths the PHY follows the RTS/CTS exchange on the primary channel.
- Only in the 80 MHz path does it decode the data frames: 16353 good MPDUs in 15 s, with 35355 FCS errors. The stick's link runs at the highest rate there is for two streams (256-QAM 5/6), and we receive it with two chains and no margin, so about one MPDU in three is a start, not a verdict.
- tcpdump shows only beacons in both paths: the microcode does not pass other stations' data or control frames up in this configuration.

So wl's 80 MHz state, applied by b43 from a cold boot, receives VHT80. Nothing was transmitted in 80 MHz mode.

What an 80 MHz link still needs:
1. Transmit in 80 MHz mode at all: 20 MHz frames on the primary inside the 80 MHz channel (management, ACK-rate frames), with the 80 MHz chanspec and the subband bits in the TX header. This is the combination of the 2026-09-26 freeze (80 MHz + TX).
2. VHT capabilities and an 80 MHz channel definition towards mac80211; the 80 MHz state exists only for the block 100–112 (centre 106).
3. VHT TX headers (frame type 3, VHT-SIG-A), as in Alessio's driver; VHT in the RX rate decode and in the TX status for minstrel.
4. RX header chanspec to primary channel mapping.
