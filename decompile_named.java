import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import java.io.File;
import java.io.FileWriter;

public class decompile_named extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File dir = new File(args[0]);
        dir.mkdirs();
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        for (int i = 1; i < args.length; i++) {
            Function f = null;
            if (args[i].matches("[0-9a-f]{8}")) {
                f = getFunctionAt(toAddr("0x" + args[i]));
            } else {
                for (Symbol s : currentProgram.getSymbolTable().getSymbols(args[i])) {
                    f = getFunctionAt(s.getAddress());
                    if (f != null) break;
                }
            }
            if (f == null) { println("not found: " + args[i]); continue; }
            DecompileResults r = ifc.decompileFunction(f, 60, monitor);
            if (!r.decompileCompleted()) { println("failed: " + args[i]); continue; }
            FileWriter fw = new FileWriter(new File(dir, f.getName() + ".c"));
            fw.write(r.getDecompiledFunction().getC());
            fw.close();
            println("ok: " + f.getName());
        }
    }
}
