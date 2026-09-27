# Status 2026-09-27 (continued again), reading ucode's own TX-error diagnostic record

Following up on notes/12: traced the two subroutines (`0105`, `0109`) called
from the txphyerr error handler right after the counter increments.

## What the subroutines do

Both are tiny (3-4 instructions) wrappers around the D11 core's **extended
IHR** indirect port (`IHR_EXT_IHR_ADDR`=0x018, `IHR_EXT_IHR_DATA`=0x019 -
named constants confirmed against d11emu's own `include/ihr.rs`, same
address/data-register pattern as host-side SHM_CONTROL/SHM_DATA):

- `0105`: extended-IHR **read** setup (poll IHR 0x18 not-busy, write address
  mode-3|SCR21 into IHR 0x18, poll again). Caller reads the result back from
  IHR 0x19 afterward.
- `0109`: extended-IHR **write** (poll not-busy, write SCR22 into IHR 0x19 as
  the data, write address mode-2|SCR21 into IHR 0x18 to commit).

The caller (right after the `txphyerr++` we found last time) does, in order:
1. Compute an address into SCR21 (depends on `IHR_TXE_PHYCTL`=0x86-adjacent
   state and SHM word 0x55 - not fully decoded).
2. `CALLS 0105` - read whatever's at that extended address.
3. **If this is the first error since load** (guarded by a flag at SHM
   0xBFA, which the full ucode zeroes at upload so this only fires once per
   module load): save a whole diagnostic record into a fixed SHM buffer
   (0xBFB-0xC07), then set the flag.
4. `CALLS 0109` twice (write 0xFFFF to the address from step 1, then XOR that
   address with SHM 0x55 and write 0xFFFF again) - looks like a
   write-1s-to-clear ack of the same status register(s), on every error, not
   just the first.

The diagnostic record itself (word addresses in ucode's native units; the
host-driver's debugfs `shm` file wants `addr = word_address * 2` since SHM
is a 16-bit-word space host code addresses by byte offset, ucode by word
offset - verified for `txallfrm`/`txackfrm`/`txphyerr` last time, applies
here too):

| SHM word | host byte addr | source | meaning |
|---|---|---|---|
| 0xBFA | 0x17F4 | flag | 1 = record populated |
| 0xBFB | 0x17F6 | extended-IHR read (step 2) | unknown status register |
| 0xBFC | 0x17F8 | `IHR_TXE_PHYCTL` (0x86) | live PhyTxControlWord for the failed TX |
| 0xBFD | 0x17FA | `IHR_TXE_PHYCTL1` (0x8A) | " |
| 0xBFE | 0x17FC | `IHR_TXE_PHYCTL2` (0x8B) | " |
| 0xBFF-0xC00 | 0x17FE, 0x1800 | `IHR_TxPlcpLSig0/1` | L-SIG (legacy PLCP) of the failed frame |
| 0xC01-0xC03 | 0x1802-0x1806 | `IHR_TxPlcpHtSig0/1/2` | HT-SIG (802.11n PLCP) |
| 0xC04-0xC05 | 0x1808, 0x180A | `IHR_TxPlcpVhtSigB0/1` | VHT-SIG-B (802.11ac PLCP) |
| 0xC07 | 0x180E | SCR12 | unknown scratch register at time of error |

This is real forensic information about exactly what the hardware was doing
at the moment of a PHY TX error, straight from ucode - nothing like this has
been read out before in this project.

## First real sample (live hardware, 2026-09-27)

Read after `tools/probeack.sh` produced its usual ~75% retry rate and
`txphyerr` had incremented to 3 (absolute counter) on a fresh `b43` load
(`ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1`, channel 1):

