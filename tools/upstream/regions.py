#!/usr/bin/env python3
"""regions.py STOCK FINAL: list the change regions (difflib opcodes other than 'equal') between two files, numbered from 1,
with the first changed line, as the unit to assign to patches. Used by tools/upstream/cut.py."""
import difflib, sys
def regions(a_lines, b_lines):
    sm = difflib.SequenceMatcher(None, a_lines, b_lines, autojunk=False)
    return [op for op in sm.get_opcodes() if op[0] != 'equal']
if __name__ == '__main__':
    a = open(sys.argv[1]).read().splitlines(); b = open(sys.argv[2]).read().splitlines()
    for n, (tag, i1, i2, j1, j2) in enumerate(regions(a, b), 1):
        first = (b[j1] if j2 > j1 else '-' + a[i1]).strip()[:78]
        print(f"{n:3d} {tag:7s} old {i1+1}-{i2} new {j1+1}-{j2} ({j2-j1:3d} lines)  {first}")
