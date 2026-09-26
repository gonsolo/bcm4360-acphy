
undefined1 si_pmu_is_sprom_enabled(long param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  undefined1 uVar4;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (((*(int *)(param_1 + 0x3c) == 0x4315) && (*(int *)(param_1 + 0x40) != 0)) &&
     ((*(byte *)(param_1 + 0x48) & 1) != 0)) {
    osl_writel(0,lVar3 + 0x650);
    uVar4 = 0;
    iVar2 = osl_readl(lVar3 + 0x654);
    if (iVar2 < 0) goto LAB_001123ff;
  }
  uVar4 = 1;
LAB_001123ff:
  si_setcoreidx(param_1,uVar1);
  return uVar4;
}

