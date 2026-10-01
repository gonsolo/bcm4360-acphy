# 111 - ucode txphyerr SHM record, good vs bad init

Tool: tools/txphyerr_shm_test.sh (reload until an init does not connect, dump shared SHM, restore a connection).
Data: test-logs/txphyerr-shm-1.log (byte range 0xBE0-0xC20: all zero, wrong range - SHM word addresses are x2),
test-logs/txphyerr-shm-2.log (0x17C0-0x1840).

Result (shared SHM byte offsets, = ucode word 0xBFA-0xC07 x2):
| offset | good init | bad init |
| 17f4 | 0000 | 0001 |
| 17f6 | 0000 | 0020 |
| 17f8 | 0000 | 0044 |
| 1802 | 0000 | 040a |
| 1804 | 0000 | 0110 |
| 180e | 0000 | 002c |
Other differences (17de, 17e0, 17e2, 1816, 183a) look like association/traffic state.
The error record is filled only after a PHY TX error, so it confirms the failure but does not yet say why.
Next: decode which IHR registers these words are (ucode txphyerr handler) and compare with PHY regs at that moment.

## Decode (layout from notes/13)
flag=1 | ext-IHR read=0x0020 | TXE_PHYCTL=0x0044 | PHYCTL1/2=0 | L-SIG=0/0 | HT-SIG0=0x040a HT-SIG1=0x0110 HT-SIG2=0 | VHT-SIG-B=0/0 | SCR12=0x002c.
- Same record type, same forensic picture as the 2026-09-27 samples (0x0045 / 0x01C0 / 0x2000 / 0x31): TXE_PHYCTL = 0x40 template | small selector,
  HT-SIG fields hold leftovers, nothing else set. Values differ per frame, so this is the generic txphyerr record, not a distinct failure signature.
- TXE_PHYCTL bits[1:0] = 0 here (0x45 had bit 0 set), so the ucode's address computation (0x0C64-66) takes the other branch: the ext-IHR read is a
  different register than "mode 3, offset 7" in notes/13 - which explains 0x0020 vs 0x2000 without a different error.
- Conclusion: the record says "PHY reported a TX error" (already known, TXE_STATUS bit 10). It carries no information on the cause. Branch closed.
- near router (signal 100/77 vs 60/39): 2/10 fresh inits connected, same as the ~21% baseline -> signal strength ruled out (test-logs/ab_reload_near_router_*.log)

## 5 GHz association attempt (tools/test_5ghz_connect.sh, test-logs/5ghz-connect-1.log)
ac_5ghz=1, connect to the 5 GHz BSSID (ch116 DFS), then 2.4 GHz on the same init to tell a bad init from a 5 GHz problem.
6/6 inits failed on both bands = bad inits, so 5 GHz itself is untested (P ~ 24% at the usual 79% failure rate). The wrapper then failed
12/12 on its first restart and connected on the second (18 bad in a row, ~1.4%): possible that ac_5ghz scans leave the chip worse; not established.
Stopped: a clean 5 GHz test needs a good init plus a 5 GHz TX chain setup that the replay does not load (see Alessio's code).

## 5 GHz receive check (ac_5ghz=1, monitor mode, rx_packets over 8 s)
freq 2462 (AP ch11): 32 frames | freq 5580 (AP ch116, signal 77 as seen by the stick): 0 frames | freq 5180: 0.
Normal scans with ac_5ghz=1 also find no 5 GHz BSS (only the three 2.4 GHz SSIDs), though the band and 38 channels are advertised.
So 5 GHz RX gets no frames at all with our replay; notes/53 only verified register read-back, not reception. Reception is independent of
the TX-side init failure (2.4 GHz receives on a bad init). Candidates: per-band FEM/antenna-switch control, RX gain/LNA setup, AGC.

## Why 5 GHz RX is dead: our 5 GHz state is a hybrid (offline reading of phy_ac.c + the wl 5 GHz trace)
- b43_phy_ac_apply_por5g() writes wl's *80 MHz ch112* first-load state (phy_ac_por5g.h, 4464 lines); the 20 MHz path then only re-tunes the radio
  tune regs, BW1A, the Farrow resampler (+resetcca/rfseq). The core's PHY bandwidth (IOCTL) stays 20 MHz. PHY regs/tables stay in 80 MHz mode.
- wl itself, in a 20 MHz scan switch (e.g. window ending at the 19b=0x69.. writes), does ~2570 PHY writes, ~360 SHM writes and ~360 table writes
  (tables 0x21, 0x40/0x60 (128 words each), 0x44/45/64/65, 0x07, 0x0b, 0x0c) plus per-core regs 0x6d4-0x6ee / 0x8d4-0x8ee. We write none of these.
- The wl trace contains 20 MHz switches to ch116 (Farrow 0x19b=0x74, 6 occurrences), so a targeted test is possible without new captures:
  extract the ch116 window from traces/decoded-firstload-5g/seq.txt, replay it on switch to 116, count RX frames in monitor mode (expect ~80 per 8 s).

## Test: replay wl's ch116 20 MHz switch (ac_win116=1; tools/gen_switch_window.py, b43-src/phy_ac_win116.h, tools/rx5g_test.sh)
Window = wl trace lines 357161-360447 (797 ops: 247 PHY, 80 radio, 453 table, 17 delays; SHM/MMIO not replayed). Replayed after our own switch
to 5580 MHz (log: "replayed wl's channel-116 switch (797 ops)"). Monitor-mode rx over 8 s: 2462 MHz 96 frames, 5580 MHz **0 frames**. Negative.
So the missing piece is not in this part of the switch. Remaining candidates: core PHY-bandwidth/clock (IOCTL stays 20 MHz while por5g leaves PHY in 80 MHz mode),
the SHM/MMIO side of wl's switch, the AGC/gain sweep + calibration engine runs that wl does after the tune, per-band FEM control.
