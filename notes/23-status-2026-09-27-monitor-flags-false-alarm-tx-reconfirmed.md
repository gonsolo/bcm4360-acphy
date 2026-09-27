# Status 2026-09-27 (late evening): the 35dB signal gap was a test artifact; TX-not-reaching-the-air reconfirmed with cleaner evidence

Direct follow-up to notes/22, same evening, after reverting the loft-comp
fix (commit b4885d6). Picked back up on the unexplained ~35dB RX signal
gap between `b43` and the USB stick, since that was the most concrete
loose end left over.

## Root cause of the "35dB gap": a stale monitor-mode flags bug in testing, not the driver

Bisected step by step: loaded b43 cleanly (`ac_replay=1 dma32=1 ac_por=0
nohwcrypt=1`, the known-good channel-6 tuning from notes/22), confirmed a
healthy baseline (-56 to -60 dBm for the AP's beacons via a plain
monitor-mode listen on `wlp3s0b1`), then reproduced the degradation by
switching the interface to `type managed` and back to `type monitor` -
every command succeeded, `iw info` correctly reported `type monitor,
channel 6 (2437 MHz)`, but the interface went completely silent: 0
packets captured in repeated 5-8s windows, not even neighbors' beacons.

The fix: re-applying the monitor flags (`iw dev $IF set monitor otherbss
control fcsfail`) immediately restored full, healthy reception (-55 to
-58 dBm). **A `type managed` -> `type monitor` round-trip silently drops
the `otherbss` flag** (and presumably `control`/`fcsfail`), and without
`otherbss` a monitor interface cannot properly see frames from a BSS it
isn't part of - which is every frame in an eavesdropping test where the
station never associates. This is a `cfg80211`/`iw` interface-flag
behavior, not a PHY/RF issue.

This fully explains notes/22's "~35 dB gap": `probeack.sh`'s own sequence
switches the main interface through `managed` before creating/using a
separate `b43mon` monitor vif, and if `b43mon` already existed from an
earlier run (as it did for most of tonight's testing - the script only
creates it when absent, never re-applies flags to an existing one), any
earlier flag loss would silently persist across every subsequent
`probeack.sh` invocation. **Not a hardware or calibration defect.**
Verified independently by testing both with and without the loft-comp fix
active - the flag bug reproduces identically either way, which is also
why notes/22's attribution of the gap to the loft-comp table was itself
wrong (see notes/22's late addendum and the b4885d6 revert).

## TX still doesn't reach the air - now confirmed by two independent, cleaner methods

With reception confirmed genuinely strong and the channel genuinely
correct, retested whether the AP responds to anything we transmit.

1. **Independent, third-party verification.** Added a second monitor vif
   on the USB stick's own phy (concurrent with its own managed
   connection to the same AP - the technique from notes/15) and captured
   there while injecting a directed probe request from `b43mon` on the
   internal chip. The USB stick's capture - a completely separate radio,
   unaffected by anything b43-side - **never saw our injected probe at
   all**, not even as a corrupted or bad-FCS frame. This is stronger
   evidence than any ucode counter: an independent receiver simply never
   detected our transmission.

2. **A real active scan finds zero networks.** `iw dev wlp3s0b1 scan`
   returned 0 BSS, and `nmcli dev wifi list` was empty - despite passive
   monitor-mode capture moments earlier clearly receiving the same AP's
   beacons at strong signal (-56 dBm) and real background traffic
   between the AP and other stations (including the USB stick's own
   normal traffic, seen as Block-Ack exchanges). dmesg confirms the scan
   does attempt to transmit (a `switch_channel`/`AC txstatus` pair per
   channel visited, matching the probe-request-per-channel pattern of an
   active scan) - so the driver isn't failing to attempt TX, but nothing
   comes back.

3. **A real `nmcli`/`wpa_supplicant` association attempt failed**, but
   inconclusively - the first attempt was contaminated by an unrelated
   `wpa_supplicant` restart apparently triggered by activating a second
   wifi interface (`NetworkManager: Couldn't initialize supplicant
   interface: Name owner lost`, coinciding with the USB stick's own
   profile-sharing disconnect/reconnect cycle), and the retry failed
   immediately with "The Wi-Fi network could not be found" - consistent
   with finding (2) above (no scan results to connect to), not new
   information on its own.

## What this means

Nothing here overturns the project's long-standing core finding
(`notes/00`, `notes/15`, `notes/17`) that outgoing transmissions from
this chip don't reliably reach the AP or elicit a response, while
reception is fine. Tonight's contribution is methodological, not a new
root cause: two real false leads from earlier tonight (the channel-1
mistuning "explains everything" theory, and the 35 dB signal-gap
"explains everything" theory) are now ruled out, and the actual remaining
symptom is reconfirmed with cleaner, more direct, more independent
evidence than before (a genuinely correct channel, genuinely strong
signal, and a truly separate receiving radio all agreeing: our TX doesn't
land).

## Open questions for a future session

1. **Reconcile with "host-queued TX works, auth/assoc succeed (AID
   assigned)"** (`notes/00`/session summaries) - that finding predates
   tonight and may have used a different test path (e.g. a fixed
   BSSID/channel bypassing scan) rather than NetworkManager's normal
   scan-then-connect flow. Worth deliberately re ­running that original
   successful-association test, under tonight's corrected channel-6
   tuning, to see if it still succeeds - would cleanly separate "scan/
   probe-response path is broken" from "all outgoing TX is broken."
2. **Decode the `AC txstatus` debug line's fields** (`b43-phy2 debug: AC
   txstatus 40fc0103 00000000 00000001 00000000` etc.) - printed for
   every scan-probe TX attempt tonight, with a suspiciously constant
   trailing pattern (`00000000 00000001 00000000`) across many attempts
   on different channels. If this encodes a real hardware ACK/completion
   status, it may be a cheap way to distinguish "frame was never really
   transmitted" from "frame transmitted, no ACK returned" without new
   register-level tracing.
3. **Re-run the historical `probeack.sh` ACK/txphyerr measurement with
   the monitor-flags bug fixed** (delete `b43mon` and let the script
   recreate it fresh every run, or manually re-apply
   `otherbss control fcsfail` if reusing an existing vif) - the
   historical ~90-95% failure baseline (notes/07-11) may itself be
   affected by this exact flag issue if `b43mon` was ever reused stale
   across sessions; worth a clean re-baseline before trusting old
   percentages precisely, even though the qualitative conclusion (TX
   fails) is not in doubt.
4. The loft-comp calibration question remains fully open (see notes/22's
   revert) - retest only after (1)-(3) give a clean, unconfounded setup.

## Session close

No crashes, no dmesg BUG/Oops/panic/WARNING lines. USB backup link 0%
packet loss throughout and at close. `b43` unloaded cleanly; chip left on
`bcma-pci-bridge`. `wl` was already restored earlier this evening (user
rebooted mid-session) and is bound and working normally on `wlp3s0b1` /
`wlp0s20u1` as usual - no further reboot needed for this round.
