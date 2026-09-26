# Out-of-tree build of a modified b43 with AC-PHY forced on.
# Everything except CONFIG_B43_PHY_AC is already set in the running
# kernel's own .config (B43_BCMA, B43_PHY_G/N/LP/HT, etc.), and gets
# pulled in automatically via the kernel build's generated autoconf.h -
# we only need to force the one flag that's off by default.

KDIR ?= /nix/store/18rsbfk0qpkx88qyn19xj5vcb98qhr6r-linux-6.18.53-dev/lib/modules/6.18.53/build
PWD := $(shell pwd)

ccflags-y := -DCONFIG_B43_PHY_AC=1

obj-m := b43.o
b43-y := main.o bus.o
b43-y += phy_g.o tables.o lo.o wa.o
b43-y += tables_nphy.o radio_2055.o radio_2056.o radio_2057.o phy_n.o
b43-y += phy_common.o
b43-y += phy_lp.o tables_lpphy.o
b43-y += phy_ht.o tables_phy_ht.o radio_2059.o
b43-y += phy_ac.o radio_2069.o tables_phy_ac.o
b43-y += sysfs.o xmit.o dma.o pio.o rfkill.o ppr.o
b43-y += leds.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
