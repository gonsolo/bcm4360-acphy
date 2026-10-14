#!/usr/bin/env python3
"""cut2.py REPO KDEV: cut the target tree (branch 'final2' of the series repo) into 14 commits on branch 'series2' (notes/166), in four series:
A 1-2 generic, B 3-5 core revisions 40/42, C 6-9 microcode formats, D 10-13 PHY, 14 RX refill retry (held back). Every commit is compile-tested with
tools/build_upstream_tree.sh. The base is the commit '2bd8d42' (stock b43 of v7.3-rc5 plus the use-after-free fix, sent separately).
Regions of a file (difflib opcodes between base and final2) are assigned to patches by number (tools/upstream/regions.py lists them)."""
import difflib, os, re, subprocess, sys
repo = os.path.abspath(sys.argv[1]); KDEV = sys.argv[2]
P = "drivers/net/wireless/broadcom/b43"; D = f"{repo}/{P}"
BASE = "2bd8d42"; FINAL = "final2"
here = os.path.dirname(os.path.abspath(__file__)); proj = os.path.abspath(f"{here}/../..")
sys.path.insert(0, here)
from messages2 import M as M_OLD
R = {1:1, 2:2, 4:3, 5:4, 6:5, 7:6, 8:7, 9:8, 10:9, 11:10, 12:11, 13:12, 14:13, 3:14}   # old number -> new number
M = [M_OLD[o - 1] for o in sorted(R, key=lambda o: R[o])]

def git(*a, **kw):
    return subprocess.check_output(["git", "-C", repo, *a], text=True, **kw)
def stock(f): return git("show", f"{BASE}:{P}/{f}")
def final(f): return git("show", f"{FINAL}:{P}/{f}")

# patch number (1-based) per region of each file
ASSIGN = {
 "main.c": {1:13, 2:13, 3:12, 4:6, 5:6, 6:5, 7:8, 8:8, 9:6, 10:6, 11:6, 12:6, 13:6, 14:5, 15:6, 16:6, 17:5, 18:5, 19:5,
            20:5, 21:3, 22:5, 23:5, 24:1, 25:10, 26:10, 27:12, 28:13, 29:10},
 "xmit.c": {1:8, 2:8, 3:9, 4:9, 5:9, 6:9, 7:9, 8:10},
 "xmit.h": {1:8, 2:8, 3:8, 4:10, 5:10},
 "dma.c":  {1:10, 2:2, 3:2, 4:2, 5:2, 6:2, 7:2, 8:10, 9:8, 10:10, 11:10, 12:10, 13:3, 14:3, 15:3},
 "dma.h":  {1:2, 2:2, 3:3, 4:2, 5:8, 6:3},
 "b43.h":  {1:2, 2:4, 3:5},
 "phy_common.c": {1:7, 2:7},
 "phy_common.h": {1:7},
}
# files first present in patch N
NEWFILES = {11: ["radio_2069.c", "radio_2069.h", "tables_phy_ac.c", "tables_phy_ac.h", "Makefile"],
            12: ["phy_ac_farrow.h"]}

# text that a region of the final tree has in an earlier form before a later patch: (file, first patch with the final text, final, earlier)
def lines(*l): return "".join(x + "\n" for x in l)
OVERRIDES = [
 # the AC burst/prefetch bits arrive in patch 4
 ("dma.c", 4, lines("\t\t\tif (b43_is_ac_core(ring->dev))", "\t\t\t\tvalue |= B43_DMA64_TXCTL_AC;"), ""),
 ("dma.c", 4, lines("\t\t\tif (b43_is_ac_core(ring->dev))", "\t\t\t\tvalue |= B43_DMA64_RXCTL_AC;"), ""),
 ("dma.h", 4, "#define B43_DMA64_TXCTL_AC\t\t\t\t0x03780040\n", ""),
 ("dma.h", 4, "#define B43_DMA64_RXCTL_AC\t\t\t\t0x036c0000\n", ""),
 # the 80 MHz chanspec arrives in patch 13
 ("phy_common.c", 13, lines(
"/* Centre channel of the 80 MHz block a 5 GHz primary belongs to, 0 if none */",
"unsigned int b43_ac_80mhz_centre(unsigned int channel)",
"{",
"\tstatic const u8 centre[] = { 42, 58, 106, 122, 138, 155 };",
"\tunsigned int i;",
"",
"\tfor (i = 0; i < ARRAY_SIZE(centre); i++)",
"\t\tif (channel >= centre[i] - 6u && channel <= centre[i] + 6u &&",
"\t\t    (channel - (centre[i] - 6u)) % 4 == 0)",
"\t\t\treturn centre[i];",
"\treturn 0;",
"}",
"",
"/*",
" * The 11ac chanspec of a primary channel as the AC microcode takes it in",
" * SHM and in the TX and RX headers: channel, 0x1000 for 20 MHz, 0xc000 on",
" * 5 GHz. In 80 MHz mode (every 5 GHz channel inside an 80 MHz block) the",
" * centre channel, 0x2000 for the width and the primary's position in the",
" * block in bits 10:8 (primary channel 112: 0xe36a).",
" */",
"u16 b43_ac_chanspec(struct b43_wldev *dev, unsigned int channel)",
"{",
"\tbool is_5ghz = b43_current_band(dev->wl) == NL80211_BAND_5GHZ;",
"\tunsigned int centre = is_5ghz ? b43_ac_80mhz_centre(channel) : 0;",
"",
"\tif (centre)",
"\t\treturn 0xe000 | (((channel - (centre - 6)) / 4) << 8) | centre;",
"\treturn channel | 0x1000 | (is_5ghz ? 0xc000 : 0);",
"}",
""),
  lines(
"/*",
" * The 11ac chanspec of a primary channel as the AC microcode takes it in",
" * SHM and in the TX and RX headers: channel, 0x1000 for 20 MHz, 0xc000 on",
" * 5 GHz.",
" */",
"u16 b43_ac_chanspec(struct b43_wldev *dev, unsigned int channel)",
"{",
"\treturn channel | 0x1000 |",
"\t       (b43_current_band(dev->wl) == NL80211_BAND_5GHZ ? 0xc000 : 0);",
"}",
"")),
 ("phy_common.h", 13, lines(
"/* 11ac chanspec of the AC microcode, and the centre channel of the 80 MHz block of a 5 GHz primary (0: none) */",
"u16 b43_ac_chanspec(struct b43_wldev *dev, unsigned int channel);",
"unsigned int b43_ac_80mhz_centre(unsigned int channel);"),
  lines(
"/* 11ac chanspec of the AC microcode */",
"u16 b43_ac_chanspec(struct b43_wldev *dev, unsigned int channel);")),
]

