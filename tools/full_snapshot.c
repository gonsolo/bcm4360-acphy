/* Fast, complete SHM (word 0-0xFFF, byte 0-0x1FFE) + IHR (word 0-0x39F)
 * snapshot via the b43ac debugfs interfaces, one open fd per file reused
 * across all reads (avoids the shell loop's ~9ms-per-word open/write/
 * read/close overhead - this does the whole thing in well under a
 * second instead of ~45s, so it can actually bracket a fast real event
 * instead of only ever seeing steady-state).
 *
 * usage: sudo full_snapshot > out.txt
 * output: "<space TAB word_hex val_hex>" per word, SHM then IHR.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int read_one(int fd, unsigned word, unsigned *val)
{
	char wbuf[16], rbuf[32];
	int wl = snprintf(wbuf, sizeof(wbuf), "%x", word);
	if (pwrite(fd, wbuf, wl, 0) != wl)
		return -1;
	ssize_t n = pread(fd, rbuf, sizeof(rbuf) - 1, 0);
	if (n <= 0)
		return -1;
	rbuf[n] = 0;
	char *sp = strchr(rbuf, ' ');
	if (!sp)
		return -1;
	*val = (unsigned)strtoul(sp + 1, NULL, 16);
	return 0;
}

int main(void)
{
	int shm_fd = open("/sys/kernel/debug/b43ac/shm", O_RDWR);
	int ihr_fd = open("/sys/kernel/debug/b43ac/ihr", O_RDWR);
	if (shm_fd < 0 || ihr_fd < 0) { perror("open"); return 1; }

	/* The driver's b43_shm_read16 divides SHARED-routing addresses by 4
	 * internally unless word-aligned (its own 32-bit-access optimization
	 * for the SHM_SHARED case only, per main.c) - passing a raw word
	 * index here (as an earlier version of this tool did) makes 3 out
	 * of every 4 reads alias onto the same "unaligned" register. Pass a
	 * BYTE offset (word*2) instead, matching the convention already
	 * validated against b43.h's documented byte offsets and a real wl
	 * SHM_CONTROL trace (notes/62). */
	for (unsigned w = 0; w < 0x1000; w++) {
		unsigned val;
		if (read_one(shm_fd, w * 2, &val) == 0)
			printf("SHM %04x %04x\n", w, val);
	}
	for (unsigned w = 0; w <= 0x39F; w++) {
		unsigned val;
		if (read_one(ihr_fd, w, &val) == 0)
			printf("IHR %04x %04x\n", w, val);
	}
	return 0;
}
