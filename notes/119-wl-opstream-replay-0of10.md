# 119: verbatim replay of wl's op stream (lines 15065-280000) -> 0/10

Diagnostic params `ac_fr_path/start/end/mask` (phy_ac.c, tools/gen_wl_ops.py -> test-data/wl_ops.bin, gitignored):
after our first-load replay, apply wl's phy/radio/tbl/delay/shm ops from seq.txt in order (261,698 ops, delays via udelay/mdelay).

Result: no hang, but 0/10 connects (baseline ~30%), 2-11 MAC suspend failures per attempt.
Interpretation: wl's trace is a 5 GHz first load; replaying it on top of our 2.4 GHz state leaves the PHY in a mixed/5 GHz-configured state
(our channel switch then does not undo it), so this arm is not a fair test of "wl's exact sequence". It only shows the stream is not a drop-in.
Fair version needs a 2.4 GHz wl trace (none available) or bisecting sub-ranges that are channel-independent (radio init/cal only, e.g. lines 15174-23819).

## Follow-up: radio init/cal only (lines 15174-23819) -> 3/10
Same as baseline (3/10, ~30%). Connected attempts had 1-3 suspend failures, failed ones 5-17. No effect.
Remaining untested: lines 23819+ (post-ucode-start cal runs, incl. the 0x380 engine), and 2.4 GHz-specific state.

## ucode comparison: identical
wl's ucode upload (trace shm region 0, 10850 w32 writes) vs firmware/b43/ucode42.fw (832.127, after the 8-byte header): zero differences. The ucode is ruled out.

## Post-ucode range (lines 23819-143115) -> 0/10
Same as the full replay: 5 GHz cal/channel state on a 2.4 GHz link breaks it. Not informative. Without a 2.4 GHz wl trace the verbatim-replay line of attack is exhausted.