ASSIGN = {f: {n: R[v] for n, v in d.items()} for f, d in ASSIGN.items()}
NEWFILES = {R[k]: v for k, v in NEWFILES.items()}
OVERRIDES = [(f, R[first], a, b) for f, first, a, b in OVERRIDES]

def staged(f, k):
    a = stock(f).splitlines(keepends=True); b = final(f).splitlines(keepends=True)
    out = []; n = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag == "equal":
            out += a[i1:i2]; continue
        n += 1
        out += b[j1:j2] if ASSIGN[f][n] <= k else a[i1:i2]
    if n != max(ASSIGN[f]):
        sys.exit(f"cut2: {f}: region count changed ({n} vs {max(ASSIGN[f])}), re-assign")
    text = "".join(out)
    for of, first, fin, early in OVERRIDES:
        if of == f and k < first:
            # only if the region is already in (assigned <= k) the final text is present
            if fin in text:
                text = text.replace(fin, early, 1)
    return text

# stage A of phy_ac.c/.h (2.4 GHz only)
tmp = subprocess.check_output(["mktemp", "-d"], text=True).strip()
fin = subprocess.check_output(["mktemp", "-d"], text=True).strip()
subprocess.run(f"git -C {repo} archive {FINAL} {P} | tar -x -C {fin}", shell=True, check=True)
subprocess.check_call(["nix-shell", "-p", "python3", "--run",
                       f"python3 -I {here}/stage_a2.py {fin}/{P} {tmp}"], stdout=subprocess.DEVNULL)
stageA = {"phy_ac.c": open(f"{tmp}/phy_ac.c").read(), "phy_ac.h": open(f"{tmp}/phy_ac.h").read()}

def kconfig(k):
    s = stock("Kconfig")
    if k < R[14]: return s
    s = s.replace('bool "Support for AC-PHY (802.11ac) devices (BROKEN)"\n\tdepends on B43 && B43_BCMA && BROKEN',
                  'bool "Support for AC-PHY (802.11ac) devices (EXPERIMENTAL)"\n\tdepends on B43 && B43_BCMA')
    s = s.replace("\tSay N, this is BROKEN and crashes driver.\n",
                  "\tThe support is experimental: there is no TX calibration, no\n\thardware crypto and no power save.\n\n\tSay N unless you have such a device and want to test it.\n")
    return s

def write(f, text):
    open(f"{D}/{f}", "w").write(text)

git("checkout", "-q", "-B", "series2", BASE)
env = dict(os.environ, GIT_AUTHOR_NAME="Andreas Wendleder", GIT_AUTHOR_EMAIL="gonsolo@gmail.com",
           GIT_COMMITTER_NAME="Andreas Wendleder", GIT_COMMITTER_EMAIL="gonsolo@gmail.com")
for k, (subject, body) in enumerate(M, 1):
    for f in ASSIGN:
        write(f, staged(f, k))
    for kk, files in NEWFILES.items():
        if kk <= k:
            for f in files: write(f, final(f))
    write("phy_ac.c", final("phy_ac.c") if k >= R[13] else (stageA["phy_ac.c"] if k >= R[12] else stock("phy_ac.c")))
    write("phy_ac.h", final("phy_ac.h") if k >= R[13] else (stageA["phy_ac.h"] if k >= R[12] else stock("phy_ac.h")))
    if k < R[11]:
        write("Makefile", stock("Makefile"))
    write("Kconfig", kconfig(k))
    git("add", "-A")
    if not git("status", "--porcelain").strip():
        sys.exit(f"cut2: patch {k} is empty")
    msg = f"{subject}\n\n{body}\n"
    subprocess.check_call(["git", "-C", repo, "commit", "-q", "-m", msg], env=env)
    r = subprocess.run(["bash", f"{proj}/tools/build_upstream_tree.sh", repo, KDEV], capture_output=True, text=True)
    new_warn = [l for l in r.stdout.splitlines() if "warning" in l and not re.search(r"phy_lcn|tables_phy_lcn|dma\.c:1[45]", l)]
    status = "OK" if "built OK" in r.stdout else "BUILD FAILED"
    print(f"{k:2d} {status}  {subject[:70]}" + (f"  [{len(new_warn)} warnings]" if new_warn else ""), flush=True)
    for l in new_warn[:5]: print("      ", l[:140])
    if status != "OK":
        print("rc", r.returncode); print(r.stdout[-1500:]); print(r.stderr[-1500:]); sys.exit(1)
d = git("diff", "--stat", FINAL, "series2", "--", ".").strip()
print("series2 vs final2:", d if d else "identical")
