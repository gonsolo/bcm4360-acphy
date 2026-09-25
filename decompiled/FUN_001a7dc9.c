
void FUN_001a7dc9(long param_1,uint param_2)

{
  undefined1 *puVar1;
  uint *puVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  char cVar9;
  byte bVar10;
  char cVar11;
  ushort uVar12;
  ushort uVar13;
  ushort uVar14;
  undefined8 uVar15;
  char cVar16;
  ushort *puVar17;
  long lVar18;
  uint uVar19;
  undefined8 uVar20;
  undefined2 uVar21;
  short sVar22;
  long lVar23;
  undefined2 uVar24;
  uint uVar25;
  undefined2 uVar26;
  long lVar27;
  bool bVar28;
  undefined2 local_98;
  undefined2 local_96;
  undefined2 local_94;
  undefined2 local_92;
  char local_83;
  char local_82;
  int local_78 [4];
  uint local_68 [2];
  long local_60;
  long local_58;
  long local_50;
  long local_48;
  int local_40;
  uint local_3c [3];
  
  lVar18 = *(long *)(param_1 + 0x138);
  local_48 = 0;
  local_50 = 0;
  local_58 = 0;
  local_60 = 0;
  cVar11 = *(char *)(lVar18 + 0x32c);
  if (*(short *)(param_1 + 0x16a) == 0x2069) {
    cVar9 = FUN_0018f6f1(param_1,param_2 & 0xff,local_3c,&local_48,&local_50,&local_58,&local_60);
    if (cVar9 == '\0') {
      return;
    }
  }
  else {
    uVar25 = 0;
    puVar17 = &chan_tuning_20691rev_1;
    if (*(char *)(param_1 + 0x16c) != '\x01') {
      return;
    }
    while ((uint)*puVar17 != (param_2 & 0xff)) {
      uVar25 = uVar25 + 1;
      puVar17 = puVar17 + 2;
      if (uVar25 == 0x4d) {
        return;
      }
    }
    local_3c[0] = (uint)(ushort)(&DAT_006ec8b2)[(ulong)uVar25 * 2];
  }
  lVar7 = *(long *)(param_1 + 0x20);
  if (((*(int *)(lVar7 + 0x44) == 2) && (*(int *)(lVar7 + 0x3c) == 0x4335)) &&
     ((*(byte *)(*(long *)(lVar7 + 0x18) + 0x48) & 4) == 0)) {
    wlc_phy_get_spurmode(param_1,(undefined2)local_3c[0]);
    if (*(char *)(lVar18 + 0x338) != *(char *)(param_1 + 0x1164)) {
      wlc_phy_setup_spurmode(param_1);
      *(undefined1 *)(lVar18 + 0x338) = *(undefined1 *)(param_1 + 0x1164);
    }
  }
  if ((*(char *)(lVar18 + 0x32c) != '\0') &&
     (((iVar6 = *(int *)(param_1 + 0x164), iVar6 == 5 || (iVar6 == 2)) ||
      ((iVar6 == 6 || (iVar6 == 3)))))) {
    phy_reg_mod(param_1,0x40a,0x200,0x200);
  }
  if ((cVar11 != '\0') ||
     (local_83 = '\0', ((param_2 & 0xc000) == 0) != (bool)*(char *)(lVar18 + 0x330))) {
    if ((*(char *)(lVar18 + 0x912) != '\0') && (cVar9 = FUN_00193240(param_1), cVar9 != '\0')) {
      if (*(char *)(lVar18 + 0x330) == '\0') {
        if (*(char *)(lVar18 + 0x911) != '\0') {
          *(short *)(lVar18 + 0x916) = (short)*(undefined4 *)(lVar18 + 0x908);
        }
      }
      else if (*(char *)(lVar18 + 0x910) != '\0') {
        *(short *)(lVar18 + 0x914) = (short)*(undefined4 *)(lVar18 + 0x908);
      }
    }
    *(bool *)(lVar18 + 0x330) = (param_2 & 0xc000) == 0;
    local_83 = '\x01';
  }
  uVar12 = phy_reg_read(param_1,0x19e);
  uVar13 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  phy_reg_mod(param_1,0x19e,1,1);
  if ((cVar11 != '\0') || (local_82 = '\0', *(uint *)(lVar18 + 0x334) != (param_2 & 0x3800))) {
    uVar25 = param_2 & 0x3800;
    *(uint *)(lVar18 + 0x334) = uVar25;
    if ((*(char *)(lVar18 + 0x32c) == '\0') &&
       ((wlapi_bmac_bw_set(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),uVar25),
        *(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4335 && (uVar25 == 0x2000)))) {
      phy_reg_write(param_1,0x16a,0xfe);
      wlc_phy_resetcca_acphy(param_1);
      phy_reg_write(param_1,0x16a,0xff);
    }
    osl_delay(2);
    local_82 = '\x01';
  }
  uVar15 = 0x100;
  if ((param_2 & 0xc000) == 0) {
    uVar15 = 0;
  }
  phy_reg_mod(param_1,3,0x100,uVar15);
  *(undefined2 *)(lVar18 + 0xc) = 0;
  wlc_phy_stay_in_carriersearch_acphy(param_1,1);
  *(undefined1 *)(lVar18 + 0x32f) = 0;
  wlc_phy_chanspec_radio_set(param_1,param_2 & 0xffff);
  lVar8 = local_48;
  lVar23 = local_50;
  lVar27 = local_58;
  lVar7 = local_60;
  if ((((local_48 == 0) && (local_50 == 0)) && (local_58 == 0)) && (local_60 == 0))
  goto LAB_001aaf6a;
  cVar9 = *(char *)(param_1 + 0x17e);
  uVar25 = *(uint *)(*(long *)(param_1 + 0x20) + 0x68);
  if (local_82 != '\0' || local_83 != '\0') {
    phy_reg_mod(param_1,0x728,0x100,0x100);
    osl_delay(1);
    phy_reg_mod(param_1,0x728,0x100,0);
  }
  if (*(char *)(param_1 + 0x16e) == '\x02') {
    if ((((uVar25 & 0x2000) == 0) || (cVar9 != '\r')) || (*(int *)(param_1 + 0xc24) != 40000000)) {
      uVar26 = *(undefined2 *)(lVar7 + 0x10);
      uVar24 = *(undefined2 *)(lVar7 + 0x12);
      uVar21 = *(undefined2 *)(lVar7 + 0x16);
      uVar4 = *(undefined2 *)(lVar7 + 0x32);
      uVar5 = *(undefined2 *)(lVar7 + 0x34);
      local_92 = *(undefined2 *)(lVar7 + 0x2c);
      local_94 = *(undefined2 *)(lVar7 + 0x2e);
      local_96 = *(undefined2 *)(lVar7 + 0x30);
      local_98 = *(undefined2 *)(lVar7 + 0x36);
    }
    else {
      local_98 = 0x6028;
      local_96 = 0x1192;
      uVar21 = 0x388;
      local_94 = 0xf;
      local_92 = 0xf;
      uVar24 = 0x3333;
      uVar5 = 0xe1e6;
      uVar4 = 0xf0c2;
      uVar26 = 0x5cb;
    }
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e8, acphychipid == 0xaa06)))) {
      uVar15 = 0x8e0;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 4));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e9, acphychipid == 0xaa06)))) {
      uVar15 = 0x8e1;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 6));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8e5, acphychipid == 0xaa06)) {
      uVar15 = 0x8dd;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 8));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e4, acphychipid == 0xaa06)))) {
      uVar15 = 0x8dc;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 10));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8ee, acphychipid == 0xaa06)))) {
      uVar15 = 0x8e6;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0xc));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8ef, acphychipid == 0xaa06)) {
      uVar15 = 0x8e7;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0xe));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8cc, acphychipid == 0xaa06)))) {
      uVar15 = 0x8c4;
    }
    write_radio_reg(param_1,uVar15,uVar26);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8cd, acphychipid == 0xaa06)))) {
      uVar15 = 0x8c5;
    }
    write_radio_reg(param_1,uVar15,uVar24);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8ed, acphychipid == 0xaa06)) {
      uVar15 = 0x8e5;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x14));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8f3, acphychipid == 0xaa06)))) {
      uVar15 = 0x8eb;
    }
    write_radio_reg(param_1,uVar15,uVar21);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8de, acphychipid == 0xaa06)))) {
      uVar15 = 0x8d6;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x18));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x113;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x125;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar7 + 0x1a));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e3, acphychipid == 0xaa06)))) {
      uVar15 = 0x8db;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x1c));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e2, acphychipid == 0xaa06)))) {
      uVar15 = 0x8da;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x1e));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8df, acphychipid == 0xaa06)) {
      uVar15 = 0x8d7;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x20));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x88c, acphychipid == 0xaa06)))) {
      uVar15 = 0x885;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x22));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x88d, acphychipid == 0xaa06)))) {
      uVar15 = 0x886;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x24));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x88e, acphychipid == 0xaa06)) {
      uVar15 = 0x887;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x26));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e1, acphychipid == 0xaa06)))) {
      uVar15 = 0x8d9;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x28));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e0, acphychipid == 0xaa06)))) {
      uVar15 = 0x8d8;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x2a));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8d1, acphychipid == 0xaa06)) {
      uVar15 = 0x8c9;
    }
    write_radio_reg(param_1,uVar15,local_92);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8d2, acphychipid == 0xaa06)))) {
      uVar15 = 0x8ca;
    }
    write_radio_reg(param_1,uVar15,local_94);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8d4, acphychipid == 0xaa06)))) {
      uVar15 = 0x8cc;
    }
    write_radio_reg(param_1,uVar15,local_96);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8cf, acphychipid == 0xaa06)) {
      uVar15 = 0x8c7;
    }
    write_radio_reg(param_1,uVar15,uVar4);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8d0, acphychipid == 0xaa06)))) {
      uVar15 = 0x8c8;
    }
    write_radio_reg(param_1,uVar15,uVar5);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x89a, acphychipid == 0xaa06)))) {
      uVar15 = 0x892;
    }
    write_radio_reg(param_1,uVar15,local_98);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8d3, acphychipid == 0xaa06)) {
      uVar15 = 0x8cb;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x38));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x112;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x124;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar7 + 0x3a));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x62f, acphychipid == 0xaa06)))) {
      uVar15 = 0x629;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x3c));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x662, acphychipid == 0xaa06)) {
      uVar15 = 0x65b;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x3e));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x665, acphychipid == 0xaa06)))) {
      uVar15 = 0x65e;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x40));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x66f, acphychipid == 0xaa06)))) {
      uVar15 = 0x668;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x42));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x11a;
      uVar25 = 0;
    }
    else {
      uVar19 = 300;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar7 + 0x44));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x11b;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x12d;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar7 + 0x46));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x115;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x127;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar7 + 0x48));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x637, acphychipid == 0xaa06)) {
      uVar15 = 0x630;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x4a));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x663, acphychipid == 0xaa06)))) {
      uVar15 = 0x65c;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x4c));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x669, acphychipid == 0xaa06)))) {
      uVar15 = 0x662;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x4e));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x674, acphychipid == 0xaa06)) {
      uVar15 = 0x66d;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar7 + 0x50));
    for (sVar22 = 0; (byte)sVar22 < *(byte *)(param_1 + 0x168); sVar22 = sVar22 + 1) {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar14 = 0x4c, acphychipid == 0xaa06)))) {
        uVar14 = 0x45;
      }
      mod_radio_reg(param_1,uVar14 | sVar22 << 9,0x7000,0x7000);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar14 = 0x12e, acphychipid == 0xaa06)))) {
        uVar14 = 0x11c;
      }
      mod_radio_reg(param_1,uVar14 | sVar22 << 9,0x1000,0x1000);
    }
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8d9, acphychipid == 0xaa06)) {
      uVar15 = 0x8d1;
    }
    mod_radio_reg(param_1,uVar15,0xff,8);
  }
  else if (*(char *)(param_1 + 0x16e) == '\x01') {
    if ((byte)(*(char *)(param_1 + 0x16c) - 0x19U) < 2) {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8e8, acphychipid == 0xaa06)) {
        uVar15 = 0x8e0;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 4));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e9, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e1;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 6));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e5, acphychipid == 0xaa06)))) {
        uVar15 = 0x8dd;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 8));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8e4, acphychipid == 0xaa06)) {
        uVar15 = 0x8dc;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 10));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8ee, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e6;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0xc));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8ef, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e7;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0xe));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8cc, acphychipid == 0xaa06)) {
        uVar15 = 0x8c4;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x10));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8cd, acphychipid == 0xaa06)))) {
        uVar15 = 0x8c5;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x12));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8ed, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e5;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x14));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8f3, acphychipid == 0xaa06)) {
        uVar15 = 0x8eb;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x16));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x91b, acphychipid == 0xaa06)))) {
        uVar15 = 0x909;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x18));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8de, acphychipid == 0xaa06)))) {
        uVar15 = 0x8d6;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x1a));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (acphychipid == 0xaa06)) {
        uVar19 = 0x113;
        uVar25 = 0;
      }
      else {
        uVar19 = 0x125;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar27 + 0x1c));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e3, acphychipid == 0xaa06)))) {
        uVar15 = 0x8db;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x1e));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e2, acphychipid == 0xaa06)))) {
        uVar15 = 0x8da;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x20));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8df, acphychipid == 0xaa06)) {
        uVar15 = 0x8d7;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x22));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x88c, acphychipid == 0xaa06)))) {
        uVar15 = 0x885;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x24));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x88d, acphychipid == 0xaa06)))) {
        uVar15 = 0x886;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x26));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x88e, acphychipid == 0xaa06)) {
        uVar15 = 0x887;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x28));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e1, acphychipid == 0xaa06)))) {
        uVar15 = 0x8d9;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x2a));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e0, acphychipid == 0xaa06)))) {
        uVar15 = 0x8d8;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x2c));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8d1, acphychipid == 0xaa06)) {
        uVar15 = 0x8c9;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x2e));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8d2, acphychipid == 0xaa06)))) {
        uVar15 = 0x8ca;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x30));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8d4, acphychipid == 0xaa06)))) {
        uVar15 = 0x8cc;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x32));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8cf, acphychipid == 0xaa06)) {
        uVar15 = 0x8c7;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x34));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8d0, acphychipid == 0xaa06)))) {
        uVar15 = 0x8c8;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x36));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x89a, acphychipid == 0xaa06)))) {
        uVar15 = 0x892;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x38));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8d3, acphychipid == 0xaa06)) {
        uVar15 = 0x8cb;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x3a));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar19 = 0x112;
        uVar25 = 0;
      }
      else {
        uVar19 = 0x124;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar27 + 0x3c));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x2f, acphychipid == 0xaa06)))) {
        uVar15 = 0x29;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x3e));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x62, acphychipid == 0xaa06)) {
        uVar15 = 0x5b;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x40));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x65, acphychipid == 0xaa06)))) {
        uVar15 = 0x5e;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x42));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x6f, acphychipid == 0xaa06)))) {
        uVar15 = 0x68;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x44));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (acphychipid == 0xaa06)) {
        uVar19 = 0x11a;
        uVar25 = 0;
      }
      else {
        uVar19 = 300;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar27 + 0x46));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar19 = 0x11b;
        uVar25 = 0;
      }
      else {
        uVar19 = 0x12d;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar27 + 0x48));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 299, acphychipid == 0xaa06)))) {
        uVar15 = 0x119;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x4a));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x37, acphychipid == 0xaa06)) {
        uVar15 = 0x30;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x4c));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 99, acphychipid == 0xaa06)))) {
        uVar15 = 0x5c;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x4e));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x69, acphychipid == 0xaa06)))) {
        uVar15 = 0x62;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar27 + 0x50));
      uVar26 = *(undefined2 *)(lVar27 + 0x52);
    }
    else {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8e8, acphychipid == 0xaa06)) {
        uVar15 = 0x8e0;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 4));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e9, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e1;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 6));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e5, acphychipid == 0xaa06)))) {
        uVar15 = 0x8dd;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 8));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8e4, acphychipid == 0xaa06)) {
        uVar15 = 0x8dc;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 10));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8ee, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e6;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0xc));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8ef, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e7;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0xe));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8cc, acphychipid == 0xaa06)) {
        uVar15 = 0x8c4;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x10));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8cd, acphychipid == 0xaa06)))) {
        uVar15 = 0x8c5;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x12));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8ed, acphychipid == 0xaa06)))) {
        uVar15 = 0x8e5;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x14));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8f3, acphychipid == 0xaa06)) {
        uVar15 = 0x8eb;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x16));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8de, acphychipid == 0xaa06)))) {
        uVar15 = 0x8d6;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x18));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar19 = 0x113;
        uVar25 = 0;
      }
      else {
        uVar19 = 0x125;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar23 + 0x1a));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8e3, acphychipid == 0xaa06)) {
        uVar15 = 0x8db;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x1c));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e2, acphychipid == 0xaa06)))) {
        uVar15 = 0x8da;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x1e));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8df, acphychipid == 0xaa06)))) {
        uVar15 = 0x8d7;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x20));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x88c, acphychipid == 0xaa06)) {
        uVar15 = 0x885;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x22));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x88d, acphychipid == 0xaa06)))) {
        uVar15 = 0x886;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x24));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x88e, acphychipid == 0xaa06)))) {
        uVar15 = 0x887;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x26));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8e1, acphychipid == 0xaa06)) {
        uVar15 = 0x8d9;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x28));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8e0, acphychipid == 0xaa06)))) {
        uVar15 = 0x8d8;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x2a));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8d1, acphychipid == 0xaa06)))) {
        uVar15 = 0x8c9;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x2c));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8d2, acphychipid == 0xaa06)) {
        uVar15 = 0x8ca;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x2e));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8d4, acphychipid == 0xaa06)))) {
        uVar15 = 0x8cc;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x30));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8cf, acphychipid == 0xaa06)))) {
        uVar15 = 0x8c7;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x32));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8d0, acphychipid == 0xaa06)) {
        uVar15 = 0x8c8;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x34));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x89a, acphychipid == 0xaa06)))) {
        uVar15 = 0x892;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x36));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8d3, acphychipid == 0xaa06)))) {
        uVar15 = 0x8cb;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x38));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (acphychipid == 0xaa06)) {
        uVar19 = 0x112;
        uVar25 = 0;
      }
      else {
        uVar19 = 0x124;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar23 + 0x3a));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x2f, acphychipid == 0xaa06)))) {
        uVar15 = 0x29;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x3c));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x62, acphychipid == 0xaa06)))) {
        uVar15 = 0x5b;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x3e));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x65, acphychipid == 0xaa06)) {
        uVar15 = 0x5e;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x40));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x6f, acphychipid == 0xaa06)))) {
        uVar15 = 0x68;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x42));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar19 = 0x11a;
        uVar25 = 0;
      }
      else {
        uVar19 = 300;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar23 + 0x44));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (acphychipid == 0xaa06)) {
        uVar19 = 0x11b;
        uVar25 = 0;
      }
      else {
        uVar19 = 0x12d;
        uVar25 = 0x800;
      }
      write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar23 + 0x46));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 299, acphychipid == 0xaa06)))) {
        uVar15 = 0x119;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x48));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x37, acphychipid == 0xaa06)))) {
        uVar15 = 0x30;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x4a));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 99, acphychipid == 0xaa06)) {
        uVar15 = 0x5c;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x4c));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x69, acphychipid == 0xaa06)))) {
        uVar15 = 0x62;
      }
      write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar23 + 0x4e));
      uVar26 = *(undefined2 *)(lVar23 + 0x50);
    }
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x74, acphychipid == 0xaa06)))) {
      uVar15 = 0x6d;
    }
    write_radio_reg(param_1,uVar15,uVar26);
  }
  else {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e8, acphychipid == 0xaa06)))) {
      uVar15 = 0x8e0;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 4));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e9, acphychipid == 0xaa06)))) {
      uVar15 = 0x8e1;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 6));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8e5, acphychipid == 0xaa06)) {
      uVar15 = 0x8dd;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 8));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e4, acphychipid == 0xaa06)))) {
      uVar15 = 0x8dc;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 10));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8ee, acphychipid == 0xaa06)))) {
      uVar15 = 0x8e6;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0xc));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8ef, acphychipid == 0xaa06)) {
      uVar15 = 0x8e7;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0xe));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8cc, acphychipid == 0xaa06)))) {
      uVar15 = 0x8c4;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x10));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8cd, acphychipid == 0xaa06)))) {
      uVar15 = 0x8c5;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x12));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8ed, acphychipid == 0xaa06)) {
      uVar15 = 0x8e5;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x14));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8f3, acphychipid == 0xaa06)))) {
      uVar15 = 0x8eb;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x16));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8de, acphychipid == 0xaa06)))) {
      uVar15 = 0x8d6;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x18));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x113;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x125;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x1a));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e3, acphychipid == 0xaa06)))) {
      uVar15 = 0x8db;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x1c));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e2, acphychipid == 0xaa06)))) {
      uVar15 = 0x8da;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x1e));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8df, acphychipid == 0xaa06)) {
      uVar15 = 0x8d7;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x20));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x88c, acphychipid == 0xaa06)))) {
      uVar15 = 0x885;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x22));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x88d, acphychipid == 0xaa06)))) {
      uVar15 = 0x886;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x24));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x88e, acphychipid == 0xaa06)) {
      uVar15 = 0x887;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x26));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e1, acphychipid == 0xaa06)))) {
      uVar15 = 0x8d9;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x28));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8e0, acphychipid == 0xaa06)))) {
      uVar15 = 0x8d8;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x2a));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8d1, acphychipid == 0xaa06)) {
      uVar15 = 0x8c9;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x2c));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8d2, acphychipid == 0xaa06)))) {
      uVar15 = 0x8ca;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x2e));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8d4, acphychipid == 0xaa06)))) {
      uVar15 = 0x8cc;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x30));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x8cf, acphychipid == 0xaa06)) {
      uVar15 = 0x8c7;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x32));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x8d0, acphychipid == 0xaa06)))) {
      uVar15 = 0x8c8;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x34));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x89a, acphychipid == 0xaa06)))) {
      uVar15 = 0x892;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x36));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x94;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0x9c;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x38));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x95;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0x9d;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x3a));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x96;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0x9e;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x3c));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x97;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0x9f;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x3e));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x99;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0xa1;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x40));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x9a;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0xa2;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x42));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x9b;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0xa3;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x44));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x9c;
      uVar25 = 0x800;
    }
    else {
      uVar19 = 0xa4;
      uVar25 = 0;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x46));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x112;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x124;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x48));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x62f, acphychipid == 0xaa06)) {
      uVar15 = 0x629;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x4a));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x662, acphychipid == 0xaa06)))) {
      uVar15 = 0x65b;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x4c));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x665, acphychipid == 0xaa06)))) {
      uVar15 = 0x65e;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x4e));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x66f, acphychipid == 0xaa06)) {
      uVar15 = 0x668;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x50));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x11a;
      uVar25 = 0;
    }
    else {
      uVar19 = 300;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x52));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x11b;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x12d;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x54));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x72b, acphychipid == 0xaa06)) {
      uVar15 = 0x719;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x56));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x637, acphychipid == 0xaa06)))) {
      uVar15 = 0x630;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x58));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x663, acphychipid == 0xaa06)))) {
      uVar15 = 0x65c;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x5a));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar15 = 0x669, acphychipid == 0xaa06)) {
      uVar15 = 0x662;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x5c));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x674, acphychipid == 0xaa06)))) {
      uVar15 = 0x66d;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x5e));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x89b, acphychipid == 0xaa06)))) {
      uVar15 = 0x893;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x60));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar19 = 0x145;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x157;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 0x62));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar19 = 0x146;
      uVar25 = 0;
    }
    else {
      uVar19 = 0x158;
      uVar25 = 0x800;
    }
    write_radio_reg(param_1,uVar19 | uVar25,*(undefined2 *)(lVar8 + 100));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x735, acphychipid == 0xaa06)))) {
      uVar15 = 0x723;
    }
    write_radio_reg(param_1,uVar15,*(undefined2 *)(lVar8 + 0x66));
    if (*(byte *)(param_1 + 0x16c) < 4) {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x335, acphychipid == 0xaa06)) {
        uVar15 = 0x323;
      }
      write_radio_reg(param_1,uVar15,0x3e9);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x535, acphychipid == 0xaa06)))) {
        uVar15 = 0x523;
      }
      write_radio_reg(param_1,uVar15,0x3e9);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x89a, acphychipid == 0xaa06)))) {
        uVar15 = 0x892;
      }
      mod_radio_reg(param_1,uVar15,0xff00,0xa000);
    }
    if (cVar9 == '\x04') {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar15 = 0x8de, acphychipid == 0xaa06)) {
        uVar15 = 0x8d6;
      }
      write_radio_reg(param_1,uVar15,0xce4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar15 = 0x8f4, acphychipid == 0xaa06)))) {
        uVar15 = 0x8ec;
      }
      mod_radio_reg(param_1,uVar15,0x70,0x50);
    }
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x64c, acphychipid == 0xaa06)))) {
      uVar15 = 0x645;
    }
    mod_radio_reg(param_1,uVar15,0x7000,0x7000);
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
      wlc_2069_rfpll_150khz(param_1);
    }
  }
  if (3 < *(byte *)(param_1 + 0x16c)) {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x735, acphychipid == 0xaa06)))) {
      uVar15 = 0x723;
    }
    write_radio_reg(param_1,uVar15,0x83e0);
  }
  if (*(char *)(param_1 + 0x16e) == '\x01') {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x89a, acphychipid == 0xaa06)))) {
      uVar15 = 0x892;
    }
    mod_radio_reg(param_1,uVar15,0xff00,0xe000);
  }
  if ((((*(char *)(param_1 + 0x16e) == '\x01') &&
       (cVar9 = *(char *)(param_1 + 0x16c), 2 < (byte)(cVar9 - 2U))) && (cVar9 != '\x12')) &&
     (((cVar9 != '\x18' && (cVar9 != '\x1a')) && ((cVar9 != '\"' && (cVar9 != '\b')))))) {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar15 = 0x80, acphychipid == 0xaa06)))) {
      uVar15 = 0x79;
    }
    write_radio_reg(param_1,uVar15,0x8484);
  }
  if (*(char *)(param_1 + 0x16e) == '\x01') {
    write_radio_reg(param_1,0x98d,0x1df3);
    write_radio_reg(param_1,0x98e,0x1ffc);
    write_radio_reg(param_1,0x98f,0x78);
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      write_radio_reg(param_1,0x18b,0);
      uVar15 = 0;
    }
    else {
      write_radio_reg(param_1,0x18b,0xffff);
      uVar15 = 0xffff;
    }
    uVar20 = 0x98c;
