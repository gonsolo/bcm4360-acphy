#!/usr/bin/env python3
"""Decode wl TX descriptors from a txtrace.sh trace (txfifo kprobe events).

usage: txdesc.py TRACE [max]

Each txfifo event carries 160 bytes of the packet handed to the DMA:
the 124-byte AC TX header followed by the start of the 802.11 frame.
Also pairs TX status reads (0x170..0x17c) that follow.
"""
import re
import struct
import sys

EV = re.compile(r"\s(\d+\.\d+): txfifo: \([^)]*\) fifo=(\d+) commit=(\S+) fid=(\S+) len=(\d+) h=\{([^}]*)\}")


def u16(b, o):
    return struct.unpack_from("<H", b, o)[0]


def decode(b):
    out = []
    out.append("PktInfo: cachelen %02x tso %02x MacTxCtlLow %04x MacTxCtlHigh %04x chanspec %04x "
               "ivoff %02x %02x framelen %u frameid %04x seq %04x tstamp %04x txstatus %04x" % (
                   b[0], b[1], u16(b, 2), u16(b, 4), u16(b, 6), b[8], b[9], u16(b, 10),
                   u16(b, 12), u16(b, 14), u16(b, 16), u16(b, 18)))
    for i in range(4):
        r = 0x14 + i * 0x14
        ptx = (u16(b, r), u16(b, r + 2), u16(b, r + 4))
        if not any(b[r:r + 0x14]):
            continue
        out.append("Rate[%d]: phyctl %04x %04x %04x plcp %s fbw %04x txrate %04x rtsctl %04x bfm %04x" % (
            i, *ptx, b[r + 6:r + 12].hex(), u16(b, r + 12), u16(b, r + 14), u16(b, r + 16),
            u16(b, r + 18)))
    out.append("Cache: %s" % b[0x64:0x7c].hex())
    fc = u16(b, 0x7c)
    out.append("802.11: fc %04x dur %04x a1 %s rest %s" % (
        fc, u16(b, 0x7e), b[0x80:0x86].hex(":"), b[0x86:0xa0].hex()))
    return out


def main():
    lim = int(sys.argv[2]) if len(sys.argv) > 2 else 1 << 30
    n = 0
    with open(sys.argv[1], errors="replace") as f:
        for ln in f:
            m = EV.search(ln)
            if not m:
                continue
            words = [int(w, 16) for w in m.group(6).split(",")]
            b = b"".join(struct.pack("<Q", w) for w in words)
            print("%s fifo %s commit %s fid %s len %s" % m.group(1, 2, 3, 4, 5))
            for s in decode(b):
                print("  " + s)
            n += 1
            if n >= lim:
                break
    print("%d descriptors" % n)


if __name__ == "__main__":
    main()
