# Status 2026-09-28 (cont'd): RESOLVED the wlc_bmac_watchdog vtable mystery - it's the RX DMA ring refill, and this port doesn't have an equivalent

Direct follow-up to notes/34 (which identified the mystery but concluded
resolving it needed open-ended, hours-scale reverse-engineering) and
notes/37 (the pragmatic ACK-ratio watchdog mitigation). This is that
open-ended work, done - and it found something concrete and actionable.

## The chain of evidence

1. Re-examined `wlc_bmac_fifoerrors` (already decompiled) with fresh eyes:
   its own parameter is indexed as `param_1[0x1a]` (offset `0xd0`, an MMIO
   register base used for the DMA0-5 REASON reads) and `*param_1` (offset
   `0`, a back-pointer, passed to `wlc_fatal_error`). `wlc_fatal_error`'s
   parameter in turn has offset `0x10` used for `wl_init()`. This is the
   classic `wlc_hw_info` shape (back-pointer to `wlc_info` at offset 0,
   MMIO base at `0xd0`) - **not** `wlc_info` itself, which is what notes/34
   assumed `wlc_bmac_watchdog`'s `lVar1` was. Getting this base structure
   identity right is what unlocked everything below.

2. `wlc_bmac_attach` (already decompiled) calls
   `plVar14 = wlc_hw_attach(...)` - confirming `plVar14` (the variable
   `wlc_bmac_watchdog`'s mystery offsets `+0x20`/`+0x38` belong to) *is*
   `wlc_hw_info`, built by `wlc_hw_attach`.

3. `wlc_hw_attach` itself (decompiled fresh, only 49 lines) just allocates
   the struct and 3 sub-buffers - doesn't touch `+0x20`/`+0x38`. Went
   looking in `wlc_bmac_attach` instead and found `wlc_hw_set_di`:

   ```c
   void wlc_hw_set_di(long param_1, uint param_2, undefined8 param_3)
   {
       *(undefined8 *)(param_1 + 0x20 + (ulong)param_2 * 8) = param_3;
       *(undefined8 *)(*(long *)(param_1 + 8) + (ulong)param_2 * 8) = param_3;
   }
   ```

   **Exact match**: `wlc_hw_info + 0x20 + index*8` is `wlc_hw_info->di[]`,
   an array of per-DMA-ring `dma_info` object pointers. `di[0]` = offset
   `0x20` (the first, unconditional `wlc_bmac_watchdog` call); `di[3]` =
   offset `0x38` (the second, conditional-on-`+0x84==4` call). `wlc_bmac_attach`
   calls `dma_attach()` for RX first, then several TX priority rings, each
   stored via `wlc_hw_set_di(plVar14, index, result)`.

4. `dma_attach()` (decompiled) allocates the `dma_info` object and sets
   its own offset-0 field (its "self" vtable pointer) to a **named static
   symbol**, `dma64proc` (64-bit DMA path - confirmed as what's actually in
   use on this hardware from earlier dmesg: "64-bit DMA initialized") or an
   unnamed `UNK_00509cb0` table for the 32-bit path.

5. `dma64proc` is a real, addressable, static `r` (read-only data) symbol.
   Wrote a new Ghidra script, `dump_vtable_slots.java`, to read its raw
   bytes directly (no execution needed) and resolve every 8-byte slot from
   `+0x0` to `+0x118` against the known function-address map built earlier
   tonight (`d7b67dc`'s disassembly work). None of the ~36 slots matched a
   *named* function (small `static` helpers, same situation as `phy_info`'s
   own callback table found earlier), but slot `+0xd8` (the exact offset
   `wlc_bmac_watchdog` calls) resolved to a real code address,
   `0x10fe8d`, and slot `+0xa0` (the conditional second call) to `0x1105d7`.

6. Decompiled both directly by address (`decompile_at_addr.java`, already
   in this project's toolkit for exactly this situation):

   - **`+0xd8` (called unconditionally, on `di[0]`)**: a loop that calls
     `osl_pktget()` (allocate a packet buffer), `osl_pktdata()`,
     `osl_dma_map()` (map it for DMA), writes the mapped address into a
     descriptor-ring array at `*(param_1+0x60) + index*8`, and finally
     `osl_writel()`s the updated "last posted index" to a hardware
     register. This is **`dma_rxfill()`** - refilling the RX descriptor
     ring with fresh packet buffers so the DMA engine has somewhere to
     write incoming frames, run as a periodic bulk sweep ("post as many
     buffers as the ring is short by", not one-at-a-time). On allocation
     failure it falls back to a couple of retry helpers before giving up
     on that slot for this pass.
   - **`+0xa0` (called conditionally, on `di[3]`, when `wlc_hw+0x84==4`)**:
     a short reset routine - zeroes a few ring bookkeeping fields, memsets
     the whole descriptor array, calls two sub-helpers with reset-looking
     signatures. Almost certainly `dma_txreset()`/`dma_rxreset()` for a
     specific ring/chip-revision combination this project's hardware
     likely doesn't hit (`+0x84==4` is a chip-generation-dependent branch,
     not confirmed to be our value).

**Conclusion, with actual evidence behind it rather than a guess**: `wlc_bmac_watchdog`
periodically (every ~1.024s, per notes/26/30's independently-measured cadence)
calls `dma_rxfill()` on the RX ring to keep it topped up with fresh buffers,
as a *bulk catch-up sweep* separate from whatever per-frame refill also
happens elsewhere.

## Why this plausibly explains the intermittent RX-reliability problem

b43's own RX handling (`dma.c`'s `dma_rx()`) *only* refills reactively, one
descriptor at a time, immediately after consuming it, via
`setup_rx_descbuffer(ring, desc, meta, GFP_ATOMIC)` - `GFP_ATOMIC` because
this runs in interrupt/softirq context and can't sleep. `GFP_ATOMIC`
allocations draw from a small reserved pool and can fail under memory
pressure without retrying. When that happens here:

```c
err = setup_rx_descbuffer(ring, desc, meta, GFP_ATOMIC);
if (unlikely(err)) {
	b43dbg(ring->dev->wl, "DMA RX: setup_rx_descbuffer() failed\n");
	goto drop_recycle_buffer;
}
...
drop_recycle_buffer:
	b43_poison_rx_buffer(ring, skb);
	sync_descbuffer_for_device(ring, dmaaddr, ring->rx_buffersize);
```

it just re-posts the *same* (poisoned) buffer back to that slot - there is
**no later retry**, ever, for that specific slot, beyond the next time a
frame happens to land there again. b43-src has **no equivalent of wl's
periodic bulk `dma_rxfill()` sweep** - nothing in this port ever goes back
and checks "is every RX slot actually holding a fresh, working buffer" as
an independent, recurring safety net.

This gives a concrete, plausible mechanism for exactly the symptom this
whole investigation has chased: a transient `GFP_ATOMIC` failure (which can
happen under ordinary memory pressure, entirely unrelated to RF conditions)
silently degrades one RX slot with no automatic recovery; if this
accumulates across multiple slots over time, the ring's effective capacity
shrinks, and RX (and therefore the round-trip acknowledgment/DHCP/keepalive
behaviour this project has been measuring all night) degrades
*intermittently and cumulatively*, exactly matching the observed pattern
(random onset, sometimes recovers, sometimes needs a full reload to fully
clear). It also explains why a full `b43_controller_restart()`/`_full()`
(which tears down and recreates the DMA rings from scratch) is at least a
plausible recovery mechanism, even without fixing the underlying gap - a
fresh ring has no poisoned slots.

**Caveat, stated plainly**: this is a strong, well-evidenced hypothesis,
not yet a proven root cause. It hasn't been tested (no code changes made
tonight to verify it), and there could be other contributing factors
(the `+0xa0`/`di[3]` reset path, whatever `+0x84==4` gates, remains
unexplored; this hardware's actual `+0x84` value on-chip is unconfirmed).

## Why not fixed tonight

Porting an equivalent (a periodic "scan the RX ring for poisoned/stale
slots and retry with `GFP_KERNEL` or a fresh allocation attempt" sweep,
callable from the same `pwork_15sec` hook the ACK-ratio watchdog already
uses) is very plausibly safe and low-risk *in principle* - it's ordinary
buffer-management logic, no PHY/RF register writes at all, a completely
different risk category from anything else this project has touched. But:

- DMA ring correctness is genuinely delicate: getting descriptor
  ownership/synchronization wrong (racing the hardware, which may still be
  actively writing to a slot) risks memory corruption or a hard crash, not
  just a missed frame - a materially higher blast radius than the
  read-only-until-threshold ACK-ratio check added earlier tonight.
- This session currently has **no way to test it**: every connection
  attempt for the last ~40 minutes has failed to complete DHCP (notes/37's
  addendum), so there's no way to verify a DMA-ring change actually helps,
  or even that it doesn't regress something, before the session ends.
- Implementing a nontrivial, correctness-critical change to a shared,
  safety-relevant subsystem without any ability to validate it live is
  exactly the situation this project's own established practice (the
  BCMA_IOCTL precedent, notes/18) says to slow down for, not push through
  solo.

## Next steps (in order)

1. **Port a periodic RX-ring health check/refill sweep** for AC-PHY (and
   plausibly all `b43_dma_rx`-using PHY types, though scope to AC first),
   modeled on `dma_rxfill()`'s bulk-catch-up shape: on each `pwork_15sec`
   tick (or a tighter-interval timer, closer to wl's ~1s cadence, if 15s
   proves too coarse), check the RX ring for any slot whose buffer is
   `b43_poison_rx_buffer()`-marked/stale and attempt to replace it - this
   time from a context that CAN use `GFP_KERNEL` (or at least retry more
   patiently than the interrupt-context path can), rather than giving up
   after one `GFP_ATOMIC` failure forever. Needs careful thought about
   descriptor ownership/hardware synchronization before writing any code -
   read `dma.c`'s existing `setup_rx_descbuffer`/`sync_descbuffer_for_*`
   helpers fully first.
2. Test it live, with the user present given the DMA-correctness risk
   category, once a stable connection can be established for testing.
3. If it measurably improves the ACK-ratio-watchdog trigger rate (notes/37),
   that would be strong practical confirmation of this whole hypothesis.
4. The `+0xa0`/`di[3]`/`+0x84==4` path is lower priority - confirm this
   hardware's actual `wlc_hw+0x84` value (if reachable) before assuming
   it's relevant here at all.
5. notes/37's `ac_ackwatchdog` mitigation remains valuable regardless (a
   general safety net for whatever residual reliability issues exist,
   including ones this RX-refill fix might not fully cover) and should stay
   enabled.

No hardware touched tonight for this - pure static analysis (Ghidra
disassembly/decompilation, already-safe/read-only per this project's
established practice for RE work) on top of the disassembly infrastructure
from `d7b67dc`. New scripts committed: `dump_vtable_slots.java`.
