
char si_pmu_update_pllcontrol(long param_1,undefined8 param_2,int param_3,char param_4)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined *puVar8;
  char cVar9;
  undefined *puVar10;
  undefined8 uVar11;
  int local_3c;
  
  local_3c = getintvar(0,"xtalfreq");
  if ((local_3c == 0) && (local_3c = param_3, param_3 == 0)) {
    uVar3 = *(uint *)(param_1 + 0x3c);
    if (uVar3 == 0x4350) {
LAB_001177ec:
      uVar4 = 37400000;
    }
    else {
      if (uVar3 < 0x4351) {
        if ((uVar3 == 0x4324) || (uVar3 == 0x4335)) goto LAB_001177ec;
      }
      else if (uVar3 - 0xa8ea < 2) goto LAB_001177ec;
      uVar4 = 20000000;
    }
    local_3c = (int)(uVar4 / 1000);
  }
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 == 0xa8e7) {
    puVar8 = (undefined *)0x0;
    uVar11 = 0;
    puVar10 = (undefined *)0x0;
LAB_00117861:
    cVar9 = '\x01';
  }
  else {
    if (uVar3 < 0xa8e8) {
      if (uVar3 == 0x4335) {
        puVar8 = &DAT_0050a550;
        uVar11 = 0x13;
        puVar10 = &DAT_0050a500;
      }
      else {
        if (uVar3 != 0x4350) goto LAB_0011788b;
        puVar8 = &DAT_0050a720;
        uVar11 = 2;
        puVar10 = &DAT_0050a718;
      }
      goto LAB_00117861;
    }
    if (uVar3 - 0xa8ea < 2) {
      puVar8 = &DAT_0050a780;
      uVar11 = 1;
      puVar10 = &DAT_0050a758;
      if (*(int *)(param_1 + 0x40) == 0) {
        puVar8 = &DAT_0050a760;
      }
      goto LAB_00117861;
    }
LAB_0011788b:
    puVar8 = (undefined *)0x0;
    uVar11 = 0;
    puVar10 = (undefined *)0x0;
    cVar9 = '\0';
  }
  uVar2 = si_coreidx(param_1);
  lVar5 = si_setcoreidx(param_1,0);
  if ((puVar10 != (undefined *)0x0) && (param_4 == '\0')) {
    bVar1 = FUN_001176d4(param_1,0,local_3c,puVar10,uVar11,puVar8);
    if (bVar1 == 0) {
      cVar9 = '\0';
      osl_printf("Invalid/Unsupported xtal value %d",local_3c);
      goto LAB_001179ad;
    }
    uVar3 = osl_readl(lVar5 + 0x600);
    osl_writel((uint)bVar1 * 4 & 0x7c | ((local_3c + 0x7fU >> 7) - 1) * 0x10000 | uVar3 & 0xff83,
               lVar5 + 0x600);
  }
  if ((cVar9 == '\0') || (param_4 == '\0')) goto LAB_001179ad;
  if (puVar8 != (undefined *)0x0) {
    FUN_001176d4(param_1,lVar5,local_3c,puVar10,uVar11,puVar8);
  }
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 == 0xa8e7) {
    uVar11 = 0x808;
    uVar6 = 0xffff;
    uVar7 = 2;
  }
  else {
    if (uVar3 < 0xa8e8) {
      if (uVar3 != 0x4324) goto LAB_001179ad;
    }
    else if (1 < uVar3 - 0xa8ea) goto LAB_001179ad;
    uVar11 = 0x700;
    uVar6 = 0xff00;
    uVar7 = 1;
  }
  si_pmu_pllcontrol(param_1,uVar7,uVar6,uVar11);
LAB_001179ad:
  si_setcoreidx(param_1,uVar2);
  return cVar9;
}

