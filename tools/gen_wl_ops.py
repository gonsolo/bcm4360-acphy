#!/usr/bin/env python3
"""seq.txt (wl trace) -> binary op stream for the ac_fr_* replay (notes/119).

usage: gen_wl_ops.py SEQ_TXT OUT_BIN
Record (little endian, 16 bytes): u32 line, u8 type, u8 width, u16 a, u32 b, u32 c
 type 1 phy(a=reg,b=val) 2 radio(a=reg,b=val) 3 tbl(a=id,b=off,c=val,width)
      4 delay(c=us)      5 shm(a=region,b=off,c=val,width 16/32)
"""
import struct, sys

T = {"phy": 1, "radio": 2, "tbl": 3, "delay": 4, "shm": 5}
n = 0
with open(sys.argv[1]) as f, open(sys.argv[2], "wb") as o:
    for ln, line in enumerate(f, 1):
        p = line.split()
        if len(p) < 3 or p[1] not in T:
            continue
        t = T[p[1]]
        h = lambda s: int(s, 16)
        if t in (1, 2):
            r = struct.pack("<IBBHII", ln, t, 0, h(p[2]), h(p[3]), 0)
        elif t == 3:
            r = struct.pack("<IBBHII", ln, t, h(p[4]), h(p[2]), h(p[3]), h(p[5]))
        elif t == 4:
            r = struct.pack("<IBBHII", ln, t, 0, 0, 0, h(p[2]))
        else:
            w = 32 if p[5] == "w32" else 16
            r = struct.pack("<IBBHII", ln, t, w, h(p[2]), h(p[3]), h(p[4]))
        o.write(r)
        n += 1
print(n, "ops")
