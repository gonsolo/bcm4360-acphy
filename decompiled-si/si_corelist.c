
undefined4 si_corelist(long param_1,undefined8 param_2)

{
  osl_memcpy(param_2,param_1 + 0x1c8,(ulong)*(uint *)(param_1 + 0x1c4) << 2);
  return *(undefined4 *)(param_1 + 0x1c4);
}

