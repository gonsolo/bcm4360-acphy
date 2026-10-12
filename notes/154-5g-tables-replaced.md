# 154: wl's 5 GHz PHY words and table words are no longer needed (radio words remain)

Cold boot, router on channel 52 (80 MHz), desk signal. `RESET=1 tools/por5g_chain.sh r,np,nt,p0,z0,z1,s0,s1` (s0/s1 = new `ac_por5g_ts0/ts1`: skip table words [s0,s1)).

- 5 GHz AGC tables (ids 0x44/0x45/0x64/0x65, 96 words): compact table `b43_ac_agc_tbls_5g` in phy_ac.c. Zeroing wl's copies with ours written afterwards works.
- Zeroing (notes/153) overstated the "essential" ids: it overwrote our own init's values. Skipping is the right test; ids 5 (22), 10 (96) are written by our init already.
- PHY words and tables substitute for each other: tables off + 0x18b only fails, tables on + PHY off works, PHY on + tables off works.
- With the PHY words off, the essential table words are id 7 offsets 0x30-0x57: the second RF sequencer's command lists (cores 0-2). 5 GHz: no leading 0x2a, 0xb0/0xb1/0xb2 instead of 0x2b. Now `b43_rfseq2_5g_tbls`, written in `b43_phy_ac_rfseq_ext_5g`.
- Result: `ac_por5g_np=0 ac_por5g_nt=0` (no PHY words, no table words, 163 radio words, our code): connects, VHT-MCS 6-9, 63-83 up / 62-66 down.

Open: switching back to 2.4 GHz in the same boot does not rewrite the 2.4 GHz rfseq2/txgain tables (existing issue, txgain too);
radio words (163) not ablated yet (needs cold boot); upload retries are higher without the replay (~500 vs ~300), check on a longer run.
