# Status 2026-09-28 (cont'd): narrowed the post-association disconnect to real, intermittent RX/ACK loss - not fixed

Direct follow-up to notes/33's "Follow-up same night" section. Used bpftrace
(kprobes on both b43.ko and mac80211, confirmed traceable - only wl.ko is
notrace) to instrument three connection attempts end-to-end and find exactly
what precedes a disconnect, rather than continuing to guess from dmesg alone.

## Ruled out: hardware/DMA fatal errors

b43 (mainline code, unmodified) already detects `B43_DMAIRQ_FATALMASK` and
PHY-TX-error-rate conditions and calls `b43_controller_restart()` on either.
`dmesg` was checked across every disconnect tonight for "Fatal DMA error",
"PHY transmission error", "Too many PHY TX errors", "restarting the
controller" - **none ever appeared**. Whatever's happening is not tripping
any hardware error-interrupt condition; it's silent from the MAC/DMA
engine's point of view. This rules out porting `wlc_bmac_fifoerrors`/
`wlc_fatal_error` as the fix - b43 already has equivalent detection+recovery
for that failure class, and it's not the one occurring.

## Confirmed: our own outgoing unicast frames intermittently get zero ACK

Traced `b43_op_tx`+`b43_handle_txstatus` (both directly kprobe-able, no BTF
struct definitions needed - direct pointer+offset reads into `struct
b43_txstatus`, same technique this project has used throughout) alongside
mac80211's `ieee80211_mgd_probe_ap_send`/`ieee80211_beacon_loss`/
`ieee80211_sta_connection_lost`/`ieee80211_send_deauth_disassoc` (all
directly traceable - only `ieee80211_sta_reset_beacon_monitor`/
`_reset_conn_monitor` needed for the full picture, also traceable).

Decoded `frame_control` directly from `((struct sk_buff *)arg2)->data` at
`b43_op_tx` (kernel BTF for `struct sk_buff` resolved fine under bpftrace,
no manual offset guessing needed for that struct specifically). Result,
across one full connect-to-disconnect cycle:

- Auth (fc=0x00b0), assoc request (fc=0x0000), EAPOL-over-QoS-data
  (fc=0x0188), and encrypted QoS data (fc=0x4188, protected bit set - real
  DHCP/data traffic post-handshake) all succeed normally (`acked=1`,
  `fcnt=2` typical - two real transmit attempts, then ACKed).
- One encrypted data frame is dropped as lifetime-expired mid-stream
  (`fcnt=0 supp=5`, i.e. never even attempted - see below).
- mac80211's connection-monitor keepalive probe (`ieee80211_mgd_probe_ap_send`,
  a short **directed unicast** probe request to the AP, fc=0x0040 len=55,
  distinct from the longer broadcast scan-time probes) fires roughly every
  ~504ms once beacon reception looks stale. The first two attempts in this
  run got ACKed normally. **The next three consecutive attempts got
  `fcnt=1 supp=0 acked=0`** - genuinely transmitted once each, no lifetime
  issue, just never ACKed by the AP (or the AP's ACK was sent but we never
  decoded it) - three real failures in a row, roughly 1.5s of no-response.
- Immediately after those three failures, mac80211 gave up on the directed
  probe and fell back to broadcast scan-style probing (the paired
  fc=0x0040 len=199/186 frames from before) - i.e. it concluded the AP is
  gone and started searching again. This is the disconnect.

This is not an ACK-*generation* bug (that was the OFDM-PHY-por/rate-block
fix from earlier tonight, and it's clearly working - the vast majority of
unicast frames throughout this trace, including two of the five keepalive
probes, get ACKed fine). It's **intermittent, occasional total silence on
receiving the AP's response to our own transmission**, exactly matching the
project's own, much older, still-unexplained finding from notes/25/26: an
~11% baseline of abnormally long gaps in ordinary steady-state RX,
independent of anything this session touched. Tonight is the first time
that baseline flakiness has been shown to actually break something
end-to-end (three unlucky consecutive misses in the same ~1.5s window is
enough to convince mac80211 the AP disappeared) - previously it only
degraded passive capture/scan statistics.

## The lifetime-expired (`supp=5`) frames are a separate, more cosmetic finding

