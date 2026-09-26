
void FUN_0019f839(long param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  ushort uVar5;
  ushort uVar6;
  char cVar7;
  undefined1 uVar8;
  int iVar9;
  undefined8 uVar10;
  long lVar11;
  undefined8 uVar12;
  undefined1 *puVar13;
  undefined *puVar14;
  uint uVar15;
  byte bVar16;
  undefined2 local_a8;
  undefined2 local_a6;
  undefined2 local_98;
  undefined2 local_96;
  undefined2 local_94;
  undefined2 local_88;
  undefined2 local_86;
  undefined2 local_84;
  undefined2 local_78;
  undefined2 local_76;
  undefined2 local_74;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  
  iVar1 = *(int *)(param_1 + 0x164);
  local_48 = 8;
  local_47 = 6;
  local_46 = 4;
  local_58 = 4;
  local_57 = 6;
  local_56 = 8;
  local_68 = 0;
  local_67 = 0;
  local_66 = 0;
  uVar5 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  cVar7 = '\x01';
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    cVar7 = (uVar6 != 0x1800) + '\x02';
  }
  phy_reg_mod(param_1,0x76,7,cVar7);
  uVar10 = 0x800;
  if ((*(ushort *)(param_1 + 0x17e) & 0x3800) != 0x1000) {
    uVar10 = 0;
  }
  phy_reg_mod(param_1,0x140,0x800,uVar10);
  uVar10 = 0x10;
  if ((*(ushort *)(param_1 + 0x17e) & 0x3800) != 0x1000) {
    uVar10 = 0;
  }
  phy_reg_mod(param_1,0x164,0x10,uVar10);
  uVar10 = 0x15;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 5, uVar6 == 0x1800)) {
    uVar10 = 0xb;
  }
  phy_reg_mod(param_1,0x180,0x1f,uVar10);
  uVar10 = 0x146;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x17a, uVar6 == 0x1800)) {
    uVar10 = 0x181;
  }
  phy_reg_mod(param_1,0x181,0x7ff,uVar10);
  uVar10 = 0x88;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x9e, uVar6 == 0x1800)) {
    uVar10 = 0x5a;
  }
  phy_reg_mod(param_1,0x182,0x7ff,uVar10);
  uVar10 = 0x146;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x17a, uVar6 == 0x1800)) {
    uVar10 = 0x181;
  }
  phy_reg_mod(param_1,0x183,0x7ff,uVar10);
  uVar10 = 0x76e;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x7ca, uVar6 == 0x1800)) {
    uVar10 = 0x793;
  }
  phy_reg_mod(param_1,0x184,0x7ff,uVar10);
  lVar11 = 0x1a8;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    lVar11 = (ulong)(uVar6 == 0x1800) * 5 + 0x1b2;
  }
  phy_reg_mod(param_1,0x185,0x7ff,lVar11);
  iVar9 = 0xa3;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    iVar9 = (uint)(uVar6 == 0x1800) * 4 + 0xbd;
  }
  phy_reg_mod(param_1,0x186,0x7ff,iVar9);
  uVar10 = 0xf4;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x114, uVar6 == 0x1800)) {
    uVar10 = 0x102;
  }
  phy_reg_mod(param_1,0x187,0x7ff,uVar10);
  iVar9 = 0xa3;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    iVar9 = (uint)(uVar6 == 0x1800) * 4 + 0xbd;
  }
  phy_reg_mod(param_1,0x188,0x7ff,iVar9);
  uVar10 = 0x684;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x6d6, uVar6 == 0x1800)) {
    uVar10 = 0x6c0;
  }
  phy_reg_mod(param_1,0x189,0x7ff,uVar10);
  uVar10 = 0xad;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0xa2, uVar6 == 0x1800)) {
    uVar10 = 0xa9;
  }
  phy_reg_mod(param_1,0x18a,0x7ff,uVar10);
  uVar10 = 0xe5;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x16c, uVar6 == 0x1800)) {
    uVar10 = 0x162;
  }
  phy_reg_mod(param_1,0x18b,0x7ff,uVar10);
  uVar10 = 0x68;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x6f, uVar6 == 0x1800)) {
    uVar10 = 0x42;
  }
  phy_reg_mod(param_1,0x18c,0x7ff,uVar10);
  uVar10 = 0xe5;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x16c, uVar6 == 0x1800)) {
    uVar10 = 0x162;
  }
  phy_reg_mod(param_1,0x18d,0x7ff,uVar10);
  uVar10 = 0x6be;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x793, uVar6 == 0x1800)) {
    uVar10 = 0x75c;
  }
  phy_reg_mod(param_1,0x18e,0x7ff,uVar10);
  iVar9 = 0x19e;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    iVar9 = (uVar6 == 0x1800) + 0x1b2;
  }
  phy_reg_mod(param_1,399,0x7ff,iVar9);
  lVar11 = 0x73;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    lVar11 = (ulong)(uVar6 != 0x1800) * 5 + 0xb1;
  }
  phy_reg_mod(param_1,400,0x7ff,lVar11);
  uVar10 = 0xb2;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0xff, uVar6 == 0x1800)) {
    uVar10 = 0xed;
  }
  phy_reg_mod(param_1,0x191,0x7ff,uVar10);
  lVar11 = 0x73;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 != 0x1000) {
    lVar11 = (ulong)(uVar6 != 0x1800) * 5 + 0xb1;
  }
  phy_reg_mod(param_1,0x192,0x7ff,lVar11);
  uVar10 = 0x5fe;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0x6b4, uVar6 == 0x1800)) {
    uVar10 = 0x692;
  }
  phy_reg_mod(param_1,0x193,0x7ff,uVar10);
  uVar10 = 0xcc;
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 != 0x1000) && (uVar10 = 0xa8, uVar6 == 0x1800)) {
    uVar10 = 0xaf;
  }
  phy_reg_mod(param_1,0x194,0x7ff,uVar10);
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 == 0x1000) || (uVar10 = 0x8b, uVar6 != 0x1800)) {
    uVar10 = 0x97;
  }
  phy_reg_mod(param_1,0x1b5,0xff,uVar10);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
    uVar10 = 0x32;
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      uVar10 = 0x19;
    }
    phy_reg_mod(param_1,0x250,0xff,uVar10);
    uVar10 = 0x28;
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      uVar10 = 0x14;
    }
    phy_reg_mod(param_1,0x261,0xfff,uVar10);
    uVar10 = 400;
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      uVar10 = 200;
    }
    phy_reg_mod(param_1,0x262,0xfff,uVar10);
    uVar3 = 0x32;
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      uVar3 = 0x19;
    }
    phy_reg_mod(param_1,0x263,0xfff,uVar3);
  }
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 == 0x1000) || (uVar10 = 9, uVar6 == 0x1800)) {
    uVar10 = 0x13;
  }
  phy_reg_mod(param_1,0x312,0xff,uVar10);
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar6 == 0x1000) || (uVar10 = 0x900, uVar6 == 0x1800)) {
    uVar10 = 0x1300;
  }
  phy_reg_mod(param_1,0x313,0xff00,uVar10);
  if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) &&
     (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4335)) {
    uVar10 = 0x200;
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      uVar10 = 0x80;
    }
    phy_reg_mod(param_1,0x361,0x1fff,uVar10);
  }
  for (bVar16 = 0; bVar16 < *(byte *)(param_1 + 0x168); bVar16 = bVar16 + 1) {
    uVar12 = 0x6ed;
    uVar10 = 10;
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) != 0x1000) {
      uVar10 = 0x14;
    }
    if ((bVar16 != 0) && (uVar12 = 0xaed, bVar16 == 1)) {
      uVar12 = 0x8ed;
    }
    phy_reg_mod(param_1,uVar12,0xff,uVar10);
    uVar10 = 0x17;
    uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    if ((uVar6 != 0x1000) && (uVar10 = 0x54, uVar6 == 0x1800)) {
      uVar10 = 0x2a;
    }
    uVar12 = 0x6ef;
    if ((bVar16 != 0) && (uVar12 = 0xaef, bVar16 == 1)) {
      uVar12 = 0x8ef;
    }
    phy_reg_mod(param_1,uVar12,0xff,uVar10);
    uVar10 = 0xe00;
    uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    if ((uVar6 != 0x1000) && (uVar10 = 0x2c00, uVar6 == 0x1800)) {
      uVar10 = 0x1600;
    }
    uVar12 = 0x6ef;
    if ((bVar16 != 0) && (uVar12 = 0xaef, bVar16 == 1)) {
      uVar12 = 0x8ef;
    }
    phy_reg_mod(param_1,uVar12,0xff00,uVar10);
  }
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 == 0x2000) {
    uVar4 = 0x3c;
    iVar9 = 6 - (uint)(*(uint *)(param_1 + 0x164) < 2);
  }
  else {
    if (uVar6 == 0x1800) {
      uVar4 = 0x1e;
      uVar15 = -(uint)(*(uint *)(param_1 + 0x164) < 2);
    }
    else {
      if (uVar6 != 0x1000) {
        uVar4 = 0xf;
        iVar9 = 0;
        goto LAB_001a0108;
      }
      uVar4 = 0xf;
      uVar15 = -(uint)(*(uint *)(param_1 + 0x164) < 2) & 0xfffffffe;
    }
    iVar9 = uVar15 + 5;
  }
