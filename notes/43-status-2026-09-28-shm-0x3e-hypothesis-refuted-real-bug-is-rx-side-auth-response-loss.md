# Status 2026-09-28 (cont'd): SHM 0x3E "frame lifetime" hypothesis mostly refuted; the real association-blocking bug is RX-side (auth response frames never arrive), not TX suppression

Direct follow-up to notes/41/42. Picked back up the ucode trace that found the
exact instruction (0x01CE, ORX writing `supp_reason=5`/LIFE) and the
surrounding TSF-based logic computing `SHM[0x867] = SHM[0x3E] + r23`, which
led to the hypothesis that **SHM word 0x3E is a configurable frame-lifetime
duration left at a bad (zero) value by this port**.

## First: a stuck debugfs/interface state from the prior session

Found the chip in the exact "Operation not supported" / debugfs "No such
device" state notes/40 flagged as recurring and unresolved. Root cause is
mundane: `/sys/kernel/debug/b43ac/*` only backs a live core (interface up);
it was simply down at the time. A clean `b43_live.sh unload` + reload fixed
it immediately, same as every previous time. Separately, `wlp3s0b1` had also
been left `unmanaged` by NetworkManager (unrelated flakiness, fixed with
`nmcli device set wlp3s0b1 managed yes`). Neither was a kernel-level wedge.
**This specific "Operation not supported"/could-not-ready symptom from
notes/40 is now understood and not mysterious**: it happens whenever the
interface is addressed while down/unmanaged, not during a real hang.

## Testing the SHM 0x3E hypothesis

Read it live: `003e 0000` - confirmed zero, and confirmed via `grep` that
neither `b43_ac_por_shm[]` nor `b43_ac_replay_shm[]` (the wl first-boot
snapshot tables) ever write offset 0x3e - it's untouched by this port,
sitting at whatever the ucode's own power-on default is.

However, mainline b43's own `b43.h` already documents this exact address:

```
#define B43_SHM_SH_NRRXTRANS  0x003E  /* # of soft RX transmitter addresses (max 8) */
```

This is a small integer count field (max 8), not a duration - a different,
plausible meaning from the "frame lifetime" read off the fresh ucode trace.
Given this project's repeated experience of SHM addresses being repurposed
across firmware/hardware generations, neither interpretation was trusted
outright; an empirical, live test was run instead.

Traced `b43_op_tx`/`b43_handle_txstatus` (bpftrace, `txtype_trace.bt`)
through a real connection attempt. Result: **every `supp=5`/`fcnt=0`
event correlates with `fc=0040` (Probe Request, broadcast) or other
non-ACK-expecting frames sent during the mac80211 scan cycle** - i.e.
`supp=5`/"expired without retrying" is the *correct*, expected outcome for
a broadcast frame with no ACK to wait for, not a bug. This is a materially
different, more mundane explanation than notes/41's framing ("many unicast
data frames suppressed early") for *this specific* batch of `supp=5`
events - **the broadcast-frame `supp=5` pattern here is not evidence of a
bug**. This doesn't retroactively disprove notes/41's original finding
(which was specifically about *unicast*, ToDS=1, encrypted QoS-data frames
during an active degraded connection) - it narrows the SHM-0x3E theory's
support to "unconfirmed, and now looks less likely to be the single
explanation," rather than refuting notes/41 outright.

**Net effect on the SHM 0x3E hypothesis: weakened, not confirmed.** No code
change was made - setting an untested value into a live register based on
a now-doubtful theory was correctly avoided (matching this project's
standing practice of not guess-and-check patching an unconfirmed
mechanism).

## The actual, clearly-reproduced finding tonight: auth frames are ACKed but the response never arrives

While testing, every association attempt failed at the very first step -
`wlp3s0b1: authentication with 8c:6a:8d:9e:2a:88 timed out` - well before
ever reaching the data-frame/ACK-ratio-watchdog territory this project has
mostly been focused on. Traced it directly:

```
TXHDR fc=00b0 len=30
TXSTATUS cookie=4034 fcnt=2 supp=0 acked=1
```

**The outgoing Authentication (open-system, frame 1 of 2) frame is
transmitted, retried once, and genuinely ACKed by the AP** (`supp=0`,
`acked=1`) - our TX path is fine for this frame. But mac80211 still times
out waiting for the AP's Authentication response (frame 2 of 2) to arrive.
This happened identically across two full attempts in the same test
(each: 3x send-auth retries at the mac80211 level, all exhausted, followed
by a full 13-channel scan, then one more 3x-retry auth round, then giving
up).

This means **the bug blocking association tonight is on the RX side**:
either the AP's auth-response frame never reaches this driver at all, or
it arrives and is dropped/mishandled somewhere in the RX path before
mac80211 sees it. This is consistent with, and a more basic/upstream
manifestation of, the already-documented RX-reliability problem
(notes/34's original disconnect diagnosis, notes/38/39's RX-ring-refill
gap) - not a new, separate mechanism, but a reminder that the RX-side
problem is severe enough to block even the very first frame exchange of
a connection attempt, not just steady-state throughput.

## Assessment / priority update

- The TSF/`supp_reason`/SHM-0x3E ucode-tracing thread from notes/41 is now
  lower-confidence as *the* explanation and should not be pursued by
  guessing a value into 0x3E without a cleaner, unicast-only repro (ideally
  re-run the same bpftrace capture during a live degraded *data* connection,
  filtering specifically for `fc` values with `ToDS=1`/unicast RA, to get a
  clean, uncontaminated-by-broadcast-scan-traffic sample - not done
  tonight).
- The RX-side auth-response-loss finding is new, concrete, and arguably
  more actionable: it reproduces on demand (every connection attempt
  tonight hit it), is easy to re-trigger, and sits upstream of everything
  else (DHCP asymmetry, ACK-ratio degradation, disconnects) - all of which
  presuppose getting past association in the first place. Recommend making
  **RX-path reliability during the auth/assoc handshake specifically** the
  next concrete investigation target, e.g. tracing whether *any* frame from
  the AP's BSSID is received between our auth request and the timeout
  (a clean way to tell "response never arrived" from "response arrived but
  was dropped/misrouted").

## Current state

No code changes this round. Chip loaded, idle (disconnected, mid
passive-scan state), no crash or hang. USB backup link (`wlp0s20u1`,
Vodafone-2A84) confirmed working throughout (0% loss, real RTTs).

## Next steps

1. Trace RX during a fresh auth attempt (`b43_rx`/equivalent kprobe) to
   determine whether the AP's auth-response frame is received by the
   hardware/driver at all, versus never arriving over the air. This is the
   single most direct next step to resolve tonight's actual blocking issue.
2. Re-run the notes/41 `supp=5` unicast-frame trace cleanly (filtering out
   broadcast/scan traffic) before drawing further conclusions about
   SHM 0x3E or any other TX-side timeout register.
3. Everything else (RX-ring refill mitigation, ACK-ratio watchdog,
   `ieee80211_restart_hw` fix) is unaffected and remains as previously
   documented (notes/38-42).
