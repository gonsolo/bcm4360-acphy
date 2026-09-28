# Status 2026-09-28 (cont'd): ac_txlifetime=800 confirmed live - first-ever clean IPv4 DHCP success; exposes a real (non-fatal) mac80211 WARN during the ACK-watchdog's restart path

Direct follow-up to notes/45. User pinned the router's 2.4 GHz channel to 6,
unblocking the connection-level test the previous round couldn't run.

## The connection-level A/B, finally run

Loaded with `ac_txlifetime=800` (wl's 0x0320), AP confirmed on channel 6
via the USB stick (55% signal) and via a fresh b43 scan. Single attempt:

```
nmcli connection up b43-test -> succeeded on the FIRST try
GENERAL.STATE: 100 (connected)
IP4.ADDRESS: 192.168.0.119/24        <- full DHCPv4 lease
IP6.ADDRESS: 4 addresses (SLAAC + privacy + link-local)
```

This is the **first time this project has gotten a clean IPv4 DHCP lease on
a first connection attempt**, on channel 6, with no retries. bpftrace
during the entire auth/assoc/DHCP sequence: 108 TX statuses, **0** with
`supp=5`, 93 acked (86%), only 1 frame exhausting the full retry limit.
Compare notes/40/44, where every prior attempt either timed out at auth or
got IPv6-only with IPv4 DHCP failing. This is strong, if single-sample,
confirmation of notes/45's diagnosis: the early-suppression bug was
starving exactly the kind of low-volume, latency-sensitive unicast
exchange (auth, assoc, DHCP request/ack) that connection setup depends on.

## But: post-association ACK ratio is still bad, and its recovery path has a real bug

~37 seconds after association, the *existing* ACK-ratio watchdog (notes/37,
unrelated to tonight's fix) saw 2/61 acked (3%) - still badly degraded.
~84 seconds in, 29/91 acked (32%) - still under its 50% threshold - so it
hit 3 consecutive bad windows and fired `b43_controller_restart_full()`.

**This is expected and correct**: notes/45's fix targets short, sparse,
below-the-radar unicast exchanges getting killed by a too-short lifetime
before they can complete. It says nothing about *sustained* post-association
throughput, which notes/34/38/39 already attribute to a different,
still-unfixed mechanism (the missing periodic RX-ring-refill sweep). Both
are real and apparently independent; tonight's fix doesn't touch the
second one, and the watchdog correctly caught it.

**What's new**: while mac80211 was replaying the `ieee80211_restart_hw()`
reconfiguration that follows, the kernel logged a real WARNING (not a
crash - `panic_on_oops` did not fire, the box stayed up, b43 stayed
loaded):

```
WARNING: CPU: 2 PID: 106279 at net/mac80211/util.c:1870 ieee80211_reconfig+0x582/0x17a0 [mac80211]
Workqueue: events_freezable ieee80211_restart_work [mac80211]
... second WARN immediately after, at ieee80211_del_chanctx+0x109/0x120 [mac80211]
```

Both are inside mac80211 itself (not b43-src), triggered from
`ieee80211_restart_work` - i.e. exactly the recovery path
`b43_controller_restart_full()` (notes/37) hands off to. The interface
ended up `disconnected`/`DOWN` afterward but the module stayed loaded and
responsive (another clean start/stop cycle followed a few seconds later) -
consistent with notes/40's already-documented "messy recovery, not a
crash" pattern, now with a concrete kernel-side WARN attached to it that
wasn't captured before.

## Assessment

- **notes/45's fix works as diagnosed.** Recommend flipping the default:
  either re-enable the POR table's 0x7C entry with 0x0320 (matching wl) or
  change `ac_txlifetime`'s default from -1 to 800, once this is confirmed
  over more than one trial.
- **Do not conflate this with the post-association ACK-ratio problem** -
  that is real, unfixed, and now has a slightly better-characterized
  failure signature: `ieee80211_reconfig`/`ieee80211_del_chanctx` WARNs
  during the watchdog's restart. Worth a closer look (what condition at
  `util.c:1870` / `ieee80211_del_chanctx+0x109` is being violated - likely
  a channel-context refcount or ordering assumption b43's restart sequence
  doesn't satisfy) but this is a mac80211-interaction bug in the *recovery*
  path, not the root throughput problem itself.

## Current state

Chip loaded (`ac_txlifetime=800` still set), interface down/disconnected
after the watchdog-triggered restart's messy recovery, module intact, no
crash, no panic. USB backup link confirmed working throughout (0% loss).
Also note: this session's `netwatch` safety monitor auto-unloaded b43
earlier in this round on a transient backup-link blip and required a
manual reload - working as designed, just recording it since it interrupted
the first attempt at this test.

## Next steps

1. Re-run the connection attempt a few more times at `ac_txlifetime=800`
   to build confidence beyond one sample before flipping any default.
2. Decide whether to re-enable the POR 0x7C entry directly (matching wl
   exactly, restoring parity with the captured trace) vs. keeping the
   explicit module param as the mechanism - either works; the POR route
   is more faithful to "do what wl does."
3. The new WARN signature at `ieee80211_reconfig+0x582`/
   `ieee80211_del_chanctx+0x109` is a concrete lead for the "messy
   recovery" half of notes/37/40's still-open work, whenever that's picked
   back up.
4. The underlying post-association ACK-ratio degradation (notes/34/38/39)
   remains the deeper, unfixed problem.