LAB_001a0108:
  for (bVar16 = 0; bVar16 < *(byte *)(param_1 + 0x168); bVar16 = bVar16 + 1) {
    iVar2 = *(int *)(param_1 + 0x164);
    if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
        cVar7 = *(char *)(*(long *)(param_1 + 0x138) + 0x346);
LAB_001a016d:
        if (cVar7 != '\0') goto LAB_001a016f;
      }
      else if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
        cVar7 = *(char *)(*(long *)(param_1 + 0x138) + 0x347);
        goto LAB_001a016d;
      }
      uVar10 = 0x6ef;
      if ((bVar16 != 0) && (uVar10 = 0xaef, bVar16 == 1)) {
        uVar10 = 0x8ef;
      }
      uVar8 = 0x17;
    }
    else {
LAB_001a016f:
      uVar10 = 0x6ef;
      uVar8 = uVar4;
      if ((bVar16 != 0) && (uVar10 = 0xaef, bVar16 == 1)) {
        uVar10 = 0x8ef;
      }
    }
    phy_reg_mod(param_1,uVar10,0xff,uVar8);
  }
  wlc_phy_set_analog_tx_lpf(param_1,0x100,0xffffffff,iVar9,iVar9,0xffffffff,0xffffffff,0xffffffff);
  if (iVar1 == 0) {
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x2000) {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 ||
          ((acphychipid == 0xaa06 || (uVar10 = 0x6d4, acphychipid == 0x4350)))))) {
        uVar10 = 0x16d4;
      }
      uVar12 = 0xcc0;
    }
    else {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         ((acphychipid == 0xaa06 || (uVar10 = 0x6d4, acphychipid == 0x4350)))) {
        uVar10 = 0x16d4;
      }
      uVar12 = 0xc60;
    }
    phy_reg_write(param_1,uVar10,uVar12);
  }
  if ((*(uint *)(param_1 + 0x164) == 3) || (*(uint *)(param_1 + 0x164) < 2)) {
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      wlc_phy_table_write_acphy(param_1,4,3,1,8,&local_48);
      puVar13 = &local_58;
    }
    else {
      puVar13 = &local_68;
      wlc_phy_table_write_acphy(param_1,4,3,1,8,puVar13);
    }
    wlc_phy_table_write_acphy(param_1,4,3,0x3d,8,puVar13);
  }
  if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x2000) {
    for (bVar16 = 0; bVar16 < *(byte *)(param_1 + 0x168); bVar16 = bVar16 + 1) {
      uVar10 = 0x73a;
      if ((bVar16 != 0) && (uVar10 = 0x93a, bVar16 != 1)) {
        uVar10 = 0xb3a;
      }
      phy_reg_mod(param_1,uVar10,0x80,0x80);
      uVar10 = 0x725;
      if ((bVar16 != 0) && (uVar10 = 0xb25, bVar16 == 1)) {
        uVar10 = 0x925;
      }
      phy_reg_mod(param_1,uVar10,0x200,0x200);
    }
    local_74 = 0;
    local_84 = 0;
    local_94 = 0;
    uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    if (uVar6 == 0x1000) {
      local_78 = 0xef52;
      local_88 = 0xef42;
      local_98 = 0xef52;
LAB_001a0420:
      local_76 = 0x94;
      local_86 = 0x84;
      local_96 = 0x84;
    }
    else {
      if (uVar6 == 0x1800) {
        local_78 = 0x4f52;
        local_88 = 0x4f42;
        local_98 = 0x4f52;
        goto LAB_001a0420;
      }
      local_78 = 0xfd2;
      local_76 = 0x96;
      local_88 = 0xfc2;
      local_86 = 0x86;
      local_98 = 0xfd2;
      local_96 = 0x86;
    }
    wlc_phy_table_write_acphy(param_1,0x14,1,0x30,0x30,&local_78);
    wlc_phy_table_write_acphy(param_1,0x14,1,0x31,0x30,&local_88);
    wlc_phy_table_write_acphy(param_1,0x14,1,0x32,0x30,&local_98);
    wlc_phy_table_write_acphy(param_1,7,8,0x30,0x10,&DAT_00676680);
    wlc_phy_table_write_acphy(param_1,7,8,0xa0,0x10,&DAT_00676690);
    wlc_phy_table_write_acphy(param_1,7,8,0x40,0x10,&DAT_006766a0);
    wlc_phy_table_write_acphy(param_1,7,8,0xb0,0x10,&DAT_006766b0);
    wlc_phy_table_write_acphy(param_1,7,8,0x50,0x10,&DAT_006766c0);
    puVar14 = &DAT_006766d0;
  }
  else {
    for (bVar16 = 0; bVar16 < *(byte *)(param_1 + 0x168); bVar16 = bVar16 + 1) {
      if (*(int *)(param_1 + 0x164) == 0) {
        uVar10 = 0x73a;
        if ((bVar16 != 0) && (uVar10 = 0xb3a, bVar16 == 1)) {
          uVar10 = 0x93a;
        }
        uVar12 = 0;
      }
      else {
        uVar10 = 0x73a;
        if ((bVar16 != 0) && (uVar10 = 0xb3a, bVar16 == 1)) {
          uVar10 = 0x93a;
        }
        uVar12 = 0x80;
      }
      phy_reg_mod(param_1,uVar10,0x80,uVar12);
      uVar10 = 0x725;
      if ((bVar16 != 0) && (uVar10 = 0x925, bVar16 != 1)) {
        uVar10 = 0xb25;
      }
      phy_reg_mod(param_1,uVar10,0x200,0x200);
    }
    wlc_phy_table_write_acphy(param_1,7,8,0x30,0x10,&DAT_006766e0);
    wlc_phy_table_write_acphy(param_1,7,8,0xa0,0x10,&DAT_006766f0);
    wlc_phy_table_write_acphy(param_1,7,8,0x40,0x10,&DAT_00676700);
    wlc_phy_table_write_acphy(param_1,7,8,0xb0,0x10,&DAT_00676710);
    wlc_phy_table_write_acphy(param_1,7,8,0x50,0x10,&DAT_00676720);
    puVar14 = &DAT_00676730;
  }
  wlc_phy_table_write_acphy(param_1,7,8,0xc0,0x10,puVar14);
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 == 0x1000) {
    local_a8 = 0xe800;
  }
  else {
    if (uVar6 != 0x1800) {
      local_a8 = 0x800;
      local_a6 = 0x86;
      goto LAB_001a071b;
    }
    local_a8 = 0x4800;
  }
  local_a6 = 0x84;
