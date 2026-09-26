
int si_socram_size(long param_1)

{
  undefined4 uVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  uint uVar8;
  int iVar9;
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
  iVar9 = 0;
  lVar7 = si_setcore(param_1,0x80e,0);
  if (lVar7 != 0) {
    cVar3 = si_iscoreup(param_1);
    if (cVar3 == '\0') {
      si_core_reset(param_1,0,0);
    }
    uVar4 = si_corerev(param_1);
    uVar5 = osl_readl(lVar7);
    bVar2 = (byte)uVar5;
    if (uVar4 == 0) {
      iVar9 = 1 << ((bVar2 & 0xf) + 0x10 & 0x1f);
    }
    else if (uVar4 < 3) {
      iVar9 = (1 << (bVar2 & 0xf) + 0xe) * ((uVar5 & 0xf0) >> 4);
    }
    else if ((uVar4 == 0xc) || (uVar4 < 8)) {
      uVar4 = (uVar5 & 0xf00000) >> 0x14;
      iVar9 = (((uVar5 & 0xf0) >> 4) - 1) + (uint)(uVar4 == 0) << (bVar2 & 0xf) + 0xe;
      if ((uVar5 & 0xf00000) != 0) {
        iVar9 = iVar9 + (1 << (char)uVar4 + 0xd);
      }
    }
    else {
      uVar4 = 0;
      iVar9 = 0;
      while( true ) {
        uVar8 = uVar4 & 0xff;
        if ((uVar5 & 0xf0) >> 4 <= uVar8) break;
        uVar4 = uVar4 + 1;
        iVar6 = FUN_0011f5ad(param_1,lVar7,uVar8,0);
        iVar9 = iVar9 + iVar6;
      }
    }
    if (cVar3 == '\0') {
      si_core_disable(param_1,0);
    }
    si_setcoreidx(param_1,uVar1);
  }
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),local_3c);
  }
  return iVar9;
}

