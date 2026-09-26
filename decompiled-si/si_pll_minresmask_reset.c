
undefined8 si_pll_minresmask_reset(long param_1)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  
  uVar5 = 0xffffffe9;
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (*(int *)(param_1 + 0x3c) == 0x4313) {
    lVar4 = lVar3 + 0x61c;
    uVar2 = osl_readl(lVar3 + 0x618);
    uVar5 = 0;
    osl_writel(uVar2 & 0xffffbfff,lVar3 + 0x618);
    osl_delay(100);
    uVar2 = osl_readl(lVar4);
    osl_writel(uVar2 & 0xffffbfff,lVar4);
    osl_delay(100);
    uVar2 = osl_readl(lVar4);
    osl_writel(uVar2 | 0x4000,lVar4);
  }
  si_setcoreidx(param_1,uVar1);
  return uVar5;
}

