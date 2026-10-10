# 144: 5 GHz beyond the block 100–112, first steps

Goal: 5 GHz on other channels than the one 80 MHz block wl's captured state belongs to. Only one 5 GHz network is in range (our router on channel 112), so other blocks cannot be tested until the router's channel is changed.

Done:

- `b43_phy_ac_80mhz_centre()`: the block centre of a primary (42, 58, 106, 122, 138, 155). 80 MHz mode, the chanspec and the subband position now work for every block; channel 165 and anything else stays on the 20 MHz path.
- Retune for another centre: synthesizer from the channel table, the per-channel PHY words 0x372–0x376 from the table (in wl's 80 MHz state they equal the table entry of channel 106; 0x371 is 0), and the resampler from Alessio's formula, `b43_phy_ac_farrow_80()`: ratio = round(f·2^18/45), deltaphase = round(0xb40000000/f), mode word 0x0b40. For 5530 MHz the formula gives exactly wl's captured words (0x8e39/0x00eb/0x0084, 0x52dd/0x0085).
- Check on our own block: `ac_5g_ctr=106` forces that retune path instead of wl's own tuning. VHT80 link, same numbers: wl's tuning up 67.8 / 72.3, down 48.8 / 44.3; retuned up 70.1 / 66.6, down 51.9 / 54.5. So the generic retune reproduces a working state for centre 106.

Found on the way, not solved:

- At a band switch `b43_phy_init()` tunes to `phy->channel`, which is still the 2.4 GHz channel: "PHY init: Channel switch to default failed" in the log, harmless. Setting `phy->channel` to the band's default (36) first removes the message, but then the driver tunes to block 36–48 (centre 42) and afterwards finds no 5 GHz network on 112 any more. Reverted. So **coming back to centre 106 after having been tuned to another block does not restore reception**: the retune writes something that the replay of wl's state for 106 does not put back. That has to be found before other blocks can be used at all, since every scan visits them.

Not done: calibration results and the rpcal fill of table 0x11 are those of channel 106; TX power targets per subband; the 20 MHz path's poor reception (notes/141); 40 MHz.

Next: with the router on another channel (36 is the simplest, no DFS), test reception in monitor mode on that block, then the round trip 106 → 42 → 106.
