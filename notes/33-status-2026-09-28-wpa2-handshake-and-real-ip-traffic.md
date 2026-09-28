# Status 2026-09-28: WPA2 handshake completes, DHCP, real ping over b43

This is the milestone the whole project has been aiming at: **b43, with the
AC-PHY port, now does a full association + WPA2 4-way handshake + DHCP + IP
ping through the actual BCM4360 hardware**, with the AP believing every step
of it (not a loopback/monitor artifact - `tcpdump` on the wire shows the
gateway's real ICMP replies arriving on `wlp3s0b1`, ~1.7-3ms RTT).

Four separate bugs had to be fixed to get here, on top of everything already
committed (channel-6 tuning, the 4 VCO-cal skips, `SHM_SH_CHAN`, and the 40
conflicting OFDM PHY por entries from earlier tonight). All four have the
same shape: **wl's channel-1 first-boot SHM/RAM snapshot (`ac_por`) contains
values that are correct as a static description of "post-boot idle state"
but wrong to *replay*, because the real driver never replays them - it
computes them at runtime from state our port doesn't have (or they were a
one-off command, not persistent state).**

## Bug 1: AC key-table "clear" zeroed the rate maps and ucode state

`b43_security_init()` reads the legacy KTP (key table pointer) word from SHM
0x56 and calls `b43_clear_keys()`, which zeroes SHM 0x000-0x3a0 based on that
pointer. On rev 40+ (AC) ucode there is no key table at that legacy address -
the word reads 0 - so this "cleared the key table" by zeroing everything from
0x000 to 0x3a0, including the OFDM/CCK basic-rate maps (0x1c0-0x23f) and a
chunk of ucode's own working state. This ran on **every** `b43_wireless_core_init()`,
i.e. every `ip link set up` / interface restart, not just first load.

