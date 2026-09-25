# Ghidra headless postScript: decompile all functions whose name matches
# our target patterns and dump each to its own .c file under OUT_DIR.
# Run via analyzeHeadless ... -postScript decompile_acphy.py <out_dir>

import os
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

args = getScriptArgs()
out_dir = args[0] if len(args) > 0 else "/tmp/acphy_decompiled"
if not os.path.exists(out_dir):
    os.makedirs(out_dir)

patterns = ["acphy", "_ac0", "_ac1", "_ac2", "_ac3", "_ac6"]

fm = currentProgram.getFunctionManager()
monitor = ConsoleTaskMonitor()

ifc = DecompInterface()
ifc.openProgram(currentProgram)

count = 0
funcs = list(fm.getFunctions(True))
println("Total functions in program: %d" % len(funcs))

for f in funcs:
    name = f.getName()
    lname = name.lower()
    if not any(p in lname for p in patterns):
        continue
    try:
        res = ifc.decompileFunction(f, 60, monitor)
        if res.decompileCompleted():
            code = res.getDecompiledFunction().getC()
            fname = os.path.join(out_dir, name + ".c")
            with open(fname, "w") as fh:
                fh.write(code)
            count += 1
        else:
            println("FAILED to decompile: %s (%s)" % (name, res.getErrorMessage()))
    except Exception as e:
        println("EXCEPTION on %s: %s" % (name, str(e)))

println("Decompiled %d functions to %s" % (count, out_dir))
