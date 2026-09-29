# Ground-truth emulation of the hot loop, seeded with real chip state

Direct follow-up to notes/63/64, same day (2026-09-29, ~10am). Corrects
notes/63 in a different direction than the earlier correction: SCR
really is unobservable live (confirmed harder - see below), but d11emu
is a genuine execution engine, not just a disassembler, and it can be
driven with real captured hardware state instead of guessing from
static reading + coarse PC polling.

## False lead first, caught and discarded

The `b43ac` debugfs "scr" file (`which==5` in `phy_ac.c`) reads via
`b43_shm_read16(dev, B43_SHM_SCRATCH, addr)` - looked like a live SCR
window. It isn't: checked d11emu's own source (`emu.rs`) and its data
model has two entirely separate arrays - `scratchpad_registers` (64
words, what the disassembly's "SCR" operand type actually addresses)
and `shared_memory` (4096 words, what `ShmDir`/`ShmIndir` and all of the
driver's SHM routings including `B43_SHM_SCRATCH` address). Same English
word, two unrelated address spaces. The debugfs "scr" file reads the
second one. notes/63's original claim stands, now with harder evidence.

## Building a real emulation harness

`d11emu` has a genuine interpreter (`eval_instruction`, `next`, `run`,
`break`, full CALL/RETS stack) behind an interactive CLI that needs a
real TTY (`dialoguer`) - unusable piped directly, but `script -qc
"d11emu ..." /dev/null < commands.txt` gives it a real pty and works
fine for scripted input. State dumps/loads are plain JSON
(`serde_json`), so a snapshot can be captured, edited, and reloaded with
no new Rust code.

Method:
1. Capture the real, live SHM (all 4096 words, `/sys/kernel/debug/b43ac
   /shm`, same technique as `state_snapshot.sh`) from the actual chip.
2. `init` + immediately `dump` d11emu's state before ever calling `run`
   (avoids any lingering effect from its own hang detector).
3. Splice the real SHM words into the dumped JSON's `shared_memory`
   array (`tools/seed_state.py` - not yet copied into the repo's
   `tools/`, currently in scratch), set `pc` to a real entry point.
4. `load` the edited JSON, single-step with `next`, read the real
   opcode/operand trace it prints.

One self-inflicted bug on the way: zeroing `num_ucode_instructions` in
the edited JSON (thinking it was some kind of counter) silently broke
every `set_pc()` call - it's actually the bounds limit `set_pc` checks
against, so with it at 0 every jump AND every fallthrough failed the
bounds check and the PC never moved, printing nothing informative (my
`grep "^PC:"` filtered out the actual "End of Microcode reached" lines
that would've explained it immediately). Leave it alone.

## Real result

Seeded real SHM, started at `0x1198` (the actual live entry point -
`CALLS 0x11BA`, matching every live PC sample all night). Full, verified
instruction-by-instruction trace to completion (16 instructions, ends
cleanly when the one real CALL's RETS pops an now-empty stack):

`1198(call)->11BA->11BF->11C0->11C1->11C2->11C4->12EE(rets)->1199->119C
->119D->119E->119F->11A0->11A3->11A4->11A5(rets, halts)`

Real captured operand values along the way: `ShmDir[0xAE4]=0`,
`IHR[0x119]=0x333B`, `ShmDir[0xADD]=0xDBF6`, `IHR[0x15B]=0`,
`ShmDir[0x6A]=0x8081`, `ShmDir[0xAF5]=0xFF`. **SCR 0x2C and SCR 0x2D are
read multiple times along this path and are 0 every time; nothing on
this path ever writes them.** The branch at `11C2` (`JZX ShmDir[0x6A]`)
resolves to "jump" even though the raw value (0x8081) is nonzero -
confirms JZX/JNZX test a specific bit-field (`(((op1<<16)|op0)>>s) &
mask`) selected by the opcode's own encoding, not "is the whole register
zero" - the exact ambiguity notes/58 flagged as undecodable from static
disassembly alone. The real emulator resolves it for free.

This matches live sampling exactly: `11A6-11B8` (the OTHER subroutine,
reached only via `11C8`/`11CC`, which this path never reaches) never
showed up in any PC sample all night either (notes/64's "which path is
more probable" check). Ground truth and live observation now agree.

## What this does and doesn't settle

Does: confirms, with real evidence instead of inference, that *this*
code path is a pure pass-through for SCR 0x2C/0x2D under the chip's
current real state - it neither depends on nor sets them here. Resolves
the JZX/JNZX opcode ambiguity in general (the emulator decodes it
correctly even where the static disassembler's plain-text dump doesn't
show it).

Doesn't: SCR's true starting value at the moment `0x1198` is reached on
real hardware is still unknown - this run necessarily started SCR at 0
(the only honest assumption available, no live capture path exists).
If something upstream of `0x1198` (its real callers, `0x01C0`/`0x027C`,
not yet traced this way) sets SCR 0x2C/0x2D to something nonzero right
before the jump into this region, real hardware's behavior here could
still differ from this emulation. Next step for whoever picks this up:
seed and run from `0x01C0`/`0x027C` themselves the same way, to see
whether the real, current chip state ever drives SCR nonzero before
reaching here at all.

## Tooling produced (not yet committed into the repo)

- `tools/psmpc_fast.c` / `tools/scr_fast.c`: tight-loop C samplers for
  the AC debugfs interface, ~200k samples/sec vs a shell loop's ~110-300
  samples/sec (fork+exec overhead per sample dominates the shell version
  entirely).
- `seed_state.py` (scratch, not yet in `tools/`): splices a real SHM
  capture into a d11emu JSON state dump.
- The `script -qc ... < commands.txt` pattern for driving d11emu's
  interactive CLI non-interactively, no Rust changes needed.
