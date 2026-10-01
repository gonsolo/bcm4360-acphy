# 107 - TX tables, gain and calibration checked (2026-10-01): not the cause

Question: is the unreliable TX path (notes/105) caused by missing TX tables, gain or calibration state?

- **Tables:** `traces/decoded-firstload/tables.txt` (wl's first load) has 3022 entries over 31 table ids.
  Our `ac_por=63` already replays exactly that set ("applied first-load state ... tbl 3022"), plus the
  ch6 replay (969 entries). The tables are not missing.
- **Calibration results** are replayed from wl's capture on this same chip (radio/PHY/tables); the
  calibration algorithms themselves (TX IQ/LO, RX IQ, idle TSSI, tempsense, periodic watchdog recal)
  are not implemented in our port (Alessio's phy_ac.c has txpwrctrl setup/program/enable, idle_tssi_meas,
  tempsense, rxiqcal - about 11k lines, 5 GHz only). TX power control off (`ac_txpctl_off`, notes/105):
  no change.
- **VCO calibration:** our `b43_radio_2069_vcocal()` kicks the calibration and returns without waiting
  or checking lock. Radio 0x090b bit 0x100 is the lock bit (reads 0x0100 when locked). Measured with a
  read-only check (`ac_pll_wait`, reverted): immediately after a channel switch it reads 0 (not locked)
  in every init, good or bad (17-28 times per attempt, also in the connected attempt); with a 2 ms wait
  the lock always comes after ~30 us. So the PLL is not the random element and waiting changes nothing:
  `ac_pll_wait=2`: 3/5 connected (noise), no pattern.
- **TX core mask / TX header:** `ac_txcore` 6 and 7, TX header format (notes/105): no change.
- Side finding: after a quick rmmod/insmod sequence the b43 netdev can keep the name `wlan0` instead of
  being renamed to `wlp3s0b1` (udev rename race), so NetworkManager shows no `wlp3s0b1`. The wrapper
  (tools/b43_load_until_connected.sh) looks for `wlp3s0b1`; if the rename never happens it finds nothing
  to judge and keeps the init. Worth handling if it shows up at boot.

Conclusion: tables, PLL, TX gain index/power loop and the TX core mask are not what separates a working
init from a failing one. What remains is the run-time calibration machinery we never ported, i.e. the
11k-line part of Alessio's code, or his answer.
