
void si_seci_down(long param_1)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  undefined4 uVar7;
  int iVar8;
  int local_40;
  
  if ((*(byte *)(param_1 + 0x1c) & 1) == 0) {
    return;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar8 = *(int *)(param_1 + 8);
    if ((iVar8 == 0x83c) || (iVar8 == 0x820)) {
      bVar2 = true;
      goto LAB_00124f1b;
    }
    if (iVar8 == 0x804) {
      bVar2 = 0xc < *(uint *)(param_1 + 0xc);
      goto LAB_00124f1b;
    }
  }
  bVar2 = false;
LAB_00124f1b:
  if (bVar2) {
    lVar5 = *(long *)(param_1 + 0xb8) + 0x3000;
    if (lVar5 == 0) {
      return;
    }
    uVar7 = 0;
  }
  else {
    uVar7 = *(undefined4 *)(param_1 + 0x1c0);
    lVar5 = si_setcore(param_1,0x800,0);
    if (lVar5 == 0) {
      return;
    }
  }
  if (*(int *)(param_1 + 0x3c) == 0x4331) {
    lVar1 = lVar5 + 0x130;
    uVar4 = osl_readl(lVar1);
    osl_writel(uVar4 | 0x80,lVar1);
    for (local_40 = 0x3f1; (cVar3 = osl_readl(lVar1), cVar3 < '\0' && (local_40 != 9));
        local_40 = local_40 + -10) {
      osl_delay(10);
    }
    osl_writel(0xdb,lVar5 + 0x1c0);
    osl_writel(0,lVar5 + 0x1c0);
    for (iVar8 = 0x3f1; (uVar6 = osl_readl(lVar5 + 0x1d4), (uVar6 & 4) != 0 && (iVar8 != 9));
        iVar8 = iVar8 + -10) {
      osl_delay(10);
    }
    lVar5 = lVar5 + 0x130;
    uVar4 = osl_readl(lVar5);
    osl_writel(uVar4 & 0xfffffffb,lVar5);
    osl_writel(uVar4 & 0xfffffffb | 1,lVar5);
  }
  FUN_00124b29(param_1,0);
  if (!bVar2) {
    si_setcoreidx(param_1,uVar7);
  }
  return;
}

