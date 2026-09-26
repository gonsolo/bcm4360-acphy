
uint si_backplane64(long param_1)

{
  return *(uint *)(param_1 + 0x18) >> 0x1b & 1;
}

