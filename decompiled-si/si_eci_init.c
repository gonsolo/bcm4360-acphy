
undefined8 si_eci_init(long param_1)

{
  char cVar1;
  short sVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  int iVar8;
  bool bVar9;
  
  if ((*(byte *)(param_1 + 0x1b) & 0x20) == 0) {
    return 0xffffffff;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar8 = *(int *)(param_1 + 8);
    if ((iVar8 == 0x83c) || (iVar8 == 0x820)) {
      bVar9 = true;
    }
    else {
      if (iVar8 != 0x804) goto LAB_00122d99;
      bVar9 = 0xc < *(uint *)(param_1 + 0xc);
    }
  }
  else {
LAB_00122d99:
    bVar9 = false;
  }
  if (bVar9) {
    lVar3 = *(long *)(param_1 + 0xb8) + 0x3000;
    if (lVar3 != 0) {
      uVar7 = 0;
      goto LAB_00122ddb;
    }
  }
  else {
    uVar7 = *(undefined4 *)(param_1 + 0x1c0);
    lVar3 = si_setcore(param_1,0x800,0);
    if (lVar3 != 0) {
LAB_00122ddb:
      if (*(int *)(param_1 + 0x14) < 0x23) {
        osl_writel(0,lVar3 + 0x168);
      }
      osl_writel(0,lVar3 + 0x164);
      osl_writel(0,lVar3 + 0x160);
      lVar4 = lVar3 + 0x144;
      uVar6 = 0xbffb0000;
      if (0x22 < *(int *)(param_1 + 0x14)) {
        osl_writel(1,lVar3 + 0x148);
        lVar4 = lVar3 + 0x14c;
        uVar6 = 0xff;
      }
      osl_writel(uVar6,lVar4);
      if (*(int *)(param_1 + 0x14) < 0x23) {
        osl_writel(0,lVar3 + 0x180);
        osl_writel(0,lVar3 + 0x17c);
        lVar3 = lVar3 + 0x178;
      }
      else {
        osl_writel(0,lVar3 + 0x174);
        lVar3 = lVar3 + 0x170;
      }
      osl_writel(0,lVar3);
      if (!bVar9) {
        si_setcoreidx(param_1,uVar7);
      }
      if ((*(int *)(param_1 + 0x3c) == 0x4325) && (5 < *(uint *)(param_1 + 0x40))) {
        cVar1 = si_is_otp_powered(param_1);
        if (cVar1 == '\0') {
          si_otp_power(param_1,1);
        }
        bVar9 = false;
        iVar8 = -0x1e;
        lVar3 = otp_init(param_1);
        if (lVar3 != 0) {
          sVar2 = otp_read_bit(lVar3,0xbc);
          bVar9 = sVar2 == 0;
          iVar8 = 0;
        }
        if (cVar1 == '\0') {
          si_otp_power(param_1,0);
        }
        if ((iVar8 == 0) && (bVar9)) {
          uVar6 = 0x40;
          if (*(int *)(param_1 + 0x14) < 0x23) {
            uVar6 = 0x40000;
          }
          uVar5 = 0x55550040;
          if (*(int *)(param_1 + 0x14) < 0x23) {
            uVar5 = 0x40000;
          }
          si_eci_notify_bt(param_1,uVar5,uVar6,0);
        }
      }
      return 0;
    }
  }
  return 0xffffffff;
}

