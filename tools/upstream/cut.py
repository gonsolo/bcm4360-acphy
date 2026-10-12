#!/usr/bin/env python3
"""cut.py REPO: cut the target tree (branch 'final' of the series repo) into the series (branch 'series', one commit per patch),
each commit compile-tested with tools/build_upstream_tree.sh. The stock tree is the first commit of the repo.
Regions of a file (difflib opcodes between stock and final) are assigned to patches by number."""
import difflib, os, re, subprocess, sys
repo = os.path.abspath(sys.argv[1]); KDEV = sys.argv[2]
P = "drivers/net/wireless/broadcom/b43"; D = f"{repo}/{P}"
here = os.path.dirname(os.path.abspath(__file__)); proj = os.path.abspath(f"{here}/../..")
sys.path.insert(0, here)
from messages import M, COVER

def git(*a, **kw):
    return subprocess.check_output(["git", "-C", repo, *a], text=True, **kw)
root = git("rev-list", "--max-parents=0", "final").split()[0]
def stock(f): return git("show", f"{root}:{P}/{f}")
def final(f): return git("show", f"final:{P}/{f}")

# patch numbers (1-based) per region of each file
ASSIGN = {
 "main.c":  {1:8, 2:11, 3:11, 4:8, 5:6, 6:6, 7:5, 8:9, 9:9, 10:6, 11:6, 12:6, 13:6, 14:6, 15:5, 16:6, 17:6, 18:5, 19:5,
             20:5, 21:5, 22:5, 23:5, 24:2, 25:12, 26:12, 27:8, 28:11, 29:12, 30:1, 31:1, 32:1},
 "xmit.c":  {1:9, 2:9, 3:9, 4:10, 5:10, 6:10, 7:10, 8:10, 9:9},
 "dma.c":   {1:12, 2:3, 3:3, 4:3, 5:3, 6:3, 7:3, 8:12, 9:9, 10:12, 11:12, 12:12, 13:4, 14:4, 15:4},
 "dma.h":   {1:3, 2:3, 3:4, 4:3, 5:9, 6:4},
 "xmit.h":  {1:9, 2:9, 3:9, 4:12, 5:12},
 "b43.h":   {1:3},
 "phy_common.c": {1:8},
}
NEWFILES = {7: ["radio_2069.c", "radio_2069.h", "tables_phy_ac.c", "tables_phy_ac.h", "Makefile"],
            8: ["phy_ac_farrow.h"]}
def staged(f, k):
    a = stock(f).splitlines(keepends=True); b = final(f).splitlines(keepends=True)
    out = []; n = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag == "equal":
            out += a[i1:i2]; continue
        n += 1
        out += b[j1:j2] if ASSIGN[f][n] <= k else a[i1:i2]
    if n != max(ASSIGN[f]):
        sys.exit(f"cut: {f}: region count changed ({n} vs {max(ASSIGN[f])}), re-assign")
    return "".join(out)

# stage A of phy_ac.c/.h
tmp = subprocess.check_output(["mktemp", "-d"], text=True).strip()
fin = subprocess.check_output(["mktemp", "-d"], text=True).strip()
subprocess.run(f"git -C {repo} archive final {P} | tar -x -C {fin}", shell=True, check=True)
subprocess.check_call(["nix-shell", "-p", "python3", "--run",
                       f"python3 -I {here}/stage_a.py {fin}/{P} {tmp}"], stdout=subprocess.DEVNULL)
stageA = {"phy_ac.c": open(f"{tmp}/phy_ac.c").read(), "phy_ac.h": open(f"{tmp}/phy_ac.h").read()}

def kconfig(k):
    s = stock("Kconfig")
    if k < 13: return s
    s = s.replace('bool "Support for AC-PHY (802.11ac) devices (BROKEN)"\n\tdepends on B43 && B43_BCMA && BROKEN',
                  'bool "Support for AC-PHY (802.11ac) devices (EXPERIMENTAL)"\n\tdepends on B43 && B43_BCMA')
    s = s.replace("\tSay N, this is BROKEN and crashes driver.\n",
                  "\tThe support is experimental: there is no TX calibration, no\n\thardware crypto and no power save.\n\n\tSay N unless you have such a device and want to test it.\n")
    return s

def write(f, text):
    open(f"{D}/{f}", "w").write(text)

git("checkout", "-q", "-B", "series", root)
env = dict(os.environ, GIT_AUTHOR_NAME="Andreas Wendleder", GIT_AUTHOR_EMAIL="andreas.wendleder@proton.me",
           GIT_COMMITTER_NAME="Andreas Wendleder", GIT_COMMITTER_EMAIL="andreas.wendleder@proton.me")
for k, (subject, body) in enumerate(M, 1):
    for f in ASSIGN:
        write(f, staged(f, k))
    for kk, files in NEWFILES.items():
        if kk <= k:
            for f in files: write(f, final(f))
    write("phy_ac.c", final("phy_ac.c") if k >= 11 else (stageA["phy_ac.c"] if k >= 8 else stock("phy_ac.c")))
    write("phy_ac.h", final("phy_ac.h") if k >= 11 else (stageA["phy_ac.h"] if k >= 8 else stock("phy_ac.h")))
    if k < 7:
        write("Makefile", stock("Makefile"))
    write("Kconfig", kconfig(k))
    git("add", "-A")
    if not git("status", "--porcelain").strip():
        sys.exit(f"cut: patch {k} is empty")
    msg = f"{subject}\n\n{body}\n"
    subprocess.check_call(["git", "-C", repo, "commit", "-q", "-m", msg], env=env)
    r = subprocess.run(["bash", f"{proj}/tools/build_upstream_tree.sh", repo, KDEV], capture_output=True, text=True)
    new_warn = [l for l in r.stdout.splitlines() if "warning" in l and not re.search(r"phy_lcn|tables_phy_lcn|dma\.c:1[45]", l)]
    status = "OK" if "built OK" in r.stdout else "BUILD FAILED"
    print(f"{k:2d} {status}  {subject[:70]}" + (f"  [{len(new_warn)} warnings]" if new_warn else ""))
    for l in new_warn[:5]: print("      ", l[:140])
    if status != "OK":
        print(r.stdout[-1500:]); sys.exit(1)
# the end state must equal the final tree
d = git("diff", "--stat", "final", "series", "--", ".").strip()
print("series vs final:", d if d else "identical")
