import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.Memory;

public class dump_bytes extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Memory mem = currentProgram.getMemory();
        for (int i = 0; i < args.length; i += 2) {
            Address addr = toAddr("0x" + args[i]);
            int len = Integer.parseInt(args[i + 1]);
            byte[] buf = new byte[len];
            mem.getBytes(addr, buf);
            StringBuilder sb = new StringBuilder();
            for (byte b : buf) {
                sb.append(String.format("%02x ", b));
            }
            println(args[i] + " (" + len + " bytes): " + sb.toString());
        }
    }
}
