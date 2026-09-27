# Status 2026-09-27 (continued again), first real look at the D11 ucode

Following "keep digging on the ack bug" + checking prior art and starting on
the D11 microcode: everything up to now (notes/07-11) reverse-engineered the
*host driver* (`wl.ko`, x86, via Ghidra). The autonomous ACK/beacon TX logic
we've been chasing actually runs on the D11 core's own microcode
(`ucode42.fw`), a completely different, never-before-touched architecture in
this project. This session got a real disassembler working against it for
the first time.

## Prior art check

No public project (OpenBRCM, the b43-ac-wip forks, etc.) has documented
fixing this specific "firmware-autonomous-TX fails, host TX is fine" failure
mode. Nothing to borrow from there. Search terms and results aren't worth
repeating here; the takeaway is just "still open elsewhere too."

## Tooling: seemoo-lab/d11-emu against our real ucode42.fw

[d11-emu](https://github.com/seemoo-lab/d11-emu) (SEEMOO lab / Nexmon team,
paper: "Rolling the D11: An Emulation Game for the Whole BCM43 Family", ACM
WiNTECH'23) is a Rust D11 core emulator supporting core revisions 15-54 -
comfortably covering our core rev 42 - and works **fully offline against a
bare ucode binary file**, no special hardware required (the Raspberry
Pi/bcm43455c0 support is only for optional *live* state extraction, which we
don't need since we can already test on our own hardware directly).

Setup (reproducible from scratch):
1. Build Nexmon's `b43-asm` v3 assembler (`buildtools/b43-v3/assembler` in
   `seemoo-lab/nexmon`) - needed only because d11emu's `build.rs`
   unconditionally assembles its own `tests/*.asm` files at build time.
   On NixOS: `make QUIET_SPARSE=true` (the Makefile's sparse-check fallback
   hardcodes `/bin/true`, which doesn't exist here).
2. Clone `seemoo-lab/d11-emu`, put `b43-asm`/`b43-asm.bin` on `PATH`,
   `cargo build --release`.
3. Convert `ucode42.fw` to the format d11emu's loader expects with
   `tools/convert_ucode_for_d11emu.py` (see that file's docstring for the
   exact byte-layout reasoning - verified empirically against `b43-asm -f
   raw-le32`'s own test output, not guessed).
4. `d11emu`'s interactive CLI uses `dialoguer`, which doesn't work over a
   plain piped stdin (it just spins reading empty commands forever - this
   filled a scratch file to 243MB in about 20 seconds before being caught
   and killed; nothing hardware-related, pure local disk churn, cleaned up).
   Patched in a non-interactive mode instead: `d11emu <ucode> disasm` now
   statically disassembles every loaded instruction and exits. Patch saved
   as `tools/d11emu-disasm.patch` (apply to a fresh `d11-emu` clone).

This is a genuinely new capability for this project: a full, correct
disassembly of the real AC-PHY ucode running on this exact chip (5425
instructions, `Length: 0x1531` confirmed self-consistent).

## Finding: located the exact txphyerr++ sites

Our host-side macstat counters (`txallfrm`=SHM byte 0xE0, `txackfrm`=0xE6,
`txphyerr`=0xFE - the ones `tools/probeack.sh` reads) are ucode-side direct
SHM word addresses at half those byte offsets (ucode's `ShmDir` operand is a
12-bit *word* address into the same 16-bit-word SHM space host code
addresses by *byte* offset). Confirmed empirically, not just by formula: the
disassembly contains exactly one `ADD 0x73,1,0x73` (`txackfrm++`, address
0x04A7) and exactly two `ADD 0x7F,1,0x7F` (`txphyerr++`, addresses **0x0C49**
and **0x0C58**) - see `disasm-ucode/txphyerr_handler_excerpt.txt` for the
full ~80-instruction block around both.

Both increments are reached via a `jext`/`jnext` (jump-on-external-condition)
branch, not a computed check against any SHM/IHR value - i.e. ucode is
directly testing a **hardware condition line**, not deciding this itself
from other state. Both paths converge immediately afterward into the same
~50-instruction block (0x0C59 onward): set a flag, poll a few more external
conditions, save several IHR registers into a small SHM buffer (0xBFA-0xC07,
looks like a TX-status/completion record), then call two subroutines
(`CALLS` to ucode addresses 0x105 and 0x109).

The old (2008-era, explicitly "highly incomplete") b43 wiki documents a
"PHY TX error" bit as condition register 2 bit 0xD, but our two branches
decode (via `Opcode.p1`=condition-register, `Opcode.p2`=bit, per d11emu's
own `Mnemonic::JEXT` semantics in `src/emu.rs`) to condition register 4 bit
7 and condition register 6 bit 15 respectively - not register 2 bit 0xD.
This isn't necessarily a contradiction (that wiki's numbering is for a much
older chip generation and the D11 core's condition-register layout is not
guaranteed stable across 15+ years of chip revisions), but it means we
cannot yet name *which* physical signal these two conditions correspond to
with confidence - only that they are hardware-asserted, not software-decided.

## Why this matters

This is independent, code-level confirmation of what notes/09-11's exhaustive
register/mechanism sweep already pointed at: **the failure is a hardware
condition the PHY itself asserts**, faithfully counted by ucode, not a
missing register write, sequencing step, or ucode software bug reachable by
comparing against wl's driver-side behavior. Everything checked so far - PHY
registers and tables, radio registers, every SHM word wl writes, the RF
sequencer, IRQ masking, and now the ucode's own error-counting logic itself -
comes back the same way: real, hardware-level, not something host-side
config can fix.

## Open questions / next steps

- What exactly sets condition register 4 bit 7 / register 6 bit 15 at the
  silicon level? Needs either (a) Nexmon's own condition-register
  documentation for a D11 core generation closer to ours than the 2008 b43
  wiki's, or (b) live extraction from *our* hardware. d11emu's `extract`
  command only knows how to pull state from the specific bcm43455c0/
  Raspberry Pi setup it was built for; getting live condition-register state
  from our PCIe BCM4360 would need new, small, purpose-built tooling (a
  kernel-side probe or debugfs read of the D11 core's own condition-register
  IHR mirror, if one exists) - not attempted yet.
- The two `CALLS` targets (ucode addresses 0x105 and 0x109) haven't been
  examined - likely the actual TX-status-to-host-and/or-retry logic. Natural
  next disassembly target.
- Backward from 0x0C41 (where this whole block starts) to find what *sets up*
  entry into this handler - is this reached from every TX completion (success
  or failure), or specifically an error path branched to earlier? Would show
  whether ucode has any of its own retry logic that might be relevant.
