
undefined4 *
wlc_phy_cal_txgainctrl_inttssi_nphy(undefined4 *param_1,long param_2,char param_3,char param_4)

{
  char cVar1;
  char cVar2;
  ushort uVar3;
  char cVar4;
  char cVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined4 uVar9;
  uint uVar10;
  long lVar11;
  undefined1 *puVar12;
  undefined8 uVar13;
  long lVar14;
  char cVar15;
  int iVar16;
  uint uVar17;
  undefined8 uVar18;
  undefined4 *puVar19;
  short *psVar20;
  short *psVar21;
  undefined1 *puVar22;
  undefined1 uVar23;
  byte bVar24;
  char cVar25;
  uint uVar26;
  ulong uVar27;
  byte bVar28;
  char local_103;
  undefined2 local_102;
  int local_cc;
  undefined4 local_c8 [8];
  short local_a8 [16];
  int local_88 [2];
  int local_80;
  undefined1 local_78;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 local_72;
  undefined1 local_71;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_6e;
  undefined1 local_6d;
  undefined1 local_6c;
  undefined1 local_6b;
  undefined1 local_6a;
  undefined1 local_69;
  undefined1 local_68 [16];
  undefined1 local_58 [2];
  undefined1 local_56 [14];
  undefined1 local_48 [2];
  undefined1 local_46 [6];
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  ushort local_3a [5];
  
  bVar28 = 0;
  uVar23 = 5;
  puVar12 = &DAT_00565d10;
  puVar22 = local_68;
  for (lVar11 = 0xd; lVar11 != 0; lVar11 = lVar11 + -1) {
    *puVar22 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar22 = puVar22 + 1;
  }
  local_78 = 0;
  local_77 = 1;
  uVar3 = *(ushort *)(param_2 + 0x17e);
  local_76 = 2;
  local_75 = 3;
  local_74 = 4;
  local_73 = 5;
  local_72 = 6;
  local_71 = 7;
  local_70 = 8;
  local_6f = 9;
  local_6e = 10;
  local_6d = 0xb;
  local_6c = 0xc;
  uVar9 = 5000;
  if ((uVar3 & 0x3800) != 0x1800) {
    uVar9 = 0x9c4;
  }
  local_6b = 0xd;
  local_6a = 0xe;
  local_69 = 0xf;
  lVar11 = *(long *)(param_2 + 0x138);
  if ((uVar3 & 0xc000) == 0xc000) {
LAB_00242882:
    puVar12 = &local_78;
    iVar16 = 0x10;
  }
  else {
    if ((uVar3 & 0xc000) != 0) {
      uVar23 = 4;
      goto LAB_00242882;
    }
    uVar23 = 4;
    iVar16 = (int)CONCAT71((uint7)(uint3)((uVar3 & 0xc000) >> 8),0xd);
    puVar12 = local_68;
  }
  if (iVar16 + -1 < (int)param_4) {
    param_4 = (char)iVar16 + -1;
  }
  cVar15 = '\0';
  if (-1 < param_4) {
    cVar15 = param_4;
  }
  wlc_phy_table_read_nphy(param_2,8,1,0xb,0x10,local_58);
  wlc_phy_table_read_nphy(param_2,8,1,0xf,0x10,local_48);
  wlc_phy_table_read_nphy(param_2,8,1,0x1b,0x10,local_56);
  wlc_phy_table_read_nphy(param_2,8,1,0x1f,0x10,local_46);
  if (*(char *)(lVar11 + 0x14) != '\0') {
    wlc_phy_stay_in_carriersearch_nphy(param_2,1);
  }
  cVar1 = *(char *)(lVar11 + 0x14);
  *(undefined1 *)(lVar11 + 0x14) = 0;
  uVar6 = phy_reg_read(param_2,1);
  phy_reg_mod(param_2,1,0x8000,0);
  FUN_00214694(param_2,*(char *)(lVar11 + 0x269) == '\0');
  local_3c = 5;
  local_3e = 0x19e;
  local_40 = 0x19e;
  if (*(char *)(*(long *)(param_2 + 0x138) + 0x269) != '\0') goto LAB_00242b3d;
  if ((*(ushort *)(param_2 + 0x17e) & 0xc000) == 0) {
    bVar24 = *(byte *)(param_2 + 0x16c);
    if (*(char *)(param_2 + 0xf60) == '\0') {
      if (bVar24 == 5) {
        if (*(char *)(param_2 + 0x16d) == '\0') goto LAB_00242b3d;
      }
      else if (bVar24 < 7) goto LAB_00242b3d;
      local_3c = 5;
      local_3e = 0x19e;
      local_40 = 0x19e;
      goto LAB_00242b3d;
    }
    if (bVar24 == 5) {
      if (*(char *)(param_2 + 0x16d) == '\0') goto LAB_00242b3d;
    }
    else if ((bVar24 != 0xd) && (bVar24 != 0xe)) {
      if (bVar24 == 7) {
        if (*(char *)(param_2 + 0x16d) == '\0') goto LAB_00242b3d;
      }
      else {
        if (bVar24 == 9) {
          local_3c = 1;
          local_3e = 0x7c;
          local_40 = 0x7c;
          goto LAB_00242b3d;
        }
        if (bVar24 == 0xb) {
          local_3c = 0;
          local_3e = 0x92;
          local_40 = 0x92;
          goto LAB_00242b3d;
        }
        if (bVar24 != 0xc) goto LAB_00242b3d;
      }
      local_3c = 0;
      local_3e = 0x8c;
      local_40 = 0x90;
      goto LAB_00242b3d;
    }
    local_3c = 2;
    local_3e = 0x1a9;
    local_40 = 0x1a9;
    goto LAB_00242b3d;
  }
  cVar2 = *(char *)(param_2 + 0x16c);
  if (cVar2 == '\a') {
    if (*(char *)(param_2 + 0x16d) == '\0') goto LAB_00242b3d;
    if ((*(char *)(param_2 + 0xf61) == '\0') || ((*(ushort *)(param_2 + 0x17e) & 0xc000) != 0xc000))
    {
      local_3c = 3;
      local_3e = 0x50;
      local_40 = 0x50;
      goto LAB_00242b3d;
    }
  }
  else {
    if (cVar2 == '\t') {
      local_3c = 4;
      local_3e = 0x70;
      local_40 = 0x70;
      goto LAB_00242b3d;
    }
    if (cVar2 == '\v') {
      local_3c = 3;
      local_3e = 0x75;
      local_40 = 0x91;
      goto LAB_00242b3d;
    }
    if (cVar2 != '\f') goto LAB_00242b3d;
  }
  local_3c = 0;
  local_3e = 0x8b;
  local_40 = 0x8b;
LAB_00242b3d:
  wlc_phy_table_write_nphy(param_2,8,1,0xb,0x10,&local_3e);
  wlc_phy_table_write_nphy(param_2,8,1,0x1b,0x10,&local_40);
  wlc_phy_table_write_nphy(param_2,8,1,0xf,0x10,&local_3c);
  wlc_phy_table_write_nphy(param_2,8,1,0x1f,0x10,&local_3c);
  uVar7 = phy_reg_read(param_2,0x91);
  uVar8 = phy_reg_read(param_2,0x92);
  local_102 = 0;
  if (6 < *(uint *)(param_2 + 0x164)) {
    local_102 = phy_reg_read(param_2,0x2ff);
  }
  FUN_00217bf3(param_2,0,0,3);
  FUN_00217bf3(param_2,2,0,3);
  if (*(char *)(lVar11 + 0x269) == '\0') {
    wlc_phy_rfctrl_override_nphy_rev7(param_2,8,0,3,0,0);
  }
  if (*(uint *)(param_2 + 0x164) < 7) {
    FUN_00217bf3(param_2,1,2,1);
    uVar13 = 2;
    uVar18 = 8;
  }
  else {
    uVar13 = 7;
    uVar18 = 2;
  }
  FUN_00217bf3(param_2,1,uVar18,uVar13);
  wlc_phy_rfctrl_override_nphy_rev7(param_2,0x1000,0,3,0,0);
  wlc_phy_tx_tone_nphy(param_2,4000,0,0,0,0);
  osl_delay(0x14);
  wlc_phy_poll_rssi_nphy(param_2,uVar23,local_88,1);
  wlc_phy_stopplayback_nphy(param_2);
  wlc_phy_rfctrl_override_nphy_rev7(param_2,0x1000,0,3,1,0);
  cVar2 = (char)local_88[0];
  cVar4 = (char)local_80;
  wlc_phy_get_tx_gain_nphy(local_a8,param_2);
  if ((*(char *)(param_2 + 0x16c) != '\x05') || (bVar24 = 0x2d, *(byte *)(param_2 + 0x16d) < 2)) {
    bVar24 = 0x40;
  }
  FUN_0021e6b4(param_2,bVar24,bVar24);
  uVar26 = 0;
  *(ushort *)(lVar11 + 0x1e6) = CONCAT11(bVar24,bVar24);
  psVar21 = local_a8;
  do {
    if (*(byte *)(param_2 + 0x168) <= uVar26) {
      wlc_phy_rfctrl_override_nphy_rev7(param_2,0x1000,0,3,1,0);
      phy_reg_write(param_2,1,uVar6);
      phy_reg_write(param_2,0x91,uVar7);
      phy_reg_write(param_2,0x92,uVar8);
      if (6 < *(uint *)(param_2 + 0x164)) {
        phy_reg_write(param_2,0x2ff,local_102);
      }
      if (*(char *)(lVar11 + 0x269) == '\0') {
        wlc_phy_rfctrl_override_nphy_rev7(param_2,8,0,3,1,0);
      }
      bVar24 = 0;
      lVar14 = *(long *)(param_2 + 0x138);
      if (6 < *(uint *)(param_2 + 0x164)) {
        for (; bVar24 < *(byte *)(param_2 + 0x168); bVar24 = bVar24 + 1) {
          uVar27 = (ulong)bVar24;
          write_radio_reg(param_2,(-(uint)(bVar24 == 0) & 0xffffffe0) + 0x198,
                          *(undefined1 *)(lVar14 + 0x1bf + uVar27 * 4));
          write_radio_reg(param_2,(-(uint)(bVar24 == 0) & 0xffffffe0) + 0x199,
                          *(undefined1 *)(lVar14 + 0x1c0 + uVar27 * 4));
          write_radio_reg(param_2,(-(uint)(bVar24 == 0) & 0xffffffe0) + 0x19b,
                          *(undefined1 *)(lVar14 + 0x1c1 + uVar27 * 4));
          if (*(char *)(param_2 + 0x16c) != '\x05') {
            write_radio_reg(param_2,(-(uint)(bVar24 == 0) & 0xffffffe0) + 0x19a,
                            *(undefined1 *)(lVar14 + 0x1c2 + uVar27 * 4));
          }
        }
      }
      wlc_phy_table_write_nphy(param_2,8,1,0xb,0x10,local_58);
      wlc_phy_table_write_nphy(param_2,8,1,0xf,0x10,local_48);
      wlc_phy_table_write_nphy(param_2,8,1,0x1b,0x10,local_56);
      wlc_phy_table_write_nphy(param_2,8,1,0x1f,0x10,local_46);
      *(char *)(lVar11 + 0x14) = cVar1;
      if (cVar1 != '\0') {
        wlc_phy_stay_in_carriersearch_nphy(param_2,0);
      }
      psVar21 = local_a8;
      puVar19 = param_1;
      for (lVar11 = 5; lVar11 != 0; lVar11 = lVar11 + -1) {
        *puVar19 = *(undefined4 *)psVar21;
        psVar21 = psVar21 + ((ulong)bVar28 * -2 + 1) * 2;
        puVar19 = puVar19 + (ulong)bVar28 * -2 + 1;
      }
      return param_1;
    }
    wlc_phy_get_tx_gain_nphy(local_c8,param_2);
    wlc_phy_rfctrl_override_nphy_rev7(param_2,0x1000,0,3,1,0);
    local_103 = '\0';
    local_cc = 0;
    local_3a[0] = (ushort)bVar24 << 8;
    cVar25 = cVar15;
    if (uVar26 != 0) {
      local_3a[0] = (ushort)bVar24;
    }
LAB_00242e0e:
    wlc_phy_tx_tone_nphy(param_2,uVar9,0xfa,0,0,0);
    wlc_phy_table_write_nphy(param_2,0xf,1,0x57,0x10,local_3a);
    wlc_phy_table_write_nphy(param_2,0xf,1,0x5f);
    uVar3 = *(ushort *)(param_2 + 0x17e);
    if ((uVar3 & 0xc000) == 0) {
      psVar21[6] = (short)(char)puVar12[cVar25];
    }
    else {
      psVar21[4] = (short)(char)puVar12[cVar25];
      if (((uVar3 & 0xc000) == 0xc000) && (*(char *)(param_2 + 0xf61) == '\0')) {
        psVar21[6] = 0xf;
      }
    }
    wlc_phy_rfctrl_override_nphy_rev7
              (param_2,0x1000,
               *psVar21 << 0xf | psVar21[2] << 0xc | psVar21[8] | psVar21[4] << 8 | psVar21[6] << 3,
               3);
    osl_delay(0x32);
    wlc_phy_poll_rssi_nphy(param_2,uVar23,local_88,10);
    if (uVar26 == 0) {
      cVar5 = (char)(local_88[0] / 10) - cVar2;
    }
    else {
      cVar5 = (char)(local_80 / 10) - cVar4;
    }
    *(undefined4 *)(lVar11 + 0x154) = 0;
    wlc_phy_stopplayback_nphy(param_2);
    cVar5 = cVar5 - param_3;
    if (local_cc == 0) {
LAB_00242fbf:
      if (cVar5 < '\0') {
        cVar25 = cVar25 + '\x01';
      }
      else {
        cVar25 = cVar25 + -1;
      }
      psVar20 = local_a8;
      puVar19 = local_c8;
      for (lVar14 = 5; lVar14 != 0; lVar14 = lVar14 + -1) {
        *puVar19 = *(undefined4 *)psVar20;
        psVar20 = psVar20 + (ulong)bVar28 * -4 + 2;
        puVar19 = puVar19 + (ulong)bVar28 * -2 + 1;
      }
      if (((iVar16 + -1 < (int)cVar25) || (cVar25 < '\0')) ||
         (local_cc = local_cc + 1, local_103 = cVar5, local_cc == 5)) goto LAB_0024300a;
      goto LAB_00242e0e;
    }
    uVar10 = (uint)local_103;
    uVar17 = (uint)cVar5;
    if (0 < (int)(uVar17 * uVar10)) goto LAB_00242fbf;
    if ((int)((uVar10 ^ (int)uVar10 >> 0x1f) - ((int)uVar10 >> 0x1f)) <
        (int)((uVar17 ^ (int)uVar17 >> 0x1f) - ((int)uVar17 >> 0x1f))) {
      puVar19 = local_c8;
      psVar20 = local_a8;
      for (lVar14 = 5; lVar14 != 0; lVar14 = lVar14 + -1) {
        *(undefined4 *)psVar20 = *puVar19;
        puVar19 = puVar19 + (ulong)bVar28 * -2 + 1;
        psVar20 = psVar20 + (ulong)bVar28 * -4 + 2;
      }
    }
LAB_0024300a:
    uVar26 = uVar26 + 1;
    psVar21 = psVar21 + 1;
  } while( true );
}

