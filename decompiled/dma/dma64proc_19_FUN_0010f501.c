
void FUN_0010f501(long param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  ulong uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  long lVar14;
  uint uVar15;
  uint uVar16;
  ulong uVar17;
  
  uVar1 = *(ushort *)(param_1 + 0x6c);
  uVar2 = *(ushort *)(param_1 + 0x6a);
  uVar3 = *(ushort *)(param_1 + 0x6e);
  uVar6 = osl_readl(*(long *)(param_1 + 0x48) + 0x14);
  uVar4 = *(ushort *)(param_1 + 0x6c);
  uVar9 = 0;
  uVar5 = *(ushort *)(param_1 + 0x6a);
  uVar6 = ((uVar6 & *(uint *)(param_1 + 0x120)) - *(int *)(param_1 + 0xa0) &
          *(uint *)(param_1 + 0x120)) >> 4;
  uVar15 = uVar6 & 0xffff;
  uVar12 = uVar15 - uVar4 & uVar5 - 1;
  if (uVar12 < (uint)uVar5 - (uVar2 - 1 & (uint)uVar3 - (uint)uVar1)) {
    uVar10 = uVar5 - 1 & *(ushort *)(param_1 + 0x6e) - 1;
    while( true ) {
      uVar16 = *(ushort *)(param_1 + 0x6a) - 1;
      iVar7 = (int)CONCAT62((int6)(uVar9 >> 0x10),*(ushort *)(param_1 + 0x6a));
      if ((uVar10 & 0xffff) == (uVar16 & uVar4 - 1)) break;
      uVar9 = (ulong)(uVar10 & 0xffff);
      uVar13 = uVar10 + uVar12 & iVar7 - 1U;
      lVar8 = uVar9 * 0x10;
      uVar11 = *(uint *)(*(long *)(param_1 + 0x58) + lVar8) & 0xefffffff;
      uVar17 = (ulong)(uVar13 & 0xffff);
      if ((uVar13 & 0xffff) == uVar16) {
        uVar11 = uVar11 | 0x10000000;
      }
      lVar14 = uVar17 * 0x10;
      *(uint *)(*(long *)(param_1 + 0x58) + lVar14) = uVar11;
      *(undefined4 *)(*(long *)(param_1 + 0x58) + lVar14 + 4) =
           *(undefined4 *)(*(long *)(param_1 + 0x58) + lVar8 + 4);
      *(undefined4 *)(*(long *)(param_1 + 0x58) + lVar14 + 8) =
           *(undefined4 *)(*(long *)(param_1 + 0x58) + lVar8 + 8);
      *(undefined4 *)(*(long *)(param_1 + 0x58) + lVar14 + 0xc) =
           *(undefined4 *)(*(long *)(param_1 + 0x58) + lVar8 + 0xc);
      *(undefined4 *)(lVar8 + *(long *)(param_1 + 0x58) + 8) = 0xdeadbeef;
      *(undefined4 *)(lVar8 + *(long *)(param_1 + 0x58) + 0xc) = 0xdeadbeef;
      *(undefined8 *)(*(long *)(param_1 + 0x70) + uVar17 * 8) =
           *(undefined8 *)(*(long *)(param_1 + 0x70) + uVar9 * 8);
      lVar8 = *(long *)(param_1 + 0x70);
      *(undefined8 *)(lVar8 + uVar9 * 8) = 0;
      uVar16 = (int)CONCAT62((int6)((ulong)lVar8 >> 0x10),*(undefined2 *)(param_1 + 0x6a)) - 1;
      uVar9 = (ulong)uVar16;
      uVar10 = uVar10 - 1 & uVar16;
    }
    *(short *)(param_1 + 0x6c) = (short)uVar6;
    uVar6 = (uint)(ushort)((short)uVar12 + *(short *)(param_1 + 0x6e)) & iVar7 - 1U;
    *(short *)(param_1 + 0x6e) = (short)uVar6;
    *(uint *)(param_1 + 8) = uVar16 - (uVar6 - uVar15 & uVar16);
    osl_writel(uVar6 * 0x10 + *(int *)(param_1 + 0xa0),*(long *)(param_1 + 0x48) + 4);
  }
  return;
}

