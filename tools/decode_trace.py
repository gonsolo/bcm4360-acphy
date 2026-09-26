#!/usr/bin/env python3
"""Decode a wl.ko MMIO trace into logical PHY/radio/table/SHM/chipcommon accesses.

Accepts two input formats:
  - bpftrace (wl_full_trace.bt):  "<ns> W32 <addr> <val>" / "<ns> R16 <addr> <val>" /
                                  "<ns> DELAY <us>"
  - tracefs kprobe events (firstload_trace.sh): lines with "w32:", "r32:"+"r32r:",
                                  "cfgw:", "delay:" events.

Writes into OUTDIR:
  phy.txt, radio.txt              final value per register ("reg val", hex), in
                                  order of last write (broadcast aliases)
  tables.txt                      final value per entry ("id off width val", dec/hex)
  shm.txt                         final value per word ("routing off val", hex)
  cc.txt, pmu-{chipctl,regctl,pllctl}.txt, wrapper.txt
  seq.txt                         ordered logical writes and delays
  summary.txt                     counts
"""
import os
import re
import sys
from collections import Counter, OrderedDict

PHY_SEL, PHY_DATA = 0x3fc, 0x3fe
RADIO_SEL, RADIO_DATA = 0x3d8, 0x3da
SHM_CTL, SHM_DATA, SHM_DATA_HI = 0x160, 0x164, 0x166
TBL_ID, TBL_OFF, TBL_D1, TBL_D2 = 0x00d, 0x00e, 0x00f, 0x010
CC_BASE, WRAP_BASE = 0x3000, 0x1000


def parse_bpftrace(lines):
    for ln in lines:
        p = ln.split()
        if len(p) < 3 or not p[0].isdigit():
            continue
        ts = int(p[0])
        if p[1] == "DELAY":
            yield ts, "delay", None, int(p[2])
        elif p[1][0] in "RW" and len(p) >= 4:
            yield ts, p[1].lower(), int(p[2], 16), int(p[3], 16)


TRACEFS_RE = re.compile(r"\s(\d+\.\d+): (\w+): \([^)]*\)(.*)$")


