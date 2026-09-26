
void FUN_001a581c(long param_1,long param_2,long param_3,long param_4,long param_5)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  char *pcVar4;
  byte bVar5;
  byte bVar6;
  undefined2 uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  byte *pbVar11;
  byte bVar12;
  short sVar13;
  undefined8 uVar14;
  byte *pbVar15;
  byte *pbVar16;
  byte *pbVar17;
  uint uVar18;
  undefined1 *puVar19;
  undefined2 *puVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  long lVar24;
  bool bVar25;
  byte local_9a;
  uint local_78;
  uint local_74;
  uint local_68 [4];
  byte local_58 [16];
  byte local_48 [12];
  ushort local_3c;
  undefined1 local_3a [10];
  
  uVar8 = *(ushort *)(param_1 + 0x17e);
  pcVar4 = *(char **)(param_1 + 0x138);
  if ((byte)uVar8 < 0xf) {
    sVar13 = (uVar8 & 0xff) * 5 + 0x967;
  }
  else {
    sVar13 = (uVar8 & 0xff) + (uVar8 & 0xff) * 4 + 5000;
  }
  iVar21 = 0;
  if ((uVar8 & 0x3800) != 0x1000) {
    iVar21 = ((uVar8 & 0x3800) != 0x1800) + 1;
  }
  if (*(uint *)(param_1 + 0x164) < 2) {
    phy_reg_mod(param_1,0x410,8,0);
    phy_reg_mod(param_1,0x410,0x380,0);
    *(undefined1 *)(param_1 + 0x116a) = 0;
    for (bVar6 = 0; bVar6 < *(byte *)(param_1 + 0x168); bVar6 = bVar6 + 1) {
      uVar14 = 0x73a;
      if ((bVar6 != 0) && (uVar14 = 0xb3a, bVar6 == 1)) {
        uVar14 = 0x93a;
      }
      phy_reg_mod(param_1,uVar14,8,0);
      uVar14 = 0x725;
      if ((bVar6 != 0) && (uVar14 = 0xb25, bVar6 == 1)) {
        uVar14 = 0x925;
      }
      phy_reg_mod(param_1,uVar14,0x40,0);
      uVar14 = 0x73a;
      if ((bVar6 != 0) && (uVar14 = 0xb3a, bVar6 == 1)) {
        uVar14 = 0x93a;
      }
      phy_reg_mod(param_1,uVar14,0x10,0);
      uVar14 = 0x725;
      if ((bVar6 != 0) && (uVar14 = 0xb25, bVar6 == 1)) {
        uVar14 = 0x925;
      }
      phy_reg_mod(param_1,uVar14,0x80,0);
      uVar14 = 0x73a;
      if ((bVar6 != 0) && (uVar14 = 0xb3a, bVar6 == 1)) {
        uVar14 = 0x93a;
      }
      phy_reg_mod(param_1,uVar14,7,0);
      uVar14 = 0x725;
      if ((bVar6 != 0) && (uVar14 = 0xb25, bVar6 == 1)) {
        uVar14 = 0x925;
      }
      phy_reg_mod(param_1,uVar14,0x20,0);
    }
  }
  iVar22 = 0;
  lVar24 = (long)iVar21 * 0x5c4;
  pbVar16 = rx_farrow_tbl_40_rev3 + lVar24;
  pbVar15 = rx_farrow_tbl_rev3 + lVar24;
  pbVar11 = rx_farrow_tbl + lVar24;
  while( true ) {
    pbVar17 = pbVar11;
    if ((*(int *)(param_1 + 0x164) == 3) &&
       (pbVar17 = pbVar16, *(int *)(param_1 + 0xc24) != 40000000)) {
      pbVar17 = pbVar15;
    }
    if ((ushort)*pbVar17 == (uVar8 & 0xff)) break;
    iVar22 = iVar22 + 1;
    pbVar16 = pbVar16 + 0xc;
    pbVar15 = pbVar15 + 0xc;
    pbVar11 = pbVar11 + 0xc;
    if (iVar22 == 0x7b) goto LAB_001a6141;
  }
  uVar7 = *(undefined2 *)(pbVar17 + 10);
  uVar1 = *(undefined2 *)(pbVar17 + 8);
  uVar2 = *(undefined2 *)(pbVar17 + 6);
  uVar3 = *(undefined2 *)(pbVar17 + 4);
  phy_reg_write(param_1,0x19a,uVar3);
  phy_reg_write(param_1,0x19b,uVar2);
  phy_reg_write(param_1,0x19c,uVar1);
  phy_reg_write(param_1,0x199,uVar7);
  phy_reg_write(param_1,0x1a1,uVar3);
  phy_reg_write(param_1,0x1a2,uVar2);
  phy_reg_write(param_1,0x1a3,uVar1);
  phy_reg_write(param_1,0x1a0,uVar7);
  if (*pcVar4 == '\x02') {
    puVar19 = tx_farrow_dac2_tbl + (long)iVar22 * 0xc + lVar24;
  }
  else if (*pcVar4 == '\x03') {
    puVar19 = tx_farrow_dac3_tbl + (long)iVar22 * 0xc + lVar24;
  }
  else if (*(int *)(param_1 + 0x164) == 3) {
    if (*(int *)(param_1 + 0xc24) == 40000000) {
      puVar19 = tx_farrow_dac1_tbl_40_rev3 + (long)iVar22 * 0xc + lVar24;
    }
    else {
      puVar19 = tx_farrow_dac1_tbl_rev3 + (long)iVar22 * 0xc + lVar24;
    }
  }
  else {
    puVar19 = tx_farrow_dac1_tbl + (long)iVar22 * 0xc + lVar24;
  }
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar14 = 0x603, acphychipid == 0x4350)))) {
    uVar14 = 0x1603;
  }
  phy_reg_write(param_1,uVar14,*(undefined2 *)(puVar19 + 4));
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar14 = 0x602, acphychipid == 0x4350)))
      ))) {
    uVar14 = 0x1602;
  }
  phy_reg_write(param_1,uVar14,*(undefined2 *)(puVar19 + 6));
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar14 = 0x607, acphychipid == 0x4350)))) {
    uVar14 = 0x1607;
  }
  phy_reg_write(param_1,uVar14,*(undefined2 *)(puVar19 + 8));
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar14 = 0x606, acphychipid == 0x4350)))
      ))) {
    uVar14 = 0x1606;
  }
  phy_reg_write(param_1,uVar14,*(undefined2 *)(puVar19 + 10));
  if (((1 < *(uint *)(param_1 + 0x164)) || (*(char *)(param_1 + 0x1169) == '\0')) ||
     ((*(ushort *)(param_1 + 0x17e) & 0x3800) != 0x1800)) goto LAB_001a60f1;
  if (sVar13 == 0x14be) {
    phy_reg_mod(param_1,0x410,8,8);
    phy_reg_mod(param_1,0x410,0x380,0);
    for (bVar6 = 0; bVar6 < *(byte *)(param_1 + 0x168); bVar6 = bVar6 + 1) {
      uVar14 = 0x73a;
      if ((bVar6 != 0) && (uVar14 = 0xb3a, bVar6 == 1)) {
        uVar14 = 0x93a;
      }
      phy_reg_mod(param_1,uVar14,8,8);
      uVar14 = 0x725;
      if ((bVar6 != 0) && (uVar14 = 0xb25, bVar6 == 1)) {
        uVar14 = 0x925;
      }
      phy_reg_mod(param_1,uVar14,0x40,0x40);
      uVar14 = 0x73a;
      if ((bVar6 != 0) && (uVar14 = 0xb3a, bVar6 == 1)) {
        uVar14 = 0x93a;
      }
      phy_reg_mod(param_1,uVar14,0x10,0);
      uVar14 = 0x725;
      if ((bVar6 != 0) && (uVar14 = 0xb25, bVar6 == 1)) {
        uVar14 = 0x925;
      }
      phy_reg_mod(param_1,uVar14,0x80,0x80);
      uVar14 = 0x73a;
      if ((bVar6 != 0) && (uVar14 = 0xb3a, bVar6 == 1)) {
        uVar14 = 0x93a;
      }
      phy_reg_mod(param_1,uVar14,7,1);
      uVar14 = 0x725;
      if ((bVar6 != 0) && (uVar14 = 0xb25, bVar6 == 1)) {
        uVar14 = 0x925;
      }
      phy_reg_mod(param_1,uVar14,0x20,0x20);
    }
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar18 = 0x145;
      uVar23 = 0;
    }
    else {
      uVar18 = 0x157;
      uVar23 = 0x800;
    }
    mod_radio_reg(param_1,uVar23 | uVar18,0xf,8);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar18 = 0x146;
      uVar23 = 0;
    }
    else {
      uVar18 = 0x158;
      uVar23 = 0x800;
    }
    mod_radio_reg(param_1,uVar23 | uVar18,0x1e0,0x100);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar18 = 0x146;
      uVar23 = 0;
    }
    else {
      uVar18 = 0x158;
      uVar23 = 0x800;
    }
    puVar20 = &DAT_006767a0;
    mod_radio_reg(param_1,uVar23 | uVar18,0xf,8);
    *(undefined1 *)(param_1 + 0x116a) = 1;
  }
  else {
    if (sVar13 != 0x1496) goto LAB_001a60f1;
    puVar20 = &DAT_00676780;
    phy_reg_mod(param_1,0x410,8,8);
    phy_reg_mod(param_1,0x410,0x380,0x100);
  }
  phy_reg_write(param_1,0x19a,*puVar20);
  phy_reg_write(param_1,0x19b,puVar20[1]);
  phy_reg_write(param_1,0x19c,puVar20[2]);
  phy_reg_write(param_1,0x1a1,puVar20[3]);
  phy_reg_write(param_1,0x1a2,puVar20[4]);
  phy_reg_write(param_1,0x1a3,puVar20[5]);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar14 = 0x603, acphychipid == 0x4350)))) {
    uVar14 = 0x1603;
  }
  phy_reg_write(param_1,uVar14,puVar20[6]);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar14 = 0x602, acphychipid == 0x4350)))
      ))) {
    uVar14 = 0x1602;
  }
  phy_reg_write(param_1,uVar14,puVar20[7]);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar14 = 0x607, acphychipid == 0x4350)))) {
    uVar14 = 0x1607;
  }
  phy_reg_write(param_1,uVar14,puVar20[8]);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar14 = 0x606, acphychipid == 0x4350)))
      ))) {
    uVar14 = 0x1606;
  }
  phy_reg_write(param_1,uVar14,puVar20[9]);
