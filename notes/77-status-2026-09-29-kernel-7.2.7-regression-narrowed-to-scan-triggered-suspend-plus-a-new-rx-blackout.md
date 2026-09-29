# Status 2026-09-29: kernel 6.18.53 -> 7.2.7 regression narrowed (not
root-caused), two partial mitigations tested and falsified, and a new,
more basic RX-blackout symptom found live

Direct continuation of notes/76 (which established, via clean A/B testing,
that the exact same driver code/binary is reliably 4-5/5 on kernel 6.18.53
and 0/5-40% on kernel 7.2.7 - a real kernel-version regression, not a
firmware/ucode bug). This note covers a full session hunting the specific
kernel-side mechanism, and pivoting to live instrumentation when the hunt
ran out of road.

## Part 1: exhaustive targeted kernel commit search, v6.18..v7.2 - nothing found

Using `~/src/linux` (a full git clone with real history, tags `v6.18`/`v7.2`
available), searched every subsystem with a plausible causal story for
"same code, different kernel, MAC-suspend-timing-sensitive failure":

- `drivers/bcma` (whole dir): 2 commits, both a cosmetic treewide
  `kzalloc`->`kzalloc_obj` rename. Ruled out.
- In-tree `drivers/net/wireless/broadcom/b43`: 13 commits, all N-PHY
  rev8/radio2057-specific, none touch AC-PHY paths. Also moot regardless -
  we don't load that module, we load our own out-of-tree `b43-src`.
- `net/mac80211/mlme.c` (67 commits): the one plausible hit
  (`5d048bbed1bb`, SAE auth timeout) only extends `IEEE80211_AUTH_TIMEOUT_SAE`
  to EPPKE - doesn't touch our WPA2-PSK path. Ruled out.
- `net/mac80211/driver-ops.c`, `tx.c`, `status.c`, `scan.c`: nothing
  relevant (scan.c: 3 commits, all cosmetic/unrelated - RX timestamp
  export, S1G beacon check, element-parsing type).
- PCI ASPM (`drivers/pci/pcie/aspm.c`): live state identical on both
  kernels (`lspci -vv`: `ASPM L0s L1 Enabled` both times, no cmdline
  override either boot).
- PCI power-up / D3hot->D0 readiness wait
  (`41167a1e9853`, real commit, v6.18..v7.2): investigated in detail,
  genuinely interesting on paper, but **structurally ruled out**: `b43`
  binds to a virtual `bcma` bus, not the PCI device directly: confirmed
  live that `rmmod b43` leaves `bcma-pci-bridge` bound and the PCI device's
  `power_state`/`runtime_status` completely unchanged. This commit's path
  can fire at most once, at cold PCI enumeration - it cannot explain the
  per-attempt variability our testing methodology (5 attempts within one
  boot) actually measures.
