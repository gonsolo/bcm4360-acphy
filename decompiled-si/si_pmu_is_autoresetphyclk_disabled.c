
undefined1 si_pmu_is_autoresetphyclk_disabled(long param_1)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  undefined1 uVar4;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (*(int *)(param_1 + 0x3c) == 0xa8e7) {
    osl_writel(0,lVar3 + 0x650);
    uVar4 = 1;
    uVar2 = osl_readl(lVar3 + 0x654);
    if ((uVar2 & 2) != 0) goto LAB_00112da8;
  }
  uVar4 = 0;
LAB_00112da8:
  si_setcoreidx(param_1,uVar1);
  return uVar4;
}

