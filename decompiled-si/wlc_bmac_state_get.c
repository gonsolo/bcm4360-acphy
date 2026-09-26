
undefined1  [16] wlc_bmac_state_get(long param_1,undefined4 *param_2)

{
  undefined1 auVar1 [16];
  char cVar2;
  ulong uStack_18;
  
  *param_2 = *(undefined4 *)(param_1 + 0xa4);
  cVar2 = wlc_phy_preamble_override_get(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28));
  param_2[1] = (int)cVar2;
  auVar1._8_8_ = 0;
  auVar1._0_8_ = uStack_18;
  return auVar1 << 0x40;
}

