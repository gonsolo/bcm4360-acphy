
void wlc_bmac_core_phypll_ctl(long param_1,char param_2)

{
  long lVar1;
  long lVar2;
  char cVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar8;
  int iVar9;
  bool bVar10;
  
  uVar7 = *(uint *)(param_1 + 0x84);
  lVar2 = *(long *)(param_1 + 0xd0);
  if (uVar7 == 0x14) {
    return;
  }
  if (uVar7 < 0x11) {
    return;
  }
  if (uVar7 == 0x1b) {
    return;
  }
  if (0x27 < uVar7) {
    return;
  }
  cVar3 = si_iscoreup(*(undefined8 *)(param_1 + 0xb8));
  if (cVar3 == '\0') {
    return;
  }
  uVar7 = *(uint *)(param_1 + 0x84);
  if (param_2 == '\0') {
    if (((uVar7 < 0x18) || (0x27 < uVar7)) || (uVar7 == 0x1d)) {
      uVar7 = 0x310;
      if (*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) != 0x4313) {
        uVar7 = 0x300;
      }
      uVar5 = osl_readl(lVar2 + 0x1e0);
      osl_writel(~uVar7 & uVar5,lVar2 + 0x1e0);
      goto LAB_001644bf;
    }
    uVar8 = 0x30;
    if (*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) != 0x4313) {
      uVar8 = 0x20;
    }
    uVar4 = osl_readw(lVar2 + 0x4f0);
    osl_writew(~uVar8 & uVar4,lVar2 + 0x4f0);
  }
  else {
    if (((uVar7 < 0x18) || (0x27 < uVar7)) || (uVar7 == 0x1d)) {
      lVar1 = lVar2 + 0x1e0;
      bVar10 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c) != 0x4313;
      uVar7 = 0x310;
      if (bVar10) {
        uVar7 = 0x300;
      }
      uVar5 = 0x20000;
      if (bVar10) {
        uVar5 = 0x3000000;
      }
      uVar6 = osl_readl(lVar1);
      osl_writel(uVar6 | uVar7,lVar1);
      for (iVar9 = 0x186a9; (uVar7 = osl_readl(lVar1), (uVar7 & uVar5) != uVar5 && (iVar9 != 9));
          iVar9 = iVar9 + -10) {
        osl_delay(10);
      }
LAB_001644bf:
      osl_readl(lVar2 + 0x1e0);
      return;
    }
    lVar1 = lVar2 + 0x4f0;
    bVar10 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c) != 0x4313;
    uVar8 = 0x30;
    if (bVar10) {
      uVar8 = 0x20;
    }
    uVar7 = 0x8000;
    if (bVar10) {
      uVar7 = 0x2000;
    }
    uVar4 = osl_readw(lVar1);
    osl_writew(uVar4 | uVar8,lVar1);
    for (iVar9 = 0x186a9; (uVar5 = osl_readw(lVar1), (uVar5 & uVar7) != uVar7 && (iVar9 != 9));
        iVar9 = iVar9 + -10) {
      osl_delay(10);
    }
  }
  osl_readw(lVar2 + 0x4f0);
  return;
}

