# 150: basement range test, 5 GHz VHT80 and 2.4 GHz

Router on channel 52 (80 MHz) / 2.4 GHz channel 1-11 mix; notebook in the basement; stick on the same router.

5 GHz, b43 VHT80 (PHY words of wl's state only, cold boot): signal -78 dBm, rx MCS 8, up 9-16, down 45-51 Mbit/s, 100 pps flood-ping loss 2.1 % (10 bursts). tx retries/failed high (126k/2046 over the session).

2.4 GHz, b43 at -58 dBm (stick at -57): up 9-17, down 15-22, flood loss 5.8 %. Stick the same minutes: up 62-64 / down 29 first, 23 up later: the environment varies a lot.
- TX power index (ac_txpwrctl=0, idx 20/8/0): no gain; idx 0 worse (MCS 12).
- A-MPDU: off -> up 21 (failed frames 2-12 instead of ~100), down 18; 2 MPDUs -> up 12-13; 4 (default) -> 13; 8 -> 16.6 (down 23-26).
So at range aggregation costs failed frames; no setting reaches the stick's best. Open: first-attempt rate/minstrel at range, TX quality of the 2-of-3 chains.
