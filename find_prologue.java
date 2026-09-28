// Print candidate function entries ("55 48 89 e5" = push rbp; mov rbp,rsp)
// in [start, end), with the byte before each. args: <start hex> <end hex>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;

public class find_prologue extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] a = getScriptArgs();
		Address s = toAddr("0x" + a[0]), e = toAddr("0x" + a[1]);
		for (Address p = s; p.compareTo(e) < 0; p = p.add(1)) {
			if ((getByte(p) & 0xff) == 0x55 && (getByte(p.add(1)) & 0xff) == 0x48 &&
			    (getByte(p.add(2)) & 0xff) == 0x89 && (getByte(p.add(3)) & 0xff) == 0xe5)
				println(String.format("PROLOGUE %s prev=%02x", p, getByte(p.subtract(1)) & 0xff));
		}
	}
}