def parse_tracefs(lines):
    pending = {}  # per-CPU read address awaiting its return event
    for ln in lines:
        m = TRACEFS_RE.search(ln)
        if not m:
            continue
        ts = int(float(m.group(1)) * 1e9)
        ev = m.group(2)
        args = dict(kv.split("=", 1) for kv in m.group(3).split() if "=" in kv)
        cpu = re.search(r"\[(\d+)\]", ln)
        cpu = cpu.group(1) if cpu else "?"
        num = lambda k: int(args[k], 0)
        if ev in ("w32", "w16", "w8"):
            yield ts, ev, num("addr"), num("val")
        elif ev in ("r32", "r16", "r8"):
            pending[(cpu, ev)] = num("addr")
        elif ev in ("r32r", "r16r", "r8r"):
            a = pending.pop((cpu, ev[:-1]), None)
            if a is not None:
                yield ts, ev[:-1], a, num("ret")
        elif ev == "cfgw":
            yield ts, "cfgw", num("off"), num("val")
        elif ev == "delay":
            yield ts, "delay", None, num("us")


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    src, outdir = sys.argv[1], sys.argv[2]
    with open(src, errors="replace") as f:
        lines = f.readlines()
    tracefs = any(": w32: (" in ln or ": w16: (" in ln for ln in lines[:5000])
    events = list((parse_tracefs if tracefs else parse_bpftrace)(lines))
    if not events:
        sys.exit("no events parsed")

    # BAR0 base: address of the most common PHY select write minus 0x3fc.
    sel = Counter(a for _, op, a, _ in events
                  if op in ("w32", "w16") and a is not None and (a & 0xfff) == PHY_SEL)
    base = sel.most_common(1)[0][0] - PHY_SEL

    # If the trace has PCI config writes, window 1 is the 802.11 core only when
    # config 0x80 holds the value most often seen around PHY accesses.
    w, wins = None, Counter()
    for _, op, a, v in events:
        if op == "cfgw" and a == 0x80:
            w = v
        elif op in ("w32", "w16") and a == base + PHY_SEL and w is not None:
            wins[w] += 1
    d11_win = wins.most_common(1)[0][0] if wins else None

    phy, radio, tables, shm = OrderedDict(), OrderedDict(), OrderedDict(), OrderedDict()
    cc, wrapper = OrderedDict(), OrderedDict()
    pmu = {"chipctl": OrderedDict(), "regctl": OrderedDict(), "pllctl": OrderedDict()}
    pmu_addr = {0x650: "chipctl", 0x658: "regctl", 0x660: "pllctl"}
    pmu_sel = {}
    seq = []
    stats = Counter()

    phy_sel = radio_sel = None
    shm_ctl = None
    tbl = {"id": 0, "off": 0, "hi": None}
    win1 = None  # PCI config 0x80: BAR0 window 1 target

    def phy_write(reg, val, ts):
        phy.pop(reg, None)
        phy[reg] = val
        stats["phy_w"] += 1
        if reg == TBL_ID:
            tbl["id"] = val
        elif reg == TBL_OFF:
            tbl["off"] = val
        elif reg == TBL_D2:
            tbl["hi"] = val
            return
        elif reg == TBL_D1:
            if tbl["hi"] is not None:
                v, w = (tbl["hi"] << 16) | val, 32
            else:
                v, w = val, 16
            tables[(tbl["id"], tbl["off"])] = (w, v)
            seq.append((ts, "tbl", tbl["id"], tbl["off"], w, v))
            stats["tbl_w"] += 1
            tbl["off"] += 1
            tbl["hi"] = None
            return
        seq.append((ts, "phy", reg, val))

    for ts, op, a, v in events:
        if op == "delay":
            seq.append((ts, "delay", v))
            continue
        if op == "cfgw":
            if a == 0x80:
                win1 = v
            seq.append((ts, "cfgw", a, v))
            continue
        off = a - base
        if not 0 <= off < 0x4000:
            stats["out_of_bar"] += 1
            continue
        write = op[0] == "w"
        if off >= CC_BASE:
            o = off - CC_BASE
            if write:
                if o in pmu_addr:
                    pmu_sel[pmu_addr[o]] = v
                elif o - 4 in pmu_addr:
                    name = pmu_addr[o - 4]
                    pmu[name][pmu_sel.get(name, -1)] = v
                    seq.append((ts, "pmu", name, pmu_sel.get(name, -1), v))
                else:
                    cc[o] = v
                    seq.append((ts, "cc", o, v))
                stats["cc_w"] += 1
            continue
        if WRAP_BASE <= off < WRAP_BASE + 0x1000:
            if write:
                wrapper[off - WRAP_BASE] = v
                seq.append((ts, "wrap", off - WRAP_BASE, v))
            continue
        if off >= 0x1000:
            stats["other_win"] += 1
            continue
        if d11_win is not None and win1 is not None and win1 != d11_win:
            if write:
                seq.append((ts, "core", win1, off, v))
                stats["other_core_w"] += 1
            continue
        # Window 1 (D11 core, unless attach is poking another core).
        if write and op == "w32" and off == PHY_SEL:
            phy_sel = v & 0xffff
            phy_write(phy_sel, v >> 16, ts)
        elif write and off == PHY_SEL:
            phy_sel = v & 0xffff
        elif write and off == PHY_DATA and phy_sel is not None:
            phy_write(phy_sel, v, ts)
        elif write and off == RADIO_SEL:
            radio_sel = v
        elif write and off == RADIO_DATA and radio_sel is not None:
            radio.pop(radio_sel, None)
            radio[radio_sel] = v
            seq.append((ts, "radio", radio_sel, v))
            stats["radio_w"] += 1
        elif write and off == SHM_CTL:
            shm_ctl = v
        elif write and off in (SHM_DATA, SHM_DATA_HI) and shm_ctl is not None:
            routing, word = (shm_ctl >> 16) & 0xff, shm_ctl & 0xffff
            byte = word * 4 + (2 if off == SHM_DATA_HI else 0)
            if op == "w32":
                shm[(routing, byte)] = v & 0xffff
                shm[(routing, byte + 2)] = v >> 16
            else:
                shm[(routing, byte)] = v
            seq.append((ts, "shm", routing, byte, v, op))
            stats["shm_w"] += 1
        elif write:
            seq.append((ts, "mmio", op, off, v))
            stats["mmio_w"] += 1

    os.makedirs(outdir, exist_ok=True)

    def dump(name, rows):
        with open(os.path.join(outdir, name), "w") as f:
            for r in rows:
                f.write(r + "\n")

    # PHY and radio in order of last write: 0x1000 (PHY) and 0x600 (radio)
    # address bits broadcast to all cores, so replaying in address order
    # lets an old broadcast write clobber later per-core values.
    dump("phy.txt", ("%04x %04x" % (r, v) for r, v in phy.items()))
    dump("radio.txt", ("%04x %04x" % (r, v) for r, v in radio.items()))
    dump("tables.txt", ("%d %d %d %x" % (i, o, w, v)
                        for (i, o), (w, v) in sorted(tables.items())))
    dump("shm.txt", ("%d %04x %04x" % (r, o, v) for (r, o), v in sorted(shm.items())))
    dump("cc.txt", ("%03x %08x" % (o, v) for o, v in sorted(cc.items())))
    dump("wrapper.txt", ("%03x %08x" % (o, v) for o, v in sorted(wrapper.items())))
    for name, d in pmu.items():
        dump("pmu-%s.txt" % name, ("%d %08x" % (i, v) for i, v in sorted(d.items())))
    dump("seq.txt", (" ".join(str(x) if isinstance(x, (int, str)) and not isinstance(x, bool)
                              and isinstance(x, str) else ("%x" % x if isinstance(x, int) else str(x))
                              for x in s) for s in seq))
    summary = ["source %s (%s)" % (src, "tracefs" if tracefs else "bpftrace"),
               "events %d, BAR0 base %x, d11 window %s" % (len(events), base,
                                                          "%x" % d11_win if d11_win is not None else "n/a"),
               "final: phy %d radio %d table entries %d shm words %d cc %d wrapper %d" %
               (len(phy), len(radio), len(tables), len(shm), len(cc), len(wrapper)),
               "pmu: " + ", ".join("%s %d" % (k, len(d)) for k, d in pmu.items())]
    summary += ["%s %d" % kv for kv in sorted(stats.items())]
    dump("summary.txt", summary)
    print("\n".join(summary))


if __name__ == "__main__":
    main()
