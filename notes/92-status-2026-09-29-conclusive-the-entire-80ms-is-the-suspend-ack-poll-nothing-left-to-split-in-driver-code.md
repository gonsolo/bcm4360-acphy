# Status 2026-09-29 (part 16): conclusive - on 7.2.7, `psctl=0ms` and
`wait=79-86ms` in every sample. The entire regression is now isolated to
one thing: the ucode taking ~80x longer to set `B43_IRQ_MAC_SUSPENDED`
after the `MACCTL` write. Nothing more to split in driver code.

Direct continuation of notes/91. User rebooted back to the default
(7.2.7) entry as planned - normal daily-use boot, `b43-ac-load.service`
auto-loaded the already-instrumented `b43-src/b43.ko` (staged at the
end of notes/91) via `tools/b43_boot.sh`. Ran `postboot.sh`
(netwatch + b43-autorecover), then simply let the boot's own first
autoload connection attempt happen and watched it with `dmesg`.

## Result: clean, tight, unambiguous

16 `suspendtiming` samples captured from the boot's own initial connect
attempt (no manual reload needed - this was completely ordinary daily-
use autoload, made the point better than a contrived test would have):

```
psctl=0ms   (16/16 samples, no exceptions)
wait=79-86ms (79, 79, 79, 80, 80, 80, 80, 80, 81, 81, 81, 81, 83, 83, 84, 85)
```

**`psctl` (the power-save wake-wait inside `b43_power_saving_ctl_bits`,
split out in notes/91) is 0ms in every single sample.** All ~80ms is in
`wait` - the loop that does nothing but repeatedly read
`B43_MMIO_GEN_IRQ_REASON` looking for `B43_IRQ_MAC_SUSPENDED`, after the
`MACCTL` write that requests the suspend. This exactly matches
notes/91's prediction, now confirmed rather than assumed. Compare
directly to 6.18.53's baseline (notes/91): `psctl=0ms`, `wait=0-3ms`,
15/15 samples - same split, same code, ~30-40x difference concentrated
entirely in this one wait.

## What this conclusively narrows the problem to

There is **no more driver-side code to split**. The full sequence for
this operation is: mask `MACCTL` to request suspend -> flush-read
`MACCTL` (forces the PCI/bcma write to actually post) -> poll
`GEN_IRQ_REASON` for the ucode's acknowledgment bit. Every step up to
and including the flush read is instrumented and accounted for
(`psctl=0ms`); everything from the flush read to the ack being observed
is `wait`. The remaining unknown is genuinely on the far side of that
write - either:

1. **The write itself** takes measurably longer to actually reach the
   hardware/ucode on 7.2.7 despite the explicit flush read (some kind
   of posted-write/backplane-arbitration difference not caught by a
   simple readback), or
2. **The ucode's own execution** - once it does see the request - takes
   longer to act on it and set the ack bit, for reasons that happen to
   correlate with kernel version (e.g. competing bus/DMA traffic
   patterns, backplane clock-gating requests, or scheduling of
   whichever internal ucode task handles this that's indirectly
   influenced by host-side timing).

Neither of these has any more driver source code that can distinguish
between them via `ktime_get()` instrumentation - the driver has already
done everything it can (write, flush, poll) by the time `wait` starts
counting. Further localization needs either bus-level tracing (e.g. a
PCIe/backplane transaction-level capture during the exact write, if any
tool in this project's kit could do that - not currently the case) or a
kernel-side investigation via `git bisect`.

## Assessment: driver-side instrumentation has reached its limit

Across notes/83-92, the timing/diagnostic instrumentation work has gone
from "some connects fail sometimes" to "one specific, single-register
poll takes ~80x longer on 7.2.7 than 6.18.53, confirmed by direct
side-by-side measurement, with every other phase of the same function
and the same surrounding code proven equally fast on both kernels."
That is about as precise a characterization as adding more `ktime_get()`
calls to `b43-src` can produce. The honest state of the investigation:
**root cause not found, but the search space has been reduced from
"somewhere in a kernel-version diff of tens of thousands of commits" to
"whatever affects how promptly this one ucode-to-host acknowledgment
happens after a MACCTL write."**

## Next steps for a future session, in order

1. **`git bisect` in `~/src/linux`**, now genuinely well-scoped: the
   bisect test is exactly this `suspendtiming: wait=` measurement (or
   even simpler, `MAC suspend failed` presence/absence over a handful of
   scan-triggered channel switches) rather than a vague "does it connect
   reliably" judgment call - a fast, unambiguous pass/fail per build.
   Confirmed in notes/77 Part 3 that each step needs a real local kernel
   build (no cache shortcut), so this is genuinely many build+boot+test
   cycles, but each individual test is now fast and mechanical.
2. If a bus-tracing tool becomes available (or is worth building) that
   can observe actual PCIe/backplane transaction timing around this
   specific write, that would directly answer "did the write arrive
   late, or did the ucode take long to act on it" without needing a
   bisect at all - but nothing in this project's current toolkit does
   this today.
3. Everything else on the daily-use plan (the module-build/deploy
   fragility, HT/throughput, suspend/resume, the 24h soak) remains
   independent of this and can proceed without the root cause being
   found - auto-recovery (notes/87/88) already makes the driver usable
   despite this regression.

## Current state at session end

No source changes this note (uses notes/91's instrumentation as-is).
Connection healthy (`wlp3s0b1`/`Vodafone-2A84`, real RX traffic).
`netwatch`/`b43-autorecover` both active, matching normal daily-use
boot state - this was an ordinary boot-time connect, not a contrived
test, and it still took 19 suspend failures before finally connecting,
consistent with every failure-rate figure this project has measured for
7.2.7. `b43-src-builds/b43-6.18.53.ko` remains staged for any future
6.18.53 reference need.
