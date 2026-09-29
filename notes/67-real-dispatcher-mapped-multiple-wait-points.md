# The real top-level dispatcher, mapped; multiple independent wait-points found

Direct follow-up to notes/66, same session. Pushed into `0xD24`, the
handler `0xCB4`'s event loop jumps to when its condition is met.

## What `0xD24` actually is

A real interrupt-source identification routine: scans bits of `IHR[0xB3]`
one at a time (shift-and-test against a growing mask, `SL`/`JNAND` at
`0xD31-0xD35`), building an index. With the chip's real current
`IHR[0xB3]=0` (no source flagged), the scan finds nothing and falls
through to `0xD51`, which jumps to `0xB7` - the start of a long,
sequential vector table: dozens of `JEXT` entries (`0xB7, 0xB8, 0xB9,
0xBA, ... 0xC6, 0xC7, 0xC8, 0xCC, ...`), each testing its own condition
and either dispatching to a handler or falling through to the next
entry. With nothing currently flagged, execution cascades through the
whole table, one entry at a time - each one a small, real subroutine.

## The 0x1198 region is confirmed genuinely on this path

`0xC6`'s entry does `CALLS 0x11B9` - exactly the code this whole
investigation (notes/58-65) has been centered on. Ground-truth-traced
here too: identical result, SCR 0x2C/0x2D still read 0 and are never
written. This *is* real, reachable code, not a red herring - it's simply
one of many small tasks the dispatcher runs each pass, and it does
nothing with SCR 0x2C/0x2D under the chip's current real conditions.

Continuing past it: `0xC7` -> `0xC8` -> `0xCC`/`0xCD` -> `0xCE` (calls
`0x10E2`) -> `0xCF`/`0xD0` -> `0xD8` -> `0xDE`/`0xDF` -> `0xF5` (calls
`0x118B`, a related/adjacent subroutine, also SCR-2C/2D-silent) -> `0xF6`
-> `0xF7` -> `0xF8` - a genuine, long walk through dozens of independent
per-tick tasks.

## Hit a real wall: 0x1EB, a second independent hardware-wait

Tried a systematic sweep: set breakpoints at every known SCR-0x2C-write
site (all ~20 found via the earlier static grep, notes/60) and let
`continue` run freely (not manual `next` - far less overhead) to see if
execution reaches any of them naturally. It ran only 20 microseconds
before hitting a *different* self-loop at `0x1EB` (`JNEXT -> 0x1EB`),
never reaching the vector-table walk at all this time - a different
task's own wait-loop, entered via a different path than `0xCB4`'s. Right
before it, `0x1E8-0x1EA` write `IHR[0x97]/[0x95]/[0x93]` - looks like a
radio/PHY register operation, waiting for its own completion.

This is at least the third independent "wait for a real hardware
completion" point found tonight (`0x000F` NAP, `0xCB4`, `0x1EB`). The
ucode is structured as many small cooperative tasks, each with its own
wait condition, not one central loop. Skipping `0x1EB` by force-setting
its PC past the self-jump was considered and rejected: unlike everything
else in notes/60-66, that would mean asserting execution continues past
a point without knowing what real condition would actually unblock it -
a guess presented as data, not a ground-truth result. Every other
finding tonight has been either a real captured value or a demonstrated
consequence of one; this is where that standard runs out for the
current tooling.

## Honest status

Real, solid architectural finding: mapped the actual top-level event
dispatcher (`0xD24` scan -> `0xB7` vector table -> dozens of per-tick
subroutines including the one this whole thread has centered on),
confirmed genuinely reachable and genuinely SCR-2C/2D-silent under the
chip's current real state, across two independent entry points now. The
remaining question - does *any* task, under *some* real condition, ever
write SCR 0x2C/0x2D before the idle check at `0x0009` - needs either
real interrupt/event timing data (not capturable with current tooling)
or continuing to map every wait-point's real unblock condition
individually, which is a large undertaking on its own.

Stopping the emulation-harness thread here for this session. The
tooling (`tools/d11emu_seed_state.py`, the `script -qc` pattern,
breakpoint sweeps) is real and reusable; what's missing now is either
more captured ground truth or a lot more mapping time.
