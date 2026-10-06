# 119: verbatim replay of wl's op stream (lines 15065-280000) -> 0/10

Diagnostic params `ac_fr_path/start/end/mask` (phy_ac.c, tools/gen_wl_ops.py -> test-data/wl_ops.bin, gitignored):
after our first-load replay, apply wl's phy/radio/tbl/delay/shm ops from seq.txt in order (261,698 ops, delays via udelay/mdelay).

Result: no hang, but 0/10 connects (baseline ~30%), 2-11 MAC suspend failures per attempt.
Interpretation: wl's trace is a 5 GHz first load; replaying it on top of our 2.4 GHz state leaves the PHY in a mixed/5 GHz-configured state
(our channel switch then does not undo it), so this arm is not a fair test of "wl's exact sequence". It only shows the stream is not a drop-in.
Fair version needs a 2.4 GHz wl trace (none available) or bisecting sub-ranges that are channel-independent (radio init/cal only, e.g. lines 15174-23819).
