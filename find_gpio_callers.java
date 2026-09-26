import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;

public class find_gpio_callers extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] targets = {"si_gpioout", "si_gpioouten", "si_gpiocontrol"};
        for (String name : targets) {
            for (Symbol s : currentProgram.getSymbolTable().getSymbols(name)) {
                println("=== " + name + " at " + s.getAddress() + " ===");
                for (Reference r : currentProgram.getReferenceManager().getReferencesTo(s.getAddress())) {
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    println("  called from " + (f != null ? f.getName() : "?") + " @ " + r.getFromAddress());
                }
            }
        }
    }
}
