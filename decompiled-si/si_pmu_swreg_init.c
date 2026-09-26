
void si_pmu_swreg_init(long param_1,undefined8 param_2)

{
  short sVar1;
  undefined4 uVar2;
  uint uVar3;
  long lVar4;
  char cVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 == 0x4330) {
LAB_00116641:
    sVar1 = getintvar(0,"cbuckout");
    if (sVar1 == 0) {
      sVar1 = 0x5dc;
    }
    lVar4 = 0;
    if (sVar1 != cbuck2vreg_tbl) {
      if (sVar1 != DAT_0059c7b4) goto LAB_00116749;
      lVar4 = 1;
    }
    cVar5 = (&DAT_0059c7b2)[lVar4 * 4];
    if (cVar5 < '\0') goto LAB_00116749;
    si_pmu_set_ldo_voltage(param_1,param_2,7,cVar5);
    uVar6 = 8;
  }
  else {
    if (0x4330 < uVar3) {
      if (uVar3 != 0x4336) {
        if (uVar3 < 0x4337) {
          if ((uVar3 != 0x4334) || ((*(uint *)(param_1 + 0x48) & 7) == 6)) goto LAB_00116749;
          uVar6 = 0x800000;
          uVar7 = 0x800000;
          uVar8 = 2;
        }
        else {
          if (uVar3 != 0xa887) {
            if (uVar3 != 0xa962) goto LAB_00116749;
            goto LAB_00116641;
          }
          si_pmu_regcontrol(param_1,0,2,2);
          si_pmu_set_ldo_voltage(param_1,param_2,7,2);
          si_pmu_set_ldo_voltage(param_1,param_2,8,2);
          si_pmu_set_ldo_voltage(param_1,param_2,9,7);
          uVar6 = 0x10;
          uVar7 = 0x3f;
          uVar8 = 0;
        }
        si_pmu_chipcontrol(param_1,uVar8,uVar7,uVar6);
        goto LAB_00116749;
      }
      if (*(uint *)(param_1 + 0x40) < 2) {
        si_pmu_set_ldo_voltage(param_1,param_2,5,0xe);
        si_pmu_set_ldo_voltage(param_1,param_2,6,0xe);
        si_pmu_set_ldo_voltage(param_1,param_2,9,0xe);
      }
      if (*(int *)(param_1 + 0x40) == 2) {
        si_pmu_set_ldo_voltage(param_1,param_2,7,0x16);
        si_pmu_set_ldo_voltage(param_1,param_2,8,0x16);
        si_pmu_set_ldo_voltage(param_1,param_2,0xb,3);
      }
      if (*(int *)(param_1 + 0x40) == 0) {
        si_pmu_regcontrol(param_1,2,0x400000,0x400000);
      }
      goto LAB_00116641;
    }
    if (uVar3 == 0x4315) {
      if (*(int *)(param_1 + 0x40) == 2) {
        uVar2 = si_coreidx();
        lVar4 = si_setcoreidx(param_1,0);
        osl_writel(4,lVar4 + 0x658);
        uVar3 = osl_readl(lVar4 + 0x65c);
        osl_writel(uVar3 | 0x10000,lVar4 + 0x65c);
        si_setcoreidx(param_1,uVar2);
      }
      goto LAB_00116749;
    }
    if (uVar3 == 0x4325) {
      if (*(uint *)(param_1 + 0x40) < 3) goto LAB_00116749;
      if ((*(byte *)(param_1 + 0x49) & 2) != 0) {
        si_pmu_set_ldo_voltage(param_1,param_2,5,0xf);
        si_pmu_set_ldo_voltage(param_1,param_2,6,0xf);
      }
      si_pmu_set_ldo_voltage(param_1,param_2,7,0xb);
      si_pmu_set_ldo_voltage(param_1,param_2,8,0xb);
      si_pmu_set_ldo_voltage(param_1,param_2,9,1);
      if ((*(byte *)(param_1 + 0x37) & 4) == 0) goto LAB_00116749;
      cVar5 = '\x01';
      uVar6 = 10;
    }
    else {
      if ((uVar3 != 0x4314) || (*(int *)(param_1 + 0x40) != 0)) goto LAB_00116749;
      cVar5 = '\0';
      uVar6 = 2;
    }
  }
  si_pmu_set_ldo_voltage(param_1,param_2,uVar6,cVar5);
LAB_00116749:
  si_pmu_otp_regcontrol(param_1,param_2);
  return;
}

