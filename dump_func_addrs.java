import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import java.io.File;
import java.io.FileWriter;

// Dump every known function's name and GHIDRA-NATIVE address (its own
// coordinate space, not the raw kernel/kallsyms address space), sorted by
// address, so containing-function lookups can be done correctly.
public class dump_func_addrs extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        FileWriter fw = new FileWriter(new File(args[0]));
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        while (it.hasNext()) {
            Function f = it.next();
            fw.write(f.getEntryPoint().getOffset() + " " + f.getEntryPoint() + " " + f.getName() + "\n");
        }
        fw.close();
        println("done");
    }
}
