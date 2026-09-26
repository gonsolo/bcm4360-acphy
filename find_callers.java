import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;

public class find_callers extends GhidraScript {
    @Override
    public void run() throws Exception {
        for (String name : getScriptArgs()) {
            for (Symbol s : currentProgram.getSymbolTable().getSymbols(name)) {
                println("=== " + name + " ===");
                for (Reference r : currentProgram.getReferenceManager().getReferencesTo(s.getAddress())) {
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    println("  from " + (f != null ? f.getName() : "?") + " @ " + r.getFromAddress());
                }
            }
        }
    }
}
