# Status 2026-09-29 (part 15): IRQ-ack race hypothesis investigated and
mostly refuted by reading the code carefully; `b43_mac_suspend()` split
further (power-save wake-wait vs. the actual suspend-ack poll),
baselined clean on 6.18.53 - still on the reference boot

Direct continuation of notes/90, same day, same 6.18.53 reference boot
(default boot entry, 7.2.7/generation 16, still untouched - a normal
reboot returns to it).

## Hypothesis investigated: does the real IRQ handler race the suspend poll?

notes/90 flagged this as the leading next hypothesis: `b43_mac_suspend`'s
poll loop does a plain, repeated read of `B43_MMIO_GEN_IRQ_REASON`
looking for `B43_IRQ_MAC_SUSPENDED` (bit `0x1`); the *real* hardware
IRQ path (`b43_do_interrupt`, the top-half) also reads this exact
register and, if any masked-in reason bit is set, writes the (masked)
`reason` value back to acknowledge/clear it. If interrupt delivery
timing differs between kernels, a race between "the real ISR clears the
bit before the poll sees it" and "the poll wins" seemed like a strong,
kernel-version-sensitive candidate.

**Read the actual masking chain in `b43-src/main.c` (`b43_do_interrupt`,
`B43_IRQ_MASKTEMPLATE`, `dev->irq_mask`, all writes to
`B43_MMIO_GEN_IRQ_MASK`)**: `B43_IRQ_MAC_SUSPENDED` (`0x1`) is **not**
included in `B43_IRQ_MASKTEMPLATE`, and every place `dev->irq_mask` gets
written into the hardware's actual `GEN_IRQ_MASK` register uses that
same template (plus AC-PHY's `B43_IRQ_AC_EXTRA_MASK`, which also
doesn't include it). This means:

1. The hardware is never configured to raise a physical interrupt for
   this bit specifically.
2. Even if `b43_do_interrupt` runs concurrently for some *other*,
   masked-in reason and happens to observe `MAC_SUSPENDED` set in its
   own read, its ACK write is `reason &= dev->irq_mask` **before**
   being written back - so it can't clear a bit that isn't in the mask,
   even by accident.

**This specific race (top-half's write-back clearing the bit) is
refuted.** The narrower remaining possibility - that `GEN_IRQ_REASON`
might be hardware-level *read-to-clear* for all bits regardless of
software masking, so even the top-half's initial informational read
could destroy the bit as a side effect - is standard b43/Broadcom
register convention to be **write-1-to-clear**, not read-to-clear (the
driver's own explicit write-back-to-ack pattern is the normal idiom for
this register family, consistent throughout this codebase and upstream
b43). Not something this session could verify against a datasheet, but
low-confidence enough, combined with point 1 (the interrupt isn't even
configured to fire for this bit), that this hypothesis is being set
aside rather than pursued further without new evidence.

## Found and tested instead: another real wait inside `b43_mac_suspend()`

`b43_mac_suspend()`'s first action is `b43_power_saving_ctl_bits(dev,
B43_PS_AWAKE)`, which has its own poll loop ("wait for the microcode to
wake up", `main.c` ~1258-1266: up to 100 x `udelay(10)` on
`B43_SHM_SH_UCODESTAT`, ~1ms max) - a *second*, separate wait bundled
inside the single `__t_suspend`/`suspend=` timing bucket notes/89
measured. Split it out: added a timestamp between this call and the
main `MACCTL`-suspend poll, logging `suspendtiming: total=Xms
psctl=Xms wait=Xms` (same `optiming_thresh_ms` param, moved earlier in
the file so both `b43_mac_suspend` and `b43_op_config` can use it).

## 6.18.53 baseline: both sub-phases clean

Rebuilt (6.18.53), reloaded, ran a fresh connect + several rescans with
the threshold at 0 (log every call): **15/15 samples**, `psctl=0ms` in
every one, `wait` at `0ms` in 14/15 and `3ms` in the one outlier. No
hidden slowness in the power-save wake-wait either - on 6.18.53, this
entire code path is uniformly fast, not just "fast on average."

## What's still needed

The actual comparison point - running this same `psctl`/`wait` split on
**7.2.7**, where notes/84/89 already showed the combined `suspend=`
bucket at ~80ms - hasn't happened yet this session. That's the natural
next step and needs the reboot back to the default (7.2.7) entry that
was already staged before this reference session began. Prediction,
not yet confirmed: given `psctl`'s own loop is hard-capped at ~1ms by
design, the ~80ms on 7.2.7 is almost certainly concentrated in `wait`
(the actual `MAC_SUSPENDED`-ack poll) - but this should be measured,
not assumed, especially after the IRQ-race hypothesis turned out to be
less solid on inspection than it first seemed.

## Next steps for a future session, in order

1. **Reboot back to 7.2.7** (normal reboot - default entry already
   correct) and run the same `psctl`/`wait`-split capture there,
   confirming or correcting the prediction above.
2. If `wait` is indeed where the ~80ms lives (expected): the open
   question becomes what, on the *ucode/hardware* side, differs in how
   promptly `B43_IRQ_MAC_SUSPENDED` gets set in `GEN_IRQ_REASON` after
   the `MACCTL` write on 7.2.7 vs. 6.18.53 - since this is a single
   register bit with no software-side kernel-version-dependent code in
   between (just a masked write, a flush read, then a plain poll), any
   remaining explanation has to route through either raw MMIO/PCIe
   transaction timing for *this specific write* reaching the hardware,
   or genuine ucode-side timing/scheduling that's somehow influenced by
   the host kernel (e.g. backplane clock-gating requests, or something
   else the AC-PHY init path leaves in a kernel-version-sensitive
   state).
3. If `psctl` turns out to matter after all (surprising, but not yet
   ruled out on 7.2.7 specifically): investigate `B43_SHM_SH_UCODESTAT`
   transition timing instead.
4. `git bisect` in `~/src/linux` remains the last-resort option,
   narrower now than notes/77 Part 1's original broad sweep but still
   only worth it if steps 1-3 don't localize things further.

## Current state at session end

Source change: `b43-src/main.c` - `b43_mac_suspend()` gained internal
`psctl`/`wait` timing (reuses the `optiming_thresh_ms` param, moved
earlier in the file for visibility ordering; log line
`suspendtiming:`). `b43-src-builds/b43-6.18.53.ko` updated to include
this split. Live `b43-src/b43.ko` rebuilt back to 7.2.7 vermagic (not
loadable on this still-6.18.53 boot, staged for after the next reboot,
same pattern as notes/89/90). Connection healthy
(`wlp3s0b1`/`b43-test`). Still on the 6.18.53 reference boot; default
boot entry (generation 16, 7.2.7) untouched, so the next reboot returns
to normal daily-use operation automatically.
