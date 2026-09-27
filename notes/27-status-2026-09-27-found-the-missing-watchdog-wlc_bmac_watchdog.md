# Status 2026-09-27 (late evening, continued yet further): identified the likely mechanism - wl's periodic watchdog (`wlc_bmac_watchdog`/`wlc_bmac_fifoerrors`/`wlc_phy_watchdog`) is never ported in b43-src

Direct follow-up to notes/26, same evening, per explicit user instruction
("set it up and run it") to check whether the real vendor driver (`wl`)
shows the same ~1.024 s periodic pattern found in b43, using the
already-proven-safe `trace_wl.sh` technique (keeps `wl` loaded and bound
throughout, only bounces the netdev, never touches PCI binding).

## Setup and capture

`wl` had been left unbound after the previous round's `b43`
experimentation; per this project's standing safety rule (never rebind
`wl` after `b43` has touched the chip in the same boot session), asked
the user to reboot first. After the reboot, verified `wl` bound and
`wlp3s0` connected, then ran `trace_wl.sh` via `systemd-run` with the
established absolute-path invocation. It completed cleanly: real
authentication/association, 20 s of steady-state traffic, and a
self-verified "WiFi is back" at the end - `traces/wl-init-20260927-212541.trace`,
9.2 MB, 222,236 valid MMIO-access lines over a 23.18 s window.

## Result: wl has an almost perfectly exact ~1.024 s periodic access pattern too

Grouped every accessed address by its gap sequence and searched for gaps
clustering near 1.024 s (30 ms tolerance). Found a clean, unambiguous
match: a specific group of MMIO offsets is touched **exactly once per
cycle, 21-22 times over the 23 s trace, with gaps of 1023.9-1024.4 ms** -
tenths-of-a-millisecond precision, not something that happens by chance.

Resolving the trace's raw kernel virtual addresses against the trace's
own base (`0xffffd1d4411ec000`) and cross-referencing `b43.h`/`dma.h`
identified every one of the periodically-touched offsets as **real,
named, well-understood b43 MMIO registers**:

- `0x020, 0x028, 0x030, 0x038, 0x040, 0x048` - `B43_MMIO_DMA{0..5}_REASON`
  (the six DMA ring interrupt-reason registers; `0x020`/DMA0 doesn't show
  up as cleanly periodic only because it's also read constantly during
  ordinary RX-done interrupt handling, drowning out its own periodic
  touch in the noise)
- `0x124` - `B43_MMIO_MACCMD` (MAC command register)
- `0x158` - `B43_MMIO_RADIO_HWENABLED_HI`
- `0x170` - `B43_MMIO_XMITSTAT_0` (**transmit status**)
- `0x184` - `B43_MMIO_REV3PLUS_TSF_HIGH` (802.11 clock, high word)
- `0x3fc/0x3fe` - the indirect PHY register select/data port (a burst of
  real PHY register reads/writes happens once per cycle)
- `0x3d8/0x3da` - the indirect radio register select/data port (same,
  for radio registers)
- `0x3e0` - `B43_MMIO_PHY_VER`
- `0x160/0x164/0x166` - the SHM select/data port

This is the unmistakable signature of a **periodic driver-side
maintenance/watchdog routine**: check every DMA ring for errors, check
MAC command state, check transmit status, check the radio, do a PHY
health pass, check SHM state - once every ~1.024 seconds.

## Identifying the actual function: `wlc_bmac_watchdog`

This project already has a decompiled (if minimal, 19-line) copy of
exactly this function from earlier work:
`decompiled-si/wlc_bmac_watchdog.c`:

```c
void wlc_bmac_watchdog(long param_1)
{
  long lVar1 = *(long *)(param_1 + 0x20);
  if (*(char *)(lVar1 + 0x10c) != '\0') {
    *(int *)(lVar1 + 0x110) = *(int *)(lVar1 + 0x110) + 1;
    wlc_bmac_fifoerrors(lVar1);
    (**(code **)(**(long **)(lVar1 + 0x20) + 0xd8))();
    if (*(int *)(lVar1 + 0x84) == 4) {
      (**(code **)(**(long **)(lVar1 + 0x38) + 0xd8))();
    }
    wlc_phy_watchdog(*(undefined8 *)(*(long *)(lVar1 + 0xe8) + 0x28));
  }
}
```

And `decompiled-si/wlc_bmac_fifoerrors.c` (also already present) matches
the trace's DMA-register access pattern *exactly*: it loops over all six
DMA rings (`base + 0x20 + i*8`, `i = 0..5` - precisely the six offsets
found above), reads each REASON register, and checks it against mask
`0xdc00` (bits 10-15: overflow/descriptor-error bits). **Every bit in
that mask, if set on any ring, leads to `wlc_fatal_error()`** - i.e. this
function is wl's real, active DMA-error detector, invoked once per
watchdog cycle, that escalates to a full error-recovery path the instant
it sees a FIFO/DMA problem on any ring.

