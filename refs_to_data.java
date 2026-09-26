import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;
import java.io.File;
import java.io.FileWriter;

// Args: <outdir> <hexaddr>...  For each address, find the enclosing labelled
// data object, then decompile every function that references anywhere inside it.
public class refs_to_data extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File dir = new File(args[0]);
        dir.mkdirs();
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        for (int i = 1; i < args.length; i++) {
            Address a = toAddr(args[i]);
            Symbol s = null;
            Address start = a;
            for (int back = 0; back < 0x400 && s == null; back += 8) {
                Address p = a.subtract(back);
                Symbol[] syms = currentProgram.getSymbolTable().getSymbols(p);
                if (syms.length > 0) {
                    s = syms[0];
                    start = p;
                }
            }
            println(args[i] + " is inside " + (s != null ? s.getName() : "?") + " @ " + start
                    + " (offset " + a.subtract(start) + ")");
            for (long off = 0; off < 0x400; off += 8) {
                for (Reference r : getReferencesTo(start.add(off))) {
                    Function f = getFunctionContaining(r.getFromAddress());
                    if (f == null) continue;
                    println("  ref to +" + off + " from " + f.getName());
                    DecompileResults res = ifc.decompileFunction(f, 120, monitor);
                    if (res.decompileCompleted()) {
                        FileWriter fw = new FileWriter(new File(dir, f.getName() + ".c"));
                        fw.write(res.getDecompiledFunction().getC());
                        fw.close();
                    }
                }
            }
        }
    }
}
