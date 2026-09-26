
undefined8 wlc_bmac_btc_flags_idx_set(undefined8 param_1,byte param_2,int param_3)

{
  undefined8 uVar1;
  uint uVar2;
  
  uVar1 = 0xfffffffe;
  if (param_2 < 9) {
    if (param_3 == 0) {
      uVar2 = 1 << (param_2 & 0x1f);
    }
    else {
      uVar2 = param_3 << (param_2 & 0x1f);
    }
    FUN_00163822(param_1,param_3 != 0,uVar2 & 0xffff,btc_ucode_flags[(ulong)param_2 * 4],
                 *(undefined2 *)(btc_ucode_flags + (ulong)param_2 * 4 + 2));
    uVar1 = 0;
  }
  return uVar1;
}

