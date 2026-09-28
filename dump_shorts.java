// Dump little-endian u16/u8 values at raw Ghidra addresses.
// args: <addr_hex> <count> [u8]  (repeatable in groups of 2 or 3)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;

public class dump_shorts extends GhidraScript {
	@Override
	public void run() throws Exception {
		String[] a = getScriptArgs();
		int i = 0;
		while (i + 1 < a.length) {
			Address base = toAddr("0x" + a[i]);
			int n = Integer.parseInt(a[i + 1]);
			boolean u8 = i + 2 < a.length && a[i + 2].equals("u8");
			StringBuilder sb = new StringBuilder(a[i] + ":");
			for (int k = 0; k < n; k++) {
				int v = u8 ? (getByte(base.add(k)) & 0xff)
					   : (getShort(base.add(2L * k)) & 0xffff);
				sb.append(" ").append(v);
			}
			println(sb.toString());
			i += u8 ? 3 : 2;
		}
	}
}
