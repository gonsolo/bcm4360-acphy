
void wlc_phy_cal_perical_nphy_run(long param_1,char param_2)

{
  char *pcVar1;
  long lVar2;
  undefined1 *puVar3;
  char cVar4;
  ushort uVar5;
  long lVar6;
  bool bVar7;
  undefined1 uVar8;
  short sVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  ushort *puVar18;
  bool bVar19;
  byte bVar20;
  undefined4 auStack_e8 [8];
  undefined8 *local_c8;
  uint local_bc;
  char local_b5;
  uint local_b4;
  ushort local_ae;
  int local_ac;
  undefined4 local_a8 [8];
  undefined4 local_88 [8];
  undefined1 local_68 [16];
  undefined8 local_58;
  ushort local_48 [12];
  
  bVar20 = 0;
  local_58 = 0;
  lVar6 = *(long *)(param_1 + 0x138);
  if (*(char *)(param_1 + 0xf88) == '\0') {
    wlc_phy_cal_perical_mphase_reset();
    return;
  }
  if ((*(byte *)(param_1 + 0x19c) & 0x10) != 0) {
    return;
  }
  if (param_2 == '\0') {
    bVar19 = *(short *)(param_1 + 0x17e) == *(short *)(*(long *)(param_1 + 0xf58) + 0x1a);
  }
  else {
    bVar19 = param_2 == '\x02';
  }
  bVar19 = !bVar19;
  if (*(char *)(lVar6 + 0x382) != '\0') {
    bVar19 = *(char *)(lVar6 + 0x382) == '\x01';
  }
  if ((1 < *(byte *)(*(long *)(param_1 + 0xf58) + 1)) &&
     (*(short *)(*(long *)(param_1 + 0xf58) + 0x1a) != *(short *)(param_1 + 0x17e))) {
    wlc_phy_cal_perical_mphase_restart(param_1);
  }
  lVar13 = *(long *)(param_1 + 0x20);
  if (*(int *)(lVar13 + 0x3c) == 0xa8e5) {
    if (*(char *)(*(long *)(param_1 + 0xf58) + 1) != '\0') {
      uVar15 = *(undefined8 *)(lVar13 + 0x20);
      uVar14 = 5000;
LAB_0024d2e0:
      wlapi_bmac_write_shm(uVar15,0xb8,uVar14);
    }
  }
  else {
    if (*(char *)(*(long *)(param_1 + 0xf58) + 1) == '\n') {
      wlapi_bmac_write_shm(*(undefined8 *)(lVar13 + 0x20),0xb8,10000);
    }
    if ((*(char *)(*(long *)(param_1 + 0xf58) + 1) == '\b') &&
       (((*(char *)(param_1 + 0xf60) != '\0' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)) ||
        ((*(char *)(param_1 + 0xf61) != '\0' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000))
        )))) {
      uVar14 = 31000;
      uVar15 = *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20);
      goto LAB_0024d2e0;
    }
  }
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa8dc) {
    wlapi_bmac_mhf(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0,2,2,2);
  }
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  wlc_phyreg_enter(param_1);
  if ((*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324) &&
     (*(int *)(*(long *)(param_1 + 0x20) + 0x40) - 3U < 2)) {
    FUN_0021583b(param_1,1);
  }
  if (0x12 < *(uint *)(param_1 + 0x164)) {
    wlc_phy_lcnxn_disable_stalls(param_1,1);
  }
  local_ae = 0;
  if (0x11 < *(uint *)(param_1 + 0x164)) {
    local_ae = phy_reg_read(param_1,0x3d4);
    local_ae = local_ae & 1;
    if (local_ae != 0) {
      wlc_phy_ocl_enable_disable_nphy(param_1,0);
      local_ae = 1;
    }
  }
  if (*(byte *)(*(long *)(param_1 + 0xf58) + 1) < 2) {
    uVar8 = FUN_00213b97(param_1,0);
    *(undefined1 *)(lVar6 + 0x1c7) = uVar8;
    uVar8 = FUN_00213b97(param_1,1);
    *(undefined1 *)(lVar6 + 0x1c8) = uVar8;
    if (*(char *)(param_1 + 0x221) == '\0') {
      *(undefined2 *)(lVar6 + 0x1ce) = 0;
      *(undefined2 *)(lVar6 + 0x1d0) = 0;
    }
    else {
      wlc_phy_table_read_nphy(param_1,7,2,0x110,0x10,lVar6 + 0x1ce);
    }
  }
  wlc_phy_get_tx_gain_nphy(local_88,param_1);
  local_b5 = *(char *)(param_1 + 0x221);
  wlc_phy_txpwrctrl_enable_nphy(param_1,0);
  if (*(char *)(param_1 + 0x180) == '\x02') {
    wlc_phy_antsel_init_nphy(param_1,1);
  }
  cVar4 = *(char *)(*(long *)(param_1 + 0xf58) + 1);
  if (cVar4 == '\0') {
    bVar7 = false;
    if (2 < *(uint *)(param_1 + 0x164)) {
      bVar7 = true;
      FUN_0024324b(param_1);
      puVar16 = (undefined4 *)(lVar6 + 0x1d2);
      puVar17 = local_88;
      for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
        *puVar17 = *puVar16;
        puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
        puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
      }
    }
    puVar16 = local_88;
    puVar17 = auStack_e8;
    for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
      *puVar17 = *puVar16;
      puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
      puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
    }
    iVar10 = wlc_phy_cal_txiqlo_nphy(param_1,bVar19,0);
    if (iVar10 == 0) {
      if ((*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324) &&
         (((iVar10 = *(int *)(*(long *)(param_1 + 0x20) + 0x40), iVar10 == 5 || (iVar10 == 2)) &&
          (*(char *)(lVar6 + 0x119) != '\0')))) {
        wlc_phyreg_exit(param_1);
        wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
        wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0xb8,10000);
        wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
        wlc_phyreg_enter(param_1);
        if ((*(char *)(param_1 + 0xf84) != '\0') ||
           (uVar11 = 0, *(char *)(*(long *)(param_1 + 0x138) + 0x382) == '\x01')) {
          uVar11 = 2;
        }
        puVar16 = local_88;
        puVar17 = auStack_e8;
        for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
          *puVar17 = *puVar16;
          puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
          puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
        }
        iVar10 = wlc_phy_cal_rxiq_nphy(param_1,uVar11,0,3);
        if (iVar10 == 0) {
          wlc_phy_dynamic_rflo_ucode_war_nphy(param_1,4);
          puVar16 = local_88;
          puVar17 = auStack_e8;
          for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
            *puVar17 = *puVar16;
            puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
            puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
          }
          iVar10 = wlc_phy_cal_txiqlo_nphy(param_1,bVar19,0);
          if (iVar10 == 0) {
            if (((*(char *)(param_1 + 0xf60) != '\0') &&
                ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)) ||
               ((*(char *)(param_1 + 0xf61) != '\0' &&
                ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000)))) {
              wlc_phyreg_exit(param_1);
              wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
              wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0xb8,31000);
              wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
              wlc_phyreg_enter(param_1);
              wlc_phy_dynamic_rflo_ucode_war_nphy(param_1,4);
              FUN_0024b7c3(param_1,1,0,*(char *)(param_1 + 0x168) + -1);
            }
            FUN_0022c733(param_1);
            FUN_0022cb4a(param_1);
            *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
                 *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
          }
          wlc_phy_dynamic_rflo_ucode_war_nphy(param_1,5);
        }
      }
      else {
        if (((*(char *)(param_1 + 0xf60) != '\0') && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0))
           || ((*(char *)(param_1 + 0xf61) != '\0' &&
               ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000)))) {
          wlc_phyreg_exit(param_1);
          wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
          if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa8e5) {
            uVar15 = 9000;
          }
          else {
            uVar15 = 31000;
          }
          wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0xb8,uVar15);
          wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
          wlc_phyreg_enter(param_1);
          FUN_0024b7c3(param_1,1,0,*(char *)(param_1 + 0x168) + -1);
        }
        wlc_phyreg_exit(param_1);
        wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
        wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0xb8,10000);
        wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
        wlc_phyreg_enter(param_1);
        if ((*(char *)(param_1 + 0xf84) != '\0') ||
           (uVar11 = 0, *(char *)(*(long *)(param_1 + 0x138) + 0x382) == '\x01')) {
          uVar11 = 2;
        }
        puVar16 = local_88;
        puVar17 = auStack_e8;
        for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
          *puVar17 = *puVar16;
          puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
          puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
        }
        iVar10 = wlc_phy_cal_rxiq_nphy(param_1,uVar11,0,3);
        if (iVar10 == 0) {
          FUN_0022c733(param_1);
          FUN_0022cb4a(param_1);
          *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
               *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
        }
      }
    }
    if ((0x11 < *(uint *)(param_1 + 0x164)) || (*(uint *)(param_1 + 0x164) == 0x10)) {
      FUN_002353de(param_1);
    }
    if (param_2 != '\0') {
      wlc_phy_rssi_cal_nphy(param_1);
    }
    if ((*(char *)(param_1 + 0xf84) != '\0') ||
       (*(char *)(*(long *)(param_1 + 0x138) + 0x382) == '\x01')) {
      *(undefined1 *)(param_1 + 0xf84) = 0;
      FUN_00241f59(param_1);
      FUN_0021ed75(param_1);
    }
    if (*(uint *)(param_1 + 0x164) < 0x13) {
      if (2 < *(uint *)(param_1 + 0x164)) {
        wlc_phy_radio205x_vcocal_nphy(param_1);
      }
    }
    else {
      wlc_20671_vco_cal(param_1,1);
    }
    goto LAB_0024df81;
  }
  switch(cVar4) {
  case '\x01':
    if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) &&
       (*(int *)(*(long *)(param_1 + 0x20) + 0x58) == 0x594)) {
      uVar8 = 0x44;
      wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
      sVar9 = wlc_phy_tempsense_nphy(param_1);
      if (10 < sVar9) {
        uVar8 = phy_reg_read(param_1,0x280);
      }
      phy_reg_mod(param_1,0x283,0xff,uVar8);
      phy_reg_mod(param_1,0x280,0xff,uVar8);
      wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    }
    *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
         *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
    *(undefined2 *)(*(long *)(param_1 + 0xf58) + 0x1a) = *(undefined2 *)(param_1 + 0x17e);
    if (*(uint *)(param_1 + 0x164) < 3) {
      wlc_phy_get_tx_gain_nphy(local_a8,param_1);
      puVar16 = local_a8;
      puVar17 = (undefined4 *)(lVar6 + 0x1d2);
      for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
        *puVar17 = *puVar16;
        puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
        puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
      }
    }
    else {
      FUN_0024324b(param_1);
    }
    goto LAB_0024df4d;
  case '\x02':
  case '\x03':
  case '\x04':
  case '\x05':
  case '\x06':
  case '\a':
    if ((*(byte *)(param_1 + 0xf86) & 0x10) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    puVar16 = (undefined4 *)(lVar6 + 0x1d2);
    puVar17 = auStack_e8;
    for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
      *puVar17 = *puVar16;
      puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
      puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
    }
    iVar10 = wlc_phy_cal_txiqlo_nphy(param_1,bVar19,1);
    if (iVar10 != 0) goto switchD_0024d83f_default;
    if (*(uint *)(param_1 + 0x164) < 3) {
      if (*(char *)(*(long *)(param_1 + 0xf58) + 1) == '\x06') {
        *(undefined1 *)(*(long *)(param_1 + 0xf58) + 1) = 8;
        break;
      }
    }
    else if ((0x12 < *(uint *)(param_1 + 0x164)) &&
            (lVar13 = *(long *)(param_1 + 0xf58), *(char *)(lVar13 + 1) == '\a')) {
      if ((*(char *)(lVar6 + 0x119) != '\0') && (*(char *)(lVar6 + 0x132) != '\0'))
      goto LAB_0024ddc6;
      goto LAB_0024dca9;
    }
    goto LAB_0024df4d;
  case '\b':
    if (0x12 < *(uint *)(param_1 + 0x164)) {
      if ((*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324) &&
         (((iVar10 = *(int *)(*(long *)(param_1 + 0x20) + 0x40), iVar10 == 5 || (iVar10 == 2)) &&
          (*(char *)(lVar6 + 0x119) != '\0')))) {
        wlc_phy_dynamic_rflo_ucode_war_nphy(param_1,4);
      }
      FUN_0022cb4a(param_1);
    }
    if ((*(byte *)(param_1 + 0xf86) & 2) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    if (((*(char *)(param_1 + 0xf60) != '\0') && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)) ||
       ((*(char *)(param_1 + 0xf61) != '\0' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000)))
       ) {
      if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa8e5) {
        FUN_0024b7c3(param_1,1,0,0);
      }
      else {
        if (6 < *(uint *)(param_1 + 0x164)) {
          uVar5 = *(ushort *)(param_1 + 0x17e);
          local_48[0] = 0;
          local_48[1] = 0x20;
          puVar18 = local_48;
          lVar13 = 0;
          uVar12 = phy_reg_read(param_1,0x79);
          local_c8 = &local_58;
          local_bc = ~-(uint)((uVar5 & 0xc000) == 0) & 0x10;
          local_b4 = (uVar12 & 0x30) >> 2;
          do {
            lVar2 = lVar13 + (long)local_c8;
            local_ac = *puVar18 + local_bc;
            puVar18 = puVar18 + 1;
            puVar3 = local_68 + lVar13;
            lVar13 = lVar13 + 4;
            wlc_phy_table_read_nphy(param_1,9,4,local_ac,8,lVar2);
            wlc_phy_table_read_nphy(param_1,9,4,local_b4 + local_ac,8,puVar3);
            wlc_phy_table_write_nphy(param_1,9,4,local_ac,8,puVar3);
          } while (lVar13 != 8);
        }
        FUN_0024b7c3(param_1,1,0,*(char *)(param_1 + 0x168) + -1);
        if (6 < *(uint *)(param_1 + 0x164)) {
          local_48[0] = 0;
          local_48[1] = 0x20;
          bVar20 = ~-((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) & 0x10;
          wlc_phy_table_write_nphy(param_1,9,4,bVar20,8,&local_58);
          wlc_phy_table_write_nphy(param_1,9,4,bVar20 + 0x20,8,(long)&local_58 + 4);
        }
      }
    }
    if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) != 0xa8e5) {
      lVar13 = *(long *)(param_1 + 0xf58);
      if (0x12 < *(uint *)(param_1 + 0x164)) goto LAB_0024de34;
      goto LAB_0024dca9;
    }
    *(undefined1 *)(*(long *)(param_1 + 0xf58) + 1) = 9;
    break;
  case '\t':
    if ((*(byte *)(param_1 + 0xf86) & 2) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    if (((*(char *)(param_1 + 0xf60) != '\0') && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)) ||
       ((*(char *)(param_1 + 0xf61) != '\0' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000)))
       ) {
      FUN_0024b7c3(param_1,1,1,1);
    }
    lVar13 = *(long *)(param_1 + 0xf58);
