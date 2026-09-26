
undefined8 FUN_0010eec4(long param_1,int *param_2,long param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined8 uVar9;
  ulong uVar10;
  long lVar11;
  ushort uVar12;
  
  if (*(short *)(param_1 + 0x6a) == 0) {
    *param_2 = 0;
    uVar9 = 0xffffffff;
  }
  else {
    iVar1 = *param_2;
    *param_2 = 0;
    uVar2 = *(uint *)(param_1 + 0x6c);
    if (param_4 == 1) {
      uVar12 = *(ushort *)(param_1 + 0x6e);
    }
    else {
      uVar6 = osl_readl(*(long *)(param_1 + 0x48) + 0x10);
      uVar3 = *(uint *)(param_1 + 0x11c);
      iVar8 = *(int *)(param_1 + 0xa0);
      uVar7 = osl_readl(*(long *)(param_1 + 0x48) + 0x14);
      uVar12 = (ushort)(((uVar6 & uVar3) - iVar8 & uVar3) >> 4);
      *(ushort *)(param_1 + 0x12a) = uVar12;
      uVar5 = (ushort)(((uVar7 & *(uint *)(param_1 + 0x120)) - *(int *)(param_1 + 0xa0) &
                       *(uint *)(param_1 + 0x11c)) >> 4);
      if (uVar5 != uVar12) {
        uVar12 = uVar5 - 1 & *(short *)(param_1 + 0x6a) - 1U;
      }
    }
    uVar10 = (ulong)uVar2;
    if (((short)uVar2 == 0) && (uVar10 = 0, *(ushort *)(param_1 + 0x6e) < uVar12)) {
      return 0xffffffff;
    }
    iVar8 = 0;
    for (; (ushort)uVar10 != uVar12;
        uVar10 = (ulong)((int)uVar10 + 1U & *(ushort *)(param_1 + 0x6a) - 1)) {
      lVar4 = *(long *)(*(long *)(param_1 + 0x70) + (uVar10 & 0xffff) * 8);
      if (lVar4 != 0) {
        if (iVar1 <= iVar8) break;
        lVar11 = (long)iVar8;
        iVar8 = iVar8 + 1;
        *(long *)(param_3 + lVar11 * 8) = lVar4;
      }
    }
    *param_2 = iVar8;
    uVar9 = 0;
  }
  return uVar9;
}

