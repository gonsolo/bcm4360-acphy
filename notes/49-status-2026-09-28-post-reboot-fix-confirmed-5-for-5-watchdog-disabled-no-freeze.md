# Status 2026-09-28 (cont'd): post-reboot, fix holds 5/5; 2+ minutes of degraded connection with the ACK-watchdog disabled produced no freeze

Direct follow-up to notes/48 (freeze + git recovery). User authorized: push, then
continue, present in case of another reboot.

## Pushed

The 6 commits from tonight (`fc8d91e` through `420d508`) are now on
`origin/master`.

## Post-reboot verification

`swap` hadn't been run yet this boot (only `postboot.sh` had), so the
first `load` attempt failed with unresolved `ssb`/`bcma`/`cordic` symbols -
expected/mundane, not a symptom of anything from the freeze. Ran `swap`,
then `load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 ac_ackwatchdog=0`
(watchdog disabled this round specifically to isolate whether its
`ieee80211_restart_hw()` path is implicated in the freeze, per notes/48).

`shm` debugfs read `007c 0320` from a completely standard load command,
confirming the POR-table fix (commit `0a9d18d`) is live and needs no
override param. Connection trial: first-try success, full IPv4 DHCP,
0/118 `supp=5`. **Running total: 5/5 clean first-try connections with the
fix across two boots.**

## 2+ minutes with the watchdog disabled, connection degraded, no freeze

Once connected, `ping -I wlp3s0b1` to the gateway showed 100% loss for
over 2 minutes straight (the pre-existing, separate post-association
ACK-ratio problem - notes/34/38/39 - confirmed still present and
untouched by tonight's fix: macstat showed txackfrm/txallfrm around 25%
over this window). With `ac_ackwatchdog=0`, no restart fires no matter how
bad the ratio gets. The system stayed completely stable throughout - no
crash, no freeze, no kernel log interruption, b43 kept logging normally,
backup link (`wlp0s20u1`) unaffected throughout.

This is **consistent with** notes/48's leading suspicion (the watchdog's
`ieee80211_restart_hw()`/`ieee80211_reconfig` path, not the degraded
connection state itself, being implicated in the hard freeze) but is not
proof - a longer/repeated test with the watchdog re-enabled, specifically
watching for the freeze to recur right as it hits 3/3 bad windows, would
be needed to actually confirm it. Not attempted tonight.

## Current state

Chip loaded and connected (degraded, as above), `ac_ackwatchdog=0`. USB
backup link confirmed working throughout. Git repo clean and pushed.

## Next steps

1. The core project goal (fixing the early-suppression bug) is done and
   confirmed 5/5. The POR-table fix is the permanent form; `ac_txlifetime`
   remains as an override/experimentation knob.
2. Post-association ACK-ratio degradation (notes/34/38/39) remains the
   next real problem, separate from tonight's fix.
3. Whether to re-enable `ac_ackwatchdog` and deliberately try to reproduce
   the freeze (with the user present) is an open question for a future
   session - genuinely risky, needs an explicit decision, not something to
   do by default.