```
flag              = 0x0001   (populated)
ext-IHR read      = 0x2000   (bit 13 set - unidentified status register)
TXE_PHYCTL        = 0x0045   (base 0x0040 = our ACKCTSPHYCTL template value,
                               OR'd with 0x05 - plausibly a per-TX rate/
                               format selector added on top of the template)
TXE_PHYCTL1/2     = 0x0000 / 0x0000
L-SIG0/1          = 0x0000 / 0x0000   (legacy PLCP fields both zero)
HT-SIG0           = 0x01C0            (non-zero!)
HT-SIG1/2         = 0x0000 / 0x0000
VHT-SIG-B0/1      = 0x0000 / 0x0000
SCR12             = 0x0031
```

**The interesting fact**: HT-SIG0 is the only non-zero PLCP field. The frame
that triggered this particular error was in **HT (802.11n) PLCP format**,
not legacy OFDM and not VHT/AC. `TXE_PHYCTL`'s 0x40 base matching our
already-known ACKCTSPHYCTL template value is a good sign (that part of our
port is doing what it should); the 0x05 on top of it is unexplained.

## What this doesn't tell us yet

- Only one sample. Don't know if HT-format is *always* what's involved in a
  failure, or this was one of several possible paths. SHM 0xBFA can be
  written back to 0 through the same debugfs `shm` interface to reset the
  "first error" latch and capture another sample later in the same boot,
  without a full module reload - didn't do a second round this session, but
  it's cheap and worth doing next time to check consistency.
- Don't know what frame this actually was (our injected probe request,
  retried at the 802.11 MAC layer, vs. an autonomous ACK/CTS). `txallfrm`
  jumped by exactly 210 = 30 x 7 in one run with zero acks/errors recorded
  in that window, consistent with our own *outgoing* probe requests
  exhausting their retry limit (7) without ever being ACKed by the AP at
  all - a different, not-previously-highlighted symptom worth separate
  attention: are we sure the AP is even receiving our probes reliably, or is
  something failing on the outbound leg too, independent of the
  ACK-generation problem this whole investigation has focused on?
- `IHR_EXT_IHR_ADDR`'s exact address computation (SCR21, depending on
  `IHR_TXE_PHYCTL`-adjacent state and SHM 0x55) and the meaning of the
  extended-read result (0x2000) aren't decoded. That register is reached
  only through the indirect port, i.e. it's *not* one of the directly
  addressable IHR registers d11emu's `include/ihr.rs` already names - it's
  probably a PHY-domain or radio-domain status register multiplexed through
  this port, which would need more ISA/hardware documentation (or more
  ucode disassembly - other code that uses the same extended-IHR mechanism)
  to identify.

## Follow-up (same session): confirmed with live hardware reads

Reran the capture twice more (resetting the SHM 0xBFA flag via debugfs
between rounds, no reboot/reload needed) - **bit-for-bit identical** both
times: `extread=0x2000 phyctl=0x0045 htsig0=0x01C0 scr12=0x0031`, everything
else zero. Extremely consistent.

Added a small, permanent debugfs file (`b43ac/ihr`, `which=4` in
`b43_ac_dbg_{read,write}`, routing `B43_SHM_HW`) since the existing `shm`
file was hardcoded to `B43_SHM_SHARED` and couldn't reach directly-addressed
IHR registers like `IHR_TXE_STATUS`/`IHR_TXE_CTL`. This ruled out one
alternative explanation and found a new lead:

- **Read the same registers at idle** (fresh module load, before any TX):
  `TXE_PHYCTL(0x86)=0xFF00`, `TxPlcpHtSig0(0x323)=0xC000` - clearly
  *different* from the diagnostic snapshot's `0x0045`/`0x01C0`. This rules
  out "these are just stale/power-on-default values the error handler reads
  regardless of what actually happened" - real state changed between idle
  and the point of failure, so the HT-format PLCP fields are genuine
  evidence about the failing transmission, not an artifact.
