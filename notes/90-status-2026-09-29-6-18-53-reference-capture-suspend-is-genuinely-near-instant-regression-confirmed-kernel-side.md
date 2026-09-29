# Status 2026-09-29 (part 14): 6.18.53 reference capture - decisive.
`b43_mac_suspend()` completes in 0-2ms on 6.18.53 vs. a consistent
~80ms on 7.2.7, same binary, same hardware, same operation. The
regression is real, kernel-side, and now precisely characterized.

Direct continuation of notes/89, same day. User explicitly asked to
pursue the actual root cause rather than only the auto-recovery
workaround, then approved a reboot. Booted into the pre-staged
one-shot 6.18.53 entry (generation 10, set via `bootctl set-oneshot`
before the reboot - default boot entry, generation 16/7.2.7, was left
untouched, so the *next* reboot returns to normal daily-use operation
automatically). This is a reference-only boot per the project's
standing rule - 6.18.53 is not, and is not becoming, the daily kernel.

## Setup

`tools/postboot.sh` (netwatch + b43-autorecover) run as usual, panic
sysctls set. `b43-autorecover` was briefly stopped during the manual
`wl`->`bcma` swap (it was already watching `wlp3s0b1`, which doesn't
exist while `wl` still owns the device under a different interface name,
`wlp3s0`, and reacting to that would have fought the manual swap) -
restarted once `wlp3s0b1` existed again. `b43_live.sh swap` performed
(unbinds `wl`, binds `bcma-pci-bridge` - "wl can't come back without a
reboot", per the script's own comment, consistent with 6.18.53 being a
one-way reference boot this session). The exact same instrumented
source, pre-built against 6.18.53 in notes/89
(`b43-src-builds/b43-6.18.53.ko`), copied into `b43-src/b43.ko` and used
via `connect_test.sh` unmodified - **identical code** to every 7.2.7
capture in notes/82-89.

