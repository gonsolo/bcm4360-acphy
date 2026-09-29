# Simulated from true chip reset with real state; found the real event loop

Direct follow-up to notes/65, same session (2026-09-29, ~11am). Resolves
that note's open question about upstream SCR effects differently than
planned - not by tracing the specific caller, but by finally getting a
full run from true reset to succeed.

## Real IHR state, and a bug in interpreting the earlier delay loop

Captured real IHR (0-0x39F, `/sys/kernel/debug/b43ac/ihr`) the same way
as SHM, extended `tools/d11emu_seed_state.py` to splice both. Re-ran the
`0x1198` trace from notes/65 with real IHR added: identical result, SCR
0x2C/0x2D still read 0 throughout and are never written on that path -
this specific subroutine chain is now doubly confirmed to be a red
herring for the actual bug, not the setter.

notes/65's reset-vector attempt had called d11emu's `init` command
first, which loads a generic, unrelated built-in AC6 initvals table -
that's what set the huge (~0xA70+) generic delay counter, not anything
inherent to address 0. Skipping `init` entirely and seeding straight
onto `State::from_ucode()`'s raw default plus the real SHM/IHR capture
gives a *much* smaller, real countdown (~0xC7F, from the chip's actual
live IHR content) - small enough that `run` (not manual `next` - no
per-step print/PTY overhead) cleared it and got much further in 8ms of
real wall-clock time.

## Where it actually goes

`0x0000` jumps immediately (unconditional `JEXT`) to `0xE25`, a real
hardware bring-up routine - the `0x0002`-`0x000E` block traced all night
(the HOSTF1/HOSTF2/HOSTF3/SCR-flag idle check) is NOT on the cold-boot
path at all; it must be reached some other way, later. `0xE25`'s
countdown loop clears, and execution runs on to `0xCB4`:

```
0CB4: JEXT -> 0xD24          (if an external hw event occurred, handle it)
0CB5-0xCB7: (periodic bookkeeping, a CALLS to a ShmIndir-dispatched table)
0CB8: JNEXT -> 0xCB4         (if NOT an external event, loop back and poll again)
```

This is a genuine, legitimate "wait for a real hardware interrupt, then
dispatch to its handler at 0xD24" loop - and the run correctly stops
here because nothing is injecting a real external event into the
emulator (no simulated AP, no real DMA completion). Not a bug in the
emulator or the seeding; an accurate simulation of "nothing has happened
yet."

## Why this matters

This looks like the *real* top-level PSM wait loop - architecturally
distinct from the `0x0000-0x0014` predicate this whole investigation
(notes/60-65) has been centered on. That block may be a narrower,
periodic/power-management-specific check reached only under certain
conditions, not the chip's actual primary "sleep until something
happens" mechanism. `0xD24` (the real event handler `0xCB4` jumps to
when its condition is met) has not been examined at all yet - it is the
natural next place to look for where SCR 0x2C/0x2D, or the real TX-
completion bookkeeping, actually lives.

## Honest scope check

This session has now run a very long time (started the previous
evening, past 11am). This is a real, solid, well-grounded stopping
point: a genuine architectural finding, fully reproducible with the
tooling already committed (notes/65's harness + this note's `init`-free
seeding correction). Continuing into `0xD24` and beyond is a reasonable
next session's starting point, not something to rush through now.

## Tooling note

`tools/d11emu_seed_state.py` now takes IHR as a required argument (pass
`-` to skip). Real SHM/IHR capture commands:

```
sudo bash -c 'for ((o=0; o<0x2000; o+=2)); do printf "%x\n" $o > /sys/kernel/debug/b43ac/shm; cat /sys/kernel/debug/b43ac/shm; done' > real_shm.txt
sudo bash -c 'for ((o=0; o<=0x39F; o++)); do printf "%x\n" $o > /sys/kernel/debug/b43ac/ihr; cat /sys/kernel/debug/b43ac/ihr; done' > real_ihr.txt
```

Seed straight onto a `State::from_ucode()` dump (no `init` call) for a
true-reset run - `init`'s built-in initvals are for a different,
unrelated bring-up scenario and only add a much larger, meaningless
delay loop.