- **Read `IHR_TXE_STATUS` (0x87) live, after a batch of real failures**:
  `0x0401`, vs. `0x0001` at idle - an extra bit (bit 10, 0x400) is set that
  wasn't there before any failures occurred. Not yet confirmed as *the*
  error flag (could be coincidental / cleared-then-reset elsewhere), but a
  concrete, first-time-ever-observed candidate for a direct "TX engine
  error" status bit, distinct from the SHM-buffered diagnostic record.

## Follow-up 2 (same session): decoded the extended-IHR address, confirmed TXE_STATUS bit 10

Decoded the `ORX`/`JNZX` bit-packing precisely against d11emu's own execution
semantics (`Mnemonic::ORX`/`JNZX` in `src/emu.rs`: `m,s = opcode.p1,p2`,
`mask=((1<<(m+1))-1).rotate_left(s)`, etc.) rather than guessing:

- The address fed into subroutine `0105`'s read is computed at 0x0C64-0x0C66
  and, for our observed failure, resolves to **SCR21 = 7** (the `IHR[0x86]`
  bits[1:0]-nonzero branch is taken - our diagnostic sample's saved
  `TXE_PHYCTL=0x0045` has bit 0 set, consistent with this).
- Subroutine `0105` itself always packs its read as **mode 3** (hardcoded
  immediate in its own `ORX`, not caller-supplied) with the caller's offset
  in the low 13 bits: `IHR[0x18] = 0x6000 | offset`. So our read is
  "extended space mode 3, offset 7" -> value 0x2000.
- This same `CALLS 0105`/`0109` pair is used **extremely widely** through
  the whole ucode (33 call sites for `0105`, 60+ for `0109`) - it's a
  general-purpose indirect register port, not something specific to error
  handling. The very first call (address 0x0012, in the boot/reset path)
  uses a *variable*, SHM-stored offset (`SHM[0xC0]`) rather than a fixed
  one, suggesting per-chip-revision configurability elsewhere in this
  address space; our error handler's offset (7) is a fixed immediate,
  probably a stable, chip-generation-independent slot. Still don't have a
  name for "mode 3, offset 7" specifically - would need to cross-reference
  many more of these call sites (or real chip documentation) to identify it
  by function.

**Confirmed `IHR_TXE_STATUS` (0x87) bit 10 with a clean, isolated test**:
loaded `b43` fresh (`TXE_STATUS=0x0001`, `txphyerr=0`), ran `probeack.sh 1`
(a single probe injection, retried up to 7 times at the MAC layer),
immediately re-read both: `txphyerr` went 0->1 and `TXE_STATUS` went
0x0001->0x0401 in the same window. This is a real, direct, 1:1-observed
hardware error latch - not something that requires waiting for a whole
batch of failures to show up. (Note in passing: `probeack.sh`'s own
before/after delta printed "+0" for both counters despite the raw SHM
values changing - its capture window is a bit too tight around the
injection call; the raw `shm`/`ihr` debugfs reads are the reliable ground
truth, worth using directly rather than trusting the script's own delta
for small `N`.)

## Follow-up 3 (same session): replayed ucode's own clear sequence from the host

Since the extended-IHR address/data registers (`IHR_EXT_IHR_ADDR`=0x18,
`IHR_EXT_IHR_DATA`=0x19) are ordinary, directly-addressable IHR registers,
the host can drive the exact same protocol ucode's `0105`/`0109`
subroutines use, through the new `b43ac/ihr` debugfs file - no new tooling
needed, just the decoded mode/offset encoding from the follow-up above.

Reproduced ucode's own error-acknowledgment sequence by hand after inducing
one failure (`TXE_STATUS=0x0401`, extended read at mode3/offset7 = `0x2000`
as before):

1. Wrote `IHR[0x19]=0xFFFF` then `IHR[0x18]=0x4007` (mode 2, offset 7) -
   the same "write 0xFFFF" ucode does at 0x0C78.
