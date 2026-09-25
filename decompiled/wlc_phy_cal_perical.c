
void wlc_phy_cal_perical(long param_1,undefined1 param_2)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  undefined1 *puVar5;
  short sVar6;
  short sVar7;
  undefined8 uVar8;
  short sVar9;
  long lVar10;
  
  *(undefined4 *)(*(long *)(param_1 + 0xf58) + 200) = 0;
  iVar4 = *(int *)(param_1 + 0x160);
  *(undefined1 *)(param_1 + 0x18d) = 1;
  if (((iVar4 != 7) && (iVar4 != 4)) && (iVar4 != 0xb)) {
    return;
  }
  cVar1 = *(char *)(param_1 + 0xf89);
  if (cVar1 == '\x03') {
    return;
  }
  if (cVar1 == '\0') {
    return;
  }
  switch(param_2) {
  case 2:
    if (((*(byte *)(param_1 + 0x19c) & 0x20) != 0) && (iVar4 == 0xb)) {
      return;
    }
    *(undefined1 *)(param_1 + 0x18d) = 0;
    *(bool *)(param_1 + 0x18e) = 0x12 < *(uint *)(param_1 + 0x164);
    if (*(char *)(param_1 + 0xf9c) != '\0') {
      iVar4 = *(int *)(param_1 + 0x160);
      if (iVar4 == 7) {
        sVar3 = wlc_phy_tempsense_htphy(param_1);
        sVar7 = *(short *)(*(long *)(param_1 + 0xf58) + 0xaa);
      }
      else if (iVar4 == 4) {
        sVar3 = wlc_phy_tempsense_nphy(param_1);
        sVar7 = *(short *)(*(long *)(param_1 + 0xf58) + 0x1a);
      }
      else {
        if (iVar4 != 0xb) goto LAB_001b6778;
        lVar10 = *(long *)(param_1 + 0xf58);
        iVar4 = *(int *)(*(long *)(param_1 + 0x20) + 0x34);
        if ((uint)(iVar4 - *(int *)(lVar10 + 0xc4)) < *(uint *)(*(long *)(param_1 + 0x20) + 0x7c)) {
          sVar3 = (short)*(undefined4 *)(lVar10 + 0xcc);
        }
        else {
          *(int *)(lVar10 + 0xc4) = iVar4;
          sVar3 = wlc_phy_tempsense_acphy(param_1);
        }
        sVar7 = *(short *)(*(long *)(param_1 + 0xf58) + 0xba);
      }
      lVar10 = *(long *)(param_1 + 0xf58);
      sVar9 = (short)*(undefined4 *)(lVar10 + 0xcc);
      sVar6 = sVar3 - sVar9;
      if (sVar3 <= sVar9) {
        sVar6 = sVar9 - sVar3;
      }
      if (((sVar6 < (short)(ushort)*(byte *)(param_1 + 0xf9c)) &&
          ((uint)(*(int *)(*(long *)(param_1 + 0x20) + 0x34) - *(int *)(lVar10 + 0xc0)) < 900)) &&
         (sVar7 == *(short *)(param_1 + 0x17e))) {
        *(undefined4 *)(lVar10 + 200) = *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x7c);
        return;
      }
      *(short *)(lVar10 + 0xcc) = sVar3;
    }
LAB_001b6778:
    if (*(char *)(param_1 + 0xf89) != '\x02') {
      if (*(char *)(param_1 + 0xf89) != '\x01') {
        return;
      }
      iVar4 = *(int *)(param_1 + 0x160);
      if (iVar4 != 4) {
LAB_001b67ca:
        if (iVar4 == 7) {
          wlc_phy_cals_htphy(param_1,0);
          return;
        }
        if (iVar4 != 0xb) {
          return;
        }
        wlc_phy_cals_acphy(param_1,0);
        return;
      }
      uVar8 = 0;
LAB_001b67bd:
      wlc_phy_cal_perical_nphy_run(param_1,uVar8);
      return;
    }
    puVar5 = *(undefined1 **)(param_1 + 0xf58);
    if (puVar5[1] != '\0') {
      return;
    }
    break;
  case 3:
    if (cVar1 != '\x02') {
      return;
    }
    if (*(char *)(*(long *)(param_1 + 0xf58) + 1) != '\0') {
      wlc_phy_cal_perical_mphase_reset(param_1);
    }
    **(undefined1 **)(param_1 + 0xf58) = 0;
    goto LAB_001b6796;
  case 4:
  case 5:
  case 6:
    if ((cVar1 == '\x02') && (*(char *)(*(long *)(param_1 + 0xf58) + 1) != '\0')) {
      wlc_phy_cal_perical_mphase_reset(param_1);
    }
    *(undefined1 *)(param_1 + 0xf84) = 1;
    if (*(int *)(param_1 + 0x160) == 4) {
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x382) = 1;
    }
    if (*(char *)(param_1 + 0xf9c) != '\0') {
      iVar4 = *(int *)(param_1 + 0x160);
      if (iVar4 == 4) {
        lVar10 = *(long *)(param_1 + 0xf58);
        uVar2 = wlc_phy_tempsense_nphy(param_1);
      }
      else if (iVar4 == 7) {
        lVar10 = *(long *)(param_1 + 0xf58);
        uVar2 = wlc_phy_tempsense_htphy(param_1);
      }
      else {
        if (iVar4 != 0xb) goto LAB_001b663a;
        lVar10 = *(long *)(param_1 + 0xf58);
        uVar2 = wlc_phy_tempsense_acphy(param_1);
      }
      *(undefined2 *)(lVar10 + 0xcc) = uVar2;
    }
LAB_001b663a:
    iVar4 = *(int *)(param_1 + 0x160);
    uVar8 = 1;
    if (iVar4 != 4) goto LAB_001b67ca;
    goto LAB_001b67bd;
  default:
    goto switchD_001b6576_caseD_7;
  case 0xb:
    if (iVar4 != 4) {
      return;
    }
    if (*(char *)(*(long *)(param_1 + 0xf58) + 1) == '\0') {
      if (*(char *)(param_1 + 0xf9c) != '\0') {
        sVar3 = wlc_phy_tempsense_nphy(param_1);
        sVar6 = (short)*(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xcc);
        sVar7 = sVar3 - sVar6;
        if (sVar3 <= sVar6) {
          sVar7 = sVar6 - sVar3;
        }
        if (sVar7 < (short)(ushort)*(byte *)(param_1 + 0xf9c)) {
          wlc_phy_txpwr_papd_cal_nphy_dcs(param_1);
          return;
        }
        *(short *)(*(long *)(param_1 + 0xf58) + 0xcc) = sVar3;
      }
    }
    else {
      wlc_phy_cal_perical_mphase_reset(param_1);
      if (*(char *)(param_1 + 0xf9c) != '\0') {
        uVar2 = wlc_phy_tempsense_nphy(param_1);
        *(undefined2 *)(*(long *)(param_1 + 0xf58) + 0xcc) = uVar2;
      }
    }
    if (*(char *)(param_1 + 0xf89) != '\x02') {
      return;
    }
    puVar5 = *(undefined1 **)(param_1 + 0xf58);
  }
  *puVar5 = 1;
LAB_001b6796:
  FUN_001b37d0(param_1,5);
switchD_001b6576_caseD_7:
  return;
}

