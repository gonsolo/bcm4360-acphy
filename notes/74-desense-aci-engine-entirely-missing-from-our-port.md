# The real periodic desense/ACI engine is entirely absent from this port

Direct follow-up to notes/73, same session. Closes the chain this
session's decompiled-source reading opened.

## The chain, end to end

1. notes/72: `wl` reads MMIO `0x158` (a raw hardware register) every
   1.024 seconds, exactly - a real periodic watchdog tick, located for
   the first time after days of this project's older notes referencing
   its existence without finding it.
2. notes/73: read the actual decompiled watchdog source
   (`wlc_bmac_watchdog.c` -> `wlc_phy_watchdog.c`, both already in the
   repo). Found it reads SHM word `0xAC` (byte `0x158` - a *different*,
   coincidentally-same-numbered address) for PHY type `0xb` = AC,
   confirmed by tracing the branch condition. Decoded: that's macstat
   index 60, inside the already-known 64-word counter block (notes/12),
   past the 50 names this project's own decoder has ever assigned.
   Pulled it from already-logged dmesg output: a real, actively
   incrementing counter on our own chip, ~55 per 15 seconds.
3. This note: traced where the counter's *delta* (computed each
   watchdog tick) actually goes. `wlc_phy_watchdog` feeds it into a
   rolling 4-sample min/max/average computation, stored in per-device
   history arrays. `wlc_phy_desense_aci_engine_acphy` - confirmed
   already decompiled, and confirmed via matching offsets that it reads
   *the same* history arrays `wlc_phy_watchdog` writes - consumes that
   average, along with a second one from a sibling counter, against
   fixed thresholds (301, 601, 100, 300) to decide whether to change the
   receiver's desensitization level, applying the change via
   `FUN_0019b279` whenever the target level actually shifts.

## What desense/ACI means, practically

Adjacent-channel-interference desensitization: continuously watching
for signs a nearby interferer (another AP, a neighboring device) is
degrading reception, and adjusting front-end sensitivity in response -
running the whole time the radio is up, not a one-time init step.

## Confirmed absent

```
phy_ac.c:1792: * 0/1. Not ported yet: wlc_phy_hwaci_setup_acphy (interference mitigation).
```

One acknowledging comment, for a *different, related* setup function -
no trace of `desense`, `hwaci`, or `aci_engine` anywhere else in this
port. The entire mechanism - the counter, the rolling average, the
threshold comparison, the hardware-adjustment call - is simply not
there. Whatever receiver sensitivity state this chip powers up in, or
drifts into, nothing in this driver ever corrects it, for as long as
the interface stays up.

## Why this is a strong candidate, honestly caveated

This matches the shape of tonight's actual symptom better than anything
else found: intermittent, ~30-40% success, no single deterministic
trigger, present regardless of channel or association speed - exactly
what a receiver stuck at the wrong sensitivity level in a noisy 2.4GHz
environment (this project's own repeated observation: multiple
neighboring APs/devices visible at meaningful signal strength, notes/58
onward) would produce. Not proven - this note traces *what the
mechanism is and that it's missing*, not that porting it fixes the
auth-reliability problem. That's the real next test.

## Honest scope for tonight

Porting `wlc_phy_desense_aci_engine_acphy` properly is a real, sizeable
task - dense bit-level arithmetic, several dependent circular-buffer
structures already partially traced in `wlc_phy_watchdog.c`, and at
least one more un-decompiled function (`FUN_0019b279`, the actual
hardware-write). Not attempted this session, deliberately - this is
exactly the kind of "understand it fully first, then port it carefully,
then test it live" task this project's own established discipline
calls for, not something to rush at the end of an already very long
session. Named clearly for whoever picks this up next:

1. Decompile `FUN_0019b279` and `wlc_phy_hwaci_engine_acphy` (the other
   consumer) to complete the picture.
2. Name macstat indices 50-63 properly in `tools/macstat_decode.pl`
   (currently only 0-49 are named).
3. Port the counter-delta + rolling-average + threshold logic into
   `phy_ac.c`'s existing 15-second periodic hook
   (`b43_phy_ac_op_pwork_15sec`, which already exists and already logs
   this exact macstat block - it just doesn't act on it).
4. Test live, with the same discipline as the rest of this session:
   does it change success rate, not just "does it compile and not
   crash."
