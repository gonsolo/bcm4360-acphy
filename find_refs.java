import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.listing.Function;
import ghidra.program.model.address.Address;
import java.io.File;
import java.io.FileWriter;

public class find_refs extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outDir = args.length > 0 ? args[0] : "/tmp/refs_out";
        new File(outDir).mkdirs();

        String[] targets = {"acphytbl_info_rev0", "acphytbl_info_rev2", "acphytbl_info_rev3", "acphytbl_info_rev6", "acphytbl_info_sz_rev0"};

        SymbolTable st = currentProgram.getSymbolTable();
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        for (String name : targets) {
            for (Symbol sym : st.getSymbols(name)) {
                Address addr = sym.getAddress();
                println(name + " at " + addr);
                for (Reference ref : currentProgram.getReferenceManager().getReferencesTo(addr)) {
                    Address from = ref.getFromAddress();
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(from);
                    if (f == null) {
                        println("  ref from " + from + " (no function)");
                        continue;
                    }
                    println("  ref from " + from + " in function " + f.getName());
                    DecompileResults res = ifc.decompileFunction(f, 60, monitor);
                    if (res.decompileCompleted()) {
                        File out = new File(outDir, f.getName() + ".c");
                        FileWriter fw = new FileWriter(out);
                        fw.write(res.getDecompiledFunction().getC());
                        fw.close();
                        println("    decompiled -> " + out);
                    }
                }
            }
        }
    }
}
