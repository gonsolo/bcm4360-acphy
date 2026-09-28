import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.address.Address;
import java.io.File;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Map;

// Binary already disassembled. Find every instruction whose operand value
// exactly equals a known function's entry address (an "address taken" /
// function-pointer store, same strict-equality technique that already
// correctly found wlc_phy_btc_adjust_acphy at +0xf8 with zero false
// positives) - this time against ALL known functions, not just "acphy"-named
// ones, and only reporting hits whose instruction text shows a positive
// (non-stack, i.e. not "RBP + -0x..") displacement of 0xd8 or 0xa0.
public class find_addr_taken_refs_at_offset extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        FileWriter fw = new FileWriter(new File(args[0]));

        Map<Long, String> allFuncs = new HashMap<>();
        SymbolIterator it = currentProgram.getSymbolTable().getSymbolIterator();
        while (it.hasNext()) {
            Symbol s = it.next();
            Function f = getFunctionAt(s.getAddress());
            if (f != null) allFuncs.put(f.getEntryPoint().getOffset(), f.getName());
        }
        fw.write("known functions: " + allFuncs.size() + "\n");

        InstructionIterator insns = currentProgram.getListing().getInstructions(true);
        long count = 0, hits = 0;
        while (insns.hasNext()) {
            Instruction insn = insns.next();
            count++;
            String rep = insn.toString();
            boolean posDisp = (rep.contains("+ 0xd8") || rep.contains("+ 0xa0"));
            if (!posDisp) continue;
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
                    String name = allFuncs.get(val);
                    if (name == null) continue;
                    hits++;
                    Function container = getFunctionContaining(insn.getAddress());
                    fw.write("HIT " + name + " (0x" + Long.toHexString(val) + ") at "
                            + insn.getAddress() + " in "
                            + (container != null ? container.getName() : "?")
                            + " : " + rep + "\n");
                }
            }
        }
        fw.write("scanned " + count + " instructions, " + hits + " hits\n");
        fw.close();
        println("done, scanned " + count + " insns, " + hits + " hits");
    }
}
