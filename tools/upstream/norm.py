import difflib, sys, re
base, ours, out = sys.argv[1:4]
a = open(base).read().splitlines(keepends=True)
b = open(ours).read().splitlines(keepends=True)
def norm(lines): return re.sub(r'[\s*]+', '', ''.join(lines))
res = []; reverted = 0
for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
    if tag == 'replace' and norm(a[i1:i2]) == norm(b[j1:j2]):
        res += a[i1:i2]; reverted += 1
    else:
        res += b[j1:j2]
open(out, 'w').write(''.join(res))
print(reverted, end='')
