
long si_seci_init(long param_1,byte param_2)

{
  long lVar1;
  int iVar2;
  bool bVar3;
  uint uVar4;
  long lVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  
  if (((*(int *)(param_1 + 0x14) < 0x23) || ((*(byte *)(param_1 + 0x1c) & 1) == 0)) || (7 < param_2)
     ) {
    return 0;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar2 = *(int *)(param_1 + 8);
    if ((iVar2 == 0x83c) || (iVar2 == 0x820)) {
      bVar3 = true;
    }
    else {
      if (iVar2 != 0x804) goto LAB_00124c1a;
      bVar3 = 0xc < *(uint *)(param_1 + 0xc);
    }
  }
  else {
LAB_00124c1a:
    bVar3 = false;
  }
  if (bVar3) {
    lVar5 = *(long *)(param_1 + 0xb8) + 0x3000;
    if (lVar5 == 0) {
      return 0;
    }
    uVar7 = 0;
  }
  else {
    uVar7 = *(undefined4 *)(param_1 + 0x1c0);
    lVar5 = si_setcore(param_1,0x800,0);
    if (lVar5 == 0) {
      return 0;
    }
  }
  if ((*(int *)(param_1 + 0x3c) == 0x4331) || (*(int *)(param_1 + 0x3c) == 0xa8e4)) {
    uVar4 = osl_readl(lVar5 + 0x28);
    osl_writel(uVar4 | 2,lVar5 + 0x28);
  }
  if (*(int *)(param_1 + 0x3c) == 0xa887) {
    uVar4 = osl_readl(lVar5 + 0x28);
    uVar4 = uVar4 & 0xfffffffc;
    if (param_2 == 1) {
      uVar4 = uVar4 | 1;
    }
    else if (param_2 == 3) {
      uVar4 = uVar4 | 2;
    }
    osl_writel(uVar4,lVar5 + 0x28);
  }
  if ((*(int *)(param_1 + 0x3c) == 0xa887) || (*(int *)(param_1 + 0x3c) == 0xa8e4)) {
    uVar4 = osl_readl(lVar5 + 0x3c);
    osl_writel(uVar4 | 1,lVar5 + 0x3c);
  }
  FUN_00124b29(param_1,1);
  lVar1 = lVar5 + 0x130;
  uVar4 = osl_readl(lVar1);
  osl_writel(uVar4 & 0xfffffffb,lVar1);
  osl_writel(1,lVar1);
  osl_writel((-(uint)(param_2 != 4 && 1 < param_2) & 0xfffffffc) + 0xd,lVar1);
  uVar4 = osl_readl(lVar1);
  osl_writel(uVar4 & 0xfffffffe,lVar1);
  if (param_2 != 4 && 1 < param_2) goto LAB_00124e5c;
  iVar2 = *(int *)(param_1 + 0x3c);
  if (((iVar2 == 0x4331) || (iVar2 == 0xa8e4)) || (iVar2 == 0xa887)) {
    uVar6 = 0xff;
LAB_00124dbb:
    FUN_00122a5d(param_1,0x1c4,0xff,uVar6);
    uVar6 = 0x44;
  }
  else {
    if (((iVar2 == 0xa9c4) || (iVar2 == 0x4360)) || ((iVar2 == 0xaa06 || (iVar2 == 0x4352)))) {
      uVar6 = 0xfe;
      goto LAB_00124dbb;
    }
    FUN_00122a5d(param_1,0x1c4,0xff,0xff);
    uVar6 = 0x22;
  }
  FUN_00122a5d(param_1,0x1dc,0xff,uVar6);
  FUN_00122a5d(param_1,0x1cc,0xff,0x28);
  FUN_00122a5d(param_1,0x1d0,0xff,0x81);
  FUN_00122a5d(param_1,0x148,0xffffffff,1);
  FUN_00122a5d(param_1,0x14c,0xffff,0xff);
LAB_00124e5c:
  lVar1 = lVar5 + 0x130;
  uVar4 = osl_readl(lVar1);
  osl_writel(uVar4 & 0xffffff8f | (uint)param_2 << 4,lVar1);
  uVar4 = osl_readl(lVar1);
  osl_writel(uVar4 & 0xfffffff7,lVar1);
  if (!bVar3) {
    si_setcoreidx(param_1,uVar7);
  }
  return lVar5;
}

