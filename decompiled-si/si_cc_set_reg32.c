
undefined4 si_cc_set_reg32(uint param_1,undefined4 param_2)

{
  *(undefined4 *)((ulong)param_1 + 0x18000000) = param_2;
  return *(undefined4 *)((ulong)param_1 + 0x18000000);
}

