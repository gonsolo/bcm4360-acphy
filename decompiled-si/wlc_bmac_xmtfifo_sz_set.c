
undefined1  [16] wlc_bmac_xmtfifo_sz_set(long param_1,uint param_2,ulong param_3)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined1 auVar4 [16];
  
  if (((ushort)param_3 < 300) && (param_2 < 6)) {
    uVar3 = (ulong)param_2;
    *(ushort *)(*(long *)(param_1 + 0x150) + uVar3 * 2) = (ushort)param_3;
    uVar2 = 0;
    if (param_2 < 4) {
      iVar1 = (uint)*(ushort *)(*(long *)(param_1 + 0x150) + uVar3 * 2) * 0x100 + -0x514;
      param_3 = (long)iVar1 % 0x672 & 0xffffffff;
      *(short *)(param_1 + 0x158 + uVar3 * 2) = (short)(iVar1 / 0x672);
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0xffffffe3;
  }
  auVar4._8_8_ = param_3;
  auVar4._0_8_ = uVar2;
  return auVar4;
}

