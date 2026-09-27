# Status 2026-09-27: wl comparison test - the hardware works, our port has the gap

User came back and asked to directly settle the question notes/17 left
open: does `wl` itself ever see the same firmware-autonomous-TX failure
on this exact hardware, or does it work reliably? Rebooted into
Generation 6 (wl bound normally, no swap-away), confirmed single
session, backup link, panic-on-hang sysctls - all per established
practice, now with the user physically present.

## What was tried first (and abandoned)

Attempted to find wl's exact internal SHM address for the `txphyerr`
counter (word 0x7F, established via the ucode disassembly in notes/12)
by attaching bpftrace kprobes to wl's own `osl_read*`/`osl_write*`
functions on the *already-running, already-bound* driver - deliberately
never touching wl's PCI binding, per the hard lesson already documented
in `trace_wl.sh` ("changing the binding of wl while probes attach
crashed the machine twice").

This surfaced one real, useful lesson and one dead end:

- **Lesson confirmed safe:** kprobing wl's hot-path register-access
  functions while it's actively associated and passing real traffic
  does not disrupt it - multiple sustained ping tests during active
  tracing showed 0% packet loss throughout. (A `wlp3s0` disconnect seen
  early in this session turned out to be unrelated: both the internal
  chip and the USB stick share one NetworkManager connection profile
  for the same SSID, so activating either deactivates the other - a
  NetworkManager detail, not a driver or tracing issue.)
- **Dead end:** the SHM routing/offset pair that matched `txphyerr`'s
  known word index (routing `0x0004`, offset `0x7e`/`0x7f`) turned out
  to hold completely static values (`0x4d353884`, `0x80086e18`,
  identical across 26+ seconds and multiple reads) - not an
  incrementing counter. It's part of a different, faster (~25ms)
  periodic routine alongside clock-control (`BCMA_CLKCTLST`) and IRQ-
  status register reads - almost certainly a hardware health/watchdog
  check, not a stats poll. wl's real macstat-equivalent block is
  elsewhere (a `routing=0x0301` region with ~56 distinct offsets was
  also observed, but its behavior wasn't characterized before this
  approach was abandoned as too slow for what it was actually needed
  to answer).

## What actually answered the question

Realized the exact counter value was never necessary. A live,
real-world behavioral test settles the same question far more directly:
**ICMP ping absolutely requires the firmware to generate an ACK for
every incoming reply** - the same category of operation
(firmware-autonomous TX) that fails ~90-95% of the time in this
project's b43 port.

Ran sustained ping over `wlp3s0` (the internal BCM4360, driven by `wl`,
on this exact physical chip):
- 60 packets, 0.2s interval, 1400-byte payload (near-MTU, not trivial
  ICMP): **60/60 received, 0% packet loss**, consistent ~16-25ms
  latency (one 180ms outlier, coinciding with the AP band-steering the
  connection from 2.4 GHz to 5 GHz mid-test - a normal roam, not a
  fault).
- Multiple earlier shorter runs during the tracing work: consistently
  0% packet loss as well, including through the roam and reconnects.

**Conclusion: the hardware is not broken.** `wl` achieves completely
reliable firmware-autonomous ACK generation on this exact chip, this
exact board, this exact radio. Whatever this port's b43 port is doing
differently - or failing to do - is a real, fixable gap in the port,
not a hardware fault.

## What this means for today's earlier conclusion (notes/16-18)

This meaningfully **weakens** (does not fully retract, but substantially
undercuts) today's earlier working hypothesis that the flat TX-
calibration measurement result pointed toward a genuine TX RF hardware
fault. That measurement is still real and still unexplained, but "the
hardware is fine, wl proves it" is now the better-supported reading of
the *combined* evidence:

- The TX-calibration measurement mechanism (notes/16-18) may itself
  still have a bug or missing precondition this project hasn't found
  yet - this is now the **more likely** explanation for that flat
  result, not "nothing to measure because the hardware can't
  transmit."
- The original independent OTA finding (notes/15: zero ACKs ever
  detected from the b43 port) stands as-is - it was always about *this
  port's* output, not the hardware's capability, and is now understood
  in that light rather than as evidence of a hardware limitation.

## Where this leaves the investigation

The calibration hypothesis is back to being a live, plausible
candidate - alongside the possibility that something else entirely
(some other piece of wl's real init/attach sequence this port hasn't
replicated) is the actual gap. The productive next step is comparing
what wl actually *does* differently from this port during normal
operation - not further attempts to read wl's internal counters, but
looking at what registers/sequences wl touches that this port's
`ac_por` replay and channel-switch path do not.

Given the significant time already spent on the SHM-tracing approach
without a clean answer, a more promising next angle: capture wl's full
register-access sequence *specifically during and immediately after
association* (using the existing, already-proven `wl_full_trace.bt` or
`trace_wl.sh`) and diff it against what this port already replays via
`ac_por`, looking specifically for anything touched close to
association time that isn't part of the existing first-load replay -
that's a much narrower, more tractable comparison than a full init
trace (already partially done in earlier sessions) or free-form counter
hunting.
