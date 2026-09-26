
int si_socdevram_remap_size(long param_1)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  byte bVar9;
  undefined4 local_40;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    local_40 = 0;
  }
  else {
    local_40 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  iVar8 = 0;
  lVar6 = si_setcore(param_1,0x80e,0);
  if (lVar6 != 0) {
    cVar2 = si_iscoreup(param_1);
    if (cVar2 == '\0') {
      si_core_reset(param_1,0,0);
    }
    iVar8 = 0;
    uVar3 = si_corerev(param_1);
    if (0xf < uVar3) {
      uVar4 = osl_readl(lVar6 + 8);
      bVar9 = (byte)((uVar4 & 0xf000) >> 0xc);
      if ((bVar9 == 5) && (uVar3 == 0x10)) {
        bVar9 = 4;
      }
      iVar8 = 0;
      uVar3 = 0;
      while ((byte)uVar3 < bVar9) {
        osl_writel(uVar3 | 0x200,lVar6 + 0x10);
        uVar7 = osl_readl(lVar6 + 0x40);
        if ((uVar7 & 0x1000000) == 0) break;
        iVar5 = FUN_0011f5ad(param_1,lVar6,uVar3,2);
        iVar8 = iVar8 + iVar5;
        uVar3 = uVar3 + 1;
      }
    }
    if (cVar2 == '\0') {
      si_core_disable(param_1,0);
    }
    si_setcoreidx(param_1,uVar1);
  }
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),local_40);
  }
  return iVar8;
}

