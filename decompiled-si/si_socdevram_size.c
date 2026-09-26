
int si_socdevram_size(long param_1)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  undefined4 local_3c;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    local_3c = 0;
  }
  else {
    local_3c = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  iVar6 = 0;
  lVar5 = si_setcore(param_1,0x80e,0);
  if (lVar5 != 0) {
    cVar2 = si_iscoreup(param_1);
    if (cVar2 == '\0') {
      si_core_reset(param_1,0,0);
    }
    iVar6 = 0;
    uVar3 = si_corerev(param_1);
    if (9 < uVar3) {
      uVar3 = osl_readl(lVar5 + 8);
      for (iVar7 = 0; (byte)iVar7 < (byte)((uVar3 & 0xf000) >> 0xc); iVar7 = iVar7 + 1) {
        iVar4 = FUN_0011f5ad(param_1,lVar5,iVar7,2);
        iVar6 = iVar6 + iVar4;
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
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),local_3c);
  }
  return iVar6;
}

