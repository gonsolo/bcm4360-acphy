
int si_pmu_measure_alpclk(long param_1)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  ulong extraout_RDX;
  ulong extraout_RDX_00;
  ulong uVar4;
  int iVar5;
  
  iVar5 = 0;
  if (9 < *(int *)(param_1 + 0x20)) {
    uVar1 = si_coreidx();
    lVar3 = si_setcoreidx(param_1,0);
    if ((*(int *)(param_1 + 0x3c) == 0x4350) || (*(int *)(param_1 + 0x3c) == 0x4335)) {
      uVar2 = osl_readl(lVar3 + 0x600);
      uVar2 = (uVar2 ^ 1) & 1;
      uVar4 = extraout_RDX;
    }
    else {
      uVar2 = osl_readl(lVar3 + 0x608);
      uVar2 = uVar2 & 0x100;
      uVar4 = extraout_RDX_00;
    }
    iVar5 = 0;
    if (uVar2 != 0) {
      lVar3 = lVar3 + 0x66c;
      osl_writel(0x80000000,lVar3);
      osl_delay(1000);
      uVar2 = osl_readl(lVar3);
      osl_writel(0,lVar3);
      uVar2 = (uVar2 & 0x1fff) * 0x2000 + 50000;
      uVar4 = (ulong)uVar2 % 100000;
      iVar5 = (uVar2 / 100000) * 100;
    }
    si_setcoreidx(param_1,uVar1,uVar4);
  }
  return iVar5;
}

