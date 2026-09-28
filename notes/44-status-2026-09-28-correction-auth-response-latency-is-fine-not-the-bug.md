# Status 2026-09-28 (cont'd): correction - auth-response RX latency is fine; notes/43's "RX-side loss" framing was a trace-correlation error

Direct follow-up and partial correction to notes/43.

## What notes/43 got wrong

notes/43 concluded the auth response was arriving ~1.7s late by comparing
a `dmesg` timestamp for "send auth (try 1/3)" from one test run against a
`bpftrace`-captured RX timestamp from a **different, later** test run. That
was an invalid cross-run correlation, not a real measurement - the two
numbers were never from the same auth attempt. Flagging this explicitly so
it isn't treated as settled fact by a future session.

## The corrected, same-run measurement

Wrote a single bpftrace script capturing both `b43_op_tx` (TX_AUTH_REQ,
matching `fc=0x00b0`) and `b43_rx` (RX_AUTH_RESP) in one run, so every
request/response pair is directly correlated by construction. Result, four
clean pairs from one connection attempt:

```
TX_AUTH_REQ -> RX_AUTH_RESP: 7.25ms, 9.28ms, 9.77ms, 9.66ms
```

This is a completely normal, healthy Wi-Fi round-trip time. **The RX path
correctly and promptly delivers the AP's auth response** - notes/43's
"RX-side frame-loss/delay blocking association" framing does not hold up
as a general, deterministic explanation.

Consistent with this: the same connection attempt that produced this clean
trace actually progressed past authentication and association this time,
reaching `state=70 (connecting, getting IP configuration)` with a valid
IPv6 link-local address - further supporting that auth/assoc *can* and did
succeed cleanly here. It later dropped back to `disconnected` after some
time, consistent with the already-documented (notes/40) IPv4 DHCP
difficulty / general intermittent RX-reliability pattern, not a new,
separate failure.

## Revised understanding

There is no evidence tonight of a deterministic "auth response never
arrives" bug. The real, still-standing picture is what earlier notes
already established: connection reliability (association survival, DHCP
completion, sustained ACK ratio) is **intermittent** - some attempts
proceed cleanly for a while, others fail early - which fits a general
RX-reliability/timing-sensitivity problem (notes/34's original disconnect
diagnosis, notes/38/39's RX-ring-refill gap) rather than a single
consistently-reproducible defect in any one specific frame exchange. The
"early-suppression" (`supp=5`/low `fcnt`) finding from notes/41, specific
to *unicast* frames during an active degraded connection, remains
unexplained and is a separate, still-open thread from tonight's auth-latency
detour.

## SHM 0x3E status

Still not modified. The empirical unicast-only re-test recommended in
notes/43 (cleanly isolating `supp=5` events on genuine unicast/ToDS=1
frames during a live degraded connection, without broadcast-scan-traffic
contamination) has not been done yet and remains the right next step
before touching that register.

## Current state

No code changes this round. Chip loaded, idle/disconnected, no crash.
USB backup link confirmed working throughout.

## Next steps

1. Do the clean unicast-only `supp=5` re-trace from notes/43, ideally by
   getting a data connection up (even briefly) and generating sustained
   ping traffic, filtering the bpftrace capture for `ToDS=1` unicast
   frames only.
2. Stop treating any single connection attempt's outcome as representative
   - tonight's own attempts ranged from clean auth+assoc+DHCP-start to
   outright auth timeout, within the same test session, same AP, same
   channel. Any future register-poke experiment (SHM 0x3E or otherwise)
   needs multiple repeated trials to be credible, not one sample.
