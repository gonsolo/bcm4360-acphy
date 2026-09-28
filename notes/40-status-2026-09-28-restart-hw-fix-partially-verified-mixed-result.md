# Status 2026-09-28 (cont'd): first real end-to-end test of the ieee80211_restart_hw fix - it works for its core purpose, but the full recovery cycle is messier than hoped

Direct follow-up to notes/37 (added `b43_controller_restart_full()`, never
verified live) and notes/39 (RX-ring refill fix, verified safe). A
connection attempt finally succeeded (IPv6-only - see below) after the
earlier suspected router-side rate-limit/RF trouble, giving the first real
chance to watch the ACK-ratio watchdog actually trigger a recovery.

## The connection that got through: IPv6 works, IPv4 DHCP still doesn't

`nmcli con up b43-test` succeeded and stayed `state=100 (connected)` for
over a minute, but `ip -4 -br addr show` showed **no IPv4 address at all**
- full IPv6 (SLAAC + privacy address + gateway + DNS) came up fine, IPv4
DHCP did not. This is a better-evidenced explanation for tonight's earlier
"persistent DHCP failure" pattern (notes/39) than a router MAC rate-limit:
**IPv6 Router Advertisements are broadcast repeatedly and periodically by
the router**, giving many chances to catch one despite occasional RX gaps,
while **DHCPv4's OFFER is a narrow, few-shot direct reply** to our
DISCOVER (2-4 retransmissions, each only sent because *we* resent
DISCOVER, over a fairly short timeout window). Both are 802.11
broadcast/multicast frames with no MAC-layer retry (notes/37's addendum),
but IPv6's design gives dramatically more attempts per unit time. This
doesn't rule out the rate-limit theory but is a cleaner, more mechanistic
fit and doesn't require assuming anything about the router's internal
policy.

## The ACK-ratio watchdog fired for real, live

Generated sustained IPv6 ping traffic to the gateway to keep the ACK ratio
under real load. Watched it degrade exactly as designed:

```
ACK ratio degraded (6/24 acked, 1/3 consecutive bad)
ACK ratio degraded (8/24 acked, 1/3 consecutive bad)
ACK ratio degraded (9/51 acked, 2/3 consecutive bad)
ACK ratio degraded (2/30 acked, 3/3 consecutive bad)
ACK ratio degraded for 3 consecutive windows, restarting the controller
Controller full RESET (AC-PHY ACK ratio degraded) ...
Controller full restart - handing off to mac80211
wlp3s0b1: deauthenticating from 8c:6a:8d:9e:2a:88 by local choice (Reason: 3=DEAUTH_LEAVING)
```

**This confirms the core fix from notes/37 works as intended**: unlike the
original `b43_controller_restart()` bug (which left the interface silently
"connected" with no IP forever), `ieee80211_restart_hw()` correctly caused
mac80211 to recognize the reset and issue a real deauth - the fundamental
problem that motivated writing `b43_controller_restart_full()` is fixed.
`nmcli` did eventually transition from its stale "connected" state to a
correct "disconnected" (rather than staying stuck), which is the key
behavioral difference from the original bug.

## But the actual recovery cycle was messy

Between the deauth and a stable end state:

- A ~45-second gap with no visible driver/interface activity at all
  (possibly NetworkManager's own reconnect backoff timing, not
  investigated further).
- Then two rapid, back-to-back full re-init cycles, each starting the
  wireless interface and stopping it again within ~10ms - looks like
  repeated failed bring-up attempts in a tight loop, not a clean single
  reconnection.
- A subsequent manual `nmcli con up` attempt failed outright with "The
  device could not be readied for configuration", and a plain
  `ip link set wlp3s0b1 up` returned "RTNETLINK answers: Operation not
  supported" - `rfkill list` showed nothing blocked (soft or hard) for
  this phy, so it wasn't a simple rfkill state mismatch; the specific
  cause wasn't identified before deciding to stop investigating live and
  do a full clean reload instead.
- A full `b43_live.sh unload` completed **cleanly** (no crash, no hang, no
  kernel oops/warning) - confirming this was not a kernel-level wedge or
  corruption, whatever it was. A fresh reload afterward showed completely
  normal operation (monitor mode, passive RX, USB backup link unaffected).

## Assessment

The fix's **specific, narrow goal** - making mac80211 aware that a restart
happened, instead of leaving it and userspace believing a silently-reset
link is still fine - is confirmed working. That was the actual bug found
and fixed in notes/37, and it's fixed.

The **broader goal** - a fully clean, hands-off recovery back to a working
connection - is not yet demonstrated. Given tonight's independently
well-documented, ongoing RF/reconnection difficulty (notes/39's
DHCP-failure investigation, the USB stick's own intermittent beacon-loss
events), it's plausible the messy recovery observed here is dominated by
the same underlying conditions that have made *every* connection attempt
tonight difficult, rather than a new defect specific to
`b43_controller_restart_full()`/`ieee80211_restart_hw()` itself - but this
is not proven, and the "Operation not supported" / repeated rapid
start-stop cycling deserves a closer look in a future session under
better conditions, ideally with more targeted tracing on exactly what
NetworkManager and mac80211 are doing during that window.

## Practical takeaway

Given the mixed result, this is a real, meaningful step forward (the
original silent-zombie bug is gone) but not yet a fully proven, clean
fix for "the driver recovers gracefully on its own." Recommend keeping
`ac_ackwatchdog=1` enabled (it's still strictly better than having no
detection/recovery attempt at all, and the old, definitely-worse silent
hang no longer happens) while treating full automatic recovery as
still-open for now.

## Current state

No code changes this round (this was pure live testing of already-committed
code from `def37a2`/`9d3f821`). Chip fully unloaded and freshly reloaded,
returned to safe idle monitor-mode state; USB backup link reconfirmed
(0% loss, real RTTs); netwatch active.

## Next steps

1. Re-test the full restart->recovery cycle under calmer RF conditions,
   with closer tracing of the ~45s gap and the rapid start/stop cycling -
   is this NetworkManager's own backoff/retry logic working as designed
   (just slow), or a real bug in how b43/mac80211 interact during
   `ieee80211_restart_hw()`'s reconfiguration?
2. Investigate the specific "Operation not supported" / rapid start-stop
   condition if it recurs - capture `iw`/`rfkill`/dmesg state at the exact
   moment it happens, not after the fact.
3. The IPv6-succeeds/IPv4-fails asymmetry is a good, concrete diagnostic
   signal for the underlying RX-reliability problem generally - worth
   using explicitly in future testing (e.g., "does IPv6 come up but not
   IPv4" as a quick way to confirm the broadcast/multicast retry-count
   theory without needing full connectivity).
4. Everything else from notes/38/39 (the RX-ring refill fix itself, and
   the still-unidentified `+0xa0`/`di[3]`/`+0x84==4` path) is unaffected
   and remains as previously documented.
