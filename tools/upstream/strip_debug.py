#!/usr/bin/env python3
"""strip_debug.py FILE...: remove every '#ifdef CONFIG_B43_PHY_AC_DEBUG ... #endif' block (nesting-aware) from the given files."""
import re, sys
for path in sys.argv[1:]:
    out, depth, skipping = [], 0, False
    for line in open(path).read().splitlines(keepends=True):
        s = line.strip()
        if not skipping and s.startswith('#ifdef CONFIG_B43_PHY_AC_DEBUG'):
            skipping, depth = True, 1
            continue
        if skipping:
            if re.match(r'#\s*if', s):
                depth += 1
            elif re.match(r'#\s*endif', s):
                depth -= 1
                if depth == 0:
                    skipping = False
            continue
        out.append(line)
    open(path, 'w').write(''.join(out))
