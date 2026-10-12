#!/usr/bin/env bash
# Build Alessio Ferri's b43-ac-wip (patches 0001-0003) against kernel v7.2 sources as out-of-tree
# bcma.ko + b43.ko for the running kernel's -dev tree. Output: b43-src-builds/ale-{bcma,b43}-<ver>.ko
# ALE_DMA=1 adds our DMA control bits and intrcvlazy0 (output ale-b43-<ver>-dma.ko).
# FORENSICS=1 adds per-function and per-register log lines (hang forensics); default is the plain build.
# usage: tools/build_alessio_driver.sh /nix/store/...-linux-X.Y.Z-dev   (needs ~/src/linux with tag v7.2,
#        ~/src/b43-ac-wip-latest)
set -eu
DEV=${1:?usage: $0 /nix/store/...-linux-X.Y.Z-dev}
P=$(cd "$(dirname "$0")/.." && pwd)
VER=$(ls "$DEV/lib/modules"); K=$DEV/lib/modules/$VER/build
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
(cd ~/src/linux && git archive v7.2 drivers/bcma drivers/net/wireless/broadcom/b43 include/linux/ssb \
	include/linux/bcma include/linux/bcm47xx_sprom.h drivers/firmware/broadcom/bcm47xx_sprom.c) | tar -x -C "$T"
cd "$T"
for p in ~/src/b43-ac-wip-latest/patches/000[123]*.patch; do patch -p1 --no-backup-if-mismatch < "$p" >&2; done
sed -i 's|<asm/unaligned.h>|<linux/unaligned.h>|' drivers/net/wireless/broadcom/b43/*.[ch]
if [ -n "${FORENSICS:-}" ]; then   # FORENSICS=1: hang forensics, floods the log and slows every access
# trace every B43_AC_FN() function entry to the kernel log (hang forensics; pr_emerg makes journald fsync each line)
sed -i 's/^#define B43_AC_FN() do { } while (0)/#define B43_AC_FN() do { if (strncmp(__func__, "b43_actab", 9)) { pr_emerg("ACFN %s\\n", __func__); mdelay(30); } } while (0)/' drivers/net/wireless/broadcom/b43/phy_ac.h
# hang forensics: log every PHY/radio port access (0x3e0-0x3f4) before it happens, with a delay for journald
perl -0pi -e 's|(static inline u16 b43_read16\(struct b43_wldev \*dev, u16 offset\)\n\{\n)|$1\tif (offset >= 0x3e0 \&\& offset < 0x3f4) { pr_emerg("RD %x\\n", offset); mdelay(8); }\n|; s|(static inline void b43_write16\(struct b43_wldev \*dev, u16 offset, u16 value\)\n\{\n)|$1\tif (offset >= 0x3e0 \&\& offset < 0x3f4) { pr_emerg("WR %x=%x\\n", offset, value); mdelay(8); }\n|' drivers/net/wireless/broadcom/b43/b43.h
fi
# ALE_DMA=1: our DMA findings on top of his tree: burst/prefetch bits in the TX and RX control words, intrcvlazy0 (notes/143)
if [ -n "${ALE_DMA:-}" ]; then
	D=drivers/net/wireless/broadcom/b43
	perl -0pi -e 's/(\t\t\tenable = B43_DMA64_TXENABLE;\n)/$1\t\t\tvalue |= 0x03780040;\n/; s/(B43_DMA64_RXFROFF_SHIFT\);\n\t\t\tvalue \|= B43_DMA64_RXENABLE;\n)/$1\t\t\tvalue |= 0x036c0000;\n/' $D/dma.c
	grep -q 0x03780040 $D/dma.c && grep -q 0x036c0000 $D/dma.c || { echo "ALE_DMA: dma.c hunks did not apply" >&2; exit 1; }
	perl -0pi -e 's/(\tb43_write32\(dev, B43_MMIO_DMA5_IRQ_MASK, 0x0000DC00\);\n)/$1\tif (dev->phy.type == B43_PHYTYPE_AC)\n\t\tb43_write32(dev, 0x100, 1 << 24);\n/' $D/main.c
	grep -q "0x100, 1 << 24" $D/main.c || { echo "ALE_DMA: main.c hunk did not apply" >&2; exit 1; }
fi
# forced includes: the patched ssb headers must win over the kernel's (regs first, ssb.h includes it)
INC="-include $T/include/linux/ssb/ssb_regs.h -include $T/include/linux/ssb/ssb.h -include $T/include/linux/bcm47xx_sprom.h"
nix-shell -p gnumake gcc --run "make -C $K M=$T/drivers/bcma modules KCFLAGS='$INC' >/dev/null; \
	make -C $K M=$T/drivers/net/wireless/broadcom/b43 modules CONFIG_B43_PHY_AC=y KCFLAGS='$INC -DCONFIG_B43_PHY_AC=1 -DALLOW_24=true' >/dev/null"
mkdir -p "$P/b43-src-builds"
cp drivers/bcma/bcma.ko "$P/b43-src-builds/ale-bcma-$VER.ko"
cp drivers/net/wireless/broadcom/b43/b43.ko "$P/b43-src-builds/ale-b43-$VER${ALE_DMA:+-dma}.ko"