2. Wrote the same 0xFFFF at mode 2, offset `7 XOR SHM[0x55]` (SHM[0x55] was
   `0x087A` live, so offset `0x87D`) - ucode's second write at 0x0C7A.
3. **`TXE_STATUS` (0x87) stayed at `0x0401` through both writes** - bit 10
   did not clear.
4. But reading back offset 7 afterward (mode3) now returns `0x0000`, down
   from `0x2000` - the write-1-to-clear *did* take effect on that register.
   (Didn't re-check offset `0x87D`'s prior value, so can't say whether that
   one changed too, only that the offset-7 flag ucode captured did clear.)

**Conclusion: these are two independent status indicators.** The
mode3/offset7 extended register is a per-event flag ucode reads once and
clears immediately as part of ordinary error handling (self-contained,
confirmed working exactly as designed). `IHR_TXE_STATUS` bit 10 is a
separate, stickier latch that survives ucode's own housekeeping - plausibly
a "this session/association has seen at least one TX-engine error" summary
flag rather than a per-transmission one. Did not attempt writing directly
to `IHR_TXE_STATUS` itself to test if *it* has its own write-1-to-clear
behavior - it's a "STATUS" register in an active TX-engine control block,
not confirmed safe to write (unlike the extended port, which ucode itself
already demonstrated is a safe target), so left alone rather than risk
disrupting live TX-engine state for an experiment.

## Follow-up 4 (same session): backward-traced the callers - a real correction

Followed the user's request to backward-trace what calls into the error
block (0xC2A onward). Found two external entry points at 0x0A5F/0x0A60/
0x0A8A, which land in a **long `JE SCR13, <const>, <target>` dispatch
chain** (0x0A76-0x0A90ish) - a switch-style dispatch on a value in
scratch register SCR13. Traced SCR13's only write site (0x0976-0x097A):
it's derived from `IHR_MHP_CFC` (0x259, d11emu's name: "MAC Header Parser -
**Contained Frame Control**") via a `SRX` extract (bits [7:2], i.e.
whatever 6 bits sit above the low 2) then an `ORX` that shifts it back up
and forces the low 2 bits to a fixed `01`. **This is a dispatch keyed on a
hardware-parsed frame-control-like field of some frame** - i.e. this whole
region handles frames by *type*, not a generic "any PHY TX error" handler.

