/*
 * Read-only dump of the BCM4360 802.11 core registers (BAR0 window 1) from
 * userspace, for comparing wl's live state with b43's. 16-bit reads.
 * Skips registers with read side effects: 0x160-0x17f (object memory and
 * TX status FIFO), 0x200-0x3ff (DMA/PIO, radio/PHY indirect ports).
 * Verifies that PCI config 0x80 (window 1) points at the 802.11 core
 * before and after the dump.
 * usage: sudo macdump [expected_window_hex] > out.txt
 */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define DEV "/sys/bus/pci/devices/0000:03:00.0/"

static uint32_t cfg80(void)
{
	uint32_t v = 0;
	int fd = open(DEV "config", O_RDONLY);

	if (fd < 0 || pread(fd, &v, 4, 0x80) != 4) {
		perror("config");
		exit(1);
	}
	close(fd);
	return v;
}

static int skip(unsigned int o)
{
	return (o >= 0x160 && o < 0x180) || (o >= 0x200 && o < 0x400);
}

int main(int argc, char **argv)
{
	uint32_t want = argc > 1 ? strtoul(argv[1], NULL, 16) : 0x18001000;
	uint32_t w0 = cfg80(), w1;
	int fd = open(DEV "resource0", O_RDONLY | O_SYNC);
	volatile uint16_t *m;
	unsigned int o;

	if (w0 != want) {
		fprintf(stderr, "window is %08x, not %08x - aborting\n", w0, want);
		return 1;
	}
	if (fd < 0) {
		perror("resource0");
		return 1;
	}
	m = mmap(NULL, 0x1000, PROT_READ, MAP_SHARED, fd, 0);
	if (m == MAP_FAILED) {
		perror("mmap");
		return 1;
	}
	for (o = 0; o < 0x1000; o += 2)
		if (!skip(o))
			printf("%03x %04x\n", o, m[o / 2]);
	w1 = cfg80();
	if (w1 != want)
		fprintf(stderr, "WARNING: window changed to %08x during dump\n", w1);
	return 0;
}
