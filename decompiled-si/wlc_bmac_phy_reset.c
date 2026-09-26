
void wlc_bmac_phy_reset(long param_1)

{
  long lVar1;
  long lVar2;
  char cVar3;
  short sVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if (*(long *)(param_1 + 0xe8) == 0) {
    return;
  }
  lVar1 = *(long *)(*(long *)(param_1 + 0xe8) + 0x28);
  if (lVar1 == 0) {
    return;
  }
  uVar5 = wlc_phy_clk_bwbits(lVar1);
  if ((*(int *)(*(long *)(param_1 + 0xe8) + 0x1c) == 0x120004) &&
     (cVar3 = si_read_pmu_autopll(*(undefined8 *)(param_1 + 0xb8)), cVar3 != '\0')) {
    if (uVar5 != 0x80) {
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xc0,0x80);
    }
    si_pmu_chipcontrol(*(undefined8 *)(param_1 + 0xb8),0,2,0);
  }
  lVar2 = *(long *)(param_1 + 0xe8);
  sVar4 = (short)*(undefined4 *)(lVar2 + 0x1c);
  if (sVar4 == 4) {
    if ((*(ushort *)(lVar2 + 0x1e) < 3) || (4 < *(ushort *)(lVar2 + 0x1e))) {
LAB_00166b00:
      uVar7 = *(undefined8 *)(param_1 + 0xb8);
      uVar6 = 0xcc;
      uVar5 = uVar5 | 0xc;
    }
    else {
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xc0,uVar5);
      osl_delay(1);
      wlc_bmac_core_phypll_reset(param_1);
      uVar7 = *(undefined8 *)(param_1 + 0xb8);
      uVar5 = 0xc;
      uVar6 = 0xc;
    }
  }
  else {
    if (sVar4 == 6) {
      if (*(short *)(lVar2 + 0x1e) == 2) {
        si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xc0,uVar5);
        if (uVar5 == 0x80) {
          si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),1,0xff000000,0x9000000);
          osl_delay(5);
          uVar7 = *(undefined8 *)(param_1 + 0xb8);
          uVar6 = 0x120c;
LAB_001668b5:
          si_pmu_pllcontrol(uVar7,2,0xffff,uVar6);
          osl_delay(5);
        }
        else {
          if (uVar5 == 0x40) {
            si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),1,0xff000000,0x12000000);
            osl_delay(5);
            uVar7 = *(undefined8 *)(param_1 + 0xb8);
            uVar6 = 0x1212;
            goto LAB_001668b5;
          }
          if (uVar5 == 0) {
            si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),1,0xff000000,0x24000000);
            osl_delay(5);
            uVar7 = *(undefined8 *)(param_1 + 0xb8);
            uVar6 = 0x2424;
            goto LAB_001668b5;
          }
        }
        si_pmu_pllupd(*(undefined8 *)(param_1 + 0xb8));
        osl_delay(5);
        si_pmu_chipcontrol(*(undefined8 *)(param_1 + 0xb8),0,0x40000000,0x40000000);
        osl_delay(5);
        si_pmu_chipcontrol(*(undefined8 *)(param_1 + 0xb8),0,0x40000000,0);
      }
      else if (*(short *)(lVar2 + 0x1e) == 3) {
        si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x618,0x40,0);
        osl_delay(100);
        si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x61c,0x40,0);
        osl_delay(100);
        if (uVar5 == 0x80) {
          si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),7,0xff000000,0x6000000);
          osl_delay(100);
          uVar7 = *(undefined8 *)(param_1 + 0xb8);
          uVar6 = 0xc08;
LAB_00166a1f:
          si_pmu_pllcontrol(uVar7,8,0xffff,uVar6);
          osl_delay(100);
        }
        else {
          if (uVar5 == 0x40) {
            si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),7,0xff000000,0xc000000);
            osl_delay(100);
            uVar7 = *(undefined8 *)(param_1 + 0xb8);
            uVar6 = 0xc0c;
            goto LAB_00166a1f;
          }
          if (uVar5 == 0) {
            si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),7,0xff000000,0x18000000);
            osl_delay(100);
            uVar7 = *(undefined8 *)(param_1 + 0xb8);
            uVar6 = 0x1818;
            goto LAB_00166a1f;
          }
        }
        si_pmu_pllcontrol(*(undefined8 *)(param_1 + 0xb8),0xb,0xffffff00,0x22222200);
        osl_delay(100);
        si_pmu_pllupd(*(undefined8 *)(param_1 + 0xb8));
        osl_delay(100);
        si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x618,0x40,0x40);
        osl_delay(100);
        si_corereg(*(undefined8 *)(param_1 + 0xb8),0,0x61c,0x40,0x40);
        osl_delay(100);
      }
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xcc,uVar5 | 0xc);
      osl_delay(100);
      goto LAB_00166b17;
    }
    if (sVar4 != 0xb) goto LAB_00166b00;
    uVar7 = *(undefined8 *)(param_1 + 0xb8);
    uVar6 = 0xce;
    uVar5 = uVar5 | 0xe;
  }
  si_core_cflags(uVar7,uVar6,uVar5);
LAB_00166b17:
  osl_delay(2);
  wlc_bmac_core_phy_clk(param_1,1);
  if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 10) {
    wlc_phy_anacore(lVar1,1);
  }
  return;
}

