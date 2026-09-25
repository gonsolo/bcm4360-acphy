
void wlc_phy_tempsense_acphy(long param_1)

{
  char cVar1;
  undefined1 uVar2;
  ulong uVar3;
  short sVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  short *psVar10;
  int iVar11;
  ushort uVar12;
  uint uVar13;
  int iVar14;
  undefined8 uVar15;
  int *piVar16;
  byte bVar17;
  short sVar18;
  uint uVar19;
  ushort uVar20;
  undefined1 *puVar21;
  uint uVar22;
  long lVar23;
  byte bVar24;
  int local_84;
  short *local_80;
  short local_78 [16];
  int local_58 [4];
  undefined1 local_46 [2];
  undefined1 local_44 [2];
  undefined1 local_42 [2];
  undefined1 local_40 [2];
  undefined2 local_3e;
  undefined2 local_3c;
  undefined1 local_39 [9];
  
  bVar24 = 0;
  uVar20 = 0x7f8;
  cVar1 = *(char *)(param_1 + 0xc35);
  local_58[0] = 0x20f;
  local_58[1] = 0x209;
  local_58[2] = 0x20a;
  local_3c = 0;
  local_3e = 0;
  local_58[3] = 0;
  local_39[0] = 0;
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  wlc_phyreg_enter(param_1);
  lVar9 = *(long *)(param_1 + 0x138);
  uVar12 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if ((uVar12 != 0x2000) && (uVar20 = 0xd5eb, uVar12 == 0x1800)) {
    uVar20 = (-(ushort)(*(char *)(param_1 + 0x116a) == '\0') & 0x201) + 0x43e9;
  }
  uVar5 = phy_reg_read(param_1,0x19e);
  *(undefined2 *)(lVar9 + 0x296) = uVar5;
  phy_reg_mod(param_1,0x19e,0x40,0);
  phy_reg_mod(param_1,0x19e,0x80,0);
  phy_reg_mod(param_1,0x19e,0x100,0);
  for (uVar7 = 0; bVar17 = (byte)uVar7, bVar17 < *(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
      iVar8 = uVar7 * 0x200;
      uVar5 = phy_reg_read(param_1,(short)(iVar8 + 0x73eU));
      lVar23 = (long)(int)(uVar7 & 0xff);
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x148) * 2) = uVar5;
      phy_reg_write(param_1,iVar8 + 0x73eU & 0xffff,0x440);
      sVar18 = (short)iVar8;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x727);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x148) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x73c);
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x150) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x721);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x150) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x729);
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x158) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x720);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x158) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x728);
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x160) * 2) = uVar5;
      uVar6 = iVar8 + 0x724U & 0xffff;
      uVar5 = phy_reg_read(param_1,uVar6);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x160) * 2) = uVar5;
      uVar22 = iVar8 + 0x736U & 0xffff;
      uVar5 = phy_reg_read(param_1,uVar22);
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x168) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x725);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x170) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x739);
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x178) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x73a);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x178) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x722);
      *(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x168) * 2) = uVar5;
      uVar5 = phy_reg_read(param_1,sVar18 + 0x734);
      uVar15 = 0x727;
      *(undefined2 *)(lVar9 + 8 + (lVar23 + 0x170) * 2) = uVar5;
      if ((bVar17 != 0) && (uVar15 = 0xb27, bVar17 == 1)) {
        uVar15 = 0x927;
      }
      phy_reg_mod(param_1,uVar15,2,2);
      uVar15 = 0x73c;
      if ((bVar17 != 0) && (uVar15 = 0xb3c, bVar17 == 1)) {
        uVar15 = 0x93c;
      }
      phy_reg_mod(param_1,uVar15,0xe,2);
      uVar15 = 0x727;
      if ((bVar17 != 0) && (uVar15 = 0xb27, bVar17 == 1)) {
        uVar15 = 0x927;
      }
      phy_reg_mod(param_1,uVar15,1,1);
      uVar15 = 0x73c;
      if ((bVar17 != 0) && (uVar15 = 0xb3c, bVar17 == 1)) {
        uVar15 = 0x93c;
      }
      phy_reg_mod(param_1,uVar15,1,1);
      uVar15 = 0x721;
      if ((bVar17 != 0) && (uVar15 = 0xb21, bVar17 == 1)) {
        uVar15 = 0x921;
      }
      phy_reg_mod(param_1,uVar15,0x100,0x100);
      uVar15 = 0x729;
      if ((bVar17 != 0) && (uVar15 = 0xb29, bVar17 == 1)) {
        uVar15 = 0x929;
      }
      phy_reg_mod(param_1,uVar15,0x100,0);
      uVar15 = 0x720;
      if ((bVar17 != 0) && (uVar15 = 0xb20, bVar17 == 1)) {
        uVar15 = 0x920;
      }
      phy_reg_mod(param_1,uVar15,0x20,0x20);
      uVar15 = 0x728;
      if ((bVar17 != 0) && (uVar15 = 0xb28, bVar17 == 1)) {
        uVar15 = 0x928;
      }
      phy_reg_mod(param_1,uVar15,0x20,0x20);
      uVar15 = 0x720;
      if ((bVar17 != 0) && (uVar15 = 0xb20, bVar17 == 1)) {
        uVar15 = 0x920;
      }
      phy_reg_mod(param_1,uVar15,0x40,0x40);
      uVar15 = 0x728;
      if ((bVar17 != 0) && (uVar15 = 0xb28, bVar17 == 1)) {
        uVar15 = 0x928;
      }
      phy_reg_mod(param_1,uVar15,0x40,0);
      uVar15 = 0x720;
      if ((bVar17 != 0) && (uVar15 = 0xb20, bVar17 == 1)) {
        uVar15 = 0x920;
      }
      phy_reg_mod(param_1,uVar15,0x10,0x10);
      uVar15 = 0x728;
      if ((bVar17 != 0) && (uVar15 = 0xb28, bVar17 == 1)) {
        uVar15 = 0x928;
      }
      phy_reg_mod(param_1,uVar15,0x10,0x10);
      phy_reg_write(param_1,uVar22,0x154);
      phy_reg_write(param_1,uVar6,0x3ff);
      uVar15 = 0x73a;
      if ((bVar17 != 0) && (uVar15 = 0xb3a, bVar17 == 1)) {
        uVar15 = 0x93a;
      }
      phy_reg_mod(param_1,uVar15,7,uVar20 & 7);
      uVar15 = 0x725;
      if ((bVar17 != 0) && (uVar15 = 0xb25, bVar17 == 1)) {
        uVar15 = 0x925;
      }
      phy_reg_mod(param_1,uVar15,0x20,0x20);
      uVar15 = 0x739;
      if ((bVar17 != 0) && (uVar15 = 0xb39, bVar17 == 1)) {
        uVar15 = 0x939;
      }
      phy_reg_mod(param_1,uVar15,0x7e,uVar20 >> 2 & 0x7e);
      uVar15 = 0x725;
      if ((bVar17 != 0) && (uVar15 = 0xb25, bVar17 == 1)) {
        uVar15 = 0x925;
      }
      phy_reg_mod(param_1,uVar15,2,2);
      uVar15 = 0x73a;
      if ((bVar17 != 0) && (uVar15 = 0xb3a, bVar17 == 1)) {
        uVar15 = 0x93a;
      }
      phy_reg_mod(param_1,uVar15,8,uVar20 >> 6 & 8);
      uVar15 = 0x725;
      if ((bVar17 != 0) && (uVar15 = 0xb25, bVar17 == 1)) {
        uVar15 = 0x925;
      }
      phy_reg_mod(param_1,uVar15,0x40,0x40);
      uVar15 = 0x73a;
      if ((bVar17 != 0) && (uVar15 = 0xb3a, bVar17 == 1)) {
        uVar15 = 0x93a;
      }
      phy_reg_mod(param_1,uVar15,0x10,uVar20 >> 6 & 0x10);
      uVar15 = 0x725;
      if ((bVar17 != 0) && (uVar15 = 0xb25, bVar17 == 1)) {
        uVar15 = 0x925;
      }
      phy_reg_mod(param_1,uVar15,0x80,0x80);
      uVar15 = 0x73a;
      if ((bVar17 != 0) && (uVar15 = 0xb3a, bVar17 == 1)) {
        uVar15 = 0x93a;
      }
      phy_reg_mod(param_1,uVar15,0x60,uVar20 >> 6 & 0x60);
      uVar15 = 0x725;
      if ((bVar17 != 0) && (uVar15 = 0xb25, bVar17 == 1)) {
        uVar15 = 0x925;
      }
      phy_reg_mod(param_1,uVar15,0x100,0x100);
      uVar15 = 0x734;
      if ((bVar17 != 0) && (uVar15 = 0xb34, bVar17 == 1)) {
        uVar15 = 0x934;
      }
      phy_reg_mod(param_1,uVar15,7,0);
      uVar15 = 0x722;
      if ((bVar17 != 0) && (uVar15 = 0xb22, bVar17 == 1)) {
        uVar15 = 0x922;
      }
      phy_reg_mod(param_1,uVar15,4,4);
    }
  }
  lVar9 = *(long *)(param_1 + 0x138);
  for (uVar7 = 0; (byte)uVar7 < *(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
    uVar6 = uVar7 & 0xff;
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
      if (*(char *)(param_1 + 0x16e) == '\0') {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (acphychipid == 0xaa06)) {
          uVar19 = 0x16e;
          uVar22 = uVar6 << 9;
        }
        else {
          uVar19 = 0x181;
          uVar22 = 0x800;
        }
        uVar5 = read_radio_reg(param_1,uVar19 | uVar22 & 0xffff);
        *(undefined2 *)(lVar9 + 0x254 + (long)(int)uVar6 * 2) = uVar5;
      }
      else {
        uVar5 = read_radio_reg(param_1,(ushort)(uVar6 << 9) | 0x182);
        *(undefined2 *)(lVar9 + 0x25c + (long)(int)uVar6 * 2) = uVar5;
      }
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar22 = 0x13, acphychipid == 0xaa06)))) {
        uVar22 = 0xe;
      }
      uVar19 = uVar6 << 9;
      uVar5 = read_radio_reg(param_1,uVar22 | uVar19 & 0xffff);
      *(undefined2 *)(lVar9 + 0x274 + (long)(int)uVar6 * 2) = uVar5;
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar22 = 0x174, acphychipid == 0xaa06)))) {
        uVar22 = 0x161;
      }
      uVar5 = read_radio_reg(param_1,uVar22 | uVar19 & 0xffff);
      *(undefined2 *)(lVar9 + 0x264 + (long)(int)uVar6 * 2) = uVar5;
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar22 = 0x1c, acphychipid == 0xaa06)) {
        uVar22 = 0x17;
      }
      uVar5 = read_radio_reg(param_1,uVar22 | uVar19 & 0xffff);
      *(undefined2 *)(lVar9 + 0x27c + (long)(int)uVar6 * 2) = uVar5;
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar22 = 0x172, acphychipid == 0xaa06)))) {
        uVar22 = 0x15f;
      }
      uVar5 = read_radio_reg(param_1,uVar22 | uVar19 & 0xffff);
      *(undefined2 *)(lVar9 + 0x26c + (long)(int)uVar6 * 2) = uVar5;
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar22 = 0x29, acphychipid == 0xaa06)))) {
        uVar22 = 0x24;
      }
      uVar5 = read_radio_reg(param_1,uVar22 | uVar19 & 0xffff);
      *(undefined2 *)(lVar9 + 0x284 + (long)(int)uVar6 * 2) = uVar5;
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar22 = 0x2a, acphychipid == 0xaa06)) {
        uVar22 = 0x25;
      }
      uVar5 = read_radio_reg(param_1,uVar22 | uVar19 & 0xffff);
      *(undefined2 *)(lVar9 + 0x28c + (long)(int)uVar6 * 2) = uVar5;
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x174, acphychipid == 0xaa06)))) {
        uVar6 = 0x161;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x4000,0x4000);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x13, acphychipid == 0xaa06)))) {
        uVar6 = 0xe;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,1,1);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar6 = 0x174, acphychipid == 0xaa06)) {
        uVar6 = 0x161;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x1000,0x1000);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x1c, acphychipid == 0xaa06)))) {
        uVar6 = 0x17;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,1,1);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x1c, acphychipid == 0xaa06)))) {
        uVar6 = 0x17;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,2,0);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar6 = 0x172, acphychipid == 0xaa06)) {
        uVar6 = 0x15f;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x2000,0x2000);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x2a, acphychipid == 0xaa06)))) {
        uVar6 = 0x25;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x3ff,0x91);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x172, acphychipid == 0xaa06)))) {
        uVar6 = 0x15f;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x4000,0x4000);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar6 = 0x29, acphychipid == 0xaa06)) {
        uVar6 = 0x24;
      }
      mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x700,0x300);
      if (*(char *)(param_1 + 0x16e) == '\x01') {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar6 = 0x29, acphychipid == 0xaa06)))) {
          uVar6 = 0x24;
        }
        mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0x30,0);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar6 = 0x29, acphychipid == 0xaa06)))) {
          uVar6 = 0x24;
        }
        mod_radio_reg(param_1,uVar6 | uVar19 & 0xffff,0xe,2);
      }
    }
  }
  psVar10 = local_78;
  for (lVar9 = 6; lVar9 != 0; lVar9 = lVar9 + -1) {
    psVar10[0] = 0;
    psVar10[1] = 0;
    psVar10 = psVar10 + ((ulong)bVar24 * -2 + 1) * 2;
  }
  FUN_0019c924(param_1,&local_3c,&local_3e,local_58 + 3,local_40,local_42,local_44,local_46,local_39
              );
  FUN_00193d3a(param_1);
  bVar24 = 0;
  for (uVar7 = 0; (byte)uVar7 < *(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
      puVar21 = &DAT_00559fb8;
      FUN_00194bfe(param_1,(uVar7 & 0xff) + 0x10,1);
      uVar22 = (uVar7 & 0xff) << 9;
      local_80 = local_78 + (int)(uVar7 & 0xff);
      uVar6 = (uint)(ushort)((ushort)uVar22 | 0x182);
      do {
        uVar2 = *puVar21;
        uVar19 = uVar6;
        if (*(char *)(param_1 + 0x16e) == '\0') {
          if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
             (acphychipid == 0xaa06)) {
            uVar13 = 0x16e;
            uVar19 = uVar22;
          }
          else {
            uVar13 = 0x181;
            uVar19 = 0x800;
          }
          uVar19 = uVar13 | uVar19 & 0xffff;
        }
        uVar15 = 0;
        mod_radio_reg(param_1,uVar19,2,2);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar19 = 0x13, acphychipid == 0xaa06)))) {
          uVar19 = 0xe;
        }
        mod_radio_reg(param_1,uVar19 | uVar22 & 0xffff,2,
                      (int)CONCAT71((int7)((ulong)uVar15 >> 8),uVar2) * 2 & 0x1fe);
        uVar19 = uVar6;
        if (*(char *)(param_1 + 0x16e) == '\0') {
          if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
             ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
            uVar13 = 0x16e;
            uVar19 = uVar22;
          }
          else {
            uVar13 = 0x181;
            uVar19 = 0x800;
          }
          uVar19 = uVar13 | uVar19 & 0xffff;
        }
        mod_radio_reg(param_1,uVar19,1,1);
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (uVar19 = 0x13, acphychipid == 0xaa06)) {
          uVar19 = 0xe;
        }
        mod_radio_reg(param_1,uVar19 | uVar22 & 0xffff,4);
        osl_delay(10);
        iVar11 = 0;
        iVar8 = 0;
        do {
          uVar12 = phy_reg_read(param_1,0x13);
          iVar14 = 0x400;
          if ((uint)((int)(uint)uVar12 >> 2) < 0x200) {
            iVar14 = 0;
          }
          iVar8 = iVar8 + 1;
          iVar11 = iVar11 + (((int)(uint)uVar12 >> 2) - iVar14);
        } while (iVar8 != 8);
        puVar21 = puVar21 + 1;
        *local_80 = (short)(iVar11 >> 3);
        local_80 = local_80 + 3;
      } while (puVar21 != &DAT_00559fbc);
      bVar24 = bVar24 + 1;
    }
  }
  iVar8 = *(int *)(param_1 + 0x164);
  if (((iVar8 == 5) || (iVar8 == 2)) || (iVar8 == 6)) {
    local_84 = 0x1aaf91;
    iVar11 = -0x154d;
  }
  else {
    local_84 = 0x19e55e;
    iVar11 = -0x15ad;
    if (iVar8 != 3) {
      psVar10 = local_78 + 3;
      piVar16 = local_58;
      local_84 = 0;
      for (uVar7 = 0; (byte)uVar7 < *(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
        if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
          uVar3 = (long)((((((int)psVar10[6] + (int)*psVar10) - (int)psVar10[3]) - (int)psVar10[-3])
                         * 0x223e) / 2 << 8) / (long)*piVar16;
          local_84 = local_84 +
                     (int)((long)((ulong)(uint)((int)uVar3 >> 0x1f) << 0x20 | uVar3 & 0xffffffff) /
                          (long)(int)(uint)bVar24);
        }
        psVar10 = psVar10 + 1;
        piVar16 = piVar16 + 1;
      }
      local_84 = local_84 + 0x1d0614;
      sVar18 = (short)cVar1;
      goto LAB_001a4fad;
    }
  }
  sVar18 = 0;
  local_84 = ((((((int)local_78[6] + (int)local_78[0]) - (int)local_78[3]) - (int)local_78[9]) / 2)
              * 800 * iVar11) / 0x400 + local_84;
