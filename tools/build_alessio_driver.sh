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
# ALE_CCK1=1: CCK frames on the lowest TX core only (his descriptor sends them on all cores, phyctl 00c4, and the ucode reports a PHY TX error)
if [ -n "${ALE_CCK1:-}" ]; then
	perl -0pi -e 's/(txcore\[B43_PHY_AC_TXCORE_CCK\] = )mask;/$1mask & -mask;/' drivers/net/wireless/broadcom/b43/phy_ac.c
	grep -q "mask & -mask;" drivers/net/wireless/broadcom/b43/phy_ac.c || { echo "ALE_CCK1: phy_ac.c hunk did not apply" >&2; exit 1; }
fi
# ALE_CCKPO0=1: CCK frames with power offset 0 in PHY control word 1, as our descriptor sends them
if [ -n "${ALE_CCKPO0:-}" ]; then
	perl -0pi -e 's/ac->rate_po_cck;/0;/' drivers/net/wireless/broadcom/b43/xmit.c
	grep -q "ac_po_zero\|ofdm ? ac->rate_po_ofdm\[b43_txhdr_ac_rate_idx(rate)\] :\n\t\t    0;" drivers/net/wireless/broadcom/b43/xmit.c || grep -Pzq "rate_idx\(rate\)\] :\n\t\t    0;" drivers/net/wireless/broadcom/b43/xmit.c || { echo "ALE_CCKPO0: xmit.c hunk did not apply" >&2; exit 1; }
fi
# ALE_DUMP=1: on the first PHY TX fault on channel 6 log every PHY/radio register of wl's final ch6 state (tools/ale_dump.h)
if [ -n "${ALE_DUMP:-}" ]; then
	D=drivers/net/wireless/broadcom/b43
	cp "$P/tools/ale_dump.h" $D/ale_dump.h
	perl -0pi -e 's/(static void b43_ac_report_phy_txerr\(struct b43_wldev \*dev\)\n)/#include "ale_dump.h"\nvoid b43_ale_tbl_dump(struct b43_wldev *dev);\nstatic void b43_ale_dump(struct b43_wldev *dev)\n{\n\tstatic bool done;\n\tunsigned int i;\n\n\tif (done || dev->phy.channel != 6)\n\t\treturn;\n\tdone = true;\n\tb43_mac_suspend(dev);\n\tfor (i = 0; i < ARRAY_SIZE(ale_phy); i++)\n\t\tpr_info("ALEDUMP P %04x %04x\\n", ale_phy[i], b43_phy_read(dev, ale_phy[i]));\n\tfor (i = 0; i < ARRAY_SIZE(ale_radio); i++)\n\t\tpr_info("ALEDUMP R %04x %04x\\n", ale_radio[i], b43_radio_read(dev, ale_radio[i]));\n\tb43_ale_tbl_dump(dev);\n\tb43_mac_enable(dev);\n}\n\n$1/; s/(static void b43_ac_report_phy_txerr\(struct b43_wldev \*dev\)\n\{\n)/$1\tb43_ale_dump(dev);\n/' $D/main.c
	printf %s '
#include "ale_dump.h"
void b43_ale_tbl_dump(struct b43_wldev *dev)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(ale_tbl); i++) {
		u32 v = 0;

		b43_actab_read_bulk(dev, ale_tbl[i].id, ale_tbl[i].off, ale_tbl[i].w, 1, &v);
		pr_info("ALEDUMP T %u %u %x\n", ale_tbl[i].id, ale_tbl[i].off, v);
	}
}
' >> $D/phy_ac.c
	grep -q "b43_ale_dump(dev);" $D/main.c || { echo "ALE_DUMP: main.c hunk did not apply" >&2; exit 1; }