Every so often, when mac80211 sends two probe requests back-to-back (which
it does during a broadcast scan, apparently once per SSID/probe-request
variant), the **second** one of the pair gets `fcnt=0 supp=5 acked=0` -
dropped by ucode as already-lifetime-expired, without a single transmit
attempt. This happens consistently after a few bursts, both before
association and again once mac80211 falls back to scanning post-disconnect.
It doesn't look like the actual blocker (scanning still finds APs fine
throughout this project's testing, since the *other* probe in each pair
typically gets out and answered), but it's a real, distinct oddity worth
noting: something about back-to-back TX submissions is causing the second
frame's lifetime field/timer to already read as expired by the time ucode
services it. Not investigated further tonight - lower priority than the
disconnect-causing issue above.

## Why this wasn't fixed tonight: the known next step is blocked on more RE work, not more live testing

notes/27-31 already did most of the legwork on "what's the missing periodic
maintenance that could explain flaky RX": `wlc_bmac_watchdog` (re-read fully
tonight, 19-line dispatcher) fires two calls through **unresolved indirect
(vtable) function pointers** - `(**(code**)(**(long**)(wlc+0x20)+0xd8))()`
and a second, conditional one through `wlc+0x38` - before calling the named,
decompiled `wlc_phy_watchdog`. notes/29/31 already concluded, correctly,
that these vtable targets are **not resolvable by static analysis alone**
(the call target is loaded from a runtime object, not a fixed address
Ghidra can already see) **and not observable via kprobes** (wl.ko is
entirely `notrace`, confirmed repeatedly this project - only its `osl_*`
shims are traceable). notes/30's trace evidence is a real, precisely
captured ~1.1-1.3ms register-touching sequence that runs every ~1.024s in
real wl operation and is the best candidate for what these vtable calls
actually do, but notes/31 already register-compared it against everything
this project has decompiled and confirmed **it doesn't match any named,
already-decompiled function** (not `hwaci_engine`, not
`desense_aci_engine`, and only partial/inconsistent overlap with the
already-ported TX-loft-cal setup code).

Separately, `wlc_phy_watchdog`'s own AC-PHY dispatch (read in full tonight,
not just grep-scanned) gates `wlc_phy_desense_aci_engine_acphy` and
`wlc_phy_hwaci_engine_acphy` behind a runtime flag byte
(`*(byte*)(wlc_hw+0x80)`, bit 0 and bits 1-2 respectively) whose value on
this real hardware/SPROM configuration **is not established** - these named
engines might not even be running in wl's real operation on this laptop, in
which case porting them would be pure completeness, not a fix for anything
observed. The `wlc_bmac_watchdog` vtable calls (unnamed, unresolved) are the
higher-confidence candidate, precisely because notes/30 caught them
actually running on real hardware.

**Conclusion: writing speculative PHY-register-poking code based on 2
sampled trace cycles of an unidentified function, and running it
periodically on a live, associated radio, would be irresponsible given this
project's own established risk standard** ("investigate the actual
mechanism before generalizing", from the BCMA_IOCTL precedent in notes/18).
The correct next step is more Ghidra work - specifically, identifying what
object type sits at `wlc_info+0x20` (and `+0x38`) and finding where its
vtable gets statically initialized in the binary, to resolve the indirect
call targets by data cross-reference rather than execution tracing. This is
read-only, zero-hardware-risk work, and is the honest, concrete next action
- not "port the named ACI engines and hope," which the evidence tonight
doesn't clearly support anyway.

## Practical takeaway for now

