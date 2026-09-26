
void si_pmu_init(long param_1)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (*(int *)(param_1 + 0x20) == 1) {
    uVar2 = osl_readl(lVar3 + 0x600);
    uVar2 = uVar2 & 0xfffffdff;
  }
  else {
    if (*(int *)(param_1 + 0x20) < 2) goto LAB_0011272e;
    uVar2 = osl_readl(lVar3 + 0x600);
    uVar2 = uVar2 | 0x200;
  }
  osl_writel(uVar2,lVar3 + 0x600);
LAB_0011272e:
  if ((*(int *)(param_1 + 0x3c) == 0x4329) && (*(int *)(param_1 + 0x40) == 2)) {
    lVar4 = lVar3 + 0x65c;
    osl_writel(2,lVar3 + 0x658);
    uVar2 = osl_readl(lVar4);
    osl_writel(uVar2 | 0x100,lVar4);
    osl_writel(3,lVar3 + 0x658);
    uVar2 = osl_readl(lVar4);
    osl_writel(uVar2 | 4,lVar4);
  }
  si_setcoreidx(param_1,uVar1);
  return;
}

