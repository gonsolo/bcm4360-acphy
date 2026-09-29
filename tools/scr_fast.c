/* High-rate sampler for PSM SCR (scratch) registers via the real,
 * host-accessible B43_SHM_SCRATCH SHM routing window, exposed at
 * /sys/kernel/debug/b43ac/scr (b43_ac_dbg_read/write, which=5).
 * Contrary to earlier notes/63, this IS observable from the host - it's
 * an ordinary SHM read with routing=B43_SHM_SCRATCH, no different in
 * kind from the SHM_SHARED reads already used all night.
 *
 * usage: sudo scr_fast SECONDS ADDR_HEX [ADDR_HEX ...] > out.txt
 * output: "<nsec> <addr> <val_hex4>" per sample, cycling the given
 * addresses in order.
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
	if (argc < 3) { fprintf(stderr, "usage: %s SECONDS ADDR_HEX...\n", argv[0]); return 1; }
	double secs = atof(argv[1]);
	int naddr = argc - 2;
	int fd = open("/sys/kernel/debug/b43ac/scr", O_RDWR);
	if (fd < 0) { perror("open"); return 1; }

	long long end = now_ns() + (long long)(secs * 1e9);
	char wbuf[16], rbuf[32];
	int i = 0;
	while (now_ns() < end) {
		const char *a = argv[2 + i];
		int wl = snprintf(wbuf, sizeof(wbuf), "%s", a);
		if (pwrite(fd, wbuf, wl, 0) != wl) { perror("pwrite"); break; }
		ssize_t n = pread(fd, rbuf, sizeof(rbuf) - 1, 0);
		if (n <= 0) { perror("pread"); break; }
		rbuf[n] = 0;
		printf("%lld %s", now_ns(), rbuf);
		i = (i + 1) % naddr;
	}
	return 0;
}
