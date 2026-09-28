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
