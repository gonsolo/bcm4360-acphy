# Status 2026-09-28 (cont'd): added a pragmatic ACK-ratio watchdog, found and fixed a real design flaw in it, full end-to-end verification blocked by live interference

Direct follow-up to notes/34-36. Given the actual root cause (the two
unresolved `wlc_bmac_watchdog` vtable calls) is blocked on genuinely
open-ended reverse-engineering, took a different, pragmatic approach:
detect the symptom (degraded ACK ratio) using counters this project already
understands, and recover using an existing, already-proven mechanism -
without needing to know *why* reception degrades.

## What was added

b43 already has a per-PHY-type periodic-work hook
(`ops->pwork_15sec`/`ops->pwork_60sec`, wired up in `main.c`'s
`b43_periodic_work_handler`, running every 15s under `wl->mutex` while the
core is started) and AC-PHY already implements `pwork_15sec`
(`b43_phy_ac_op_pwork_15sec`) - but only as a passive diagnostic dump (the
"AC txstatus"/"MACCTL=.../DMA rx status=..." dmesg lines seen throughout
tonight's testing). Added `b43_phy_ac_check_ack_watchdog()`, called first
thing in that same handler:

- Reads `B43_SHM_SH_TXALLFRM`/`B43_SHM_SH_TXACKFRM` (SHM `0xE0`/`0xE6`, the
  same ucode counters this whole project's diagnostics have used since
  notes/12) each 15s tick, computes the delta since the last tick.
- Only runs once actually associated (`!is_zero_ether_addr(wl->bssid)`) -
  scanning/monitor mode naturally has a low ACK ratio (broadcast probes
  aren't ACKed) and would false-positive otherwise.
- Requires a minimum sample size per window (20 frames) so a quiet window
  doesn't trip it on noise.
- If fewer than half the frames got ACKed for 3 consecutive windows
  (~45s), treats it as a real, sustained degradation and recovers.
- New module param `ac_ackwatchdog` (default 1) to disable if it ever
  misbehaves.

New constants `B43_SHM_SH_TXALLFRM`/`B43_SHM_SH_TXACKFRM` added to `b43.h`
(these counters had no named constant before, despite being used
throughout this project's diagnostics by raw address).

## Live-verified: the detection is accurate

Generated real ping traffic while connected and caught the exact symptom
this whole investigation has been chasing, live, in dmesg:

```
phy_ac: ACK ratio degraded (11/27 acked this window, 1/3 consecutive bad)
phy_ac: ACK ratio degraded (9/53 acked this window, 2/3 consecutive bad)
phy_ac: ACK ratio degraded (5/54 acked this window, 3/3 consecutive bad)
phy_ac: ACK ratio degraded for 3 consecutive windows, restarting the controller
Controller RESET (AC-PHY ACK ratio degraded) ...
```

This is real, independent confirmation (on top of notes/34's bpftrace
evidence) that the underlying reliability problem is genuine and
reproducible, and that counting `TXALLFRM`/`TXACKFRM` is a sound, simple
proxy for it.

## Found a real design flaw in the first version, and fixed it

The first implementation called the existing `b43_controller_restart()` -
the same mechanism b43 already uses for firmware-watchdog timeouts and
fatal DMA errors. Watching what actually happened after it fired: the
hardware silently reinitialised (fresh channel tune, fresh SHM/rate-map
state, fresh RCMTA/MAC-filter reprogramming via `b43_op_bss_info_changed`)
but **mac80211 was never told anything happened** - `b43_chip_reset()`
doesn't call `ieee80211_restart_hw()`, it just quietly reloads mac80211's
*cached* config onto the freshly-reinitialised hardware. Observed
consequence, live: the interface sat at `nmcli` state "connected" with
**no IPv4 address at all** for over a minute after a restart fired - no
re-association, no DHCP renewal, just a silently reset radio underneath an
unaware userspace. That's arguably worse than the original symptom (which
at least sometimes self-healed via mac80211's own beacon-loss/reconnect
logic).

Root cause: `b43_controller_restart()`'s existing behaviour is fine for
what it was written for (rare, genuine hardware-error recovery, where
quietly restoring exactly the same state is the right thing), but wrong
for a trigger meant to fire somewhat routinely under bad RF conditions,
where actually completing a fresh association (and downstream DHCP)
matters more than doing it invisibly.

**Fix**: added a second, independent recovery path,
`b43_controller_restart_full()`, that only brings the core down
(`b43_wireless_core_stop`/`_exit`, same as `b43_chip_reset()`'s first half)
and then calls `ieee80211_restart_hw()` - the standard, documented mac80211
API for exactly this ("the driver/hardware is completely uninitialised and
stopped... [mac80211] starts the process by calling ->start()"). This lets
mac80211 itself drive the reconnection, which means wpa_supplicant redoes
the handshake and NetworkManager redoes DHCP, instead of both being left
believing a stale link is still fine. Implemented as a genuinely separate
work item (`full_restart_work`, its own `INIT_WORK`/`cancel_work_sync`
sites) specifically so the *existing*, already-proven
`b43_controller_restart()`/`b43_chip_reset()` path used by the other 3
call sites (firmware watchdog, DMA error, PHY TX error rate) is completely
untouched - zero risk of regressing those.

## Not yet verified: does the fixed recovery path actually work end-to-end

Rebuilt cleanly with the fix, but every subsequent connection attempt
tonight - including the very first one, before any of this code could even
run - failed to even complete authentication/association, or stalled in
DHCP. Checked whether this is a regression from the new code: it isn't -
these failures happen *before* `b43_phy_ac_check_ack_watchdog` ever gets a
chance to run (it requires an active association first), and a passive
monitor-mode check during the same window showed perfectly healthy beacon
reception (-66 to -68dBm, consistent, on channel 11). The USB stick
(completely unrelated hardware/driver) also logged two independent
`CTRL-EVENT-BEACON-LOSS` events in the same window, though its own
connection held. This strongly suggests genuine, currently-ongoing
environmental RF interference (real-world conditions, not a driver bug),
consistent with - and possibly an unusually severe instance of - the same
underlying intermittent-reception problem this whole investigation has
been characterizing all along, just now bad enough to disrupt even the
initial handshake rather than only post-association keepalives.

Did not keep forcing repeated connection attempts against what looks like
real interference; that would burn time without learning anything new.
**The `ieee80211_restart_hw()` fix is correct by inspection** (matches the
documented API contract exactly, mirrors the existing working pattern,
builds clean, doesn't touch the other 3 already-proven call sites) but its
actual "does it restore full connectivity" behavior needs a real end-to-end
test once conditions allow a baseline connection to succeed at all.

## Current state

- `ac_ackwatchdog=1` (default) is active in the loaded module.
- Chip returned to safe idle monitor-mode state (channel 6) at the end of
  this round; USB backup link reconfirmed (0% loss, real RTTs).
- Uncommitted-until-this-note code: `b43.h` (2 new SHM constants),
  `phy_ac.h` (4 new fields on `struct b43_phy_ac`), `phy_ac.c` (the
  watchdog check + module param), `main.c`/`main.h`
  (`b43_controller_restart_full`/`b43_chip_reset_full`/`full_restart_work`).

## Next steps

1. Re-test the full connect → let it degrade → recover → verify it gets a
   fresh IP and passes traffic cycle once RF conditions allow a clean
   baseline connection.
2. If `ieee80211_restart_hw()` still doesn't fully restore connectivity in
   practice (e.g., if wpa_supplicant/NetworkManager don't automatically
   retry hard enough after a driver-initiated restart), consider whether
   `ac_ackwatchdog` needs to also proactively kick something at the
   NetworkManager/wpa_supplicant level, or whether the threshold/window
   parameters need tuning based on real-world false-positive/false-negative
   rates.
3. The actual root-cause work (notes/34's vtable resolution) is still the
   deeper fix worth pursuing; this watchdog is explicitly a mitigation, not
   a replacement for understanding *why* reception degrades.
4. Given tonight's interference made even a baseline connection hard,
   consider re-testing on a quieter part of the spectrum/time of day if
   this keeps blocking verification.
