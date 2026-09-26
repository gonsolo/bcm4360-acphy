
uint si_eci(long param_1)

{
  return *(uint *)(param_1 + 0x18) >> 0x1d & 1;
}

