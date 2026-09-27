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

## Next steps

1. Take 2-3 more samples (reset flag via debugfs, don't need a reboot) to
   see whether HT-SIG0=0x1C0 (or a similar HT-format signature) shows up
   consistently, which would make "why is an HT-format frame involved in
   this specific hardware fault" a concrete, checkable question against our
   own PHY/rate-table setup.
2. Check whether the AP-probe-request-never-acked symptom (210 = 30x7 retries,
   zero macstat activity in that window) is the SAME root cause or a
   separate issue - if our own outgoing frames are also failing to reach
   the AP some of the time, that's new and wasn't part of the original "host
   TX is 100% reliable" characterization.
3. Find more code that touches the extended-IHR port (grep the full
   disassembly for other `CALLS 0105`/`CALLS 0109` sites) to build up a
   table of known SCR21 address values and what they read/write, which
   would help identify what 0x2000's bit 13 actually means.