This was the root cause of two symptoms chased over the last two sessions:
RX going dead after any interface restart, and `iw scan` finding nothing in
managed mode (notes/24's dead end). AC has no hardware-crypto key table yet
(`nohwcrypt=1` is required), so the fix is simply to never touch key memory
for AC:

```c
static void b43_security_init(struct b43_wldev *dev)
{
	if (dev->phy.type == B43_PHYTYPE_AC)
		return;
	...
}
```

and `b43_op_set_key()` now returns `-EOPNOTSUPP` for AC unconditionally (not
just under `nohwcrypt`), so loading without `nohwcrypt=1` can't corrupt SHM
either.

## Bug 2: `configure_filter` didn't reprogram MACCTL after a restart

`b43_op_start()` unconditionally zeroes `wl->filter_flags` on every start
(by design, so stale state from a previous core doesn't leak). But
`b43_op_configure_filter()` only calls `b43_adjust_opmode()` (which writes
MACCTL) when mac80211's own `changed` bitmask is nonzero - and mac80211
computes that bitmask against *its own* cached filter flags, which didn't
change across the restart. So after a restart the hardware kept whatever
MACCTL bits were zeroed at start, never getting the real filter reprogrammed.
Fixed by also comparing against what we actually last programmed:

```c
if (wl->filter_flags != *fflags)
	changed |= wl->filter_flags ^ *fflags;
wl->filter_flags = *fflags;
```

## Bug 3: SHM 0x5c (byte 0xb8) is a ucode *command*, not persisted state

Ucode address 0x0CA3 (`wlc_bmac_watchdog`-adjacent code, see notes/12/13)
reads SHM word 0x5c and, if nonzero, fires a CTS-to-self with that value as
the NAV duration - a one-shot command left over from some wl calibration
step, not a piece of state that's supposed to persist. Both `ac_replay`
(captured mid-run on channel 6, value `0x7148` = 29 ms) and `ac_por`
(captured at first boot on channel 1, same value) had it, so every load
fired a bogus CTS-to-self with a zero-rate PLCP, which the PHY rejected
as a `txphyerr` (2 registers - a false positive contribution to the
`txphyerr`/`txcts` counters seen throughout notes/12-19). Skipped in both
tables now (`{ 0xffff, 0x00b8, ... }`).

## Bug 4: the per-rate SHM blocks (word 1) were zeroed - no valid ACK PLCP

This was the one that actually blocked every ACK. SHM words 0x98c-0xa9b hold
per-rate blocks (8 words per OFDM rate at 0x980+n\*8-ish, 4 words per CCK
rate) that the rate maps (`0x1c0`/`0x1e0` OFDM direct/basic, `0x200`/`0x220`
CCK direct/basic) point into; ucode's ACK/CTS-generation path
(`0x0C2A`/notes/12-13's txphyerr handler, and separately `0x08AE` for
Probe-Response) reads *word 1* of each block directly into
`IHR_TxPlcpLSig0/HtSig0`/CCK SIGNAL to build the PLCP header for its own
autonomous replies.

initvals sets these up correctly (confirmed by dumping the block right after
`ac_replay=1 ac_por=0` load: e.g. word 0x98e = `0x01cb`, a real OFDM L-SIG).
But `ac_por`'s first-boot SHM capture has **zero** at the exact same words
(`0x98e = 0x0000`, `0x9aa = 0x0000`, ... one pair per rate, 9 rates total) -
apparently wl computes these on the fly right before it needs them and they
just hadn't been written yet at the point of the first-boot capture. Applying
`ac_por` (needed for the channel-6 radio/PHY/table fix) clobbered them back
to zero, and every firmware ACK's PLCP then had rate field 0 -> `txphyerr`,
`txcts`/`txctsfrm` never incrementing for real CTS but a phantom cost on
every RX that should have gotten an ACK. This matches notes/13's diagnostic
record byte-for-bit: `TXE_PHYCTL=0x0045`, `HT-SIG0=0x01C0` (a bogus non-zero
value happening to be picked up from the wrong SHM word) captured on a
guaranteed-to-fail ACK.

Fixed by excluding the whole 0x98c-0xa9b range from `b43_ac_por_shm[]`'s
apply loop (leaving the two entries wl *does* still want changed at
0x0a2c/0x0a2e - those are outside the per-rate-block range that matters,
turned out to be inside it actually, see below - kept explicit `0xffff`
markers there too since they duplicate initvals's own value 1:1, no
information lost by skipping them):

```c
if (off >= 0x098c && off < 0x0a9c)
	continue;
```

Verified: dumped the whole block after load with the fix, it's now
byte-for-byte identical to the `ac_por=0` (initvals-only) case.

## Result

With all four fixes:

- RX survives repeated interface restarts (previously died after the first).
- `iw scan` in managed mode lists real APs (previously empty).
- `nmcli con up` on a WPA-PSK profile completes: auth -> assoc -> **WPA:
  Key negotiation completed ... CTRL-EVENT-CONNECTED** -> DHCPv4 lease
  (192.168.0.x) and DHCPv6/SLAAC addresses assigned.
- `ping -I wlp3s0b1 192.168.0.1`: 4/5 replies, RTT 1.7-3.1ms.
- `ping -I wlp3s0b1 8.8.8.8`: real replies confirmed on the wire by tcpdump
  (request/reply pairs, ~14ms RTT) but `ping` itself reports 0 received -
  this is a **host routing/socket artifact**, not a driver bug: this test
  box has two simultaneous default routes to the same LAN (the USB stick at
  metric 600, b43 at metric 900), and something in that dual-default-route
  setup stops the raw ping socket bound to `wlp3s0b1` from matching replies
  that did physically arrive on that interface. rp_filter is loose (2) and
  not the cause; no martian-packet or nftables drop was found. Not
  investigated further tonight since the gateway ping (single subnet, no
  routing ambiguity) already proves real bidirectional IP delivery through
  b43.

One rough edge seen during testing: the first WPA2 handshake completed, then
5 seconds later `wpa_supplicant` logged a second "Key negotiation completed"
followed immediately by `4WAY_HANDSHAKE_TIMEOUT` and a reconnect (which
itself then succeeded cleanly). Possibly a GTK rekey or a duplicate message
4 that confused state on either side - worth watching for on the next
connection rather than assuming it's fixed; the retry path clearly works,
which is what matters for now.

## Corrections to earlier notes

None new this session, but see notes/32 (already flagged there) for the
radiotap/`SHM_CHAN` correction, and notes/31 for the sweep-decompilation
correction. This note's bugs 1-4 supersede the "?" left in notes/29 about
why ACKs still weren't reliable after the desense/hwaci watchdog analysis -
the watchdog was never the blocker; the SHM state was.

## Still open

- The 4-way-handshake-timeout-then-reconnect blip above.
- Confirm stability over a longer connected session (sustained ping, actual
  data transfer, DHCP renewal).
- Rates 11/24 Mbps "6 of 10 attempts" oddity (notes/12-ish, still
  unexplained, lower priority now that association works).
- Watchdog porting (`wlc_bmac_watchdog`/`wlc_phy_watchdog`, decompiled but
  not ported) - matters more now that longer-running sessions are possible.
- The loft-comp question remains stashed (`git stash@{0}`), rebuild blocked
  by the permission classifier, left for the user as noted previously.
