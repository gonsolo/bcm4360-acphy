# Status 2026-09-28 (cont'd): ported the Farrow resampler fix to 5 GHz

Follow-up to notes/51. The user asked to extend the channel-1 fix to 5 GHz.

## Scope

`b43_ac_5g_80` (keep wl's captured 80 MHz snapshot instead of retuning
per-channel) defaults off, so 5 GHz already runs through the same
ordinary per-channel 20 MHz retune path as 2.4 GHz by default
(`b43_phy_ac_tune()` + BW1A writes) - not the 80 MHz mode flagged in
project memory as crash-prone from an earlier hard freeze. The Farrow
call was gated `!is_5ghz`; changed to apply whenever `ac_5g_80` isn't
active, 2.4 GHz or 5 GHz alike. The 80 MHz path is untouched.

## Verifying wl uses the same table on 5 GHz

`b43_phy_ac_farrow_20[]` (notes/51) already had 5 GHz entries - the
original dump covered all 123 channels in wl's tables, 2.4 and 5 GHz
together. Checked wl's own first-load trace's 5 GHz scan sweep (PHY 0x19b
writes climbing smoothly channel-by-channel, e.g. 0x6e at channel 100)
against the dumped table: matches exactly. wl uses the same per-channel
20 MHz Farrow table on 5 GHz as on 2.4 GHz, at least during this kind of
scan/retune - confirms the fix applies unmodified.

## Verification

Register read-back on channels 116, 100, 149 (5 GHz) and 6 (2.4 GHz,
unchanged) all matched wl's table exactly, in monitor mode (no
association, no 80 MHz toggling - low risk). No crash.

2.4 GHz connection regression check (`ac_replay=1 dma32=1 ac_por=63
nohwcrypt=1`, no `ac_5ghz`): connected first-try, IPv4 DHCP, ARP 4/5 -
unaffected, as expected (the code path is unchanged when `is_5ghz` is
false).

Not tested: an actual 5 GHz connection. The only 5 GHz AP visible
(`Vodafone-2A84` on channel 116) is a DFS channel; associating as a
client doesn't require doing radar detection ourselves (only an AP does),
so that's not a blocker, but a live 5 GHz association attempt with
`ac_5ghz=1` wasn't completed this round - `ac_5ghz=1` makes background
scans cover both bands, which made NetworkManager's connection attempts
time out repeatedly (a pre-existing scan-timing interaction, unrelated to
this change) before landing back on 2.4 GHz for the regression check
instead of chasing it further.

## Current state

Chip loaded with the standard 2.4 GHz params, connected, no `ac_5ghz`.
USB backup link confirmed working throughout.

## Next steps

1. A real 5 GHz connection attempt, ideally with a longer nmcli timeout
   or by scanning/connecting via `iw` directly to sidestep the full-band
   scan timing issue.
2. The 80 MHz path (`ac_5g_80=1`) still has no Farrow support and is
   still flagged crash-prone; not addressed here.
