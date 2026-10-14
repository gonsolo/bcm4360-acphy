# 167: the long-suspend failure is fixed by Alessio's BCMA patch; use-after-free patch taken; series A trimmed

## Use-after-free patch accepted
`wifi: b43: fix use-after-free in b43_bcma_remove()` is in wireless-next: commit c6c8bc355657115664131b38c53c5ddf7d93b072
(https://git.kernel.org/pub/scm/linux/kernel/git/wireless/wireless-next.git/commit/?id=c6c8bc355657115664131b38c53c5ddf7d93b072).
Sent 2026-10-13 (notes/163).

## Long suspend: reproduced, cause confirmed
- Lid closed 00:59, opened about 12:08 (11 h): `HT force timeout`, `PLL enable timeout`, `Microcode not responding` at resume; `b43-resume.service` ran
  `b43_load_until_connected.sh` 12 tries with the new dead-chip evidence and `b43_pci_reset.sh` between tries ("reset" = PCI bus reset): **the bus reset does not
  revive the chip** (every try dead=6-8). The stick kept the network. (notes/164 recovery idea: wrong, a bus reset is not enough.)
- With the chip still dead, loading Alessio's bcma + b43 (`tools/try_alessio_driver.sh`, c452fdd, built for 7.2.10) brought it up at once: no timeouts, scanned,
  associated, ARP answered. Then `try_alessio_driver.sh restore` (stock bcma + our b43): clean on the first try. So the chip only needs its PMU PLL programmed again.
- Why: his bcma patch adds BCM4352/BCM4360 cases to `bcma_pmu_pll_init()` (PLLCTL2 = 0x0c31, PLLCTL3 = 0x100e, then PLL_UPD; the values the stock wl writes
  at attach); stock bcma has no case for this chip. After power loss the PLL control registers are at their ROM values and nobody writes them. On a cold boot the
  Apple EFI has done it; after S3 `bcma_bus_resume()` -> `bcma_core_chipcommon_init()` -> `bcma_pmu_init()` -> `bcma_pmu_pll_init()` runs, so the same patch covers resume.
- To do here: get the bcma patch onto this laptop (an `extra/bcma.ko` with his patch next to the b43 module in configuration.nix, or load `ale-bcma-<ver>.ko` in
  `tools/b43_boot.sh` as a stopgap). `b43_pci_reset.sh` stays as a harmless extra step but does not fix it.

## Alessio's replies to the mail and series A (2026-10-14)
- c452fdd results fine; his remark on CCMP (key lost in the MAC on the reset path, mac80211 not asking to reprogram it) does not apply here: software crypto.
- The cut and the gating (core revision for the core, ucode revision for layouts): "Yes". For B, C and D the two code bases have to be merged first, so one code base
  generates them all.
- Series A: "You can send it for both" (he is reviewing my patches). Provenance: A cites brcmsmac (same mechanism); B, C, D cite the captures and hardware tests.
- Patch 1: shorten the story, it belongs in the cover letter. Patch 2: he tested it on a Wi-Fi N core with a 64-bit DMA engine in his router, still works.
- **Patch 3 (RX refill retry): "are you really sure about the problem it solves? I didn't encounter it."** Honest answer: no. It came from reading the vendor driver's
  periodic `dma_rxfill()` (notes/38/39) as a plausible mechanism; the failure was never observed (`recovered N stuck RX` has never been logged, no `setup_rx_descbuffer() failed`
  in any journal). Dropped from series A; kept as the held-back last patch (`upstream/split/X/`).

## What changed in the series
14 commits on `series2`: A = 1-2 (MAC filter, DMA64), B = 3-5, C = 6-9, D = 10-13, X = 14 (retry, held back). `tools/upstream/cut2.py` remaps the old numbering
(RX retry last), `format2.py` writes A, B, C, D and X; patch 1 has a short message, patch 2 cites brcmsmac's `_dma_descriptor_align()`, the series A cover carries the story.
`upstream/split/A-list/` is series A for the list: 2 patches + cover, signed off. `tools/upstream/send_series_a.sh [--dry-run]` sends it to linux-wireless
(Cc Johannes Berg, b43-dev, Michael Buesch, Alessio Ferri, linux-kernel); the dry run was checked, nothing was sent. The Signed-off-by is the sender's decision.
