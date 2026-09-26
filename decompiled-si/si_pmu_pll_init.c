
void si_pmu_pll_init(long param_1,undefined8 param_2,int param_3)

{
  long lVar1;
  long lVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  undefined8 uVar9;
  int iVar10;
  undefined8 uVar11;
  bool bVar12;
  
  uVar3 = si_coreidx();
  lVar7 = si_setcoreidx(param_1,0);
  uVar6 = *(uint *)(param_1 + 0x3c);
  if (uVar6 == 0x4336) goto LAB_00117de0;
  if (uVar6 < 0x4337) {
    if (uVar6 == 0x4324) goto LAB_00117f2c;
    if (uVar6 < 0x4325) {
      if (uVar6 != 0x4315) {
        if (uVar6 < 0x4316) {
          if (uVar6 != 0x10f6) {
            if (uVar6 != 0x4314) goto LAB_00117f81;
            goto LAB_00117f67;
          }
        }
        else {
          if (uVar6 == 0x4319) goto LAB_00117de0;
          if (uVar6 != 0x4322) goto LAB_00117f81;
        }
LAB_00117df5:
        if (*(int *)(param_1 + 0x40) == 0) {
          lVar1 = lVar7 + 0x618;
          lVar2 = lVar7 + 0x61c;
          uVar4 = osl_readl(lVar1);
          uVar5 = osl_readl(lVar2);
          uVar6 = osl_readl(lVar1);
          osl_writel(uVar6 & 0xffffffdf,lVar1);
          uVar6 = osl_readl(lVar2);
          osl_writel(uVar6 & 0xffffffdf,lVar2);
          for (iVar10 = 0x4e29;
              (uVar8 = osl_readl(lVar7 + 0x1e0), (uVar8 & 0x20000) != 0 && (iVar10 != 9));
              iVar10 = iVar10 + -10) {
            osl_delay(10);
          }
          lVar1 = lVar7 + 0x618;
          lVar2 = lVar7 + 0x61c;
          uVar6 = osl_readl(lVar1);
          osl_writel(uVar6 & 0xffffffef,lVar1);
          uVar6 = osl_readl(lVar2);
          osl_writel(uVar6 & 0xffffffef,lVar2);
          osl_delay(1000);
          osl_writel(10,lVar7 + 0x660);
          osl_writel(0x380005c0,lVar7 + 0x664);
          osl_delay(100);
          osl_writel(uVar5,lVar2);
          osl_delay(100);
          osl_writel(uVar4,lVar1);
          osl_delay(100);
        }
        goto LAB_00117f81;
      }
    }
    else if (uVar6 == 0x4329) {
      if (param_3 == 0) {
        param_3 = 0x9600;
      }
    }
    else if (uVar6 < 0x432a) {
      if (uVar6 != 0x4325) {
        if (uVar6 != 0x4328) goto LAB_00117f81;
        goto LAB_00117dc1;
      }
    }
    else {
      if (uVar6 == 0x4334) goto LAB_00117f71;
      if (0x4334 < uVar6) goto LAB_00117f2c;
      if (uVar6 != 0x4330) goto LAB_00117f81;
    }
LAB_00117de0:
    FUN_00113e81(param_1,param_2,lVar7,param_3);
    goto LAB_00117f81;
  }
  if (uVar6 == 0xa8d5) goto LAB_00117df5;
  if (uVar6 < 0xa8d6) {
    if (uVar6 == 0x4360) goto LAB_00117f18;
    if (0x4360 < uVar6) {
      if (uVar6 == 0x5354) {
        if (param_3 == 0) {
          param_3 = 25000;
        }
LAB_00117dc1:
        FUN_00113b27(param_1,param_2,lVar7,param_3);
        goto LAB_00117f81;
      }
      if ((uVar6 < 0x5354) || (1 < uVar6 - 0xa886)) goto LAB_00117f81;
LAB_00117f67:
      if (param_3 == 0) {
        param_3 = 20000;
      }
LAB_00117f71:
      FUN_00116832(param_1,param_2,lVar7,param_3);
      goto LAB_00117f81;
    }
    if (uVar6 != 0x4350) {
      bVar12 = uVar6 == 0x4352;
      goto LAB_00117dac;
    }
    FUN_001179ca(param_1,param_2,lVar7,param_3);
    if (param_3 != 40000) goto LAB_00117f81;
    uVar9 = 0;
    uVar11 = 0x3c8;
  }
  else {
    if (uVar6 < 0xa8ec) {
      if (uVar6 < 0xa8ea) {
        if (uVar6 == 0xa8df) goto LAB_00117df5;
        if (uVar6 != 0xa8e7) goto LAB_00117f81;
      }
LAB_00117f2c:
      FUN_001179ca(param_1,param_2,lVar7,param_3);
      goto LAB_00117f81;
    }
    if (uVar6 == 0xa962) goto LAB_00117de0;
    bVar12 = uVar6 == 0xa9c4;
LAB_00117dac:
    if (!bVar12) goto LAB_00117f81;
LAB_00117f18:
    if (*(uint *)(param_1 + 0x40) < 3) goto LAB_00117f81;
    uVar9 = 0x62;
    uVar11 = 0x3c0;
  }
  FUN_00117afd(param_1,uVar11,uVar9);
LAB_00117f81:
  si_setcoreidx(param_1,uVar3);
  return;
}

