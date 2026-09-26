
void wlc_bmac_mctrl(long param_1,uint param_2,uint param_3)

{
  param_3 = ~param_2 & *(uint *)(param_1 + 0x168) | param_3;
  if (param_3 != *(uint *)(param_1 + 0x168)) {
    *(uint *)(param_1 + 0x168) = param_3;
    FUN_001612ed();
  }
  return;
}

