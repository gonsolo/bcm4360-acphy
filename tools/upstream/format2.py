#!/usr/bin/env python3
"""format2.py REPO OUTDIR: git format-patch the 14 commits of branch 'series2' into four series A (1-3), B (4-6), C (7-10), D (11-14),
each with its cover letter from messages2.COVERS, plus one mbox per series (OUTDIR/<X>/series-<X>.mbox).
Series A is sent as [PATCH wireless-next n/3], the later ones as [PATCH RFC wireless-next n/m]. No Signed-off-by lines (the sender adds them)."""
import os, re, subprocess, sys
repo = os.path.abspath(sys.argv[1]); out = os.path.abspath(sys.argv[2])
here = os.path.dirname(os.path.abspath(__file__)); sys.path.insert(0, here)
from messages2 import COVERS
BASE = "2bd8d42"
SERIES = {"A": (0, 2), "B": (2, 5), "C": (5, 9), "D": (9, 13), "X": (13, 14)}   # X: held back, not proven
def git(*a): return subprocess.check_output(["git", "-C", repo, "-c", "user.name=Andreas Wendleder", "-c", "user.email=gonsolo@gmail.com", *a], text=True)
commits = git("rev-list", "--reverse", f"{BASE}..series2").split()
assert len(commits) == 14, len(commits)
for name, (a, b) in SERIES.items():
    d = f"{out}/{name}"; os.makedirs(d, exist_ok=True)
    for f in os.listdir(d): os.remove(f"{d}/{f}")
    first = commits[a] + "^"; last = commits[b - 1]
    prefix = "PATCH wireless-next" if name == "A" else "PATCH RFC wireless-next"
    if name == "X":
        git("format-patch", "-q", "--no-signature", f"--subject-prefix={prefix}", "-o", d, f"{first}..{last}")
        print(name, "held back:", os.listdir(d)); continue
    git("format-patch", "-q", "--cover-letter", "--no-signature", f"--subject-prefix={prefix}", "-o", d, f"{first}..{last}")
    cover = [f for f in os.listdir(d) if f.startswith("0000")][0]
    subj, body = COVERS[name]
    s = open(f"{d}/{cover}").read()
    assert "*** SUBJECT HERE ***" in s and "*** BLURB HERE ***" in s
    s = s.replace("*** SUBJECT HERE ***", subj).replace("*** BLURB HERE ***", body.rstrip("\n"))
    open(f"{d}/{cover}", "w").write(s)
    files = sorted(f for f in os.listdir(d) if f.endswith(".patch"))
    with open(f"{d}/series-{name}.mbox", "w") as m:
        for f in files:
            t = open(f"{d}/{f}").read()
            m.write(t if t.startswith("From ") else "")
    print(name, len(files) - 1, "patches +cover", f"{d}")