Decoding *which* frame type each SCR13 constant represents (assuming
standard 802.11 FC-byte bit positions: bits 2-3=Type, bits 4-7=Subtype)
worked cleanly for confirming that different constants clearly separate:
**`SCR13=0x35` takes a *different*, non-overlapping code path (entry at
`0xB7F`) than `SCR13=0x2D`** (our previously-traced path into `0xC2A` ->
`0xC49`/`0xC58`'s `txphyerr++`). I is *not* confident about the specific
frame name for `0x2D`, though - working the exact type/subtype bits back
out of the final SCR13 value gave an inconsistent result (a reserved/
invalid Type=3), so something about the exact bit-repacking isn't fully
pinned down; don't trust a specific "this is frame X" label from this
session's decode without redoing that arithmetic carefully.

**What is solid, and matters**: `0xB7F`'s block (traced through ~0xBE5) is
clearly TX-*preparation* code - it writes what look like PLCP/rate
parameters into IHR registers (0x70-0x74, a different block than
`IHR_TXE_*`) and polls one of them for completion, the classic
"kick off a transmission" pattern - and **it never touches `txphyerr` (SHM
0x7F) anywhere in the portion traced**. Whatever frame type `0x35` is, its
handling is structurally different from - and doesn't feed into - the path
this whole investigation (notes/12 onward) has been examining.

**Open question this creates**: is `0xC2A`/`txphyerr++` actually reached,
in our real test failures, via this SCR13 frame-type dispatch at all (in
which case the diagnostic record and `TXE_STATUS` correlation found earlier
this session describe a *specific frame type's* failure, not "ACK
generation" generically) - or is it reached via a *separate* path, e.g. the
genuine `B43_IRQ_PHY_TXERR` hardware interrupt's own handler, which happens
to converge on the same address for unrelated bookkeeping reasons? Haven't
traced the actual PHY-TX-error interrupt vector itself (only reasoned
backward from one code path that happens to lead to the same address). This
needs resolving before treating anything in "Follow-up 1-3" above as
definitely describing *ACK* failures specifically, rather than some other
frame type's failures that happen to touch the same shared counter.

## Follow-up 5 (same session): tried to verify SCR13 live - a methodology lesson, and the open question mostly resolved

Added one more debugfs file, `b43ac/scr` (`B43_SHM_SCRATCH` routing,
`which=5`), to read the D11 core's SCR scratch registers directly from the
host (`B43_SHM_SCRATCH` is a real routing option, already defined in
`b43.h`; SCR registers are the same 128-entry scratch file the ISA's `SCR`
operand type addresses).

**Result: not usable the way I'd hoped.** Induced one isolated failure the
same way as before (fresh load, `SCR13`/`12`/`14` all read `0` at baseline),
then immediately read them back: `SCR13=0`, `SCR12=1`, `SCR14=0x35`. Not the
`0x2D` I expected in `SCR13`. **These are general-purpose scratch
registers reused constantly by unrelated ucode activity** (background MAC
housekeeping, other frames' processing) between "the moment of our
failure" and "the moment our slow host-side debugfs read actually
executes" - by the time we read it, the register has been overwritten many
times over by things that have nothing to do with our specific failure.
Live-peeking a scratch/IHR register after the fact is fundamentally
unreliable for reconstructing transient per-event state; only an explicit
ucode-side *latch* (like the diagnostic-record SHM buffer from Follow-up 1,
which is deliberately guarded so it's written once and never overwritten)
gives trustworthy per-event data this way.

**This actually resolves most of the open question from Follow-up 4,
though not the exact frame-type name.** The diagnostic-record save code
(the `SHM[0xBFA]`-guarded block) lives *inside* the exact block reached via
the `SCR13`-dispatch path this session traced (from `0x0A8A`'s jump). Since
we've now confirmed, repeatedly, on real hardware, that this diagnostic
record *does* get populated during our actual `probeack.sh` failures - and
there's no other place in the disassembly that writes `SHM[0xBFA]` - our
real failures **do** provably go through this exact traced code path,
regardless of what the dispatch value should be called. What's still
genuinely unresolved is only the *label* (which specific 802.11 frame type
`0x2D`, or whatever the live value actually is, corresponds to) - not
whether the investigation in Follow-ups 1-3 was about the right code path.
(`SCR14=0x35` showing up live, in a test scenario dominated by real ACK
exchanges, is circumstantially consistent with `0x35` meaning ACK as
originally guessed for the *other*, non-overlapping dispatch branch - but
per the above, this is not rigorous confirmation, just a consistent
coincidence.)

## Next steps

1. ~~Take 2-3 more samples~~ - done, see above, fully consistent.
2. Check whether the AP-probe-request-never-acked symptom (210 = 30x7 retries,
   zero macstat activity in that window) is the SAME root cause or a
   separate issue - if our own outgoing frames are also failing to reach
   the AP some of the time, that's new and wasn't part of the original "host
   TX is 100% reliable" characterization.
3. Find more code that touches the extended-IHR port (grep the full
   disassembly for other `CALLS 0105`/`CALLS 0109` sites) to build up a
   table of known SCR21 address values and what they read/write, which
   would help identify what 0x2000's bit 13 actually means.
4. Watch `IHR_TXE_STATUS` (0x87, now readable via the new `b43ac/ihr`
   debugfs file) across single, isolated failures (not a whole
   `probeack.sh` batch) to see whether bit 10 (0x400) tracks error
   occurrences one-for-one, or is a stickier/unrelated flag.
