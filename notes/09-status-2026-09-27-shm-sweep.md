# Status 2026-09-27 (continued), exhaustive SHM sweep for a "may originate TX" switch

Following up on the idea from notes/08: since wl definitely sends ACKs in
plain STA mode too, look for a register/table write that gates "ucode may
originate its own TX" as a capability switch, distinct from content/timing
(both already checked exhaustively).

## Candidates found and tested — all ruled out

- **`B43_SHM_SH_PRMAXTIME` (SHM 0x74)**: b43's own source comment says
  "Setting the MaxTime to one usec will always trigger a timeout, so we
  never send any probe resp" — an explicit, named, legacy switch that
  disables one specific class of firmware-autonomous TX (probe responses).
  wl's captured value is 0 (enabled); b43's `b43_wireless_core_init` writes
  1 (disabled) unconditionally, no phy-type check. **But live on hardware
  it already reads 0**, not 1 — something else (a later code path,
  possibly re-running part of `b43_chip_init`) overwrites it back to 0
  before the interface comes up. So this is already matching wl's value in
  practice; not the cause, and no fix needed.

- **FIFO 7 ("template FIFO") threshold setup** in `b43_ac_fifo_init`: this
  is the specific hardware queue autonomous frames (ACK, beacon) are
  transmitted from, as opposed to FIFOs 0-5 (host DMA-descriptor TX,
  proven 100% clean). Re-derived the exact arithmetic from wl's decompiled
  `FUN_00168c3d` by hand for our core_rev (42): every value our port
  writes for fifo==7 (0x54a, 0x54c, 0x520, 0x54e, 0x550, 0x548) matches
  wl's formula bit-for-bit. Ruled out with exact math, not guessing.

- **Full sweep of all 795 SHM words wl is captured writing** (first-load
  trace), diffed live against the running chip on channel 6: only **10**
  differ. 8 are the already-known, already-tested per-rate-table words
  (0x24a/24c/26a/26c/28a/28c/2aa/2ac — tested in the 09-26 22:40 session,
  no effect). The 2 new ones:
  - `0x15ba`: turned out to be a live, constantly-changing runtime counter
    (re-reading it immediately gave a different value again) — not a
    configuration register, the "difference" was just two snapshots of a
    moving target. Not meaningful.
  - `0x1816`: a real, static, writable register (held the forced value).
    Forced to wl's captured value (0x0281) and re-ran the probe-ACK test:
    no measurable change (37/40 = 92.5% PHY-error rate, same as baseline).

So: **every single SHM word wl is known to write has now been checked**
against the live chip, on top of the PHY registers, all PHY tables, radio
registers, MAC IHR registers (61-word diff, tested), chipcommon/PMU, RF
control overrides, and template RAM already covered in earlier notes.
Nothing found in host-visible, host-writable state explains the failure.

## What this suggests

The remaining candidates are outside what a register/table comparison
between wl and b43 can find:

- Something in the PHY's own internal analog/calibration state that isn't
  exposed as a normal register at all (gain-ramp calibration, TX power
  control loop state) and that only reaches a valid state through actual
  RF activity in a specific sequence we haven't reproduced — not
  something either driver "writes" in the traceable sense.
- A genuine hardware/firmware limitation specific to how this ucode
  version's autonomous-TX path interacts with bcma-mediated PCIe access
  (vs. wl's own bus layer, which may not be identical to Linux's bcma
  subsystem at this level of detail) — something below the register/SHM
  abstraction entirely.

Both would require instrumentation beyond what's practical here (e.g. an
actual RF capture of what happens electrically during a "PHY transmission
error" event, or vendor documentation of the analog calibration state
machine). This is a reasonable point to consider the register-comparison
approach exhausted for this specific problem, absent a new idea.