The driver **works** - association, WPA2, DHCP, and real data all function
- but a connection has a real chance (not yet quantified, but high enough
to have hit it in the majority of tonight's attempts) of self-disconnecting
within the first ~15 seconds due to this pre-existing RX flakiness, with an
automatic reconnect that sometimes succeeds and sometimes needs a manual
retry. This is a materially better state than "doesn't work at all," but
not yet "usable daily driver" - that needs either the vtable resolution
above, or a lucky connection.

## Updated priority list for a future session

1. Resolve `wlc_bmac_watchdog`'s two vtable calls via Ghidra
   data-cross-reference (not execution tracing) - find the object type at
   `wlc_info+0x20`/`+0x38` and its static vtable initializer.
2. Once resolved: decompile the actual target function(s), understand them
   fully (matching this project's standard for anything RF-touching)
   before writing any port.
3. Determine whether `wlc_hw+0x80`'s ACI-engine gate bits are set on this
   hardware (check SPROM/board flags data already extracted, or find the
   write site in decompiled code) - resolves whether the 4 named AC engines
   (already decompiled, notes/27-28) are worth porting at all.
4. The `supp=5` lifetime-expiry-on-second-back-to-back-probe oddity -
   lower priority, cosmetic so far.
5. Loft-comp question (notes/22) - still stashed, still open.

No hardware changes tonight from this investigation (read-only bpftrace and
dmesg checks only); the earlier session's fixes (`37455b6`, `1aa39fb`) are
unaffected. Chip left in safe idle monitor-mode state, USB backup link
verified, netwatch active.

## Addendum: checked whether the vtable resolution is a quick win - it isn't

Before deferring item 1 above to "a future session," spent a bounded,
read-only effort actually checking whether it's tractable right now.

`grep -rn "0xd8" decompiled-*` across every already-decompiled file found
**two more call sites at the exact same vtable slot** (offset `0xd8`):
`wlc_bmac_recv.c` (`param_1[(ulong)param_2 + 4]`) and `wlc_bmac_init.c`
(`param_1[4]` and, guarded by the identical `+0x84 == 4` condition seen in
`wlc_bmac_watchdog`, `param_1[7]`). `wlc_bmac_init.c` also loops over
`param_1+0x20` through `+0x48` (6 slots, 8 bytes apart) calling each
populated slot's *own* vtable offset `+8` (a different, generic per-slot
hook) - `param_1[4]` and `param_1[7]` are two specific slots inside that
same 6-element array. This confirms `wlc_info+0x20`/`+0x38` are elements of
an array of per-PHY-instance object pointers (most likely one entry per
active band/core), each with its own vtable, and slot `0xd8` (index 27) is
a **generic, driver-wide callback present in every PHY type's ops table** -
called from `recv`, `init`, and `watchdog` alike, not a bespoke
AC-PHY-only hook. That's useful structural confirmation, but still doesn't
say *which* function AC-PHY's specific ops table has at slot 27.

Checked for a shortcut past that: if the AC-PHY ops table is a single
`static const` struct literal somewhere in the binary, its address ought to
carry its own symbol, and the `.ko`'s relocations at that symbol+0xd8 would
name the target function *statically*, no execution needed. Searched the
full extracted symbol dump (`extracted/wl_kallsyms.txt`, 5156 entries,
confirmed to include local/static data symbols - e.g. per-core LUT arrays
like `acphy_est_pwr_lut_core1_rev0` show up by name - so this isn't a
"only exported symbols" limitation) for anything resembling a per-phytype
ops/function table (`*_ops`, `*_fns`, `*_vtbl`, `acphy_ops`, `phy_ops`,
etc.) - **found none for any PHY type**, only unrelated driver-level `ops`
structs (`wl_netdev_ops`, `wl_cfg80211_ops`, `wl_ethtool_ops`). The most
likely explanation is that this vtable gets populated **field-by-field at
runtime** (`pi->ops->slot27 = wlc_phy_watchdog_hook_acphy;`, scattered
across a per-phytype attach path with conditional compilation) rather than
via one static initializer - which means there's no single symbol+offset
to statically resolve, and the earlier "read the ELF relocations" idea
doesn't apply here.

This is a real (if negative) result: it rules out the one shortcut that
could have made this a 10-minute win, and confirms notes/29/31's original
assessment was correct rather than overly pessimistic. The actual next step
is unchanged from the priority list above (item 1) but is now known with
more confidence to require finding and decompiling whichever per-PHY-type
attach function does the field-by-field vtable population - a genuinely
open-ended decompilation task, not a quick lookup.

## Addendum 2: made real (if incomplete) progress on this same night

Decided the "genuinely open-ended decompilation task" above was still worth
a bounded, read-only attempt, since it's the single highest-value remaining
lead and there was no reason to believe it needed *hours*, only that it
needed *more than a symbol-table lookup*.

**Disassembled the entire wl.ko binary for the first time in this
project's history.** Every previous decompilation (all of `decompiled*/`)
used Ghidra's `-noanalysis` import, which - confirmed directly, not
assumed - never populates the cross-reference database *or* even the
instruction listing outside of functions individually decompiled by name:
`getReferencesTo()` returned 0 hits even for `wlc_phy_watchdog`, a function
we *know* is called directly (its call site is sitting right there in
`wlc_bmac_watchdog.c`), and `getInstructions(true)` returned 0 program-wide.
Fixed by calling `disassemble()` from every one of the 2958 known function
symbols (`dump_func_addrs.java`, `find_addr_taken_refs.java`) - fast,
zero semantic analysis, purely mechanical - which produced 359,169 real
`Instruction` objects, now permanently saved in `ghidra_proj/` (gitignored,
as always - this only touches local RE tooling state, nothing hardware- or
repo-facing). This is a genuinely useful, reusable improvement for *any*
future decompilation work on this binary, independent of tonight's specific
question.

With real instructions to scan, wrote `find_addr_taken_refs.java` (strict
address-equality match against every known function's entry point - the
same technique, just done via raw operand scanning instead of Ghidra's
empty reference database) and found a **first, concrete, verified example**
of exactly the pattern being hunted: inside `wlc_phy_attach_acphy` (already
decompiled tonight, just never read this far - line 737 of that file),
AC-PHY's `phy_info` object gets a whole block of direct-field callback
pointers populated at attach time:

```c
*(undefined **)(param_1 + 0x28)  = &UNK_001b0ecf;
*(undefined **)(param_1 + 0x30)  = &UNK_0018f4ba;
*(undefined **)(param_1 + 0x38)  = &UNK_001a7dc9;
*(undefined **)(param_1 + 0x40)  = &UNK_0019a1df;
*(undefined **)(param_1 + 0x100) = &UNK_001980bd;
*(undefined **)(param_1 + 0xc0)  = &UNK_00198b6b;
*(undefined **)(param_1 + 0xd0)  = &UNK_0019a268;
*(undefined **)(param_1 + 200)   = &UNK_00193ba7;
*(code **)(param_1 + 0xf8) = wlc_phy_btc_adjust_acphy;
```

This is real, new information: `phy_info` (AC-PHY's `pi`) stores several
callback hooks as **direct struct fields**, not through a separate
`vtable`-pointer indirection - the earlier mental model ("obj->vtable->slot")
was wrong for *this* structure. One slot is a named, already-known function
(`wlc_phy_btc_adjust_acphy`, Bluetooth-coexistence adjustment - not
previously connected to any offset in this project). The other seven are
unnamed code addresses that fall *inside* other already-named AC-PHY
functions (`wlc_phy_tx_tone_acphy`, `wlc_phy_ac_caps`,
`wlc_phy_stf_chain_temp_throttle_acphy`, `wlc_phy_table_write_acphy` x2,
`wlc_phy_txpower_sromlimit_get_acphy`, `wlc_phy_rxcore_setstate_acphy`,
`wlc_phy_crs_min_pwr_cal_acphy`) - almost certainly small `static` helper
functions that never got their own symbol in the extracted table, callable
individually via `decompile_at_addr.java` in a future session if any of
them turn out to matter.

**Crucially, ran the exact same strict-match scan for offset `0xd8`
against all 2958 known functions (not just AC-PHY ones) across the whole
359k-instruction disassembly, and it does NOT appear anywhere as a direct
immediate-address store** (the one clean hit found this way,
`wlc_lcnphy_set_tx_pwr_ctrl` at some *other* object's `+0xd8`, belongs to
LCN-PHY's attach path, a different phy type entirely - not ours). Combined
with `phy_info`'s own field list above (which has no `0xd8` entry for
AC-PHY), **this now conclusively rules out `phy_info` as the object
`wlc_bmac_watchdog`'s vtable calls operate on** - it's confirmed to be a
separate, still-unidentified structure, most likely `wlc_hw_info`'s or
`wlc_info`'s array of per-band/per-core sub-objects (the same 6-slot array,
offsets `+0x20` through `+0x48`, that `wlc_bmac_init.c`'s loop iterates and
that `wlc_bmac_watchdog`/`wlc_bmac_recv` also index into at slots 4 and 7).
Checked two plausible constructors for where that array gets *populated*
(`wlc_bmac_attach`, `wlc_attach` - both decompiled fresh tonight) and found
several *other*, unrelated `+0x20`-offset writes in each (this offset is
heavily reused across many distinct structs in this codebase, as
expected) but not the specific array-of-6 write - still open.

**Net effect**: didn't finish resolving the original question, but turned
"not resolvable, needs open-ended decompilation" into a precisely scoped
remaining task with working tools already built and one wrong hypothesis
(`phy_info`) definitively eliminated with hard evidence rather than
assumption. The reusable scripts (`dump_func_addrs.java`,
`find_addr_taken_refs.java`, `find_addr_taken_refs_at_offset.java`) are
committed for whichever future session picks this back up - point them at
`wlc_bmac_attach`/`wlc_attach`/other constructor candidates and search for
a write to offsets `0x20`/`0x28`/.../`0x48` on a register that also gets
compared against `+0x84 == 4` nearby, which is the concrete fingerprint of
the right structure. No hardware touched; only the local Ghidra project
database (gitignored) was modified by the disassembly pass.
