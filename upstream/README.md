# AC-PHY series for b43 (RFC, not sent)

**Current: `split/`** (notes/166): 14 patches in four series after Alessio Ferri's plan, on top of mainline b43 as of v7.3-rc5 plus the
use-after-free fix that was sent separately. Nothing here has been sent except that fix. No Signed-off-by yet: the sender adds their own.

| series | dir | patches |
|---|---|---|
| A generic | `split/A/` | MAC filter after restart, 64-bit DMA engines with bus-address index registers, RX refill retry |
| B core 40/42 | `split/B/` | DMA burst bits, MAC core setup, address match table/templates/beacons |
| C formats | `split/C/` | 11ac chanspec, TX descriptor/status, RX header, A-MPDU |
| D PHY | `split/D/` | radio 2069 + tables, PHY init + 2.4 GHz, 5 GHz/80 MHz/VHT, drop BROKEN |

Each directory has the cover letter, the patches and `series-<X>.mbox`. Read: `git log --stat series2` in ~/b43-upstream (branch `final2` is the
end state), `b4 am -m split/A/series-A.mbox -o /tmp/out`, or the files.
Regenerate: edit `final2`, `REMOTE=pampelmuse python3 tools/upstream/cut2.py ~/b43-upstream <kernel -dev path>` (compile test per patch),
`python3 tools/upstream/format2.py ~/b43-upstream upstream/split`.

The older 13-patch RFC (`series/`, `b43-ac-series.mbox`, `PROVENANCE-REVIEW.txt`) is what Alessio received; it is kept for reference.

## Before it can be sent
- provenance wording agreed with Alessio (the cover letter of series D has a placeholder),
- series A first; B to D follow once it is merged,
- checkpatch: no errors besides the missing Signed-off-by; warnings are block comment style and long data lines.
