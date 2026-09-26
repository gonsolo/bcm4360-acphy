
void si_pmu_rcal(long param_1)

{
  long lVar1;
  long lVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  byte bVar9;
  
  uVar3 = si_coreidx();
  lVar6 = si_setcoreidx(param_1,0);
  if (*(int *)(param_1 + 0x3c) == 0x4325) {
    lVar1 = lVar6 + 0x654;
    osl_writel(1,lVar6 + 0x650);
    uVar5 = osl_readl(lVar1);
    osl_writel(uVar5 & 0xfffffffb,lVar1);
    uVar5 = osl_readl(lVar6 + 0x2c);
    uVar4 = osl_readl(lVar1);
    osl_writel(uVar4 | 4,lVar1);
    for (iVar8 = 0x989689; (uVar7 = osl_readl(lVar6 + 0x2c), (uVar7 & 8) == 0 && (iVar8 != 9));
        iVar8 = iVar8 + -10) {
      osl_delay(10);
    }
    bVar9 = 6;
    if ((uVar5 & 8) == 0) goto LAB_00113688;
  }
  else {
    if (*(int *)(param_1 + 0x3c) != 0x4329) goto LAB_001137b3;
    lVar1 = lVar6 + 0x654;
    osl_writel(1,lVar6 + 0x650);
    uVar5 = osl_readl(lVar1);
    osl_writel(uVar5 & 0xfffffffb,lVar1);
    uVar5 = osl_readl(lVar1);
    osl_writel(uVar5 | 4,lVar1);
    for (iVar8 = 0x989689; (uVar7 = osl_readl(lVar6 + 0x2c), (uVar7 & 8) == 0 && (iVar8 != 9));
        iVar8 = iVar8 + -10) {
      osl_delay(10);
    }
LAB_00113688:
    uVar5 = osl_readl(lVar6 + 0x2c);
    bVar9 = (byte)(uVar5 >> 5) & 0xf;
  }
  lVar1 = lVar6 + 0x65c;
  osl_writel(0,lVar6 + 0x658);
  uVar5 = osl_readl(lVar1);
  osl_writel((uint)bVar9 << 0x1d | uVar5 & 0x1fffffff,lVar1);
  osl_writel(1,lVar6 + 0x658);
  uVar5 = osl_readl(lVar1);
  lVar2 = lVar6 + 0x650;
  lVar6 = lVar6 + 0x654;
  osl_writel((uint)(bVar9 >> 3) | uVar5 & 0xfffffffe,lVar1);
  osl_writel(0,lVar2);
  uVar5 = osl_readl(lVar6);
  osl_writel((uint)bVar9 << 0x1e | uVar5 & 0x3fffffff,lVar6);
  osl_writel(1,lVar2);
  uVar5 = osl_readl(lVar6);
  osl_writel((uint)(bVar9 >> 2) | uVar5 & 0xfffffffc,lVar6);
  osl_writel(0,lVar2);
  uVar5 = osl_readl(lVar6);
  osl_writel(uVar5 | 0x20000000,lVar6);
  osl_writel(1,lVar2);
  uVar5 = osl_readl(lVar6);
  osl_writel(uVar5 & 0xfffffffb,lVar6);
LAB_001137b3:
  si_setcoreidx(param_1,uVar3);
  return;
}

