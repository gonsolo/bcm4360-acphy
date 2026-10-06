# 116: Alessio's rccal / LPF code vs our init (read-only comparison)

- Our rccal (phy_ac.c b43_radio_2069_rccal) exists and works: step 1 cap = 0x0b, step 2 = 0x1eb on every init
  (journalctl, 2026-10-06). wl's replay (phy_ac_por.h) writes 0x126/0x043 low bits = 0x0b: same value.
  So the rccal result is not what differs between good and bad inits.
- We have NO afe_lpf_stage, set_analog_tx_lpf or RX-LPF table 7 code; those states only arrive via the
  wl-trace replay (final register values from one wl run). His afe_lpf_stage is plain masks on phy 0x728/0x721
  and radio 0x45/0x49 per core: covered by replay, no calibration engine involved.
- Conclusion: LPF state is replayed and rccal matches wl, so LPF is unlikely to explain the per-init coin flip.
  Remaining candidates stay: calibration engine runs (rxiqcal etc.) and ordering/timing in init, and for
  5 GHz the PHY-bandwidth/SHM side. femctrl is ruled out (notes/112 context).

## Follow-up: the calibration-engine comparison was already done
notes/107 and notes/108 cover it: tables/PLL/gain are not the difference, and a partial port of his RX AFE
calibration engine failed (engine measures zeros without the radio loopback + DDS tone setup of the rxiqcal
chain). A faithful port is the whole rxiqcal chain (~1500 lines of his code, 5 GHz-validated only).
Nothing new learned from re-reading it; not repeated.
