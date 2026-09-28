// Dump wl's Farrow resampler tables: per entry "chan v4 v6 v8 v10".
// args: <symbol> [<symbol> ...]; each is 3 bandwidths x 123 entries x 12 B.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Symbol;

public class dump_farrow extends GhidraScript {
	@Override
	public void run() throws Exception {
		for (String name : getScriptArgs()) {
			for (Symbol sym : currentProgram.getSymbolTable().getSymbols(name)) {
				Address base = sym.getAddress();
				for (int bw = 0; bw < 3; bw++) {
					StringBuilder sb = new StringBuilder();
					for (int i = 0; i < 123; i++) {
						Address e = base.add(bw * 0x5c4 + i * 12);
						int ch = getByte(e) & 0xff;
						if (ch == 0)
							continue;
						sb.append(String.format(" %d:%04x,%04x,%04x,%04x", ch,
							getShort(e.add(4)) & 0xffff, getShort(e.add(6)) & 0xffff,
							getShort(e.add(8)) & 0xffff, getShort(e.add(10)) & 0xffff));
					}
					println("FARROW " + name + " bw" + bw + sb);
				}
			}
		}
	}
}
