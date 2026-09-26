import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class decompile_acphy extends GhidraScript {

    static boolean funcNameMatches(Function f, String[] patterns) {
        String lname = f.getName().toLowerCase();
        for (String p : patterns) {
            if (lname.contains(p)) return true;
        }
        return false;
    }

    int decompileOne(DecompInterface ifc, Function f, File dir) {
        try {
            DecompileResults res = ifc.decompileFunction(f, 60, monitor);
            if (res.decompileCompleted()) {
                String code = res.getDecompiledFunction().getC();
                File out = new File(dir, f.getName() + ".c");
                FileWriter fw = new FileWriter(out);
                fw.write(code);
                fw.close();
                return 1;
            } else {
                println("FAILED: " + f.getName() + " " + res.getErrorMessage());
            }
        } catch (Exception e) {
            println("EXCEPTION on " + f.getName() + ": " + e.getMessage());
        }
        return 0;
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outDir = args.length > 0 ? args[0] : "/tmp/acphy_decompiled";
        File dir = new File(outDir);
        if (!dir.exists()) dir.mkdirs();

        String[] patterns = {"acphy", "_ac0", "_ac1", "_ac2", "_ac3", "_ac6",
            "phy_reg_mod", "phy_reg_write", "phy_reg_read", "mod_radio_reg",
            "write_radio_reg", "read_radio_reg", "and_radio_reg", "or_radio_reg",
            "xor_radio_reg", "gen_radio_reg", "wlc_phy_write_table_ext",
            "wlc_phy_read_table_ext", "wlapi_suspend_mac_and_wait",
            "wlapi_enable_mac", "cal_perical", "mphase", "init_radio_prefregs"};

        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        int count = 0;

        String[] explicitAddrs = {
            "00190879", "00190fbd", "001a08b2", "0019665e", "001a1202", "001a7dc9",
            "0019330c", "001ac9b6", "001aeb3a", "00193e5b", "00194b87",
            "001b0ce9", "001b1f67",
            "00193d3a", "0019454f", "00195603", "001982a2",
            "0019ccd9", "0019d3ac", "0019d550", "0019d65d",
            "00199491", "0019d224", "001986fc", "00161ca7", "0010f3af", "001a1924", "001a784f", "0019f839", "0019173d", "0019bc45", "0019ae61", "0019b279", "00196f43", "00193c3b", "0019a2eb"
        };
        for (String a : explicitAddrs) {
            Function f = getFunctionAt(toAddr("0x" + a));
            if (f != null) {
                count += decompileOne(ifc, f, dir);
            } else {
                println("no function at 0x" + a);
            }
        }

        FunctionIterator fiter = currentProgram.getFunctionManager().getFunctions(true);
        List<Function> funcs = new ArrayList<Function>();
        while (fiter.hasNext()) {
            funcs.add(fiter.next());
        }
        println("Total functions: " + funcs.size());

        for (Function f : funcs) {
            if (!funcNameMatches(f, patterns)) continue;
            count += decompileOne(ifc, f, dir);
        }

        println("Decompiled " + count + " functions to " + outDir);
    }
}
