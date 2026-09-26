
undefined8 wlc_bmac_seci_upd(undefined8 *param_1)

{
  int iVar1;
  undefined8 uStack_18;
  
  if (((((*(byte *)((long)param_1 + 0x8c) & 1) != 0) && (-1 < *(char *)(param_1 + 0x12))) &&
      ((*(byte *)(param_1[0x17] + 0x1c) & 1) != 0)) &&
     ((*(byte *)((long)param_1 + 0xa7) & 0x20) != 0)) {
    iVar1 = wlc_btc_mode_get(*param_1);
    if (iVar1 != 0) {
      si_seci_upd(param_1[0x17],1);
    }
  }
  return uStack_18;
}

