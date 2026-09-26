
undefined8 FUN_0011083d(long param_1,long param_2,char param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  ushort uVar6;
  long lVar7;
  uint local_3c [3];
  
  local_3c[0] = 0;
  uVar6 = *(ushort *)(param_1 + 0x6e);
  lVar4 = param_2;
  do {
    do {
      lVar7 = lVar4;
      if (lVar7 == 0) {
        if ((local_3c[0] & 0x40000000) == 0) {
          *(uint *)((long)(int)(uVar6 - 1 & *(ushort *)(param_1 + 0x6a) - 1) * 0x10 +
                   *(long *)(param_1 + 0x58)) = local_3c[0] | 0x60000000;
        }
        *(long *)(*(long *)(param_1 + 0x70) +
                 (long)(int)(uVar6 - 1 & *(ushort *)(param_1 + 0x6a) - 1) * 8) = param_2;
        *(ushort *)(param_1 + 0x6e) = uVar6;
        if (param_3 != '\0') {
          osl_writel((uint)uVar6 * 0x10 + *(int *)(param_1 + 0xa0),*(long *)(param_1 + 0x48) + 4);
        }
        uVar5 = *(ushort *)(param_1 + 0x6a) - 1;
        *(uint *)(param_1 + 8) =
             uVar5 - ((uint)*(ushort *)(param_1 + 0x6e) - (uint)*(ushort *)(param_1 + 0x6c) & uVar5)
        ;
        return 0;
      }
      uVar3 = osl_pktdata(*(undefined8 *)(param_1 + 0x30),lVar7);
      iVar1 = osl_pktlen(*(undefined8 *)(param_1 + 0x30),lVar7);
      lVar4 = osl_pktnext(*(undefined8 *)(param_1 + 0x30),lVar7);
      if ((uVar6 + 1 & *(ushort *)(param_1 + 0x6a) - 1) == (uint)*(ushort *)(param_1 + 0x6c))
      goto LAB_001109e1;
    } while (iVar1 == 0);
    uVar2 = osl_dma_map(*(undefined8 *)(param_1 + 0x30),uVar3,iVar1,1,lVar7,
                        (ulong)uVar6 * 0x90 + *(long *)(param_1 + 0x80));
    local_3c[0] = 0;
    if (lVar7 == param_2) {
      local_3c[0] = 0x80000000;
    }
    if (lVar4 == 0) {
      local_3c[0] = local_3c[0] | 0x60000000;
    }
    if ((uint)uVar6 == *(ushort *)(param_1 + 0x6a) - 1) {
      local_3c[0] = local_3c[0] | 0x10000000;
    }
    FUN_0010ea38(param_1,*(undefined8 *)(param_1 + 0x58),uVar2,uVar6,local_3c,iVar1);
    uVar6 = uVar6 + 1 & *(short *)(param_1 + 0x6a) - 1U;
  } while (uVar6 != *(ushort *)(param_1 + 0x6c));
LAB_001109e1:
  osl_pktfree(*(undefined8 *)(param_1 + 0x30),param_2,1);
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  *(undefined4 *)(param_1 + 8) = 0;
  return 0xffffffff;
}

