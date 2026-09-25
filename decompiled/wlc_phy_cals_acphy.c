
void wlc_phy_cals_acphy(long param_1,undefined1 param_2)

{
  char *pcVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  int iVar9;
  undefined1 local_51;
  undefined2 local_3a [5];
  
  lVar6 = *(long *)(param_1 + 0xf58);
  bVar2 = *(byte *)(lVar6 + 1);
  local_3a[0] = 0xacdc;
  if ((*(byte *)(param_1 + 0x19c) & 0x10) != 0) {
    return;
  }
  lVar7 = *(long *)(param_1 + 0x20);
  uVar3 = *(undefined1 *)(lVar7 + 0xa7);
  uVar4 = *(undefined1 *)(lVar7 + 0xa6);
  *(undefined1 *)(lVar7 + 0xa7) = *(undefined1 *)(lVar7 + 0xa5);
  *(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa6) =
       *(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa4);
  wlc_phy_rxcore_setstate_acphy(param_1,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa5));
  if (((bVar2 == 0x11) || (bVar2 == 0)) && (*(char *)(*(long *)(param_1 + 0x138) + 0x33c) != '\0'))
  {
    *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x33d) = 1;
    wlc_phy_noise_sample_request_crsmincal(param_1);
  }
  if ((*(short *)(param_1 + 0x17e) != *(short *)(lVar6 + 0xba)) ||
     (local_51 = param_2, *(char *)(lVar6 + 100) == '\0')) {
    local_51 = 0;
  }
  if ((1 < bVar2) && (*(short *)(lVar6 + 0xba) != *(short *)(param_1 + 0x17e))) {
    wlc_phy_cal_perical_mphase_restart(param_1);
  }
  uVar5 = *(undefined1 *)(param_1 + 4000);
  if (bVar2 == 0) {
    FUN_0019330c(param_1,29000);
    *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
         *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
    *(undefined2 *)(lVar6 + 0xba) = *(undefined2 *)(param_1 + 0x17e);
    if (*(char *)(param_1 + 0xf84) != '\0') {
      FUN_001b0ce9(param_1);
    }
    FUN_001b1f67(param_1,lVar6 + 0x92);
    FUN_001ac9b6(param_1,local_51,0,0);
    FUN_001ac9b6(param_1,local_51,0,1);
    FUN_001aeb3a(param_1);
    uVar8 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    wlc_phy_table_write_acphy(param_1,0xc,1,0x5f,0x10,local_3a);
    phy_reg_mod(param_1,0x19e,2,(uVar8 >> 1 & 1) * 2);
    *(undefined1 *)(param_1 + 0xf84) = 0;
    *(undefined2 *)(*(long *)(param_1 + 0x138) + 0x44a) = 0;
    wlc_phy_scanroam_cache_cal_acphy(param_1,1);
    goto LAB_001b2588;
  }
  switch(bVar2) {
  case 1:
    FUN_0019330c(param_1,0x3c);
    *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
         *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
    *(undefined2 *)(lVar6 + 0xba) = *(undefined2 *)(param_1 + 0x17e);
    FUN_001b1f67(param_1,lVar6 + 0x92);
    break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
    if ((10 < bVar2) && (*(int *)(param_1 + 0x164) != 1)) goto switchD_001b2309_caseD_d;
    FUN_0019330c(param_1,0x1130);
    if ((*(byte *)(param_1 + 0xf86) & 0x10) != 0) {
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x44c) = 1;
    }
    iVar9 = FUN_001ac9b6(param_1,local_51,1,0);
    if (iVar9 != 0) goto LAB_001b2574;
    if (bVar2 == 0xc) {
      pcVar1 = (char *)(*(long *)(param_1 + 0xf58) + 1);
      *pcVar1 = *pcVar1 + '\x01';
    }
    break;
  case 0xd:
switchD_001b2309_caseD_d:
    pcVar1 = (char *)(*(long *)(param_1 + 0xf58) + 1);
    *pcVar1 = *pcVar1 + '\x01';
    return;
  case 0xe:
  case 0xf:
  case 0x10:
    FUN_0019330c(param_1,0x1130);
    if ((*(byte *)(param_1 + 0xf86) & 0x10) != 0) {
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x44c) = 1;
    }
    iVar9 = FUN_001ac9b6(param_1,local_51,1,1);
    if (iVar9 != 0) goto LAB_001b2574;
    break;
  case 0x11:
    FUN_0019330c(param_1,0x251c);
    if ((*(byte *)(param_1 + 0xf86) & 1) != 0) {
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x44c) = 1;
    }
    FUN_001aeb3a(param_1);
    *(undefined2 *)(*(long *)(param_1 + 0x138) + 0x44a) = 0;
    wlc_phy_scanroam_cache_cal_acphy(param_1,1);
    break;
  case 0x12:
    FUN_0019330c(param_1,300);
    if ((*(byte *)(param_1 + 0xf86) & 4) != 0) {
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x44c) = 1;
    }
    FUN_00193e5b(param_1);
    FUN_00194b87(param_1,1);
    *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
         *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
    *(undefined2 *)(lVar6 + 0xba) = *(undefined2 *)(param_1 + 0x17e);
    if (*(char *)(param_1 + 0xf84) == '\0') goto LAB_001b250c;
    break;
  case 0x13:
    FUN_0019330c(param_1,0x60e);
    if ((*(byte *)(param_1 + 0xf86) & 8) != 0) {
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x44c) = 1;
    }
    FUN_001b0ce9(param_1);
    *(undefined1 *)(param_1 + 0xf84) = 0;
LAB_001b250c:
    uVar8 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    wlc_phy_table_write_acphy(param_1,0xc,1,0x5f,0x10,local_3a);
    phy_reg_mod(param_1,0x19e,2,(uVar8 >> 1 & 1) * 2);
LAB_001b2574:
    wlc_phy_cal_perical_mphase_reset(param_1);
    goto LAB_001b2588;
  default:
    wlc_phy_cal_perical_mphase_reset(param_1);
    return;
  }
  pcVar1 = (char *)(*(long *)(param_1 + 0xf58) + 1);
  *pcVar1 = *pcVar1 + '\x01';
LAB_001b2588:
  wlc_phy_txpwrctrl_enable_acphy(param_1,uVar5);
  wlc_phyreg_exit(param_1);
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  *(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa7) = uVar3;
  *(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa6) = uVar4;
  wlc_phy_rxcore_setstate_acphy(param_1,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa7));
  return;
}

