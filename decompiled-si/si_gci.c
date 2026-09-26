
uint si_gci(long param_1)

{
  return *(uint *)(param_1 + 0x1c) & 4;
}

