/* High-rate, multi-register sampler across the b43ac debugfs interfaces
 * (mmio16 for MMIO/PSM-PC, ihr for Internal Hardware Registers, shm for
 * shared memory), for real hardware timing - not simulation. Cycles
 * through a fixed list of (file, addr, label) probes as fast as the
 * kernel will answer, one open fd per underlying file (reused across
 * samples, no per-sample open/close).
 *
 * usage: sudo hw_timing SECONDS > out.txt
 * output: "<nsec> <label> <val_hex>" per sample.
 *
 * Probe list is fixed below (notes/58-67's known-relevant addresses):
 *   pc      mmio16 154   - PSM program counter (packed with a status byte)
 *   ihrb3   ihr    b3    - interrupt-source scan register (notes/67)
 *   ihr93   ihr    93    - radio/PHY op, written right before the 0x1EB wait
 *   ihr95   ihr    95
 *   ihr97   ihr    97
 *   shm6a   shm    6a    - tested at 0x11C2/0x119C (notes/58)
 *   ihr15b  ihr    15b   - tested at 0x11C1 (notes/58)
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

struct probe { const char *file; const char *addr; const char *label; int fd; };

static struct probe probes[] = {
	{ "mmio16", "154", "pc" },
	{ "ihr",    "47",  "ihr47" },   /* gates entry to the 0xEC0 timer block (notes/69) */
	{ "ihr",    "150", "ihr150" },
	{ "ihr",    "151", "ihr151" },
	{ "ihr",    "155", "ihr155" },
	{ "ihr",    "156", "ihr156" },
	{ "ihr",    "159", "ihr159" },
	{ "ihr",    "119", "ihr119" },  /* low half of the free-running timer */
};
#define NPROBES (int)(sizeof(probes) / sizeof(probes[0]))

int main(int argc, char **argv)
{
	double secs = argc > 1 ? atof(argv[1]) : 5.0;
	char path[128];
	for (int i = 0; i < NPROBES; i++) {
		snprintf(path, sizeof(path), "/sys/kernel/debug/b43ac/%s", probes[i].file);
		probes[i].fd = open(path, O_RDWR);
		if (probes[i].fd < 0) { perror(path); return 1; }
	}

	long long end = now_ns() + (long long)(secs * 1e9);
	char wbuf[16], rbuf[32];
	int i = 0;
	while (now_ns() < end) {
		struct probe *p = &probes[i];
		int wl = snprintf(wbuf, sizeof(wbuf), "%s", p->addr);
		ssize_t wr = pwrite(p->fd, wbuf, wl, 0);
		ssize_t n = wr == wl ? pread(p->fd, rbuf, sizeof(rbuf) - 1, 0) : -1;
		if (n <= 0) {
			/* The debugfs fd can transiently go away (interface
			 * mode changes during disconnect/reconnect) - reopen
			 * and keep sampling rather than losing the rest of
			 * the capture window. */
			close(p->fd);
			snprintf(path, sizeof(path), "/sys/kernel/debug/b43ac/%s", p->file);
			p->fd = open(path, O_RDWR);
			i = (i + 1) % NPROBES;
			continue;
		}
		rbuf[n] = 0;
		/* rbuf is "addr val\n" - keep only val */
		char *sp = strchr(rbuf, ' ');
		printf("%lld %s %s", now_ns(), p->label, sp ? sp + 1 : rbuf);
		i = (i + 1) % NPROBES;
	}
	return 0;
}
