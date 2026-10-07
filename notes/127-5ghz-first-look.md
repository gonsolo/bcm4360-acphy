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

## Follow-up: 80 MHz listen-only run (same day, no TX, no PHY debugfs)
Tools: tools/rx5g_listen.sh "<freqs>" [module params] (monitor mode, tcpdump count; needs b43_boot_dev.sh wrapper
from the session scratchpad, i.e. insmod of b43-src/b43.ko). `sysctl net.core.message_cost=0` is needed: b43info is
ratelimited and hides the "applied 5 GHz" / "80 MHz test" lines otherwise.
- `ac_5ghz=1 ac_5g_80=1` (wl's 80 MHz first-load state, IOCTL 0x1d5): 5560 and 5580 MHz: 0 frames; 2462 MHz in the same
  session 130-150 frames. The 80 MHz path does run (log shows "5 GHz 80 MHz test, ioctrl 000001d5").
- Caveat: wl's captured state is the block with primary 112 (centre ch106, 5530). The only 5 GHz AP now is on 116
  (block centre 122, 5610), so the 80 MHz baseline of notes/07 (88/100 beacons, router then on ch112) cannot be
  validated with this AP. New test param `ac_5g_ctr=<ch>` retunes the 80 MHz setup (radio tune + BW1A + Farrow) to a
  block-centre channel (tables have 106 and 122): `ac_5g_ctr=122`, 5580 MHz: 0 frames.
- Also seen: right after load, ch6 monitor capture is sometimes 0 frames (flaky ch6 replay RX), so always sanity-check
  with 2462 first.
- No freeze, no kernel errors from the 5 GHz switches themselves (MAC suspend failure only sporadically at the first
  switch of a fresh core).
Open: need a 5 GHz source we can control or a strong one (AP is ~-75 dBm: weak for a path that has never been
validated); the CRS-glitch counter was the signal in notes/07 (PHY debugfs, avoid on 5 GHz without the user).
Candidates unchanged from notes/111: core PHY BW in IOCTL for the 20 MHz path, SHM/MMIO side of wl's switch,
AGC/gain sweep + calibration runs after the tune, per-band FEM control, `wlc_2069_rfpll_150khz`.
Link restored afterwards (b43 default route, stick backup).
