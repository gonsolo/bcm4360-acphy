# 143: VHT 80 MHz link on 5 GHz, and the 50 Mbit/s cap was the DMA engine

## VHT

Behind `ac_vht=1` (with `ac_5ghz=1 ac_5g_80=1`, AP on channels 100–112):

- 5 GHz band: VHT capabilities (MCS 0–9 on one and two streams, no short GI, no LDPC, no beamforming) and 40 MHz capability in the HT caps, which mac80211 wants before it uses 80 MHz.
- TX: `b43_txhdr_ac_vht_block()` builds the VHT rate block as the stock driver and Alessio's driver do (frame type 3, width in word 0 bits 15:14, subband of the primary within the width in word 1, MCS and NSS-1 in word 2, VHT-SIG-A1/A2, FBW 0x0300). Only session frames go out as VHT, since a VHT frame is always an A-MPDU; a VHT rate on a frame outside a session is sent as the HT20 rate of the same stream count.
- RX: VHT-SIG-A decoded into mac80211's rate info.
- TX status: VHT counted like HT for minstrel.

First try, next to the router (-50 dBm): associated, `rx bitrate 585 MBit/s VHT-MCS 7 80MHz NSS 2`, `tx bitrate 780 MBit/s VHT-MCS 9 80MHz NSS 2`. No error, no freeze.

## The cap

Throughput stayed at about 50 Mbit/s whatever the rate (VHT 780, HT 130, 2.4 or 5 GHz), aggregate size or AQL setting. The TX status timing shows why: its last word's low half grows by about 240 µs per MPDU of an aggregate (8: 1.85 ms, 16: 3.8 ms, 32: 7.85 ms) while the minimum for any size is 141 µs. The microcode was waiting for MPDUs: they reached the TX FIFO at one per 240 µs, 1500 bytes in 240 µs = 6 MB/s = 50 Mbit/s. On the host side b43_dma_tx takes 2–8 µs and the ring is filled in bursts of ~50 frames followed by 8–16 ms pauses; the 802.11 core runs on the HT clock (clk_ctl_st 0x030b0342).

wl's DMA control registers (trace): TX `0x03780841`, RX `0x036c0851`. b43: TX `0x00000801`, RX `0x0000084d`. The missing bits are burst length, prefetch control and prefetch threshold. b43 now sets them on the AC-PHY (`ac_dmaburst`, default on): TX `0x03780841`, RX `0x036c084d`.

iperf3 next to the router, VHT80, after the change:

| | b43 VHT80 | stick (mt76x2u, VHT80, 866 Mbit/s rate) |
|---|---|---|
| TCP up, 1 stream, 4 MPDUs per aggregate | 60.8, 68.8 | |
| TCP up, 1 stream, 32 MPDUs | 72.5, 72.3 | |
| TCP up, 4 streams | 82.1 | 77.6 |
| TCP down, 4 streams | 52.1 | 52.4 |
| TCP down, 1 stream | 49.8–52.9 | 55.6 |
| UDP up (600M offered) | 60.3 | 70.3 |
| UDP down | 56.1 | 55.2 |

b43 and the stick now reach the same numbers, so the remaining limit is the test path (the router's bridging or the iperf host), about 55 Mbit/s down and 70–80 up. The link itself cannot be measured further against this setup.

2.4 GHz with the DMA change: up 48.6, 35.9, 33.9; down 34.6, 42.1 (one load, not compared carefully yet).