LAB_001a60f1:
  uVar7 = phy_reg_read(param_1,0x601);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar14 = 0x601, acphychipid == 0x4350)))) {
    uVar14 = 0x1601;
  }
  phy_reg_write(param_1,uVar14,uVar7);
LAB_001a6141:
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    bVar6 = *(byte *)(*(long *)(param_1 + 0x138) + 0x410);
  }
  else {
    bVar6 = *(byte *)(*(long *)(param_1 + 0x138) + 0x411);
  }
  bVar5 = wlc_phy_get_chan_freq_range_acphy(param_1,0);
  bVar12 = 0;
  if (bVar5 < 5) {
    bVar12 = (&DAT_00559fc0)[bVar5];
  }
  local_48[0] = 0;
  local_48[1] = 0;
  local_48[2] = 0;
  local_58[0] = 0;
  lVar24 = (ulong)bVar12 + (ulong)bVar6 * 5;
  local_58[1] = 0;
  local_58[2] = 0;
  bVar5 = *(byte *)(param_1 + 0x168);
  pbVar16 = local_48;
  pbVar15 = local_58;
  pbVar17 = &DAT_00559980 + (ulong)bVar6 * 0x1e + (ulong)bVar12 * 6;
  pbVar11 = &DAT_00559c80 + lVar24 * 4;
  for (bVar6 = 0; bVar6 < bVar5; bVar6 = bVar6 + 1) {
    uVar18 = *(uint *)(param_1 + 0x164);
    if (uVar18 < 2) {
      *pbVar16 = *pbVar17;
      bVar12 = pbVar17[3];
LAB_001a621b:
      *pbVar15 = bVar12;
    }
    else if (((uVar18 == 5) || (uVar18 == 2)) || (uVar18 == 6)) {
      if (bVar6 == 0) {
        local_48[0] = (&DAT_00559be0)[lVar24 * 2];
        local_58[0] = (&DAT_00559be1)[lVar24 * 2];
      }
    }
    else if (uVar18 == 3) {
      *pbVar16 = *pbVar11;
      bVar12 = pbVar11[2];
      goto LAB_001a621b;
    }
    pbVar17 = pbVar17 + 1;
    pbVar16 = pbVar16 + 1;
    pbVar15 = pbVar15 + 1;
    pbVar11 = pbVar11 + 1;
  }
  uVar8 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  for (uVar18 = 0; (byte)uVar18 < *(byte *)(param_1 + 0x168); uVar18 = uVar18 + 1) {
    if (((*(byte *)(*(long *)(param_1 + 0x20) + 0xa5) >> (uVar18 & 0x1f) & 1) != 0) &&
       (((((iVar21 = *(int *)(param_1 + 0x164), iVar21 == 5 || (iVar21 == 2)) || (iVar21 == 6)) &&
         ((byte)uVar18 == 0)) || (((iVar21 != 5 && (iVar21 != 2)) && (iVar21 != 6)))))) {
      iVar22 = (uVar18 & 0xff) * 0x10;
      iVar21 = iVar22 + 0x3cd;
      wlc_phy_table_read_acphy(param_1,7,1,(short)iVar21,0x10,local_3a);
      local_3c = local_48[(int)(uVar18 & 0xff)] & 7 | (ushort)local_58[(int)(uVar18 & 0xff)] << 3;
      wlc_phy_table_write_acphy(param_1,7,1,iVar21,0x10,&local_3c);
      iVar21 = *(int *)(param_1 + 0x164);
      if ((((iVar21 == 5) || (iVar21 == 2)) || ((iVar21 == 6 || (iVar21 == 3)))) &&
         (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
        wlc_phy_table_write_acphy(param_1,7,1,(short)iVar22 + 0x3ce,0x10,&local_3c);
      }
    }
  }
  phy_reg_mod(param_1,0x19e,2,uVar8 & 2);
  iVar21 = *(int *)(param_1 + 0x164);
  if (iVar21 == 3) {
    sVar13 = *(short *)(param_5 + 2);
  }
  else if (((iVar21 == 5) || (iVar21 == 2)) || (iVar21 == 6)) {
    if ((byte)(*(char *)(param_1 + 0x16c) - 0x19U) < 2) {
      sVar13 = *(short *)(param_4 + 2);
    }
    else {
      sVar13 = *(short *)(param_3 + 2);
    }
  }
  else {
    sVar13 = *(short *)(param_2 + 2);
  }
  if (*(char *)(param_1 + 0x16e) == '\x02') {
    bVar6 = osl_readl(*(long *)(param_1 + 0x148) + 0x120);
    local_9a = (bVar6 ^ 1) & 1;
    if (((bVar6 ^ 1) & 1) == 0) {
      wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    }
    uVar9 = phy_reg_read(param_1,0x19e);
    uVar10 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    phy_reg_mod(param_1,0x19e,1,1);
    uVar8 = *(ushort *)(param_1 + 0x17e);
    if ((uVar8 & 0x3800) == 0x1000) {
      if ((uVar8 & 0xc000) == 0) {
        if (sVar13 != 0x9a3) goto LAB_001a64e0;
        bVar25 = *(int *)(param_1 + 0xc24) == 40000000;
LAB_001a64de:
        if (bVar25) goto LAB_001a64e0;
        wlc_phy_table_read_acphy(param_1,8,1,6,0x3c,local_68);
        uVar18 = local_68[0];
        wlc_phy_table_read_acphy(param_1,8,1,0,0x3c,local_68);
        uVar18 = uVar18 & 0xe3fff | 0xc000;
        uVar23 = local_68[0] & 0xe3fff | 0xc000;
      }
      else {
        if (sVar13 != 0x1685) {
          bVar25 = sVar13 == 0x1671;
          goto LAB_001a64de;
        }
LAB_001a64e0:
        wlc_phy_table_read_acphy(param_1,8,1,6,0x3c,local_68);
        uVar18 = local_68[0];
        wlc_phy_table_read_acphy(param_1,8,1,0,0x3c,local_68);
        uVar18 = uVar18 & 0xe3fff | 0x10000;
        uVar23 = local_68[0] & 0xe3fff | 0x10000;
      }
      local_78 = uVar18 << 0x14 | uVar18;
      local_74 = uVar18 >> 0xc | uVar18 << 8;
      wlc_phy_table_write_acphy(param_1,8,1,6,0x3c,&local_78);
      uVar14 = 0;
      local_78 = uVar23 << 0x14 | uVar23;
      local_74 = uVar23 >> 0xc | uVar23 << 8;
LAB_001a6776:
      wlc_phy_table_write_acphy(param_1,8,1,uVar14,0x3c,&local_78);
      wlc_phy_force_rfseq_acphy(param_1,0);
      wlc_phy_force_rfseq_acphy(param_1,1);
    }
    else if ((uVar8 & 0x3800) == 0x1800) {
      if (((sVar13 == 0x167b) || ((uVar8 & 0xc000) == 0)) || (sVar13 == 0x15ae)) {
        wlc_phy_table_read_acphy(param_1,8,1,7,0x3c,local_68);
        uVar18 = local_68[0];
        wlc_phy_table_read_acphy(param_1,8,1,1,0x3c,local_68);
        uVar18 = uVar18 & 0xe3fff | 0x8000;
        uVar23 = local_68[0] & 0xe3fff | 0x8000;
      }
      else {
        wlc_phy_table_read_acphy(param_1,8,1,7,0x3c,local_68);
        uVar18 = local_68[0];
        wlc_phy_table_read_acphy(param_1,8,1,1,0x3c,local_68);
        uVar18 = uVar18 & 0xe3fff | 0x4000;
        uVar23 = local_68[0] & 0xe3fff | 0x4000;
      }
      local_78 = uVar18 << 0x14 | uVar18;
      local_74 = uVar18 >> 0xc | uVar18 << 8;
      wlc_phy_table_write_acphy(param_1,8,1,7,0x3c,&local_78);
      uVar14 = 1;
      local_78 = uVar23 << 0x14 | uVar23;
      local_74 = uVar23 >> 0xc | uVar23 << 8;
      goto LAB_001a6776;
    }
    if (local_9a == 0) {
      wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    }
    phy_reg_mod(param_1,0x19e,2,uVar9 & 2);
    phy_reg_mod(param_1,0x19e,1,uVar10 & 1);
  }
  iVar21 = *(int *)(param_1 + 0x164);
  if (iVar21 == 3) {
    phy_reg_write(param_1,0x371,*(undefined2 *)(param_5 + 0x52));
    phy_reg_write(param_1,0x372,*(undefined2 *)(param_5 + 0x54));
    phy_reg_write(param_1,0x373,*(undefined2 *)(param_5 + 0x56));
    phy_reg_write(param_1,0x374,*(undefined2 *)(param_5 + 0x58));
    phy_reg_write(param_1,0x375,*(undefined2 *)(param_5 + 0x5a));
    uVar7 = *(undefined2 *)(param_5 + 0x5c);
  }
  else if (((iVar21 == 5) || (iVar21 == 2)) || (iVar21 == 6)) {
    if ((byte)(*(char *)(param_1 + 0x16c) - 0x19U) < 2) {
      phy_reg_write(param_1,0x371,*(undefined2 *)(param_4 + 0x54));
      phy_reg_write(param_1,0x372,*(undefined2 *)(param_4 + 0x56));
      phy_reg_write(param_1,0x373,*(undefined2 *)(param_4 + 0x58));
      phy_reg_write(param_1,0x374,*(undefined2 *)(param_4 + 0x5a));
      phy_reg_write(param_1,0x375,*(undefined2 *)(param_4 + 0x5c));
      uVar7 = *(undefined2 *)(param_4 + 0x5e);
    }
    else {
      phy_reg_write(param_1,0x371,*(undefined2 *)(param_3 + 0x52));
      phy_reg_write(param_1,0x372,*(undefined2 *)(param_3 + 0x54));
      phy_reg_write(param_1,0x373,*(undefined2 *)(param_3 + 0x56));
      phy_reg_write(param_1,0x374,*(undefined2 *)(param_3 + 0x58));
      phy_reg_write(param_1,0x375,*(undefined2 *)(param_3 + 0x5a));
      uVar7 = *(undefined2 *)(param_3 + 0x5c);
    }
  }
  else {
    phy_reg_write(param_1,0x371,*(undefined2 *)(param_2 + 0x68));
    phy_reg_write(param_1,0x372,*(undefined2 *)(param_2 + 0x6a));
    phy_reg_write(param_1,0x373,*(undefined2 *)(param_2 + 0x6c));
    phy_reg_write(param_1,0x374,*(undefined2 *)(param_2 + 0x6e));
    phy_reg_write(param_1,0x375,*(undefined2 *)(param_2 + 0x70));
    uVar7 = *(undefined2 *)(param_2 + 0x72);
  }
  phy_reg_write(param_1,0x376,uVar7);
  uVar8 = *(ushort *)(param_1 + 0x17e);
  uVar9 = uVar8 & 0x3800;
  if (uVar9 == 0x2000) {
    uVar9 = uVar8 & 0x700;
    if ((uVar8 & 0x700) == 0) {
      uVar14 = 0;
    }
    else if (uVar9 == 0x100) {
LAB_001a6a6e:
      uVar14 = 0x4000;
    }
    else {
      uVar14 = 0x8000;
      if ((uVar9 != 0x200) && (uVar14 = 0xc000, uVar9 != 0x300)) goto LAB_001a6aad;
    }
LAB_001a6aa0:
    phy_reg_mod(param_1,0x30f,0xc000,uVar14);
  }
  else {
    if (uVar9 == 0x1800) {
      if ((uVar8 & 0x3f00) == 0x1900) {
        phy_reg_mod(param_1,0x164,0x10,0x10);
        goto LAB_001a6a6e;
      }
LAB_001a6a8c:
      phy_reg_mod(param_1,0x164,0x10,0);
      uVar14 = 0;
      goto LAB_001a6aa0;
    }
    if (uVar9 == 0x1000) goto LAB_001a6a8c;
  }
LAB_001a6aad:
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
    if (((*(ushort *)(param_1 + 0x17e) & 0x3800) != 0x2000) ||
       (uVar7 = 0x100, 1 < *(uint *)(param_1 + 0x164))) {
      uVar7 = 0xbf;
    }
  }
  else {
    iVar21 = *(int *)(param_1 + 0x164);
    if ((((iVar21 == 5) || (iVar21 == 2)) || (iVar21 == 6)) || (uVar7 = 0xff, iVar21 == 3)) {
      uVar7 = 0x80;
    }
  }
  phy_reg_write(param_1,0x31c,uVar7);
  phy_reg_write(param_1,0x31d,uVar7);
  phy_reg_write(param_1,0x31e,uVar7);
  phy_reg_write(param_1,799,uVar7);
  osl_memset(*(long *)(param_1 + 0x138) + 0x14,0,4);
  osl_memset(*(long *)(param_1 + 0x138) + 0x3d,0,4);
  osl_memset(*(long *)(param_1 + 0x138) + 0x2c,0,0x10);
  *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x43) = 0;
  *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x3c) = 0;
  wlc_phy_crs_min_pwr_cal_acphy(param_1,1);
  uVar18 = *(uint *)(param_1 + 0x164);
  if (((uVar18 == 5) || (uVar18 == 2)) || ((uVar18 == 6 || ((uVar18 == 3 || (uVar18 < 2)))))) {
    if (sVar13 == 0x9b4) {
      uVar18 = phy_reg_read(param_1,0x3a9);
      phy_reg_mod(param_1,0x3a9,0x7f,uVar18 & 0x3f);
      phy_reg_mod(param_1,0x3a9,0x800,0x800);
      bVar6 = 0;
    }
    else {
      if (uVar18 == 3) {
        phy_reg_mod(param_1,0x3a9,0x800,0);
        goto LAB_001a6cc4;
      }
      uVar18 = phy_reg_read(param_1,0x3a9);
      phy_reg_mod(param_1,0x3a9,0x7f,
                  uVar18 & 0x3f | (*(byte *)(*(long *)(param_1 + 0x138) + 0x8fe) & 2) << 5);
      phy_reg_mod(param_1,0x3a9,0x800,
                  ((int)(*(byte *)(*(long *)(param_1 + 0x138) + 0x8fe) & 4) >> 2) << 0xb);
      bVar6 = *(byte *)(*(long *)(param_1 + 0x138) + 0x8fe) & 1;
    }
    FUN_001a55a7(param_1,bVar6);
  }
LAB_001a6cc4:
  if ((*(uint *)(param_1 + 0x164) == 3) || (*(uint *)(param_1 + 0x164) < 2)) {
    wlc_phy_populate_recipcoeffs_acphy(param_1);
  }
  return;
}

