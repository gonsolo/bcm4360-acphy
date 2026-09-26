
void si_pmu_otp_power(long param_1,undefined8 param_2,char param_3)

{
  long lVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  int iVar9;
  bool bVar10;
  undefined4 local_40;
  uint local_3c [3];
  
  cVar2 = si_is_otp_disabled();
  if (cVar2 != '\0') {
    return;
  }
  uVar3 = si_coreidx(param_1);
  lVar8 = si_setcoreidx(param_1,0);
  uVar5 = *(uint *)(param_1 + 0x3c);
  if (uVar5 == 0x4336) {
LAB_00113a00:
    uVar5 = 0x200;
  }
  else if (uVar5 < 0x4337) {
    if (uVar5 == 0x4324) goto LAB_001139f9;
    if (uVar5 < 0x4325) {
      if (uVar5 < 0x4316) {
        if (uVar5 < 0x4314) {
          bVar10 = uVar5 == 0x10f6;
LAB_001138f4:
          if (!bVar10) goto LAB_001139e5;
          goto LAB_001139f2;
        }
      }
      else if (uVar5 != 0x4319) {
        bVar10 = uVar5 == 0x4322;
        goto LAB_001138f4;
      }
    }
    else {
      if (uVar5 == 0x4330) goto LAB_00113a00;
      if (uVar5 < 0x4331) {
        if ((uVar5 != 0x4325) && (uVar5 != 0x4329)) goto LAB_001139e5;
      }
      else if (uVar5 != 0x4334) {
        if (uVar5 != 0x4335) goto LAB_001139e5;
        goto LAB_001139f9;
      }
    }
LAB_00113925:
    uVar5 = 0x400;
  }
  else if (uVar5 == 0xa8d5) {
LAB_001139f2:
    uVar5 = 0x100;
  }
  else {
    if (uVar5 < 0xa8d6) {
      if (uVar5 == 0x4360) goto LAB_001139f2;
      if (0x4360 < uVar5) {
        if (uVar5 == 0xa886) goto LAB_00113925;
        bVar10 = uVar5 == 0xa887;
LAB_0011391a:
        if (!bVar10) goto LAB_001139e5;
        goto LAB_00113a00;
      }
      if (uVar5 != 0x4350) {
        bVar10 = uVar5 == 0x4352;
        goto LAB_001138f4;
      }
    }
    else {
      if (0xa8eb < uVar5) {
        if ((uVar5 != 0xa9c4) && (uVar5 != 0xaa06)) {
          bVar10 = uVar5 == 0xa962;
          goto LAB_0011391a;
        }
        goto LAB_001139f2;
      }
      if (uVar5 < 0xa8ea) {
        bVar10 = uVar5 == 0xa8df;
        goto LAB_001138f4;
      }
    }
LAB_001139f9:
    uVar5 = 0x800;
  }
  uVar6 = FUN_00112632(param_1,param_2,lVar8,uVar5,1);
  local_3c[0] = 0;
  local_40 = 0;
  FUN_00111ef0(param_1,local_3c,&local_40);
  lVar1 = lVar8 + 0x618;
  uVar7 = ~local_3c[0];
  if (param_3 == '\0') {
    uVar4 = osl_readl(lVar1);
    osl_writel(uVar4 & ~(uVar5 | uVar6 & uVar7),lVar1);
  }
  else {
    uVar4 = osl_readl(lVar1);
    osl_writel(uVar6 & uVar7 | uVar5 | uVar4,lVar1);
    osl_delay(1000);
    for (iVar9 = 0x4e29; (uVar6 = osl_readl(lVar8 + 0x60c), (uVar6 & uVar5) == 0 && (iVar9 != 9));
        iVar9 = iVar9 + -10) {
      osl_delay(10);
    }
  }
  for (iVar9 = 0xbc1;
      (uVar5 = osl_readl(lVar8 + 0x10), (uVar5 & 0x1000) != (~-(uint)(param_3 == '\0') & 0x1000) &&
      (iVar9 != 9)); iVar9 = iVar9 + -10) {
    osl_delay(10);
  }
LAB_001139e5:
  si_setcoreidx(param_1,uVar3);
  return;
}

