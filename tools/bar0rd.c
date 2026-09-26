/* Read-only: print BAR0 32-bit words at the given hex offsets. */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
	int fd = open("/sys/bus/pci/devices/0000:03:00.0/resource0", O_RDONLY | O_SYNC);
	if (fd < 0) { perror("open"); return 1; }
	volatile uint32_t *m = mmap(NULL, 0x4000, PROT_READ, MAP_SHARED, fd, 0);
	if (m == MAP_FAILED) { perror("mmap"); return 1; }
	for (int i = 1; i < argc; i++) {
		unsigned long off = strtoul(argv[i], NULL, 16) & 0x3ffc;
		printf("%04lx %08x\n", off, m[off / 4]);
	}
	return 0;
}
