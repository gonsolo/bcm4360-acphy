#!/usr/bin/env python3
"""Count 802.11 management-frame retries in a pcap by reading the real
frame-control retry bit (0x0800), not tcpdump's summary text (which doesn't
print "Retry" for management frames). No external deps.

usage: fc_retry.py PCAP [subtype_filter]   e.g. fc_retry.py x.pcap resp
"""
import struct
import sys

SUBTYPES = {0: "assocreq", 1: "assocresp", 4: "req", 5: "resp",
            0xb: "auth", 0xc: "deauth"}


def frames(path):
    data = open(path, "rb").read()
    off = 24
    while off < len(data):
        _, _, incl_len, _ = struct.unpack("<IIII", data[off:off + 16])
        off += 16
        pkt = data[off:off + incl_len]
        off += incl_len
        if len(pkt) < 4:
            continue
        rt_len = struct.unpack("<H", pkt[2:4])[0]
        if len(pkt) < rt_len + 2:
            continue
        fc = struct.unpack("<H", pkt[rt_len:rt_len + 2])[0]
        if (fc >> 2) & 0x3 != 0:  # management only
            continue
        yield (fc >> 4) & 0xf, bool(fc & 0x0800)


def main():
    want = sys.argv[2] if len(sys.argv) > 2 else None
    n, retries = 0, 0
    per = {}
    for subtype, retry in frames(sys.argv[1]):
        name = SUBTYPES.get(subtype, "sub%d" % subtype)
        if want and want not in name:
            continue
        n += 1
        retries += retry
        per.setdefault(name, [0, 0])
        per[name][0] += 1
        per[name][1] += retry
    for name, (tot, r) in sorted(per.items()):
        print("%-10s %d frames, %d retries (%d originals)" % (name, tot, r, tot - r))
    if n:
        print("total: %d frames, %d retries (%.0f%%)" % (n, retries, 100.0 * retries / n))


if __name__ == "__main__":
    main()
