import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;
import java.io.File;
import java.io.FileWriter;

public class decompile_dma extends GhidraScript {

    DecompInterface ifc;
    File dir;

    void dump(Function f, String name) throws Exception {
        DecompileResults res = ifc.decompileFunction(f, 120, monitor);
        if (!res.decompileCompleted()) {
            println("FAILED: " + name);
            return;
        }
        FileWriter fw = new FileWriter(new File(dir, name + ".c"));
        fw.write(res.getDecompiledFunction().getC());
        fw.close();
    }

    @Override
    public void run() throws Exception {
        dir = new File(getScriptArgs()[0]);
        dir.mkdirs();
        ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        for (String n : new String[] {"dma_attach", "dma_addrwidth", "dma_txpioloopback"}) {
            for (Symbol s : currentProgram.getSymbolTable().getSymbols(n)) {
                Function f = getFunctionAt(s.getAddress());
                if (f != null) dump(f, n);
            }
        }

        for (Symbol s : currentProgram.getSymbolTable().getSymbols("dma64proc")) {
            Address start = s.getAddress();
            Data d = getDataAt(start);
            long len = (d != null) ? d.getLength() : 0x200;
            println("dma64proc at " + start + " len " + len);
            for (long off = 0; off < len; off += 8) {
                Address a = start.add(off);
                long ptr = getLong(a);
                Address target = toAddr(ptr);
                Function f = getFunctionAt(target);
                if (f == null) {
                    f = getFunctionContaining(target);
                }
                if (f == null) {
                    println("  slot " + (off / 8) + " -> " + Long.toHexString(ptr) + " (no function)");
                    continue;
                }
                String name = String.format("dma64proc_%02d_%s", off / 8, f.getName());
                println("  slot " + (off / 8) + " -> " + f.getName());
                dump(f, name);
            }
        }
    }
}