- `kernel/irq/{chip,manage}.c`, `kernel/workqueue.c`, `kernel/time/hrtimer.c`:
  all checked, all irrelevant (percpu/NMI/cpuset-housekeeping/WQ_UNBOUND
  affinity machinery, nothing touching per-CPU `system_wq` timing or
  shared-IRQF_SHARED threaded-handler dispatch at our ~40-90ms scale).
  `b43` itself registers via `request_threaded_irq(..., b43_interrupt_handler,
  ..., IRQF_SHARED, ...)` with a real primary handler, so the one
  IRQ commit that looked promising (`51d0656959bc`, "forced secondary
  interrupt handler" priority) doesn't even apply - that's only for
  drivers with no primary handler at all.

**Net result: every subsystem with a plausible causal story has been
checked against real commit history and ruled out.** Whatever's different
between 6.18.53 and 7.2.7 is not a small, isolated commit in any of the
usual suspects.

## Part 2: is our own driver stale relative to stock b43? No.

Checked whether `b43-src` itself had drifted from what stock b43 looks
like on 7.2.7, using `b43-src/b43_vs_stock_7.2.7.diff` (already in the
repo from an earlier session). The only non-deliberate divergence is a
cosmetic `kzalloc`/`kzalloc_obj` naming difference (zero behavior change,
a treewide macro rename we haven't picked up). Everything else in the
diff is real, intentional, already-documented AC-PHY engineering
(`phy_ac.c`, the 64-bit DMA `ptr_is_addr` handling, RX-refill-retry
logic). **Our code is not stale relative to current stock b43** - this
rules out "our driver just needs a routine rebase" as an explanation too.

## Part 3: can NixOS's binary cache shortcut a bisect? No, not really.

Investigated whether intermediate/historical kernel versions could be
tested without local compiles (downloading substitutes from
cache.nixos.org instead). Concretely tested: pinned nixpkgs to a commit
from just before `linux_7_0` was pruned as EOL, asked to build it -
**the kernel derivation itself (`linux-7.0.13.drv`) still required a full
local build**, even though every *other* build dependency (stdenv, gcc,
the raw tarball) substituted fine. Hydra doesn't retain kernel binaries
once a version drops out of the active channel. Our two actual reference
points (6.18.53, 7.2.7) cost nothing (already built, already in the local
store from all this testing) - but any bisection step, coarse or fine,
needs a real local kernel compile. This makes a full `git bisect` a real
time cost (many build+reboot+retest cycles), not a free option.

## Part 4: live-testing two known mitigations - both falsified

Rather than keep archaeology going, pivoted to directly instrumenting a
real failure on 7.2.7, using tooling built two nights ago
(`b43_mac_suspend_diag()`, already wired into `main.c`, dumps
`psmdebug`/`phydebug`/`MACCTL`/`IRQ_REASON`/`UCODESTAT` + a kernel stack
trace on every suspend failure).

- **`ac_hostflags=1`** (notes/62's causally-confirmed NAP fix, HOSTF2/
  HOSTF3) had never actually been passed in any of this session's earlier
  7.2.7 tests tonight - it defaults off and nothing enabled it. Enabled it
  live: confirmed real effect (PSM PC now visibly moves across samples
  instead of freezing at one address) but **0/5 connections, still**.
- **`suspend_ms=90`** (matching wl's real, decompiled ~83ms suspend-wait
  bound from notes/28-29, vs our default 40ms): tested alone, **0/5**, and
  the diagnostic showed `psmdebug` frozen at the *identical* address
  (`00ff800f`) across all 8 samples spanning the full 90ms window - the
  ucode wasn't slowly-but-surely progressing and running out of time, it
  was completely halted. More patience genuinely could not have helped.
- **Both combined**: still **0/5**.

## Part 5: the real trigger, found via the diagnostic's own stack trace

The suspend-failure stack trace (already being captured, just not
previously read closely) shows the failing call chain is
`ieee80211_scan_work -> drv_config -> b43_op_config -> b43_mac_suspend` -
**every single failure this session traced back to a background/connect-
time scan trying to switch channels while we were (or scan itself was)
mid-operation**, not a TX-contention race during active auth as earlier
sessions assumed. `net/mac80211/scan.c` itself is unchanged between
kernels (Part 1), so this isn't new scan *logic* - it's that whatever
differs about the kernel makes this specific, always-possible collision
resolve badly now.

`b43_op_config` (`main.c`) is a single, unified path for every
reconfigure (initial bring-up and scan-triggered alike) - no separate
code path exists for scan vs. non-scan calls. The first, one-time
reconfigure at chip bring-up reliably succeeds; scan-triggered ones,
which necessarily come in a rapid, repeated series (one per channel,
~250ms apart, sweeping 1-13), do not - though even within one scan sweep,
most individual channel switches actually succeed silently and only a
handful randomly fail (confirmed via ms-precision `journalctl -o
short-monotonic` timestamps: channels 6/7 failed in one sweep, 11/12 in
the next, most others didn't) - genuinely intermittent, not a
deterministic block on every call.

## Part 6: a more basic, and more concerning, live finding - RX is currently dark

While testing, found that a clean, isolated `iw scan` (NetworkManager
taken off the interface first, so no competing scan) completes with exit
code 0 but returns **zero access points** - not even our own AP, always
in range all session. At the same time: the shared IRQ line **is** firing
(38 interrupts during the scan attempt), and TX status registers **are**
updating on every channel switch - so the chip isn't dead. But
`rx_packets` stayed at exactly 0 across the whole scan. Earlier the same
boot, the driver's own RX hex-dump debug line (gated to AC-PHY,
`dma.c`) had fired 228 times, so real frames were received successfully
at some earlier point tonight. Something changed state between then and
"now" (immediately before the reboot this note follows), or the RX window
per scanned channel isn't landing on a beacon reliably.

**This was not chased further before the reboot** - both because it's a
better-motivated next lead (a real, measurable settle-time-vs-scan-dwell
question, not a guess) and because, after this many live `rmmod`/`insmod`/
mode-toggle cycles in one boot, the finding itself is as likely to be
accumulated test-session state drift as it is a fact about the kernel.
**A clean reboot was done specifically to get a trustworthy baseline
before pursuing this.**

## Standing safety note, found and worth keeping visible (notes/59)

An unrelated, independent BCM4360 reverse-engineering project
(github.com/kimptoc/bcm4360-re, different hardware/approach) found strong
evidence their own sample's silicon was permanently degraded by
cumulative crash/reload testing - their previously-working vendor driver
eventually stopped attaching at all, with every software explanation
ruled out. This project has already had one hard freeze (notes/07) and,
across tonight and notes/56-58, has put this chip through many hundreds
of failed-MAC-suspend cycles. Nothing here is known to have caused
damage, but "the module reloads and nothing crashed" is not proof of
that, per kimptoc's own experience. Prefer reboots over long live
reload-cycling sessions where practical; if `wl` (the historical
known-good baseline) ever fails to attach with no software explanation,
treat that as a serious signal.

## Where this leaves things, precisely

**Confirmed observable symptom** (unchanged from notes/76, now more
precisely localized): the exact same driver, same load sequence, gets
clean 5/5 connections with zero suspend failures on 6.18.53, and 0/5 to
~40% on 7.2.7, with the specific, reproducible failure being scan-
channel-switch-triggered `b43_mac_suspend()` calls that the chip's own
firmware doesn't honor in time - genuinely halted (not slow) when it
fails, genuinely intermittent (most scan-triggered switches do succeed)
when it doesn't.

**Not yet found**: the specific kernel-side mechanism causing this,
despite a now fairly exhaustive targeted commit search (Part 1) - and a
newer, more basic, unexplained RX-silence symptom (Part 6) that may
turn out to be the more productive thread, or may turn out to be session
artifact. Needs re-testing clean, post-reboot, before drawing conclusions
either way.

## Next steps for a future session, in order

1. **Post-reboot, before any connection attempts**: reload cleanly
   (`sudo tools/b43_boot.sh ac_hostflags=1`), and immediately measure
   channel-switch settle time against mac80211's scan dwell window, using
   `tools/hw_timing`/`tools/psmpc_fast` - does the radio actually finish
   retuning and become receive-stable within the ~250ms-per-channel
   budget a scan gives it? This is the most concrete open lead.
2. Re-check the RX-completely-empty symptom (Part 6) on the clean boot -
   confirm whether it reproduces immediately (a real, basic bug) or only
   appears after extended live reload-cycling (a testing artifact worth
   documenting as a "don't trust extended-session RX numbers" methodology
   note, not a kernel finding).
3. If the settle-time-vs-dwell theory doesn't pan out: the honest next
   step for actually finding the kernel-side cause is a real `git bisect`
   in `~/src/linux` - now confirmed to need genuine local kernel builds at
   every step (no cache shortcut, Part 3), realistically several hours of
   build+reboot+retest cycles. Not started this session.
4. Longer-term, independent of the kernel-regression thread: the
   desense/ACI engine port (notes/74, real, confirmed-missing
   functionality) and naming macstat indices 50-63 remain open, lower-
   priority items.

## Current state at session end

Reboot done (user-initiated, per standing project rule that physical
reboots are always user-initiated, never model-initiated), landing back
on kernel 7.2.7 (generation 16, the current default). No source changes
this session - `suspend_ms` and `ac_hostflags` were only exercised live
via their existing runtime-settable (`0644`) sysfs parameters, nothing
persisted, and both are back at their defaults (`suspend_ms=40`,
`ac_hostflags` off) after the reboot since nothing was loaded yet. USB
stick backup link (`stick-backup` profile) was up and used as the
network path throughout all of tonight's live b43 testing.
