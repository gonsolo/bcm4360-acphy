# Status 2026-09-27 (continued again), gain-override freshness theory - also ruled out

Following up further on "find that register": since the failure is
~90-95% *probabilistic*, not deterministic, that's more the signature of
a marginal analog/timing condition than a missing digital config value
(a wrong config value would typically be closer to 0% or 100%). Host TX
always has extra software/scheduling latency before it starts; firmware
auto-TX (ACK within 10us, beacon right at TBTT) doesn't. That pointed at
something needing settling time that host TX gets "for free."

## The lead: per-core gain-override registers (PHY 0x644/0x844)

Decompiled `wlc_phy_txpwrctrl_enable_acphy` (called around the AGC/cal
block in the channel-set tail): disabling power control reads the
*current* auto-settled gain per core (PHY 0x640/0x840, bits 0x7f00) via
`FUN_001913ee`; re-enabling writes that saved value into a *different*
register (PHY 0x644/0x844, bits 0x7f) via `FUN_00190114`. This is a
"freeze the currently-good auto-gain as a fixed override" pattern -
exactly what a fast, no-settling-time TX path would need to read instead
of waiting for the closed loop.

Checked live: 0x644/0x844 already matched wl's *captured* values exactly
(they're part of the already-verified "all PHY registers match" set).
But the *current, live* auto-gain (0x640/0x840) had drifted from wl's
one-time snapshot: core0 current=38 vs frozen=22, core1 current=25 vs
frozen=20. Plausible: our replay gives a value correct for wl's capture
conditions, but stale for whatever RF conditions exist now, and this
mechanism is designed to be re-run periodically, not applied once.

**Tested**: read the live current gain and manually re-froze it into the
override registers (0x644<-0x26, 0x844<-0x19), then re-ran the
probe-ACK test. **No change**: 38/40 = 95% PHY-error rate, same as
baseline. Ruled out.

## Pattern across all four candidates tried tonight

PRMAXTIME, FIFO-7 threshold math, the full 795-word SHM sweep, and now
gain-override freshness - none moved the failure rate even slightly, it
stays pinned at roughly 90-95% no matter what's poked. That consistency
argues against any single *computed value* (power, gain, rate, a missing
capability bit) being the explanation, and more toward the transmission
*mechanism/path itself* - something in how the D11 core's internal
sequencer pulls from the template FIFO and hands off to the PHY,
independent of what value is loaded into any register we can reach from
the host side.

## Where this leaves the investigation

Register/table comparison against wl, across everything reachable from
the host side, is now genuinely exhausted - not from lack of trying, but
because every specific, well-reasoned candidate (each backed by actual
decompiled wl code, not blind guessing) empirically changed nothing.
What's left needs different instrumentation than this project has:

- An RF capture (SDR or spectrum analyzer) of what's actually happening
  electrically during a "PHY transmission error" event - is a signal
  going out at all, malformed, at wrong power, or not at all?
- Silicon-level documentation of the AC-PHY analog calibration/TX-ramp
  state machine, which isn't available for this chip.

This is a reasonable point to set the ACK/firmware-TX problem aside as a
known, well-characterized limitation, and redirect effort elsewhere (5
GHz work, porting the replay into real init code, or something else the
user prefers) rather than continuing to guess registers with diminishing
returns.
