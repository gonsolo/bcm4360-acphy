# Fresh wl association trace captured; hit a real wall on the remaining gap

Direct follow-up to notes/60-62, same day. Rebooted into generation 10
(kernel 6.18.53, `wl` active - the only pre-7.2.7 generation still on
disk) specifically to capture a trace covering a real association, not
just bring-up. `trace_wl.sh` ran clean (`traces/wl-init-20260929-093137
.trace[.xz]`/`.meta`, 211k lines, ~20s post-IFUP window, WiFi confirmed
back afterward, no crash). Rebooting back to generation 16 (b43,
default) right after.

## Why this trace alone can't finish the job

`wl` doesn't log `authenticate`/`associated` the way mac80211 does (it's
a monolithic blob handling its own SME) - no dmesg anchor for exactly
when auth happens inside the 20s window, unlike every b43-side trace in
this project. Not fatal (the whole window can be scanned), but the
deeper problem is what's actually being looked for:

notes/60 identified the ucode's idle-loop predicate reads two SCR
(scratch) registers (0x2C, 0x2D) in addition to the two SHM hostflag
words already tested (notes/62). **SCR is PSM-internal scratch space -
there is no host-side MMIO or SHM path to it at all.** Nothing in any
host trace, however carefully diffed, can show what wl writes there,
because wl (running on the host CPU) never touches it either - only the
D11 core's own microcode can read or write its own SCR registers. If the
remaining gap is genuinely gated by SCR 0x2C/0x2D (as opposed to some
host-visible precondition that merely causes the ucode to *set* those
SCR bits internally), trace-diffing the host side is the wrong tool.

Also unresolved: the JNZX opcodes testing SCR 0x2C at 0x0009 and 0x000B
differ (`505`/`508`) despite the disassembler printing the same operand -
d11emu's static disassembly doesn't decode whatever bitmask/condition the
opcode's low nibble encodes, and no public documentation for this ISA
covers it either. Confirming what these actually test would need either
real Broadcom documentation (not available) or instrumenting d11emu
itself to execute real captured register state and observe branch
outcomes - a real research project, not a quick step.

## Honest status

This is the point where the productive, bounded "diff a host-visible
register against wl's real trace" method (which found and fixed the
HOSTF2/HOSTF3 bug, notes/62) runs out of things it can see. Continuing
requires either:
1. Real d11 PSM ISA documentation (ask upstream b43-dev/nexmon - the
   d11emu authors may know, or have already documented this opcode
   family), or
2. A different empirical technique: single-step or watchpoint the D11
   core itself (not the host) while it's in the failing state - not
   something this project's current tooling (bpftrace on host kprobes,
   debugfs MMIO peeks) can do; would need real JTAG/ARM-debug access to
   the D11 core, which is not known to exist for this chip on this
   hardware.

Not a dead end for the project overall (notes/62's HOSTF2/HOSTF3 fix is
real and worth keeping), but real trace-diffing progress on the
remaining auth-reliability gap has hit its ceiling for tonight without
new tooling or documentation neither of which is in hand right now.
