
undefined4 si_coreid(long param_1)

{
  return *(undefined4 *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4);
}

