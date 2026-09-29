import json, sys

state_in, shm_txt, ihr_txt, pc_hex, state_out = sys.argv[1:6]
d = json.load(open(state_in))

shm = d['shared_memory']
with open(shm_txt) as f:
    for line in f:
        parts = line.split()
        if len(parts) != 2:
            continue
        byte_off = int(parts[0], 16)
        val = int(parts[1], 16)
        word = byte_off // 2
        if word < len(shm):
            shm[word] = val

if ihr_txt != '-':
    ihr = d['internal_hardware_registers']
    with open(ihr_txt) as f:
        for line in f:
            parts = line.split()
            if len(parts) != 2:
                continue
            word = int(parts[0], 16)
            val = int(parts[1], 16)
            if word < len(ihr):
                ihr[word] = val

d['pc'] = int(pc_hex, 16)
d['running'] = True
# num_ucode_instructions is a bounds limit for set_pc(), not a counter to
# reset - leave it as whatever the real loaded ucode reported (do not touch).

json.dump(d, open(state_out, 'w'))
print(f"seeded {state_out}: pc={hex(d['pc'])}, shm[0x2f/0x30/0x31]={hex(shm[0x2f])}/{hex(shm[0x30])}/{hex(shm[0x31])}")
