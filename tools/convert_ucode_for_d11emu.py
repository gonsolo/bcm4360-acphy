#!/usr/bin/env python3
"""Convert a b43 ucode .fw file into the raw instruction format expected by
seemoo-lab/d11-emu (https://github.com/seemoo-lab/d11-emu).

b43's .fw format is an 8-byte b43_fw_header (see b43-src/b43.h) followed by
the raw ucode as big-endian 32-bit words, two words per 64-bit instruction
(this is how b43_upload_microcode() in b43-src/main.c writes it to hardware,
one 32-bit MMIO write per word, auto-incrementing the SHM_UCODE address).

d11emu's loader (src/emu.rs load_ucode()) instead expects one 64-bit
instruction per 8 bytes, decoded via u64::from_le_bytes(). Empirically
verified against b43-asm's own "-f raw-le32" test output (see notes/12):
same word order as the b43 format, each 32-bit word individually
byte-swapped to little-endian. This script does exactly that: strip the
header, byte-swap every 32-bit word, keep the word order unchanged.

usage: convert_ucode_for_d11emu.py ucode42.fw ucode42_le.bin
"""
import sys
import struct

B43_FW_HEADER_LEN = 8


def convert(inpath: str, outpath: str) -> None:
    with open(inpath, "rb") as f:
        data = f.read()

    body = data[B43_FW_HEADER_LEN:]
    if len(body) % 4 != 0:
        raise ValueError(f"body length {len(body)} is not a multiple of 4")

    words = struct.unpack(f">{len(body) // 4}I", body)
    out = struct.pack(f"<{len(words)}I", *words)

    with open(outpath, "wb") as f:
        f.write(out)

    print(f"{inpath}: {len(data)} bytes -> stripped {B43_FW_HEADER_LEN}-byte "
          f"header -> {len(words)} words ({len(words) // 2} instructions) "
          f"-> {outpath}")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)
    convert(sys.argv[1], sys.argv[2])
