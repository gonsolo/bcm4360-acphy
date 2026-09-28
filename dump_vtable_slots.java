import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.Memory;
import java.io.File;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Map;

// Given a data symbol name (a vtable/ops table) and a list of byte offsets,
// read the 8-byte little-endian pointer at each offset and report which
// known function (if any) it matches.
public class dump_vtable_slots extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args[0]);
        String symName = args[1];

        Map<Long, String> allFuncs = new HashMap<>();
        SymbolIterator it = currentProgram.getSymbolTable().getSymbolIterator();
        Address symAddr = null;
        while (it.hasNext()) {
            Symbol s = it.next();
            if (s.getName().equals(symName) && symAddr == null) {
                symAddr = s.getAddress();
            }
            Function f = getFunctionAt(s.getAddress());
            if (f != null) allFuncs.put(f.getEntryPoint().getOffset(), f.getName());
        }

        FileWriter fw = new FileWriter(out);
        if (symAddr == null) {
            fw.write("symbol not found: " + symName + "\n");
            fw.close();
            println("done - not found");
            return;
        }
        fw.write(symName + " @ " + symAddr + "\n");
        Memory mem = currentProgram.getMemory();
        for (int i = 2; i < args.length; i++) {
            long off = Long.decode(args[i]);
            Address a = symAddr.add(off);
            byte[] b = new byte[8];
            try {
                mem.getBytes(a, b);
            } catch (Exception e) {
                fw.write(String.format("+0x%x: read failed: %s\n", off, e.getMessage()));
                continue;
            }
            long val = 0;
            for (int k = 7; k >= 0; k--) val = (val << 8) | (b[k] & 0xffL);
            String name = allFuncs.get(val);
            fw.write(String.format("+0x%x: 0x%x  %s\n", off, val, name != null ? name : "(unnamed/unresolved)"));
        }
        fw.close();
        println("done");
    }
}
