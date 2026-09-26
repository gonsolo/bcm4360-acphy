
long FUN_0010fb4d(long param_1,int param_2)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;
  
  if (*(short *)(param_1 + 0x6a) != 0) {
    uVar9 = *(uint *)(param_1 + 0x6c);
    if (param_2 == 1) {
      uVar3 = *(ushort *)(param_1 + 0x6e);
    }
    else {
      uVar3 = *(ushort *)(param_1 + 0x12a);
      lVar6 = *(long *)(param_1 + 0x48);
      if ((ushort)uVar9 == uVar3) {
        uVar7 = osl_readl(lVar6 + 0x10);
        uVar3 = (ushort)(((uVar7 & *(uint *)(param_1 + 0x11c)) - *(int *)(param_1 + 0xa0) &
                         *(uint *)(param_1 + 0x11c)) >> 4);
        *(ushort *)(param_1 + 0x12a) = uVar3;
      }
      if (param_2 == 3) {
        uVar4 = osl_readl(lVar6 + 0x14);
        uVar4 = (ushort)((uVar4 & (ushort)*(undefined4 *)(param_1 + 0x120)) -
                         *(short *)(param_1 + 0xa0) & (ushort)*(undefined4 *)(param_1 + 0x11c)) >> 4
        ;
        if (uVar3 != uVar4) {
          uVar3 = uVar4 - 1 & *(short *)(param_1 + 0x6a) - 1U;
        }
      }
    }
    if (((ushort)uVar9 != 0) || (uVar9 = 0, uVar3 <= *(ushort *)(param_1 + 0x6e))) {
      lVar6 = 0;
      for (; (lVar6 == 0 && ((ushort)uVar9 != uVar3));
          uVar9 = uVar9 + 1 & *(ushort *)(param_1 + 0x6a) - 1) {
        lVar8 = (ulong)(uVar9 & 0xffff) * 0x10;
        lVar6 = lVar8 + *(long *)(param_1 + 0x58);
        iVar1 = *(int *)(lVar6 + 8);
        uVar7 = *(uint *)(lVar6 + 4);
        iVar2 = *(int *)(param_1 + 0xfc);
        *(undefined4 *)(lVar6 + 8) = 0xdeadbeef;
        *(undefined4 *)(lVar8 + *(long *)(param_1 + 0x58) + 0xc) = 0xdeadbeef;
        plVar5 = (long *)((ulong)(uVar9 & 0xffff) * 8 + *(long *)(param_1 + 0x70));
        lVar6 = *plVar5;
        *plVar5 = 0;
        osl_dma_unmap(*(undefined8 *)(param_1 + 0x30),iVar1 - iVar2,uVar7 & 0x7fff,1);
      }
      *(ushort *)(param_1 + 0x6c) = (ushort)uVar9;
      uVar7 = *(ushort *)(param_1 + 0x6a) - 1;
      *(uint *)(param_1 + 8) =
           uVar7 - ((uint)*(ushort *)(param_1 + 0x6e) - (uVar9 & 0xffff) & uVar7);
      return lVar6;
    }
  }
  return 0;
}

