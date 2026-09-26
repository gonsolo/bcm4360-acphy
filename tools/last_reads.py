#!/usr/bin/env python3
"""Last value wl *read* from each PHY and radio register in a trace.

usage: last_reads.py TRACE OUTDIR  -> OUTDIR/phy-read.txt, radio-read.txt
Write-only state (decode_trace.py) and readback can differ for registers
with status or hardware-driven fields; these files give wl's readback.
"""
import os
import sys
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from decode_trace import (parse_tracefs, parse_bpftrace, PHY_SEL, PHY_DATA,
                          RADIO_SEL, RADIO_DATA)


def main():
    src, outdir = sys.argv[1], sys.argv[2]
    with open(src, errors="replace") as f:
        lines = f.readlines()
    tracefs = any(": w32: (" in ln or ": w16: (" in ln for ln in lines[:5000])
    events = list((parse_tracefs if tracefs else parse_bpftrace)(lines))
    sel = Counter(a for _, op, a, _ in events
                  if op in ("w32", "w16") and a is not None and (a & 0xfff) == PHY_SEL)
    base = sel.most_common(1)[0][0] - PHY_SEL
    phy, radio = {}, {}
    phy_sel = radio_sel = None
    win1 = d11 = None
    for _, op, a, v in events:
        if op == "cfgw":
            if a == 0x80:
                win1 = v
            continue
        if op == "delay" or a is None:
            continue
        off = a - base
        if off == PHY_SEL and op[0] == "w":
            phy_sel = v & 0xffff
            d11 = win1
        elif off == RADIO_SEL and op[0] == "w":
            radio_sel = v & 0xffff
        elif win1 != d11:
            continue
        elif off == PHY_DATA and op[0] == "r" and phy_sel is not None:
            phy[phy_sel] = v & 0xffff
        elif off == RADIO_DATA and op[0] == "r" and radio_sel is not None:
            radio[radio_sel] = v & 0xffff
    os.makedirs(outdir, exist_ok=True)
    for name, d in (("phy-read.txt", phy), ("radio-read.txt", radio)):
        with open(os.path.join(outdir, name), "w") as f:
            for r in sorted(d):
                f.write("%04x %04x\n" % (r, d[r]))
        print(name, len(d))


if __name__ == "__main__":
    main()
