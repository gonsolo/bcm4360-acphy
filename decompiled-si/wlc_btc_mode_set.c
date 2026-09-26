
undefined4 wlc_btc_mode_set(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = wlc_bmac_btc_mode_set(*(undefined8 *)(param_1 + 0x20));
  lVar1 = *(long *)(param_1 + 0x690);
  uVar3 = wlc_bmac_btc_mode_get(*(undefined8 *)(param_1 + 0x20));
  *(undefined4 *)(lVar1 + 0xc) = uVar3;
  return uVar2;
}

