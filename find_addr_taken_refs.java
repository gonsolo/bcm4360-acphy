import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolType;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.address.Address;
import java.io.File;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Map;

// This project's -noanalysis import never persisted disassembly into the
// Listing at all (getInstructions() returns 0 program-wide; decompilation
// apparently disassembles on the fly without storing it). Disassemble from
// every known function symbol first (fast, no semantic analysis passes),
// then scan every resulting instruction's raw operands for an immediate
// matching a target function's entry address - this finds "address taken"
// (function-pointer / vtable-population) sites.
public class find_addr_taken_refs extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args[0]);
        String needle = args[1];

        FileWriter fw = new FileWriter(out);

        int nsyms = 0, ndis = 0;
        SymbolIterator allSyms = currentProgram.getSymbolTable().getSymbolIterator();
        while (allSyms.hasNext()) {
            Symbol s = allSyms.next();
            if (s.getSymbolType() != SymbolType.FUNCTION) continue;
            nsyms++;
            try {
                if (getInstructionAt(s.getAddress()) == null) {
                    disassemble(s.getAddress());
                    ndis++;
                }
            } catch (Exception e) {
                // best-effort; skip failures
            }
        }
        fw.write("function symbols: " + nsyms + ", disassemble calls: " + ndis + "\n");

        Map<Long, String> targets = new HashMap<>();
        SymbolIterator it = currentProgram.getSymbolTable().getSymbolIterator();
        while (it.hasNext()) {
            Symbol s = it.next();
            if (!s.getName().toLowerCase().contains(needle.toLowerCase())) continue;
            Function f = getFunctionAt(s.getAddress());
            if (f == null) continue;
            targets.put(f.getEntryPoint().getOffset(), f.getName());
        }
        fw.write("scanning for " + targets.size() + " target functions\n");

        InstructionIterator insns = currentProgram.getListing().getInstructions(true);
        long count = 0, hits = 0;
        while (insns.hasNext()) {
            Instruction insn = insns.next();
            count++;
            int n = insn.getNumOperands();
            for (int i = 0; i < n; i++) {
                Object[] objs = insn.getOpObjects(i);
                for (Object o : objs) {
                    Long val = null;
                    if (o instanceof Scalar) {
                        val = ((Scalar) o).getUnsignedValue();
                    } else if (o instanceof Address) {
                        val = ((Address) o).getOffset();
                    }
                    if (val == null) continue;
                    String name = targets.get(val);
                    if (name != null) {
                        hits++;
                        Function container = getFunctionContaining(insn.getAddress());
                        fw.write("HIT " + name + " (0x" + Long.toHexString(val) + ") at "
                                + insn.getAddress() + " in "
                                + (container != null ? container.getName() : "?")
                                + " : " + insn.toString() + "\n");
                    }
                }
            }
        }
        fw.write("scanned " + count + " instructions, " + hits + " hits\n");
        fw.close();
        println("done, scanned " + count + " insns, " + hits + " hits");
    }
}
