# Auth timeouts: our TX is held off by the PHY's carrier sense

Follow-up to notes/57, same afternoon (2026-09-28, ~17:00).

## New diagnostics (main.c)

On AC, a failed `b43_mac_suspend()` now dumps what brcmsmac dumps on the
same timeout: psmdebug (MMIO 0x154, sampled 8x), phydebug (0x158), psm_brc
(0x490), MACCTL, IRQ reason, UCODESTAT, plus a stack. Rate-limited to 3
per 10 s.

## What it shows

- psmdebug samples all differ (low bits 0x0008..0x11c1). The PSM is
  running, mostly at low addresses (main loop), not hung.
- phydebug = 0x00000005 = PDBG_CRS | PDBG_TXF: the MAC is asking the PHY
  to transmit, and the PHY is asserting carrier sense. So the ucode is
  mid-TX, waiting for a clear channel, and won't suspend.
- IRQ reason 0x800 (PHY_TXERR) is pending, MACCTL has BEACPROMISC (scan).
- Callers of the failing suspends: `b43_op_config` (channel change during
  `ieee80211_scan_work`), a few `b43_op_bss_info_changed`.
- TX status trace (bpftrace, raw offsets into struct b43_txstatus), one
  failed connect: 90x sent once/unacked, 31x suppressed CHAN (scan), 1x
  phy_stat 0x20. Zero ACKed frames.

## phydebug sampled via /sys/kernel/debug/b43ac/mmio16 (~9 ms/sample)

- Idle (disconnected): 141x 0000, 58x 0040, 1x 0001. No stuck CRS.
- During a connect attempt: 0x0005 in ~10% of samples, including two
  continuous runs of ~785 ms. The run 17:06:50.68-51.47 covers exactly
  the three "send auth" tries (50.68/50.88/51.09) and the timeout (51.30).
  The auth frames never got on the air.

So CRS+TXF appears only when we have something to send.

## What it is not

- Not the bring-up path: replaying the boot -7 manual sequence (monitor
  ch6 first, then managed) on a fresh reload still gives 1/3 connects and
  26 suspend failures.
- Not the channel: boot -7 (good, 2/2 auths, 0 suspend failures) was also
  on ch11 (2462).
- Not the code: boot -7 loaded the same build (b43-7.2.7.ko, 14:39) with
  the same params.

Suspend failures per boot: -7 (14:53) 0; -6 (15:44) 10; -1 (16:22) 491;
0 (16:44) 457+. It gets worse the longer the machine has been up.

## Leading hypothesis: temperature drift, no periodic calibration

`b43_phy_ac_op_pwork_15sec` does no calibration (RX refill + logging).
wl recalibrates periodically, with temperature compensation. The TX
IQ/LO calibration never worked in this port (notes/16-22). A warm chip
with uncalibrated LO leakage could trip its own energy detect whenever
the TX chain starts: CRS only while TX is pending, clear when idle, as
observed.

Test: a real cold start. Power off for 30+ min, boot gen 16 (auto-load),
try b43 immediately, then watch whether suspend failures appear as it
warms. If cold = works, next is porting wl's periodic cal / tempsense.

The notes/57 correlation still holds, but with the cause reversed.
Suspend failures don't break RX; both come from TX being held off.