`wlc_phy_watchdog()` (the PHY-side half, matching the periodic PHY/radio
register burst in the trace) has not been decompiled in this project yet
- worth doing next, since it's plausibly the piece most directly relevant
to the RX-blackout finding, the way `wlc_bmac_fifoerrors` is plausibly
the piece most relevant to TX reliability.

## Neither `wlc_bmac_watchdog` nor its callees are referenced anywhere in `b43-src`

Confirmed via direct search: **this entire periodic maintenance
mechanism is completely absent from this project's b43 port.** Whatever
`wlc_phy_watchdog` actually does (recalibration, error-bit clearing, a
sanity re-tune - not yet known, undecompiled), and whatever recovery
`wlc_fatal_error` performs when `wlc_bmac_fifoerrors` detects a DMA
problem, none of it ever runs in this port. If the real AC-PHY hardware
does experience occasional DMA/FIFO errors or PHY drift under normal
operation (plausible, and arguably *expected* given wl itself carries an
active error-detection-and-recovery path for exactly this), b43 has no
mechanism to ever notice or correct it.

## Why this is significant

This is the first concrete, comparably-evidenced candidate in the
project's history that plausibly connects *both* long-standing problems
at once:

- **The newly-found RX blackout** (notes/25, notes/26): a missing
  periodic PHY health/recalibration pass (`wlc_phy_watchdog`) is a very
  natural explanation for periodic reception degradation that self-
  corrects (or doesn't) without any external trigger.
- **The project's original, central finding** (firmware-autonomous TX/
  ACK failing ~90-95% of the time): a missing DMA-error detection-and-
  recovery path (`wlc_bmac_fifoerrors`/`wlc_fatal_error`) is a very
  natural explanation for TX reliability silently degrading over time
  with nothing in the driver ever noticing or fixing it.

Neither connection is *proven* - `wlc_phy_watchdog` and `wlc_fatal_error`
still need decompiling to know what they actually do, and nothing tonight
directly tested whether porting either function changes real-world
behavior. But this is a qualitatively different kind of lead than
anything found earlier in the project: it's not a guess about what
*might* be missing, it's a specific, named function, independently
confirmed present and running on a precise ~1 s cycle in the real driver,
provably absent from this port, whose already-decompiled half does
exactly the kind of error-recovery work whose *absence* would predict
the exact symptoms this project has spent many sessions chasing.

## Deliberately not attempted tonight

Porting a new function that touches DMA reset/recovery and PHY
recalibration state is a materially different risk category from
tonight's read-only trace analysis - consistent with this project's
established practice (mirrors the caution already applied to the TX
calibration work, notes/16), this needs decompiling `wlc_phy_watchdog`
and `wlc_fatal_error` first, understanding exactly what they do, and then
staging/testing incrementally on real hardware with the user present -
not rushed into a single very long session already deep into the night.

## Next steps for a future session

1. Decompile `wlc_phy_watchdog` and `wlc_fatal_error` (both referenced,
   neither yet extracted) to see exactly what recovery/recalibration
   they perform.
2. Decompile the two indirect-called functions in `wlc_bmac_watchdog`
   itself (`(**(code **)(**(long **)(lVar1 + 0x20) + 0xd8))()` and the
   conditional second one) - virtual/vtable calls, harder to resolve
   statically, may need a live wl-side trace of the *call targets* (e.g.
   via `uprobe`s on the resolved addresses) rather than static analysis.
3. Find where `wlc_bmac_watchdog` itself is scheduled (a timer setup
   with a ~1024-tick or `WATCHDOG_INTERVAL`-style constant) to confirm
   the exact intended period and whether it's configurable.
4. Once understood, port incrementally and test on real hardware **with
   the user present**, given the risk profile (DMA/reset-path code).
5. The RX-blackout (notes/25/26) and scan-finds-nothing (notes/24)
   findings should be re-tested once any watchdog-related code lands, to
   see whether they resolve.
6. Loft-comp calibration question (notes/22) remains fully open and
   untouched.

## Session close

No crashes, no dmesg BUG/Oops/panic lines. `wl` remains bound and
working normally throughout and after this trace (verified: `wlp3s0`
connected, 0% packet loss to 8.8.8.8, `trace_wl.sh`'s own self-check
reported "WiFi is back"). No `b43-src` changes tonight from this note's
work - trace capture and read-only analysis only.
