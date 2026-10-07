# notes/127: 5 GHz first look (2026-10-07), RX in the 20 MHz path is dead

Setup: hand build, `ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 ac_5ghz=1`, stick connected as backup, monitor mode
(parked on ch6 first so the wl ch6 replay runs; without it even 2.4 GHz captures 0 frames), tcpdump via nix-shell.
Target: Vodafone-2A84 on ch116 (5580 MHz, DFS), seen by the stick at ~-75 dBm.

- `iw scan` (active or passive) on b43 finds no 5 GHz BSS; the stick finds the AP.
- Monitor on 5580: 0 frames in 6-8 s, repeatedly. Same session on 2462: 300 frames. Back to 2462 after 5580 recovers
  fine, no MAC suspend failure at the 5 GHz switch itself (one failure at an earlier first scan step on a fresh core,
  the old init-time effect).
- So the ordinary per-channel 20 MHz retune on 5 GHz (`b43_phy_ac_apply_por5g()` + `tune()` + Farrow, ac_5g_80 off)
  does not receive. notes/07: 5 GHz RX worked only with `ac_5g_80=1` (wl's 80 MHz state, ch112 centre), and that
  mode is the one involved in the 2026-09-26 hard freeze (with TX injection). notes/53's check was register read-back
  only, no frames.
- Not tried (needs the user present): `ac_5g_80=1` RX-only on ch116/112 to confirm the baseline still works on this
  kernel/reset order; then diff 20 MHz vs 80 MHz register state to find what the 20 MHz path misses (candidates:
  `wlc_2069_rfpll_150khz` not ported, notes/05; RF control overrides, AFE/ADC clock for 20 MHz mode, BW IOCTL).

Link restored afterwards: production-style load, b43 default route, stick backup.