One environment snag, fixed: after the first successful load, a second
`connect_test.sh` reload failed firmware loading ("Firmware file
`b43/ucode42.fw` not found") - `b43_live.sh swap`'s one-time firmware
search-path override gets restored by the following `load` once the
interface comes up, and this particular NixOS generation's own
`hardware.firmware` doesn't carry this project's custom firmware (that
wiring is presumably 7.2.7-generation-specific). Fixed by manually
re-pointing `/sys/module/firmware_class/parameters/path` at the
project's `firmware/` dir before the retry - not a finding, just
environment friction from testing on an older generation.

## Result: completely clean, three separate captures

1. **First full `connect_test.sh`** (fresh `rmmod`/reload + scan + auth,
   the exact same operation notes/82's original 62%-slow finding and
   notes/84's `b43_mac_suspend`-failure finding were captured from on
   7.2.7): **zero `optiming` lines** at the default 15ms threshold - no
   `b43_op_config` call took longer than 15ms, at all, during the whole
   connect sequence. **Zero `MAC suspend failed` lines.**
2. **Steady-state scanning** (already associated, `optiming_thresh_ms`
   lowered to 0 to log every call, 3 rescans, matching notes/85/86's
   methodology exactly): **38/38 samples**, `suspend=0ms` in 37, `2ms`
   in the other one outlier; `chan` a steady 8-9ms (one 16ms outlier);
   **zero suspend failures**.
3. **Second full `connect_test.sh`** (independent fresh reload): again
   **zero `optiming` lines**, **zero suspend failures**.

**Every single `b43_mac_suspend()` call across all three captures
completed near-instantly.** Compare directly to 7.2.7 (notes/84, 7/7
slow samples): `lock=0ms suspend=80-85ms` on *every* slow call, and
notes/82 found 62% of scan-time `drv_config` calls were slow in the
first place.

## What this settles

This is the most direct, controlled comparison this project has ever
run for this regression: **identical driver binary logic** (same
pre-built instrumented source), **identical hardware** (same laptop,
same chip, same boot session's RF environment), **identical operation**
(the same `connect_test.sh` script, the same channel-switch/scan
sequence) - the only variable is the kernel underneath. The result is
unambiguous: `b43_mac_suspend()` - a function that does nothing but
write a register and poll another one - takes ~40x longer (or fails
outright) on 7.2.7 than on 6.18.53, for the exact same request. **This
conclusively confirms the regression is real and kernel-side**, not a
measurement artifact, not driver drift, not RF/environmental noise. Every
piece of evidence back to notes/76 pointed this way; this is the first
capture with fine-grained, apples-to-apples timing proving it directly
rather than inferring it from connect success/failure rates.

**It does not, by itself, say *what* changed in the kernel.** No
`suspend diag` output exists for this boot (the diagnostic only fires on
failure, and nothing failed) - there's no 6.18.53 PSM-PC data to compare
against 7.2.7's two failure signatures from notes/89 (frozen vs. moving
PC), because there's nothing to sample.

## What this does narrow down

Since `b43_mac_suspend()` is purely "write a masked register, then poll
another register" - no firmware upload, no complex state, no timing-
sensitive sequencing beyond that single register pair - a ~40x slowdown
specific to *this* operation, but not (per notes/78-88's fast `chan`/
`txpwr`/`antenna`/`mac_enable` timings, both kernels) affecting the rest
of the same function's other MMIO-heavy work, points toward something
narrow: either (a) the *ucode's own* response latency to a suspend
request specifically differs (its internal scheduling/priority for
handling this particular request, independent of raw MMIO timing), or
(b) something in this *specific* MMIO read (`B43_MMIO_GEN_IRQ_REASON`)
or write (`B43_MMIO_MACCTL`) path is slower on 7.2.7 in a way that
doesn't show up on the other, similarly-MMIO-heavy phases of the same
function. A generic "everything is slower" kernel-side explanation
(e.g. a global PCIe/bus latency regression) seems hard to square with
`chan`/`txpwr`/`antenna` all being equally fast on both kernels -
whatever changed looks targeted at this one wait, not MMIO broadly.

## Next steps for a future session, in order

1. **Return to 7.2.7** (next reboot; default boot entry was left
   unchanged, so this happens automatically) and, informed by this
   capture, look specifically at what's unusual about
   `B43_MMIO_GEN_IRQ_REASON`/`B43_MMIO_MACCTL` handling on that kernel -
   IRQ masking state, whether something else is also reading/writing
   `GEN_IRQ_REASON` concurrently (the real hardware IRQ handler does,
   `b43_interrupt_handler`) and could be racing the poll, or clearing
   the bit before the poll sees it.
2. Check whether `b43_interrupt_handler` (the real IRQ path, separate
   from this polling loop) reads-and-clears `GEN_IRQ_REASON` - if the
   real IRQ fires between the register being set and this function's
   poll happening to land in that same instant, and the ISR clears the
   bit as part of normal ack handling, a kernel-version difference in
   *interrupt latency/scheduling* (not raw MMIO speed) could explain a
   race that's rare on a fast-IRQ-dispatch kernel and common on a
   slower one - worth checking `b43_interrupt_handler`'s handling of
   this specific bit.
3. If that doesn't pan out: the `git bisect` in `~/src/linux`, now
   informed by a much narrower question ("what changed about IRQ
   delivery/masking, or `GEN_IRQ_REASON` access ordering, between
   v6.18 and v7.2") rather than the broad sweep notes/77 Part 1
   originally tried.

## Current state at session end

6.18.53 boot, `wl` swapped out for `bcma`/our own `b43.ko` this session
(cannot be undone without a reboot, expected and fine - this was always
a one-shot reference boot). `b43-src/b43.ko` currently holds the
6.18.53 build (not the 7.2.7 one) - **will need rebuilding for 7.2.7
again after the next reboot**, same as notes/89 already did once (a
one-command fix,
`nix-shell -p gnumake gcc bc flex bison elfutils --run "make KDIR=.../linux-7.2.7-dev/..."`).
Connection currently healthy (`wlp3s0b1`, `b43-test` profile).
`netwatch`/`b43-autorecover` both active. Firmware search path
currently manually overridden to the project's local `firmware/` dir
(a `/sys/module/firmware_class/parameters/path` runtime setting, not
persisted, irrelevant after the next reboot).
