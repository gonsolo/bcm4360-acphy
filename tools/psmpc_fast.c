/* High-rate sampler for the AC-PHY PSM program counter, via the existing
 * /sys/kernel/debug/b43ac/mmio16 interface (same one used by hand all
 * night: write a hex offset, read back "offset value"). A shell loop of
 * `echo 154 > mmio16; cat mmio16` costs a fork+exec per sample (~3-9ms
 * observed); this keeps the fd open and does write+read in a tight
 * loop, no new process per sample. Read-only in effect (mmio16's write
 * side only sets which offset the next read targets, per the driver's
 * own debugfs implementation - not a hardware write).
 *
 * usage: sudo psmpc_fast SECONDS > out.txt
 * output: one "<nsec> <raw32hex>" line per sample.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static long long now_ns(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int main(int argc, char **argv)
{
	double secs = argc > 1 ? atof(argv[1]) : 5.0;
	int fd = open("/sys/kernel/debug/b43ac/mmio16", O_RDWR);
	if (fd < 0) { perror("open"); return 1; }

	long long end = now_ns() + (long long)(secs * 1e9);
	char buf[32];
	while (now_ns() < end) {
		if (pwrite(fd, "154", 3, 0) != 3) { perror("pwrite"); break; }
		ssize_t n = pread(fd, buf, sizeof(buf) - 1, 0);
		if (n <= 0) { perror("pread"); break; }
		buf[n] = 0;
		printf("%lld %s", now_ns(), buf);
	}
	return 0;
}
