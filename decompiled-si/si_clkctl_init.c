
void si_clkctl_init(long param_1)

{
  bool bVar1;
  ulong uVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  undefined4 uVar7;
  
  if ((*(byte *)(param_1 + 0x1a) & 4) == 0) {
    return;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar6 = *(int *)(param_1 + 8);
    if ((iVar6 == 0x83c) || (iVar6 == 0x820)) {
      bVar1 = true;
      goto LAB_0012124c;
    }
    if (iVar6 == 0x804) {
      bVar1 = 0xc < *(uint *)(param_1 + 0xc);
      goto LAB_0012124c;
    }
  }
  bVar1 = false;
LAB_0012124c:
  if (bVar1) {
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
  if (9 < *(int *)(param_1 + 0x14)) {
    uVar3 = osl_readl(lVar5 + 0xc0);
    osl_writel(uVar3 | 0x40000,lVar5 + 0xc0);
  }
  iVar4 = FUN_00120439(param_1);
  iVar6 = 0x47e;
  if (iVar4 == 1) {
    iVar6 = 0x96;
  }
  iVar4 = FUN_00120494(param_1,*(int *)(param_1 + 0x14) < 10,lVar5);
  uVar2 = (ulong)(iVar6 * iVar4 + 999999);
  osl_writel(uVar2 / 1000000,lVar5 + 0xb0,uVar2 % 1000000);
  uVar2 = (ulong)(iVar4 * 200 + 999999);
  osl_writel(uVar2 / 1000000,lVar5 + 0xb4,uVar2 % 1000000);
  osl_delay(20000);
  if (!bVar1) {
    si_setcoreidx(param_1,uVar7);
  }
  return;
}

