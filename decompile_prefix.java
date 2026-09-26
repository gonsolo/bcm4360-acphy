import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import java.io.File;
import java.io.FileWriter;

public class decompile_prefix extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File dir = new File(args[0]);
        dir.mkdirs();
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        int n = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            String name = f.getName();
            boolean match = false;
            for (int i = 1; i < args.length; i++)
                if (name.startsWith(args[i]) || name.contains(args[i])) match = true;
            if (!match) continue;
            DecompileResults r = ifc.decompileFunction(f, 60, monitor);
            if (!r.decompileCompleted()) continue;
            FileWriter fw = new FileWriter(new File(dir, name + ".c"));
            fw.write(r.getDecompiledFunction().getC());
            fw.close();
            n++;
        }
        println("decompiled " + n);
    }
}
