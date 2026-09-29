# CRS|TXF reconfirmed with real timing; a bit-level nuance not yet resolved

Direct follow-up to notes/70, same session. Returned to notes/58's
original finding (phydebug `CRS|TXF` during failed auth attempts) with
the tools built tonight (`hw_timing.c`) and the causal-direction
discipline established in notes/68/70, since it's the most direct,
symptom-adjacent lead from the whole session and was never re-verified
with real timing after the NAP/hostflags detour.

Also fixed a real gap in `hw_timing.c` while adding these probes:
`mmio16` is a 16-bit read; `MACCTL`/`IRQ_REASON` are 32-bit registers,
so added the high-half offsets (`0x122`, `0x12a`) rather than silently
reading only the bottom half as a previous version implicitly would
have.

## Reconfirmed: real, tight timing correlation with failures

phydebug `0x0005` (CRS|TXF) during a real failed attempt: 98% of all
hits (21900/22368) land in the exact two 1-second buckets the real auth
send/timeout was happening in, against 468 stray hits before it. Not
spread randomly - tightly bound to the active-attempt window, exactly
as notes/58 first reported, now with hard live timing instead of a
single earlier sample.

## But it's not simply absent during success

Checked the success case properly this time (unlike earlier detours):
`0x0005` does occur during a successful capture too (9173 hits) - but
concentrated in the ~2 seconds *before* the successful send, from an
earlier attempt within the same capture window that hadn't yet
succeeded. In the narrow window immediately around the actual
successful exchange (`authenticate`/`authenticated`/`associated`, all
within ~12ms of each other), the dominant value is `0x0040` (a bit not
yet identified), with brief `0x0045` (CRS|TXF *together with* that bit)
during the real TX/RX activity of the successful exchange - not bare
`0x0005`.

This suggests the real distinction may be finer than "CRS|TXF present
vs. absent": possibly whether bit6 (`0x40`) accompanies it (briefly,
during real successful activity) versus CRS|TXF persisting *without*
it (extended stretches during failure). Not resolved - the raw capture
needed careful, narrow time-windowing to even see this, and a byte-level
bit-identity for `0x40` was not chased down this session.

## Honest status

The core symptom (CRS|TXF correlating tightly with failed attempts) is
now reconfirmed with real, timestamped, live evidence rather than a
single sample from hours earlier - a genuine strengthening of notes/58,
not a new claim. The refinement (does bit6 matter, and what does it
mean) is a real, concrete, well-scoped next step, not chased further
tonight given the length of this session. `tools/hw_timing.c`'s current
probe list has `phydebug`/`macctl_lo`/`macctl_hi`/`irqreason_lo`/
`irqreason_hi` wired up and ready for whoever continues this.

## Session summary (this thread, notes/58 through 71)

Real, kept results: HOSTF2/HOSTF3 bug found and fixed (notes/62, causal,
confirmed via NAP elimination, default off pending the rest); HOSTF1
gate found via static analysis (notes/64, inconclusive fix); a working
d11emu ground-truth-emulation harness (notes/65-67, real architecture
mapped: the dispatcher, multiple independent hardware-wait points);
live multi-register and full-snapshot hardware timing tools (notes/68-
71) with two self-caught-and-fixed tooling bugs (SHM addressing,
16-vs-32-bit MMIO reads) and one self-corrected overclaim (the timer
block's failure-specificity). CRS|TXF's tight correlation with failed
attempts, now reconfirmed live, remains the most direct, unresolved lead
into the actual root cause.
