# 118: replaying wl's RF-sequencer kicks verbatim does not change the good-init rate

Hypothesis (after notes/117): wl runs engines (RF sequencer cmd 1/2 pairs x5, cmd 0x20 x4, cal engine 0x380 x32)
whose analog side effects are invisible in registers; our replay only writes final values.

Test: module param `ac_rfkick` (phy_ac.c): after apply_por (the ch6 first-load replay) run wl's kick windows
verbatim in wl's order (bit 0: 5 pairs from seq.txt ~137500, bit 1: 4 x cmd 0x20), polling PHY 0x403.
No hang on 2.4 GHz (the pair is what hung Alessio's driver; his extra 0x16d8 write is the likelier culprit).

A/B, same session (ab_reload_test.sh, connect_test.sh, ch6 replay): baseline 3/10; ac_rfkick=3: 4/10 and 3/10
(7/20 = 35 % vs 30 %; earlier baseline 118 attempts ~21 %). No effect. Side fix: connect_test.sh renames wlan0
itself when udev loses the rename race.

Conclusion: the sequencer kicks are not the missing piece. Not yet tested: the 0x380 cal engine runs (need the RX-IQ
loopback setup, notes/108), full verbatim replay of wl's op stream with its timing (ideas in notes/119 if done).
