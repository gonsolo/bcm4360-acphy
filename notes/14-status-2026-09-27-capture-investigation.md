# Status 2026-09-27 (continued again), packet-capture investigation - mostly null results, one real correction

Per the user's "pick a genuinely different angle" redirect, investigated
the "our own probe requests exhaust retries with zero macstat activity"
symptom flagged in notes/13's first sample, using `probeack.sh`'s pcap
(kept instead of deleted, via a modified copy of the script).

## The retry-exhaustion symptom didn't reproduce

Ran the identical test (`CH=1`, home AP, `RATE=12`, `N=30`) four more times
on a fresh module load. All four came back with the normal ~65-75% retry
rate and macstat behaving as expected (`txackfrm`/`txphyerr` incrementing
together). The original anomaly (`txallfrm+210=30x7`, zero ack/error
activity, missing `probe resp` line) did not reproduce even once. Most
likely explanation: a one-off timing/environmental hiccup in that specific
run (possibly the test harness's own scan/offchannel setup not having
settled yet), not a systematic, separate bug. Downgrading this from "worth
investigating" to "probably noise" - not chasing it further unless it
recurs.

## RTS/CTS: absent, as expected - one real negative data point

Checked the captures for RTS/CTS frames directly (they'd be a strong,
independent confirmation or refutation of the tentative "0x2D might be RTS"
guess from notes/13's backward-trace, which was already flagged as
low-confidence due to an inconsistent bit-decode). **Zero RTS/CTS frames
appear anywhere in three full capture runs** (only Beacon, Probe Request,
Probe Response, Acknowledgment). This is genuine evidence against RTS being
involved in this test scenario at all (consistent with RTS threshold being
disabled/high by default, as expected) - whatever `0x2D` represents in the
ucode dispatch, it's very unlikely to be RTS specifically, at least not in
this test's traffic mix.

## A finding that looked exciting but is actually a null result - correcting myself here

Checked every captured "Acknowledgment" frame's receiver address across a
capture: **all 29 have `RA = our own MAC`** - meaning every single Ack we
captured is the *AP* acknowledging *our* outgoing probe requests, not our
own firmware acknowledging the AP's probe responses. Initially read this as
"we have zero captured evidence our own ACK transmissions ever radiate,
even to our own co-located monitor" - a seemingly strong, direct symptom.

**This is wrong, and I want to be explicit about correcting it rather than
letting it stand:** `b43mon` sits on the *same* radio/antenna as the
managed-mode interface doing the actual transmitting (documented in
`probeack.sh`'s own header comment). A single radio is half-duplex - it
physically cannot receive while it is transmitting on the same antenna.
**We would see exactly this same "zero self-captured ACKs" pattern in a
perfectly healthy, bug-free driver too**, purely because of this
architectural limitation, not because of anything related to the PHY-TX-
error investigation. This tells us nothing. Flagging this explicitly so a
future session (or me, later) doesn't rediscover this pattern and get
excited by it again.

## Why this wasn't tested further with an independent second radio

Getting a *real*, independent over-the-air answer to "does our firmware's
ACK actually radiate, successfully or not" would need a receiver on a
*different* radio - the USB stick (`wlp0s20u1`) is the obvious candidate,
put into monitor mode instead of managed mode for one test. **Did not do
this**: the user is away for this whole session, and the USB stick is
currently the *only* network path this Claude session itself has (the
internal chip is deliberately idle on `bcma-pci-bridge`, not connected).
Switching the USB stick to monitor mode would cut this session's own
connection to the API with no one available to help recover if anything
went wrong - exactly the scenario the project's WiFi-testing safety notes
warn about. This is a legitimate, valuable next experiment, but it should
be run only with the user present (or from a setup with a third, unused
network path), not attempted solo while the primary operator is
unreachable.

## Where this leaves things

Two threads mostly closed out (retry-exhaustion: probably noise; ACK
self-capture: architecturally uninformative by construction). One small
positive: RTS/CTS absence is real evidence against that specific guess from
notes/13. The genuinely promising unexplored option - an independent
capture via the USB stick - is deliberately parked pending the user's
presence, not abandoned for lack of a lead.
