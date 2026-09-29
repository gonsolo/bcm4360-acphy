# HOSTF1 gate is real; the guessed bits (EDCF|ACIW) don't show a confirmed fix

Direct follow-up to notes/62/63, same day, after the user correctly
pushed back on "hit a wall" - the microcode disassembly itself still had
untapped, purely static analysis available: where do SCR 0x2C/0x2D
actually get *written*, not just read.

## What static analysis of the existing disassembly found

Grepped every instruction writing SCR 0x2C (17AC) or 0x2D (17AD) as
destination. One write site (ucode42.fw 0x0400-0x042D) sits directly in
front of `TXALLFRM++` (the same counter `tools/probeack.sh` reads) - this
is the TX-status-processing routine. Inside it:

- `0406`: clears SCR 0x2C unconditionally on entry.
- `0407`: `JZX ShmDir(0x2F), 0, -> 0x414` - **if HOSTF1 (SHM 0x5E, word
  0x2F) is zero, skip the entire block** (0408-0413: an indirect CALL
  through a table at `ShmIndir+0x74 base=1`, presumably per-FIFO
  dispatch, plus more IHR/SCR bookkeeping) and jump straight to 0x414.
- `040B`: after that block (if it ran), `JZX SCR(0x2C), 0, -> 0x414` -
  i.e. whether the rest of this routine does extra work depends on
  whether the skipped/not-skipped block set SCR 0x2C.

So HOSTF1==0 disables a real code path that can set one of the exact two
flags the idle loop (notes/60) checks before deciding to NAP - a second,
deeper instance of the same category of bug as HOSTF2/HOSTF3 (notes/62):
`phy_ac.c` never calls `b43_hf_write` at all, for any of the three words.

## Why no captured ground truth this time

Unlike HOSTF2/HOSTF3 (caught mid-association in the existing ifdown/ifup
trace), HOSTF1 never showed up as a write in either wl trace - it's
plausibly set once at initial attach, before any ifdown/ifup window
starts. Capturing that moment needs tracing across an actual module
(re)load, which `trace_wl.sh`'s own comment already flags: "changing the
binding of wl while probes attach crashed the machine twice." Not
repeated solo tonight, consistent with today's own notes/59 caution
about repeated crash-adjacent testing.

## Test: a reasoned guess, not a captured value

Added `ac_hostf1` (default off): writes `B43_HF_EDCF | B43_HF_ACIW` if
set. Chosen from b43.h's own named bits, not measured: `EDCF` ("on if
WME and MAC suspended" - this port's whole story) and `ACIW` ("shift
bits by 2 on PHY CRS" - notes/58's CRS|TXF finding).

10 connect attempts with `ac_hostflags=1 ac_hostf1=1` together: 4
succeeded (40%), against notes/62's 4/13 (~31%) for `ac_hostflags` alone.
Not a confirmed improvement at this sample size - could easily be noise.
Sampled the live PSM PC during one attempt (same method as before): the
hot addresses are the *same* subroutine cluster as every earlier sample
(0107/11ba/11c2/11c4/12ee), no sign of reaching a qualitatively new code
path. Doesn't rule the guess in or out cleanly either way.

## Honest status

Real, static-analysis-confirmed structural finding (the HOSTF1 gate
exists and this port never opens it). The specific bits tried are an
informed guess, not a verified fix, and the data doesn't clearly support
or refute them. Two ways to actually resolve this:

1. A **safe** (not a live rebind) capture of wl's real HOSTF1 value: a
   trace armed by a systemd service that starts *before* wl's normal
   boot-time module load in generation 10 - a first load, not a rebind,
   so it doesn't carry the hazard `trace_wl.sh`'s comment warns about.
   Needs one more reboot into gen10; not done yet, flagged rather than
   done solo given how many live-testing cycles this session has already
   run.
2. Resolve the indirect dispatch table (`ShmIndir+0x74 base=1`) target(s)
   from the disassembly alone, to find the actual SCR-0x2C-setter
   instruction and read its real precondition directly, without needing
   wl's value at all.

`ac_hostf1` left off by default pending either.
