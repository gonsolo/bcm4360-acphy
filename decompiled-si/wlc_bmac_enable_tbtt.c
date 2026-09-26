
void wlc_bmac_enable_tbtt(long param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = param_3 & param_2 | ~param_2 & *(uint *)(param_1 + 0xa0);
  *(uint *)(param_1 + 0xa0) = uVar1;
  if (uVar1 == 0) {
    *(uint *)(param_1 + 0x9c) = *(uint *)(param_1 + 0x9c) & 0xfdfffffb;
  }
  else {
    *(uint *)(param_1 + 0x9c) = *(uint *)(param_1 + 0x9c) | 0x2000004;
  }
  return;
}

