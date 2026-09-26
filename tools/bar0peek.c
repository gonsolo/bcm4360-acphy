/* Read-only peek at BCM4360 BAR0 fixed windows: core wrapper (+0x1000) and chipcommon (+0x3000). */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

static const struct { unsigned off; const char *name; } regs[] = {
	{0x3000, "cc chipid"}, {0x3028, "cc chipcontrol"}, {0x302c, "cc chipstatus"},
	{0x3058, "cc gpiopullup"}, {0x305c, "cc gpiopulldown"}, {0x3060, "cc gpioin"},
	{0x3064, "cc gpioout"}, {0x3068, "cc gpioouten"}, {0x306c, "cc gpiocontrol"},
	{0x3070, "cc gpiopol"}, {0x3074, "cc gpiointmask"}, {0x3600, "pmu control"},
	{0x3608, "pmu status"}, {0x3618, "pmu min_res_mask"}, {0x361c, "pmu max_res_mask"},
	{0x3620, "pmu res_state"}, {0x1408, "d11 ioctrl"}, {0x1500, "d11 iostatus"},
	{0x1800, "d11 resetctrl"},
};

int main(int argc, char **argv)
{
	const char *path = argc > 1 ? argv[1] : "/sys/bus/pci/devices/0000:03:00.0/resource0";
	int fd = open(path, O_RDONLY | O_SYNC);
	if (fd < 0) { perror(path); return 1; }
	volatile uint32_t *m = mmap(NULL, 0x4000, PROT_READ, MAP_SHARED, fd, 0);
	if (m == MAP_FAILED) { perror("mmap"); return 1; }
	for (unsigned i = 0; i < sizeof(regs) / sizeof(regs[0]); i++)
		printf("%04x %-18s %08x\n", regs[i].off, regs[i].name, m[regs[i].off / 4]);
	return 0;
}
