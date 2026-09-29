# Live hardware timing: IHR[0xB3]/SHM[0x6A] ruled out, no smoking gun found yet

Direct follow-up to notes/67, same session. Built `tools/hw_timing.c`: a
multi-register sampler cycling through `pc`/`ihrb3`/`ihr93`/`ihr95`/
`ihr97`/`shm6a`/`ihr15b` via the `b43ac` debugfs interfaces, one open fd
per file reused across samples (~30k full cycles/sec). Made it resilient
to a transient "No such device" on the fd (happens during interface
mode changes across disconnect/reconnect - reopens and keeps sampling
instead of dying, which the first version did, silently truncating
captures).

## Real, replicated result: IHR[0xB3] and SHM[0x6A] don't discriminate

notes/67 left off suspecting `IHR[0xB3]` (the interrupt-source scan
register the real dispatcher checks at `0xD24`) never getting set was
why the chip's firmware always takes the "nothing happened" fallback
path during failures. Captured it live, at high rate, through two
independent real failed attempts and one real successful one:

- Failures (2 independent captures): `IHR[0xB3]` and `SHM[0x6A]` both
  100% zero for the entire window (auth sends, timeout, all of it).
- Success: **also** 100% zero, the entire time, including through the
  moment authentication and association actually happened.

This directly disproves the hypothesis - if `IHR[0xB3]` never getting
set were the problem, the successful attempt couldn't have succeeded
either. Whatever real mechanism actually gates success doesn't route
through this register at all. The `0xD24`/`0xB7`-vector-table dispatcher
mapped in notes/67 is real ucode architecture, but not the relevant path
for this specific bug - live A/B evidence, stronger than anything the
static/simulated tracing alone could show.

`IHR[0x15B]` (checked at `0x11C1`, notes/58) is also a flat, unchanging
`0x1030` in every capture - real, but not discriminating either.

## A real difference exists, but it's a consequence, not a cause

`ihr93`/`ihr95`/`ihr97` (radio/PHY-adjacent, written right before the
`0x1EB` hardware-wait found in notes/67) show materially richer activity
during the successful attempt (more distinct values, transient resets
to 0) than during either failure (a simple 2-value toggle). Looked
promising - `ihr97` specifically takes on a new value (`0x0d74`, one bit
different from the constant `0x0d70` seen in both failures) only in the
successful capture.

Checked the exact timing: `0x0d74` first appears at t=4170.794s;
`wlp3s0b1: associated` was logged at t=4170.787s - seven milliseconds
*before*. This is a downstream consequence of successful association
(routine post-connection PHY/rate activity), not a precondition for it.
Real, but not the mechanism.

## Honest status

Ruled out three specific registers as the discriminating factor between
success and failure, with real live A/B data, not inference - a
legitimate result even though it isn't the answer. The three chosen
were the most promising candidates from the whole night's static and
simulated tracing (notes/58-67), and none of them pan out, which itself
narrows things: the real cause is not in the code paths this session's
static/simulated work centered on.

`tools/hw_timing.c`'s probe list is a fixed array of 7 - trivial to
extend to more addresses for whoever continues this (the SHM/IHR
address space is large; this session picked candidates from what the
disassembly work had already flagged as relevant, not an exhaustive
sweep). A genuinely different approach worth considering next: instead
of guessing which of hundreds of SHM/IHR words to watch, capture *all*
of SHM (4096 words) and a wide IHR range at a slower but exhaustive rate
across a success and a failure, then diff the two captures
mechanically - closer to the trace-diffing method that found the real,
confirmed HOSTF2/HOSTF3 bug (notes/62) than the targeted-guess method
used here.
