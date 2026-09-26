
undefined8 wlc_bmac_xmtfifo_sz_get(long param_1,uint param_2,uint *param_3)

{
  undefined8 uVar1;
  
  uVar1 = 0xffffffe3;
  if (param_2 < 6) {
    *param_3 = (uint)*(ushort *)(*(long *)(param_1 + 0x150) + (ulong)param_2 * 2);
    uVar1 = 0;
  }
  return uVar1;
}

