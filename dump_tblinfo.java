import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Symbol;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;

// Args: <outdir> <list symbol> <count symbol>
// Dumps each {ptr, count, id, offset, width} entry of an acphytbl_info list:
// writes <outdir>/index.txt and one .bin per table with the raw data bytes.
public class dump_tblinfo extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File dir = new File(args[0]);
        dir.mkdirs();
        Address list = currentProgram.getSymbolTable().getSymbols(args[1]).next().getAddress();
        Address cnt = currentProgram.getSymbolTable().getSymbols(args[2]).next().getAddress();
        int n = getInt(cnt);
        FileWriter idx = new FileWriter(new File(dir, "index.txt"));
        for (int i = 0; i < n; i++) {
            Address e = list.add(i * 24L);
            Address data = toAddr(getLong(e));
            int count = getInt(e.add(8));
            int id = getInt(e.add(12));
            int offset = getInt(e.add(16));
            int width = getInt(e.add(20));
            int bytesPer;
            switch (width) {
                case 8: bytesPer = 1; break;
                case 16: bytesPer = 2; break;
                case 32: bytesPer = 4; break;
                case 48: bytesPer = 6; break;
                case 60: case 64: bytesPer = 8; break;
                default: bytesPer = 0;
            }
            Symbol s = getSymbolAt(data);
            String sym = (s != null) ? s.getName() : data.toString();
            String file = String.format("%02d_id%d_off%d.bin", i, id, offset);
            byte[] buf = getBytes(data, count * bytesPer);
            FileOutputStream fo = new FileOutputStream(new File(dir, file));
            fo.write(buf);
            fo.close();
            String line = String.format("%d %s id=%d offset=%d count=%d width=%d file=%s",
                                        i, sym, id, offset, count, width, file);
            println(line);
            idx.write(line + "\n");
        }
        idx.close();
    }
}