LAB_001a071b:
  wlc_phy_table_write_acphy(param_1,0x14,1,0x33,0x30,&local_a8);
  wlc_phy_table_write_acphy(param_1,7,0x10,0x10,0x10,&DAT_00676740);
  wlc_phy_table_write_acphy(param_1,7,0x10,0x80,0x10,&DAT_00676760);
  iVar1 = *(int *)(param_1 + 0x164);
  if (((iVar1 == 5) || (iVar1 == 2)) || (iVar1 == 6)) {
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      phy_reg_write(param_1,0x171,1);
      phy_reg_mod(param_1,0x16e,8,8);
      uVar10 = 4;
    }
    else {
      phy_reg_write(param_1,0x171,0x20);
      phy_reg_mod(param_1,0x16e,8,0);
      uVar10 = 0;
    }
    phy_reg_mod(param_1,0x16e,4,uVar10);
  }
  iVar1 = *(int *)(param_1 + 0x164);
  if (((iVar1 != 5) && (iVar1 != 2)) && (iVar1 != 6)) {
    if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
      phy_reg_write(param_1,0x197,0x14);
      uVar10 = 0x10;
    }
    else {
      phy_reg_write(param_1,0x197,0x1e);
      uVar10 = 0x14;
    }
    phy_reg_write(param_1,0x198,uVar10);
  }
  phy_reg_mod(param_1,0x19e,2,uVar5 & 2);
  return;
}

