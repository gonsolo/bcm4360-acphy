
undefined1 si_socdevram_remap_isenb(long param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  uint uVar7;
  undefined1 local_48;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    uVar3 = 0;
  }
  else {
    uVar3 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar5 = si_setcore(param_1,0x80e,0);
  local_48 = 0;
  if (lVar5 != 0) {
    cVar2 = si_iscoreup(param_1);
    if (cVar2 == '\0') {
      si_core_reset(param_1,0,0);
    }
    uVar4 = si_corerev(param_1);
    if (uVar4 < 0x10) {
LAB_00121b76:
      local_48 = 0;
    }
    else {
      uVar4 = osl_readl(lVar5 + 8);
      uVar7 = 0;
      do {
        if ((byte)((uVar4 & 0xf000) >> 0xc) <= (byte)uVar7) goto LAB_00121b76;
        osl_writel(uVar7 | 0x200,lVar5 + 0x10);
        uVar6 = osl_readl(lVar5 + 0x40);
        uVar7 = uVar7 + 1;
      } while ((uVar6 & 0x1000000) == 0);
      local_48 = 1;
    }
    if (cVar2 == '\0') {
      si_core_disable(param_1,0);
    }
    si_setcoreidx(param_1,uVar1);
  }
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar3);
  }
  return local_48;
}