LAB_001aaf5a:
    write_radio_reg(param_1,uVar20,uVar15);
  }
  else if (*(char *)(param_1 + 0x16e) == '\x02') {
    write_radio_reg(param_1,0x98d,0x1df3);
    write_radio_reg(param_1,0x98e,0x1ffc);
    uVar15 = 0x78;
    uVar20 = 0x98f;
    goto LAB_001aaf5a;
  }
  FUN_00193e5b(param_1);
LAB_001aaf6a:
  if (((*(int *)(param_1 + 0x164) == 3) &&
      ((*(byte *)(*(long *)(param_1 + 0x20) + 0x69) & 0x20) != 0)) &&
     (*(int *)(param_1 + 0xc24) == 40000000)) {
    lVar7 = *(long *)(param_1 + 0x138);
    local_68[0] = 0;
    local_78[0] = 0;
    local_68[1] = 0;
    local_78[1] = 0;
    local_40 = 0;
    if (*(char *)(lVar7 + 0x8bd) != '\0') {
      wlc_phy_table_write_acphy(param_1,3,1,*(undefined1 *)(lVar7 + 0x8be),0x20,&local_40);
      wlc_phy_table_write_acphy(param_1,3,1,*(undefined1 *)(lVar7 + 0x8bf),0x20,&local_40);
      *(undefined1 *)(lVar7 + 0x8bd) = 0;
    }
    if (*(char *)(param_1 + 0x17e) == '\r') {
      local_78[0] = 0x19;
      local_78[1] = 0x1a;
      local_68[0] = 7;
      local_68[1] = 8;
      lVar7 = *(long *)(param_1 + 0x138);
      uVar14 = *(ushort *)(param_1 + 0x17e) & 0x3800;
      cVar9 = '\0';
      if (uVar14 != 0x2000) {
        cVar9 = '@';
        if (uVar14 == 0x1800) {
          cVar9 = -0x80;
        }
      }
      lVar23 = 0;
      lVar27 = lVar7;
      do {
        cVar16 = (char)*(int *)((long)local_78 + lVar23);
        if (*(int *)((long)local_78 + lVar23) < 0) {
          cVar16 = cVar9 + cVar16;
        }
        *(char *)(lVar27 + 0x8be) = cVar16;
        puVar2 = (uint *)((long)local_68 + lVar23);
        lVar23 = lVar23 + 4;
        local_40 = (*puVar2 & 0xff) << 8;
        puVar1 = (undefined1 *)(lVar27 + 0x8be);
        lVar27 = lVar27 + 1;
        wlc_phy_table_write_acphy(param_1,3,1,*puVar1,0x20,&local_40);
      } while (lVar23 != 8);
      *(undefined1 *)(lVar7 + 0x8bd) = 1;
    }
  }
  phy_reg_mod(param_1,0x19e,2,uVar12 & 2);
  phy_reg_mod(param_1,0x19e,1,uVar13 & 1);
  if (cVar11 != '\0') {
    FUN_001a1924(param_1);
    FUN_001a784f(param_1);
  }
  if (local_83 != '\0' || cVar11 != '\0') {
    FUN_0019f0b8(param_1);
  }
  if ((local_82 != '\0') || (cVar11 != '\0')) {
    FUN_0019f839(param_1);
  }
  if ((*(char *)(lVar18 + 0x912) != '\0') &&
     ((local_82 != '\0' || (local_83 != '\0' || cVar11 != '\0')))) {
    wlc_phy_hirssi_elnabypass_set_ucode_params_acphy(param_1);
  }
  if ((((local_48 != 0) || (local_50 != 0)) || (local_58 != 0)) || (local_60 != 0)) {
    FUN_001a581c(param_1,local_48,local_50,local_58,local_60);
  }
  *(undefined8 *)(lVar18 + 0x8a8) = 0;
  bVar28 = false;
  if ((*(uint *)(param_1 + 0x19c) & 0x206) != 0) {
    bVar28 = *(char *)(param_1 + 0x240) != (char)*(undefined2 *)(param_1 + 0x17e);
  }
  if (!bVar28) {
    *(char *)(param_1 + 0x240) = (char)*(undefined2 *)(param_1 + 0x17e);
    uVar15 = FUN_00193c3b(param_1,param_2 & 0xffff,1);
    *(undefined8 *)(lVar18 + 0x8a8) = uVar15;
  }
  FUN_0019173d(param_1);
  FUN_0019bc45(param_1,cVar11,local_83,local_82);
  FUN_0019ae61(param_1);
  FUN_0019b279(param_1,*(undefined1 *)(lVar18 + 0x670));
  if ((local_82 != '\0') || (*(char *)(lVar18 + 0x32c) != '\0')) {
    wlc_phy_resetcca_acphy(param_1);
    osl_delay(1);
    FUN_00196f43(param_1);
  }
  iVar6 = *(int *)(param_1 + 0x164);
  if (((iVar6 == 5) || (iVar6 == 2)) || ((iVar6 == 6 || (iVar6 == 3)))) {
    phy_reg_mod(param_1,0x40a,0x200,0x200);
  }
  for (uVar12 = 0; uVar12 < *(byte *)(param_1 + 0x168); uVar12 = uVar12 + 1) {
    wlc_phy_txpwr_by_index_acphy
              (param_1,1 << ((byte)uVar12 & 0x1f) & 0xff,
               (int)*(char *)(*(long *)(param_1 + 0x138) + 0x10 + (long)(int)(uint)uVar12));
  }
  uVar3 = *(undefined1 *)(param_1 + 4000);
  wlc_phy_txpwrctrl_enable_acphy(param_1,0);
  bVar10 = wlc_phy_tssivisible_thresh_acphy(param_1);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar15 = 0x641, acphychipid == 0x4350)))) {
    uVar15 = 0x1641;
  }
  phy_reg_write(param_1,uVar15,bVar10 + 0x7f00);
  FUN_0019a2eb(param_1,*(undefined1 *)(param_1 + 0xfa2));
  wlc_phy_txpwrctrl_enable_acphy(param_1,uVar3);
  if (((local_48 != 0) || (local_50 != 0)) || ((local_58 != 0 || (local_60 != 0)))) {
    FUN_00194b87(param_1,0);
  }
  if (cVar11 != '\0') {
    bVar10 = phy_reg_read(param_1,0xb);
    cVar11 = *(char *)(*(long *)(param_1 + 0x20) + 0xa7);
    if ((cVar11 != (char)((char)(1 << (bVar10 & 7)) + -1)) ||
       (*(char *)(*(long *)(param_1 + 0x20) + 0xa4) != cVar11)) {
      wlc_phy_rxcore_setstate_acphy(param_1,cVar11);
    }
  }
  wlc_phy_resetcca_acphy(param_1);
  cVar11 = wlc_phy_get_rxgainerr_phy(param_1,local_78);
  if (cVar11 == '\0') {
    for (bVar10 = 0; bVar10 < *(byte *)(param_1 + 0x168); bVar10 = bVar10 + 1) {
      cVar11 = FUN_0018fdc6(param_1,bVar10,0x45,0,local_68);
      *(char *)(param_1 + 0x212 + (long)(int)(uint)bVar10) =
           (char)*(undefined2 *)((long)local_78 + (long)(int)(uint)bVar10 * 2) + cVar11 * -2 + -0x76
      ;
    }
  }
  else {
    cVar11 = *(char *)(param_1 + 0x168);
    lVar18 = param_1;
    for (cVar9 = '\0'; cVar9 != cVar11; cVar9 = cVar9 + '\x01') {
      *(undefined1 *)(lVar18 + 0x212) = 0;
      lVar18 = lVar18 + 1;
    }
  }
  iVar6 = *(int *)(param_1 + 0x164);
  if (((iVar6 == 5) || (iVar6 == 2)) || (iVar6 == 6)) {
    phy_reg_mod(param_1,0x400,1,0);
  }
  wlc_phy_stay_in_carriersearch_acphy(param_1,0);
  return;
}

