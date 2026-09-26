
int si_pmu_ilp_clock(undefined8 param_1)

{
  long lVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  
  if (DAT_006f0774 == 0) {
    uVar2 = si_coreidx();
    lVar6 = si_setcoreidx(param_1,0);
    lVar1 = lVar6 + 0x614;
    iVar3 = osl_readl(lVar1);
    iVar4 = osl_readl(lVar1);
    if (iVar3 != iVar4) {
      iVar3 = osl_readl(lVar1);
    }
    lVar6 = lVar6 + 0x614;
    osl_delay(10000);
    iVar4 = osl_readl(lVar6);
    iVar5 = osl_readl(lVar6);
    if (iVar4 != iVar5) {
      iVar4 = osl_readl(lVar6);
    }
    DAT_006f0774 = (iVar4 - iVar3) * 100;
    si_setcoreidx(param_1,uVar2);
  }
  return DAT_006f0774;
}

