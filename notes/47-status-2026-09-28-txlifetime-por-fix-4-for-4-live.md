# Status 2026-09-28 (cont'd): re-enabled wl's SHM 0x7C entry in the POR table - 4/4 clean connections, fix is now permanent

Direct follow-up to notes/45/46. notes/46 confirmed `ac_txlifetime=800` (a
debug override param) 3/3 live. With that confidence, restored the actual
`b43_ac_por_shm[]` entry wl's trace captured (`{ 1, 0x007c, 0x0320 }`,
previously disabled to `0xffff` by the flawed bisect described in
notes/45), so the fix applies with the project's standard load command
(`ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1`) and needs no override param.

Verified live: fresh load (no `ac_txlifetime` param), `shm` debugfs read
back `007c 0320` from the POR table alone, then a 4th independent
connection trial: `nmcli connection up` succeeded on the first try with a
full IPv4 DHCP lease, 0/90 TX frames `supp=5`, 75/90 acked (83%).

**Running total: 4/4 clean first-try connections (2 via the `ac_txlifetime`
override, 2 via the restored POR entry), 0 total `supp=5` events across
382 combined TX statuses, versus the project's entire prior history of
auth timeouts and IPv6-only connections.**

The `ac_txlifetime` module param (notes/45) is left in place as a live
override/experimentation knob (default -1, no effect); the real fix is now
the POR table entry, matching wl exactly.

## Current state

Chip loaded with the standard params, connected, IPv4+IPv6 both up. USB
backup link confirmed working throughout every trial tonight.

## Still open (unchanged from notes/46)

- Post-association ACK-ratio degradation (notes/34/38/39) is a separate,
  still-unfixed mechanism; the existing ACK-ratio watchdog (notes/37) is
  expected to keep catching it.
- The `ieee80211_reconfig`/`ieee80211_del_chanctx` mac80211 WARNs seen
  during that watchdog's restart recovery (notes/46) are a concrete,
  not-yet-investigated lead.
- Channel-1 CCK corruption (notes/45 section 5) is unrelated to tonight's
  fix and remains unexplained; moot for now since the router is pinned to
  channel 6.