fi
# ALE_FIX1=<letters>: on 2.4 GHz, write wl's values of the config registers that differ, at the end of every channel switch:
# a 0x0003=0, b 0x0402=2, c 0x0910-0x0913=0x0101, d 0x073b/0x093b/0x173b=0x18 (ALE_FIX1=1 means all four)
if [ -n "${ALE_FIX1:-}" ]; then
	Q='"'; F=$ALE_FIX1; [ "$F" = 1 ] && F=abcd
	W=""
	case $F in *a*) W="$W\\t\\tb43_phy_write(dev, 0x0003, 0x0000);\\n";; esac
	case $F in *b*) W="$W\\t\\tb43_phy_write(dev, 0x0402, 0x0002);\\n";; esac
	case $F in *c*) W="$W\\t\\tfor (fi = 0; fi < 4; fi++)\\n\\t\\t\\tb43_phy_write(dev, 0x0910 + fi, 0x0101);\\n";; esac
	case $F in *e*) W="$W\\t\\tb43_radio_write(dev, 0x000e, 0x0001);\\n\\t\\tb43_radio_write(dev, 0x020e, 0x0001);\\n\\t\\tb43_radio_write(dev, 0x0017, 0x0011);\\n\\t\\tb43_radio_write(dev, 0x0217, 0x0011);\\n";; esac
	case $F in *f*) W="$W\\t\\tb43_radio_write(dev, 0x0024, 0x0303);\\n\\t\\tb43_radio_write(dev, 0x0224, 0x0003);\\n\\t\\tb43_radio_write(dev, 0x0225, 0x0000);\\n\\t\\tb43_radio_write(dev, 0x0113, 0x0000);\\n";; esac
	case $F in *g*) W="$W\\t\\t{\\n\\t\\t\\tstatic const u16 t2r[16] = { 0xb3, 4, 3, 6, 5, 0, 2, 1, 8, 0x2a, 0xf, 0, 0xf, 0x2b, 0x1f, 0x1f };\\n\\t\\t\\tstatic const u16 d80[16] = { 1, 8, 4, 2, 2, 1, 3, 4, 6, 4, 0xa, 4, 2, 1, 1, 1 };\\n\\n\\t\\t\\tb43_actab_write_bulk(dev, 7, 0x10, 16, 16, t2r);\\n\\t\\t\\tb43_actab_write_bulk(dev, 7, 0x80, 16, 16, d80);\\n\\t\\t}\\n";; esac
	case $F in *h*) cp "$P/tools/ale_fixh.h" drivers/net/wireless/broadcom/b43/ale_fixh.h; W="$W\\t\\t{\\n#include ${Q}ale_fixh.h${Q}\\n\\t\\t\\tunsigned int hi;\\n\\n\\t\\t\\tfor (hi = 0; hi < ARRAY_SIZE(ale_fixh); hi++)\\n\\t\\t\\t\\tb43_phy_write(dev, ale_fixh[hi][0], ale_fixh[hi][1]);\\n\\t\\t}\\n";; esac
	case $F in *d*) W="$W\\t\\tb43_phy_write(dev, 0x073b, 0x0018);\\n\\t\\tb43_phy_write(dev, 0x093b, 0x0018);\\n\\t\\tb43_phy_write(dev, 0x173b, 0x0018);\\n";; esac
	W="$W" perl -0pi -e 'BEGIN{ $w = $ENV{W}; $w =~ s/\\t/\t/g; $w =~ s/\\n/\n/g } s/(\tdev->phy.ac->txpwr_adjust_due = true;\n\tdev->phy.ac->tuned = true;\n)(\treturn 0;)/$1\tif (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {\n\t\tunsigned int fi = 0;\n\n$w\t\t(void)fi;\n\t}\n$2/' drivers/net/wireless/broadcom/b43/phy_ac.c
	grep -q "(void)fi;" drivers/net/wireless/broadcom/b43/phy_ac.c || { echo "ALE_FIX1: phy_ac.c hunk did not apply" >&2; exit 1; }
fi
# ALE_GPIO=1: the MacBookAir6,1 front-end pins as our driver drives them (GPIO 0,1,2,5,7 host-driven, 1+2 high)
if [ -n "${ALE_GPIO:-}" ]; then
	perl -0pi -e 's/(\tbcma_chipco_gpio_outen\(cc, leds, leds\);\n)/$1\tbcma_chipco_gpio_control(cc, 0xa7, 0);\n\tbcma_chipco_gpio_out(cc, 0xa7, 0x06);\n\tbcma_chipco_gpio_outen(cc, 0xa7, 0xa7);\n/' drivers/net/wireless/broadcom/b43/main.c
	grep -q "gpio_out(cc, 0xa7, 0x06)" drivers/net/wireless/broadcom/b43/main.c || { echo "ALE_GPIO: main.c hunk did not apply" >&2; exit 1; }
fi
# forced includes: the patched ssb headers must win over the kernel's (regs first, ssb.h includes it)
INC="-include $T/include/linux/ssb/ssb_regs.h -include $T/include/linux/ssb/ssb.h -include $T/include/linux/bcm47xx_sprom.h"
nix-shell -p gnumake gcc --run "make -C $K M=$T/drivers/bcma modules KCFLAGS='$INC' >/dev/null; \
	make -C $K M=$T/drivers/net/wireless/broadcom/b43 modules CONFIG_B43_PHY_AC=y KCFLAGS='$INC -DCONFIG_B43_PHY_AC=1 -DALLOW_24=true' >/dev/null"
mkdir -p "$P/b43-src-builds"
cp drivers/bcma/bcma.ko "$P/b43-src-builds/ale-bcma-$VER.ko"
cp drivers/net/wireless/broadcom/b43/b43.ko "$P/b43-src-builds/ale-b43-$VER${ALE_DMA:+-dma}${ALE_CCK1:+-cck1}${ALE_CCKPO0:+-ccko0}${ALE_DUMP:+-dump}${ALE_FIX1:+-fix$ALE_FIX1}${ALE_GPIO:+-gpio}.ko"
