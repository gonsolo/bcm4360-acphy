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

## Step 1: transmit in 80 MHz mode, as an HT20 client. Works, no freeze

`ac_5ghz=1 ac_5g_80=1`: the PHY keeps wl's 80 MHz state (centre 106, IOCTL 0x1d5), mac80211 sees a 20 MHz HT channel 112. New for this:

- `b43_phy_ac_chanspec()`: in 80 MHz mode (only channels 100–112, the one block wl's state covers) the chanspec is `0xe000 | position << 8 | 106`, for channel 112 0xe36a as wl has it. It goes to SHM 0x00a0 and into the TX header.
- TX header word 1 of every rate block carries the subband (the primary's position, 3 for channel 112) for our 20 MHz frames.
- RX header chanspec with the 80 MHz width is mapped back to the primary channel (centre - 6 + 4 * position).
- Other 5 GHz channels use the 20 MHz path even with `ac_5g_80=1`.

Result, next to the router (-50 dBm): authenticated, associated, WPA handshake, DHCP; no error, no warning.

| | upload | download |
|---|---|---|
| 20 MHz path (notes/141) | 51–52 | 18–19 |
| 80 MHz mode, HT20 frames | 51.5, 51.8, 51.4, 51.8 | 49.8, 51.1, 51.8, 53.5 |

The download problem of the 20 MHz path is gone: the AP sends MCS 15 to us. So the receive side of wl's snapshot only fits when the PHY runs at 80 MHz, as suspected.

Also fixed on the way: the `if (have_5ghz_phy && b43_ac_5ghz)` around the 5 GHz band registration had lost its braces with the HT change (the band was registered without `ac_5ghz`); generation 31's boot module has that bug.

Next: VHT capabilities and VHT80 frames.
