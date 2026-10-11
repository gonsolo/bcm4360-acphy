# 149: how much of wl's 5 GHz replay is needed

Method: `tools/por5g_chain.sh`, after a cold boot, nested steps (first N radio / PHY / table words of `b43_ac_por5g_*`, module params `ac_por5g_nr/np/nt`), router on channel 52 (80 MHz), VHT80 connection, iperf both ways.

First cold boot (no throughput measured): nothing -> not connected; radio words only -> not connected; radio + PHY, no tables -> connected, rx MCS 6; plus tables -> MCS 7-9.

Second cold boot, throughput (Mbit/s up/down):
- 0,0,0: not connected
- 0,318,0 (**PHY words only**): connected, rx MCS 8, 81 / 61
- 163,318,0: 82 / 62; 163,318,20/50: 80 / 67; 163,318,200: 83 / 64; 163,318,400: 88 / 64; 3142 (all): 79 / 57.
(one 100-step dip to 34/41 was noise; neither more radio words nor tables make a consistent difference.)

So of wl's captured 5 GHz state only the 318 PHY words are needed; the 163 radio words, the 3142 table entries (plus SHM, chipcommon, PMU, which were already off) are not. rfseq extension (table 0x14), the wide tables and the generic retune are our own code.

Next: another cold boot, same chain on the PHY words (np = 20, 40, 80, 160, 318) to see which ones matter, then write those as init code.
