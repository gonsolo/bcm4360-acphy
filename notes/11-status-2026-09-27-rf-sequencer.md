# Status 2026-09-27 (continued), RF-sequencer force/settle steps - also ruled out

Following "make the ack work": since register/table *value* comparison
against wl was exhausted (notes/09, notes/10 - PRMAXTIME, FIFO-7 threshold
math, the full 795-word SHM sweep, gain-override freshness, all unchanged
the ~90-95% firmware-TX PHY-error rate), this looked for a *mechanism/
sequencing* step instead of a value: something wl runs as an action
(write, poll, wait) that a one-time "replay wl's captured register
snapshot" approach would never reproduce.

## The lead: `wlc_phy_force_rfseq_acphy`

Decompiled this function: it ORs one of 6 mode-specific bits into PHY
0x402, then actively polls PHY 0x403 for that same bit to clear (a
hardware completion handshake, bounded wait ~200ms), bracketed by saving/
restoring PHY 0x400 and 0x19e. This is a genuine RF-sequencer "kick an
analog transition and wait for hardware ready" primitive - completely
unported; PHY 0x400/0x401/0x402/0x403/0x160 appeared nowhere in
`phy_ac.c` before this session.

Found all real callers by fixing the Ghidra project (a from-scratch
`-import` with full auto-analysis, not `-noanalysis` - the previously
cached project's cross-reference database was empty, which silently
produced zero hits from `find_callers.java` and briefly pointed at a
phantom caller via a `nm`/`objdump` nearest-symbol artifact). The three
callers that actually fire for our exact chip (radio 2069 rev4, board
0117, confirmed against a real wl init trace, `traces/wl-init-*.trace`):

- `wlc_phy_rxcore_setstate_acphy(mask)` - cases 0+1, wraps them with a
  PHY 0x160/0x401 RX-core-count reconfiguration, MAC suspended. Called
  from the real channel-set tail (`wlc_phy_stf_chain_set`,
  `wlc_phy_cals_acphy`) whenever active RX-core count changes.
- `FUN_001aeb3a` (the real channel/PLL-tuning function) - case 2, bare,
  called unconditionally at the very start of every channel tune, right
  after `wlc_phy_stay_in_carriersearch_acphy(dev,1)`.
- `FUN_0019dc93` (a TX-gain/scan-roam calibration cache restore routine)
  - case 2 again, bare, after a batch of per-core TX-gain/filter table
  writes.

Cases 3, 4, 5 and the `FUN_001a581c` table-8-write variant of cases 0+1
(gated on a per-chip classification field, `phy+0x16e==2`) never fire in
the real trace for this hardware at all - confirmed by a `tbl 8` write
count of 0 across the whole captured init. Not relevant to this chip.

## Ported and tested

Added `b43_phy_ac_force_rfseq()` (the primitive, all 6 cases) and
`b43_phy_ac_rxcore_setstate()` (the case 0+1 wrapper) to `phy_ac.c`,
gated behind a new `ac_rfseq` module parameter. Verified byte-for-byte
against the real wl trace (`phy 160 7b`, `phy 401 7733`, `phy 402 1`,
`phy 402 2`, restores, etc. - exact match, including polling-loop
bounds) - confirmed live on hardware too via debugfs (`phy 0x160` read
back `0x7b` after running, matching wl and nothing else in the codebase
touches that register).

**Tested on real hardware, same boot session, same conditions each time
(`tools/probeack.sh`, CH 1, home AP `8c:6a:8d:9e:2a:88`, N=30):**

| config | probe retries | ucode txphyerr / txallfrm |
|---|---|---|
| baseline (no rfseq) | 75% | 115/151 |
| + rxcore_setstate (cases 0+1) | 74% | 113/151 |
| + force_rfseq(2) also | 73% | 115/157 |

All three runs are statistically indistinguishable. **Ruled out.**

## Where this leaves the investigation

This closes essentially the last concrete, decompiled-code-backed
mechanism candidate. Combined with notes/09-10's exhaustive register/
table value sweep, this project has now checked, against real decompiled
wl.ko logic (not blind guessing): every PHY/radio register, every PHY
table, every SHM word wl is known to write, the TX FIFO 7 threshold
formula, gain-override freshness, and now every RF-sequencer action wl
actually performs for this chip. None of it moves the firmware-
autonomous-TX failure rate off ~90-95%.

The `ac_rfseq` code itself is real, verified-correct driver logic (fills
a genuine gap - wl does run this on real hardware) and is kept; it's
just not the fix.

**What's actually left**, unchanged from notes/10's conclusion:

- An RF capture (SDR/spectrum analyzer) during a failure, to see whether
  a signal goes out at all, malformed, at the wrong power, or not at all.
- Silicon-level documentation of the AC-PHY analog TX-ramp/calibration
  state machine (not available for this chip).
- A structurally different idea: something *ucode-side* that gates
  "firmware may originate its own TX" as a race/timing condition rather
  than a static value - e.g. the exact handoff between the D11 core's
  autonomous-TX trigger (RX-response for ACK, TBTT for beacon) and PHY
  readiness. This is speculative and not yet backed by any decompiled
  evidence the way every candidate above was.

Given the pattern (7 well-motivated, code-backed candidates now checked,
zero effect), it's reasonable to treat this as a genuine, well-
characterized hardware/microcode-level limitation of the replay-based
approach, not a quick register fix. If continuing, prefer a fresh idea
over re-checking anything above.

## Also checked tonight, both dead ends

- **Host IRQ masking of `B43_IRQ_PHY_TXERR`**: wl's real trace shows it
  reprogramming `GEN_IRQ_MASK` (MMIO 0x12C) far more often than
  `GEN_IRQ_REASON` (2527 vs 1536 writes in one capture), which looked
  promising - maybe wl masks this interrupt during firmware TX because
  it's expected/benign there. Checked mainline b43: `B43_IRQ_PHY_TXERR`
  is unmasked in the shared `B43_IRQ_MASKTEMPLATE` for every b43 PHY
  family, and the handler just logs + counts (only restarts the
  controller after 1000 accumulated errors, main.c:2117). Masking this
  IRQ changes whether the *host* is told, not whether the PHY transmit
  itself succeeds - the ucode's own `txphyerr` counter (what
  `probeack.sh` actually reads) is independent of host IRQ masking. Not
  a lead.
- **Does wl itself see any `txphyerr` on this exact hardware?** This
  would be a very informative data point (an anomaly unique to our port
  vs. a baseline rate inherent to this chip/environment that wl also
  hits but tolerates). Tried to answer it from the existing captured
  traces (`traces/wl-tx-*.trace`) by looking for wl's own host-side reads
  of the macstat SHM block - found none in the ~12s capture window, so
  wl apparently doesn't poll these counters during ordinary operation
  (probably only on an explicit `wl counters` call or a much slower
  timer). **Can't be answered from existing data.** Getting a real
  answer needs wl bound and associated again, which needs a reboot (wl
  can't be rebound after b43 without one) - genuinely needs the user
  present. Do NOT build a tool that pokes `SHM_CONTROL`/`SHM_DATA`
  directly while wl owns the device to get this answer faster:
  `tools/macdump.c` deliberately skips that exact register range
  because it has read side effects and wl may be mid-access at any
  time - a second, independent accessor racing it is the same class of
  hazard as the two-driver-touching-hardware hard freeze from
  2026-09-26. If this is worth pursuing later, do it via a kprobe on
  wl's own stats-reading path (safe, observes only what wl itself
  already does), not a new independent register poke, and either force
  a `wl counters` call during the capture or capture for longer.
