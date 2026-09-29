# Cautionary note: repeated crash-testing may permanently damage BCM4360 silicon

Not a finding from this project - a warning worth keeping visible given
this project's own testing style (frequent live rmmod/insmod, forced
firmware states, one hard freeze already on 2026-09-26).

## Source

github.com/kimptoc/bcm4360-re (cloned locally at ~/src/bcm4360-re,
2026-09-29) - an unrelated, independent BCM4360 reverse-engineering
project. Different specific hardware (MacBook Pro 11,1, PCI id
14e4:43a0) and a different approach (patching brcmfmac/FullMAC to speak
BCDC to the chip's own ARM firmware, not a b43/SoftMAC port like ours) -
none of their protocol-level findings transfer directly. Their
conclusion, however, is a direct warning:

> Investigations through Phases 5 and 6 reached strong evidence that this
> project's BCM4360 sample has been degraded at the silicon level by the
> cumulative crash testing the project conducted... The proprietary `wl`
> driver consistently fails at `wlc_attach` with `code 1` regardless of
> kernel version, mitigation flags, IOMMU settings, or module parameters.

Their own vendor `wl` blob - previously confirmed working on the same
hardware under Debian - stopped attaching at all after enough repeated
firmware crashes/wedges, with software causes (kernel, mitigations,
IOMMU) ruled out one by one. Their working theory is cumulative physical
damage that `lspci`-level checks can't see. Project is now on hold,
pending a replacement chip.

## Why this matters here

This project has already had one hard freeze (notes/07, 2026-09-26,
BCMA_IOCTL PHY-bandwidth write on a running+transmitting core) and, as
of tonight (notes/57-58), routinely puts the chip through hundreds of
failed MAC-suspend states per boot while investigating the CRS/TXF
carrier-sense lockup. None of that is known to have damaged this chip -
but the kimptoc project is a concrete, independent example of a BCM4360
sample degrading after exactly this kind of repeated hard-crash testing,
on hardware that used to work fine.

## Practical takeaway

- Don't treat "the module reloads and the machine didn't freeze" as
  proof nothing was harmed - kimptoc's degradation wasn't visible at
  that level either until `wl` itself stopped attaching.
- Prefer reboots over repeated live crash/reload cycling when iterating
  on anything that can leave the chip in a bad firmware state, especially
  once a session has already produced hard-freeze-adjacent symptoms.
- If `wl` (the known-good baseline) ever starts failing to attach on
  this hardware with no software explanation, treat that as a serious
  signal, not a random glitch - it was kimptoc's key discriminator.
