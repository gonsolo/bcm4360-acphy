// List functions containing an instruction with any of the given scalar
// operands. args: <hex imm> [<hex imm> ...]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.util.*;

public class find_imm extends GhidraScript {
	@Override
	public void run() throws Exception {
		Set<Long> want = new HashSet<>();
		for (String a : getScriptArgs())
			want.add(Long.parseLong(a, 16));
		Map<String, Set<String>> hits = new TreeMap<>();
		InstructionIterator it = currentProgram.getListing().getInstructions(true);
		while (it.hasNext()) {
			Instruction ins = it.next();
			for (int i = 0; i < ins.getNumOperands(); i++) {
				for (Object o : ins.getOpObjects(i)) {
					if (!(o instanceof Scalar))
						continue;
					long v = ((Scalar) o).getUnsignedValue();
					if (!want.contains(v))
						continue;
					Function f = getFunctionContaining(ins.getAddress());
					String fn = f == null ? "(none)" : f.getName() + "@" + f.getEntryPoint();
					hits.computeIfAbsent(fn, k -> new TreeSet<>())
					    .add(String.format("0x%x@%s", v, ins.getAddress()));
				}
			}
		}
		for (Map.Entry<String, Set<String>> e : hits.entrySet())
			println("HIT " + e.getKey() + " " + e.getValue());
	}
}
