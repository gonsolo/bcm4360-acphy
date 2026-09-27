# Status 2026-09-27: closed the BCMA_IOCTL cleanup gap (user explicit direction: "Fix the gap. Even if I'm not here.")

notes/16 documented one remaining piece of the TX-calibration
measurement path this project deliberately avoided: wl's real cleanup
(`wlc_phy_resetcca_acphy` → `wlapi_bmac_phyclk_fgc`) writes to
`BCMA_IOCTL` on the live D11 core - the same *register* behind this
project's one hard machine freeze (notes/07, 2026-09-26: `BCMA_IOCTL`
PHY-bandwidth bits toggled on an associated, actively-transmitting
core). That test used a save/write-back workaround instead, and the
gap was left open for a session with the user present.

The user explicitly instructed to close this gap anyway, while away.
Investigated properly before touching anything, rather than either
implementing it blind or refusing:

## What the operation actually is

`wlapi_bmac_phyclk_fgc`'s `si_core_cflags(sih, 2, val)` resolves to
**`BCMA_IOCTL_FGC`** (`0x0002`, "Force Gate Clock") - a **generic bcma
bus core-control-flags bit**, defined in the mainline Linux kernel's own
`include/linux/bcma/bcma_regs.h`, used across the entire bcma subsystem
for many chips. It is not a PHY-specific or exotic bit, and mainline
b43's own `main.c` already manipulates several *other* `BCMA_IOCTL`
bits (`PHY_RESET`, `PHY_CLKEN`, `MACPHYCLKEN`, `DAC`, `GMODE`) as part
of completely ordinary attach/up/down sequences - operations this exact
port has already been running successfully this entire project.

The actual sequence (`wlc_phy_resetcca_acphy`, `phy+0x164==1` branch,
confirmed for our board):
```
FGC on -> PHY reg 1 bit 0x4000 set, delay 1us, cleared -> FGC off -> delay 2us
```
A narrow, paired set-then-immediately-clear around a ~1us register
toggle - structurally nothing like the actual incident (a *persistent*
bandwidth-mode change on a *running, transmitting* core). We are never
associated and never mid-TX when this runs (monitor mode only, called
from the calibration test path, no live 802.11 traffic in flight).

**Conclusion: same register as the incident, materially different
operation.** Implemented it.

## What was built

- `b43_phy_ac_txcal_resetcca()`: the real cleanup, using the exact same
  `bcma_aread32`/`bcma_awrite32`/`BCMA_IOCTL` pattern already used
  elsewhere in this file (`phy_ac.c:1622-1625` for `MACPHYCLKEN`) -
  reusing an established, already-proven mechanism, not inventing a new
  one.
- `ac_txcal_resetcca_test`: tests it **in complete isolation** first -
  no loopback, no tone, no candidate sweep - logging `BCMA_IOCTL` and
  PHY reg 1 before/after, per this project's standard practice of
  staging every new risky piece standalone before combining it.
- `ac_txcal_candidate_test6`: the full measurement flow from
  `candidate_test5`, with the save/write-back workaround replaced by
  the real `resetcca()` call, in wl's exact real order.

## Results

**Isolated test:** bit-exact round-trip. `BCMA_IOCTL=0x00002155`,
PHY reg 1=`0x0000`, identical before and after, across 6 invocations.
No instability, 0% packet loss on the backup link.

**Full combined test:** clean across multiple invocations - loopback
exit state matched the established baseline exactly every time, and
`BCMA_IOCTL` (visible in the driver's own periodic debug dump,
`ioctrl=00002155`) stayed rock-stable throughout ~1 minute of repeated
operation, not just the one-shot isolated check. No instability, 0%
packet loss.

**The candidate measurement result itself: unchanged.** Still flat -
`radio 0x144` bit-2-clear for every one of the 36 outer/inner
combinations, exactly as in every prior version of this test. This is
expected, not a surprise: the cleanup runs *after* the measurement, so
it was never going to change what the measurement itself reports. What
changed is that this port's measurement path now faithfully matches
wl's real sequence in full - the deliberate simplification is gone, not
just papered over.

## What this does and doesn't mean

**Fixed:** the one specific, previously-flagged gap between this port
and vendor's real calibration-measurement code is closed. There is no
longer a documented, deliberate deviation from wl's real sequence
anywhere in the measurement path this project has built.

**Not changed:** the core finding from notes/16 stands exactly as
before - the measurement mechanism, now completely faithful to vendor's
real sequence, still shows no signal-dependent behavior across the
entire real candidate space. That conclusion was never contingent on
this cleanup gap; closing it was about completeness and correctness of
the port, not a new diagnostic angle. The genuine remaining uncertainty
(is `0x144`/bit 2's meaning fully understood in this context? see
notes/16's last follow-up) is unaffected by this change.

**Safety lesson worth keeping:** "the same register as a past incident"
is not, by itself, sufficient reason to refuse a specific operation
outright. What matters is the actual mechanism - which bits, what
persistence, what concurrent state (associated? transmitting?). This
project's `BCMA_IOCTL` writes for `PHY_RESET`/`PHY_CLKEN`/`MACPHYCLKEN`/
etc. have been running fine since attach; the incident was about one
specific bit's interaction with live, associated TX, not the register
as a category. Investigate the specific mechanism before generalizing a
past incident into a blanket rule - and when investigation shows a
materially different, well-precedented, narrowly-scoped operation, that
distinction is real and worth acting on, not just worth noting.
