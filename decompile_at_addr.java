import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.io.File;
import java.io.FileWriter;

public class decompile_at_addr extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File dir = new File(args[0]);
        dir.mkdirs();
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        for (int i = 1; i < args.length; i++) {
            Address addr = toAddr("0x" + args[i]);
            Function f = getFunctionAt(addr);
            if (f == null) {
                f = createFunction(addr, null);
            }
            if (f == null) {
                println("could not create function at: " + args[i]);
                continue;
            }
            DecompileResults r = ifc.decompileFunction(f, 60, monitor);
            if (!r.decompileCompleted()) { println("failed: " + args[i]); continue; }
            String name = f.getName();
            FileWriter fw = new FileWriter(new File(dir, name + ".c"));
            fw.write(r.getDecompiledFunction().getC());
            fw.close();
            println("ok: " + args[i] + " -> " + name);
        }
    }
}