LAB_001a4fad:
  local_84 = local_84 / 0x4000;
  lVar9 = *(long *)(param_1 + 0x138);
  phy_reg_write(param_1,0x19e,*(undefined2 *)(lVar9 + 0x296));
  for (uVar7 = 0; (byte)uVar7 < *(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
      lVar23 = (long)(int)(uVar7 & 0xff);
      sVar4 = (short)uVar7 * 0x200;
      phy_reg_write(param_1,sVar4 + 0x73e,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x148) * 2));
      phy_reg_write(param_1,sVar4 + 0x727,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x148) * 2));
      phy_reg_write(param_1,sVar4 + 0x73c,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x150) * 2));
      phy_reg_write(param_1,sVar4 + 0x721,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x150) * 2));
      phy_reg_write(param_1,sVar4 + 0x729,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x158) * 2));
      phy_reg_write(param_1,sVar4 + 0x720,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x158) * 2));
      phy_reg_write(param_1,sVar4 + 0x728,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x160) * 2));
      phy_reg_write(param_1,sVar4 + 0x724,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x160) * 2));
      phy_reg_write(param_1,sVar4 + 0x736,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x168) * 2));
      phy_reg_write(param_1,sVar4 + 0x725,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x170) * 2));
      phy_reg_write(param_1,sVar4 + 0x739,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x178) * 2));
      phy_reg_write(param_1,sVar4 + 0x73a,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x178) * 2));
      phy_reg_write(param_1,sVar4 + 0x722,*(undefined2 *)(lVar9 + 0x10 + (lVar23 + 0x168) * 2));
      phy_reg_write(param_1,sVar4 + 0x734,*(undefined2 *)(lVar9 + 8 + (lVar23 + 0x170) * 2));
      uVar7 = uVar7 & 0xff;
    }
  }
  lVar9 = *(long *)(param_1 + 0x138);
  for (bVar24 = 0; bVar24 < *(byte *)(param_1 + 0x168); bVar24 = bVar24 + 1) {
    uVar7 = (uint)bVar24;
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
      if (*(char *)(param_1 + 0x16e) == '\0') {
        uVar5 = *(undefined2 *)(lVar9 + 0x254 + (long)(int)uVar7 * 2);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar20 = 0x16e;
          uVar12 = (ushort)bVar24 << 9;
        }
        else {
          uVar20 = 0x181;
          uVar12 = 0x800;
        }
        uVar12 = uVar12 | uVar20;
      }
      else {
        uVar5 = *(undefined2 *)(lVar9 + 0x25c + (long)(int)uVar7 * 2);
        uVar12 = (ushort)bVar24 << 9 | 0x182;
      }
      write_radio_reg(param_1,uVar12,uVar5);
      uVar7 = (uint)bVar24;
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar6 = 0x13, acphychipid == 0xaa06)) {
        uVar6 = 0xe;
      }
      uVar22 = uVar7 << 9;
      write_radio_reg(param_1,uVar6 | uVar22 & 0xffff,
                      *(undefined2 *)(lVar9 + 0x274 + (long)(int)uVar7 * 2));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x174, acphychipid == 0xaa06)))) {
        uVar6 = 0x161;
      }
      write_radio_reg(param_1,uVar6 | uVar22 & 0xffff,
                      *(undefined2 *)(lVar9 + 0x264 + (long)(int)uVar7 * 2));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x1c, acphychipid == 0xaa06)))) {
        uVar6 = 0x17;
      }
      write_radio_reg(param_1,uVar6 | uVar22 & 0xffff,
                      *(undefined2 *)(lVar9 + 0x27c + (long)(int)uVar7 * 2));
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar6 = 0x172, acphychipid == 0xaa06)) {
        uVar6 = 0x15f;
      }
      write_radio_reg(param_1,uVar6 | uVar22 & 0xffff,
                      *(undefined2 *)(lVar9 + 0x26c + (long)(int)uVar7 * 2));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x29, acphychipid == 0xaa06)))) {
        uVar6 = 0x24;
      }
      write_radio_reg(param_1,uVar6 | uVar22 & 0xffff,
                      *(undefined2 *)(lVar9 + 0x284 + (long)(int)uVar7 * 2));
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar6 = 0x2a, acphychipid == 0xaa06)))) {
        uVar6 = 0x25;
      }
      write_radio_reg(param_1,uVar6 | uVar22 & 0xffff,
                      *(undefined2 *)(lVar9 + 0x28c + (long)(int)uVar7 * 2));
    }
  }
  FUN_0019cb53(param_1,&local_3c,&local_3e,local_58 + 3,local_40,local_42,local_44,local_46,local_39
              );
  wlc_phyreg_exit(param_1);
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  *(short *)(*(long *)(param_1 + 0x138) + 0x8dc) = sVar18 + (short)local_84;
  return;
}

