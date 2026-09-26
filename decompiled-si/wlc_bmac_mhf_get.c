
undefined8 wlc_bmac_mhf_get(long param_1,byte param_2,int param_3)

{
  long lVar1;
  
  if (param_3 == 1) {
    lVar1 = *(long *)(param_1 + 0xf8);
  }
  else if (param_3 == 2) {
    lVar1 = *(long *)(param_1 + 0xf0);
  }
  else {
    if (param_3 != 0) {
      return 0;
    }
    lVar1 = *(long *)(param_1 + 0xe8);
  }
  if (lVar1 == 0) {
    return 0;
  }
  return CONCAT62((int6)((ulong)lVar1 >> 0x10),*(undefined2 *)(lVar1 + 8 + (ulong)param_2 * 2));
}

