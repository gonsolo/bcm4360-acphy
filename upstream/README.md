# AC-PHY series for b43 (RFC, not sent)

13 patches on top of mainline b43 as of v7.3-rc5, one commit each, every one compile-tested against the 7.2.9 headers.
Nothing here has been sent anywhere. There is no Signed-off-by yet: the sender adds their own.

| # | patch |
|---|---|
| 1 | fix use-after-free in b43_bcma_remove() (Fixes:, Cc: stable) |
| 2 | reprogram the MAC filter after an interface restart |
| 3 | 64-bit DMA engines whose index registers hold bus addresses (+ burst/prefetch bits) |
| 4 | retry RX buffer refills that failed under memory pressure |
| 5 | MAC core setup for core revisions 40 and 42 |
| 6 | address match table, templates and beacons for the AC microcode |
| 7 | radio 2069 and AC-PHY tables (data) |
| 8 | AC-PHY init and 2.4 GHz channel switching |
| 9 | TX descriptor and TX status |
| 10 | RX header handling |
| 11 | 5 GHz, 80 MHz and VHT |
| 12 | A-MPDU |
| 13 | enable the AC-PHY support (drop BROKEN) |

## Reading it

- **git**: `cd ~/b43-upstream; git log --stat series`, `git show series~5`, branch `final` is the target tree, the first commit is stock b43.
- **vim / pager**: `series/0000-cover-letter.patch` ... `series/0013-*.patch` (git format-patch output, in order).
- **b4**: `b4 am -m b43-ac-series.mbox -o /tmp/out` (it lists the 13 patches and writes an mbx for `git am`).
  Note: b4 asks lore.kernel.org whether the thread exists; nothing is uploaded except the message ids.
- **mutt / any mail reader**: open `b43-ac-series.mbox`.

## Regenerating

`tools/upstream/merge.sh` (b43-src -> v7.3-rc5), `clean.sh` (debug code, private references, comment polish), commit the result to the
`final` branch of ~/b43-upstream, then `python3 tools/upstream/cut.py ~/b43-upstream <kernel -dev path>` and `git format-patch`.

## Before it can be sent

- the provenance wording (PROVENANCE-REVIEW.txt lists the comments; the cover letter has a placeholder),
- agreement with Alessio Ferri, who has a series for the same hardware (several blocks follow his tree, credited in comments),
- checkpatch: 0 errors; warnings are long data lines in patch 7 and comment style,
- the GPIO pattern of patch 5 is the MacBookAir6,1's; other boards may need other values.