LAB_0024dca9:
    *(undefined1 *)(lVar13 + 1) = 10;
    break;
  case '\n':
    if ((*(byte *)(param_1 + 0xf86) & 1) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa8e5) {
      if ((*(char *)(param_1 + 0xf84) != '\0') || (uVar11 = 0, *(char *)(lVar6 + 0x382) == '\x01'))
      {
        uVar11 = 2;
      }
      puVar16 = local_88;
      puVar17 = auStack_e8;
      for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
        *puVar17 = *puVar16;
        puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
        puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
      }
      iVar10 = wlc_phy_cal_rxiq_nphy(param_1,uVar11,0,1);
      if (iVar10 == 0) {
        FUN_0022c733(param_1);
      }
      *(undefined1 *)(*(long *)(param_1 + 0xf58) + 1) = 0xb;
    }
    else {
      if ((*(char *)(param_1 + 0xf84) != '\0') || (uVar11 = 0, *(char *)(lVar6 + 0x382) == '\x01'))
      {
        uVar11 = 2;
      }
      puVar16 = local_88;
      puVar17 = auStack_e8;
      for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
        *puVar17 = *puVar16;
        puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
        puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
      }
      iVar10 = wlc_phy_cal_rxiq_nphy(param_1,uVar11,0,3);
      if (iVar10 == 0) {
        FUN_0022c733(param_1);
      }
      if (*(uint *)(param_1 + 0x164) < 0x13) goto LAB_0024de2d;
      if ((*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324) &&
         (((iVar10 = *(int *)(*(long *)(param_1 + 0x20) + 0x40), iVar10 == 5 || (iVar10 == 2)) &&
          (*(char *)(lVar6 + 0x119) != '\0')))) {
        wlc_phy_dynamic_rflo_ucode_war_nphy(param_1,4);
        *(undefined1 *)(*(long *)(param_1 + 0xf58) + 1) = 2;
        *(undefined1 *)(lVar6 + 0x132) = 1;
      }
      else {
        lVar13 = *(long *)(param_1 + 0xf58);
LAB_0024ddc6:
        *(undefined1 *)(lVar13 + 1) = 8;
        *(undefined1 *)(lVar6 + 0x132) = 0;
      }
    }
    break;
  case '\v':
    if ((*(byte *)(param_1 + 0xf86) & 1) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    if ((*(char *)(param_1 + 0xf84) != '\0') || (uVar11 = 0, *(char *)(lVar6 + 0x382) == '\x01')) {
      uVar11 = 2;
    }
    puVar16 = local_88;
    puVar17 = auStack_e8;
    for (lVar13 = 5; lVar13 != 0; lVar13 = lVar13 + -1) {
      *puVar17 = *puVar16;
      puVar16 = puVar16 + (ulong)bVar20 * -2 + 1;
      puVar17 = puVar17 + (ulong)bVar20 * -2 + 1;
    }
    iVar10 = wlc_phy_cal_rxiq_nphy(param_1,uVar11,0,2);
    if (iVar10 == 0) {
      FUN_0022c733(param_1);
    }
LAB_0024de2d:
    lVar13 = *(long *)(param_1 + 0xf58);
LAB_0024de34:
    *(undefined1 *)(lVar13 + 1) = 0xc;
    break;
  case '\f':
    if ((*(byte *)(param_1 + 0xf86) & 4) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    FUN_0022cb4a(param_1);
    wlc_phy_rssi_cal_nphy(param_1);
    if (*(uint *)(param_1 + 0x164) < 0x13) {
      if (2 < *(uint *)(param_1 + 0x164)) {
        wlc_phy_radio205x_vcocal_nphy(param_1);
      }
    }
    else {
      wlc_20671_vco_cal(param_1,1);
    }
    if (*(char *)(param_1 + 0xf84) == '\0') {
      if ((*(uint *)(param_1 + 0x164) < 0x13) && (*(uint *)(param_1 + 0x164) != 0x10)) {
        wlc_phy_cal_perical_mphase_reset(param_1);
      }
      else {
        *(undefined1 *)(*(long *)(param_1 + 0xf58) + 1) = 0xe;
        if (((*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324) &&
            ((iVar10 = *(int *)(*(long *)(param_1 + 0x20) + 0x40), iVar10 == 5 || (iVar10 == 2))))
           && (*(char *)(lVar6 + 0x119) != '\0')) {
          wlc_phy_dynamic_rflo_ucode_war_nphy(param_1,5);
        }
      }
    }
    else {
      pcVar1 = (char *)(*(long *)(param_1 + 0xf58) + 1);
      *pcVar1 = *pcVar1 + '\x01';
    }
    bVar7 = true;
    goto LAB_0024df81;
  case '\r':
    if ((*(byte *)(param_1 + 0xf86) & 8) != 0) {
      *(undefined1 *)(lVar6 + 0x18d) = 1;
    }
    if (*(char *)(param_1 + 0xf84) != '\0') {
      *(undefined1 *)(param_1 + 0xf84) = 0;
      FUN_00241f59(param_1);
      FUN_0021ed75(param_1);
    }
    uVar12 = *(uint *)(param_1 + 0x164);
    if (((uVar12 != 0x12) && (uVar12 != 0x10)) && (uVar12 < 0x13)) goto switchD_0024d83f_default;
LAB_0024df4d:
    pcVar1 = (char *)(*(long *)(param_1 + 0xf58) + 1);
    *pcVar1 = *pcVar1 + '\x01';
    break;
  case '\x0e':
    if ((0x11 < *(uint *)(param_1 + 0x164)) || (*(uint *)(param_1 + 0x164) == 0x10)) {
      FUN_002353de(param_1);
    }
  default:
switchD_0024d83f_default:
    wlc_phy_cal_perical_mphase_reset(param_1);
  }
  bVar7 = false;
LAB_0024df81:
  if ((2 < *(uint *)(param_1 + 0x164)) && (bVar7)) {
    if (local_b5 == '\0') {
      wlc_phy_txpwr_index_nphy(param_1,1,(int)*(char *)(lVar6 + 0x217),0);
      wlc_phy_txpwr_index_nphy(param_1,2,(int)*(char *)(lVar6 + 0x229),0);
    }
    else {
      wlc_phy_txpwr_index_nphy(param_1,1,(int)*(char *)(lVar6 + 0x1c7),0);
      wlc_phy_txpwr_index_nphy(param_1,2,(int)*(char *)(lVar6 + 0x1c8),0);
      *(undefined1 *)(lVar6 + 0x216) = 0xff;
      *(undefined1 *)(lVar6 + 0x228) = 0xff;
    }
  }
  if ((0x11 < *(uint *)(param_1 + 0x164)) && (local_ae != 0)) {
    wlc_phy_ocl_enable_disable_nphy(param_1,1);
  }
  if (0x12 < *(uint *)(param_1 + 0x164)) {
    wlc_phy_lcnxn_disable_stalls(param_1,0);
  }
  if ((*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324) &&
     (*(int *)(*(long *)(param_1 + 0x20) + 0x40) - 3U < 2)) {
    FUN_0021583b(param_1,0);
  }
  wlc_phy_txpwrctrl_enable_nphy(param_1,local_b5);
  wlc_phyreg_exit(param_1);
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa8dc) {
    wlapi_bmac_mhf(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0,2,0,2);
  }
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return;
}

