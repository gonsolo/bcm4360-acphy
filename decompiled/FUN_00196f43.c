
void FUN_00196f43(long param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  ulong uVar7;
  ushort uVar8;
  uint uVar9;
  undefined8 uVar10;
  byte bVar11;
  int iVar12;
  uint uVar13;
  short sVar14;
  int iVar15;
  char local_39;
  
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar10 = 0x8f2, acphychipid == 0xaa06)) {
    uVar10 = 0x8ea;
  }
  mod_radio_reg(param_1,uVar10,0x80,0x80);
  for (iVar12 = 0; bVar11 = (byte)iVar12, bVar11 < *(byte *)(param_1 + 0x168); iVar12 = iVar12 + 1)
  {
    iVar15 = iVar12 * 0x200;
    uVar1 = phy_reg_read(param_1,(short)(iVar15 + 0x739U));
    sVar14 = (short)iVar15 + 0x725;
    uVar6 = iVar15 + 0x73aU & 0xffff;
    uVar2 = phy_reg_read(param_1,uVar6);
    uVar3 = phy_reg_read(param_1,sVar14);
    uVar10 = 0x739;
    if ((bVar11 != 0) && (uVar10 = 0xb39, bVar11 == 1)) {
      uVar10 = 0x939;
    }
    phy_reg_mod(param_1,uVar10,0x80,0x80);
    uVar10 = 0x725;
    if ((bVar11 != 0) && (uVar10 = 0xb25, bVar11 == 1)) {
      uVar10 = 0x925;
    }
    phy_reg_mod(param_1,uVar10,4,4);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar9 = 0x133, acphychipid == 0xaa06)) {
      uVar9 = 0x121;
    }
    uVar13 = iVar12 << 9;
    mod_radio_reg(param_1,uVar9 | uVar13 & 0xffff,0x1000,0);
    osl_delay(100);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x133, acphychipid == 0xaa06)))) {
      uVar9 = 0x121;
    }
    mod_radio_reg(param_1,uVar9 | uVar13 & 0xffff,0x1000,0x1000);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x134, acphychipid == 0xaa06)))) {
      uVar9 = 0x122;
    }
    uVar5 = read_radio_reg(param_1,uVar9 | uVar13 & 0xffff);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar9 = 0x134, acphychipid == 0xaa06)) {
      uVar9 = 0x122;
    }
    write_radio_reg(param_1,uVar9 | uVar13 & 0xffff,uVar5 | 0xf);
    local_39 = '\0';
    do {
      osl_delay(10);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar9 = 0x156, acphychipid == 0xaa06)))) {
        uVar9 = 0x144;
      }
      uVar4 = read_radio_reg(param_1,uVar9 | uVar13 & 0xffff);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar9 = 0x156, acphychipid == 0xaa06)))) {
        uVar9 = 0x144;
      }
      uVar7 = read_radio_reg(param_1,uVar9 | uVar13 & 0xffff);
    } while ((((uVar7 & 1) == 0) || ((uVar4 & 2) == 0)) &&
            (local_39 = local_39 + '\x01', local_39 != '\n'));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x134, acphychipid == 0xaa06)))) {
      uVar9 = 0x122;
    }
    write_radio_reg(param_1,uVar9 | uVar13 & 0xffff,uVar5 & 0xfff0);
    phy_reg_write(param_1,sVar14,uVar3);
    phy_reg_write(param_1,iVar15 + 0x739U & 0xffff,uVar1);
    phy_reg_write(param_1,uVar6,uVar2);
  }
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar10 = 0x8f2, acphychipid == 0xaa06)))) {
    uVar10 = 0x8ea;
  }
  mod_radio_reg(param_1,uVar10,0x80,0);
  if (*(byte *)(param_1 + 0x16c) < 4) {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar10 = 0x8f2, acphychipid == 0xaa06)) {
      uVar10 = 0x8ea;
    }
    mod_radio_reg(param_1,uVar10,0x80,0x80);
    for (sVar14 = 0; (byte)sVar14 < *(byte *)(param_1 + 0x168); sVar14 = sVar14 + 1) {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x172, acphychipid == 0xaa06)))) {
        uVar5 = 0x15f;
      }
      uVar4 = sVar14 << 9;
      mod_radio_reg(param_1,uVar5 | uVar4,0x20,0x20);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x172, acphychipid == 0xaa06)))) {
        uVar5 = 0x15f;
      }
      mod_radio_reg(param_1,uVar5 | uVar4,0x10,0x10);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x155, acphychipid == 0xaa06)) {
        uVar5 = 0x143;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x147, acphychipid == 0xaa06)))) {
        uVar8 = 0x135;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x154, acphychipid == 0xaa06)))) {
        uVar5 = 0x142;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar8 = 0x146, acphychipid == 0xaa06)) {
        uVar8 = 0x134;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x153, acphychipid == 0xaa06)))) {
        uVar5 = 0x141;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x145, acphychipid == 0xaa06)))) {
        uVar8 = 0x133;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x152, acphychipid == 0xaa06)) {
        uVar5 = 0x140;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x144, acphychipid == 0xaa06)))) {
        uVar8 = 0x132;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x151, acphychipid == 0xaa06)))) {
        uVar5 = 0x13f;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar8 = 0x143, acphychipid == 0xaa06)) {
        uVar8 = 0x131;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x150, acphychipid == 0xaa06)))) {
        uVar5 = 0x13e;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x142, acphychipid == 0xaa06)))) {
        uVar8 = 0x130;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x14f, acphychipid == 0xaa06)) {
        uVar5 = 0x13d;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x141, acphychipid == 0xaa06)))) {
        uVar8 = 0x12f;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x14e, acphychipid == 0xaa06)))) {
        uVar5 = 0x13c;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar8 = 0x140, acphychipid == 0xaa06)) {
        uVar8 = 0x12e;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x14d, acphychipid == 0xaa06)))) {
        uVar5 = 0x13b;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x13f, acphychipid == 0xaa06)))) {
        uVar8 = 0x12d;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x14c, acphychipid == 0xaa06)) {
        uVar5 = 0x13a;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x13e, acphychipid == 0xaa06)))) {
        uVar8 = 300;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x14b, acphychipid == 0xaa06)))) {
        uVar5 = 0x139;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar8 = 0x13d, acphychipid == 0xaa06)) {
        uVar8 = 299;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x14a, acphychipid == 0xaa06)))) {
        uVar5 = 0x138;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x13c, acphychipid == 0xaa06)))) {
        uVar8 = 0x12a;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x149, acphychipid == 0xaa06)) {
        uVar5 = 0x137;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar8 = 0x13b, acphychipid == 0xaa06)))) {
        uVar8 = 0x129;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x148, acphychipid == 0xaa06)))) {
        uVar5 = 0x136;
      }
      uVar5 = read_radio_reg(param_1,uVar5 | uVar4);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar8 = 0x13a, acphychipid == 0xaa06)) {
        uVar8 = 0x128;
      }
      write_radio_reg(param_1,uVar8 | uVar4,~uVar5);
    }
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar10 = 0x8f2, acphychipid == 0xaa06)))) {
      uVar10 = 0x8ea;
    }
    mod_radio_reg(param_1,uVar10,0x80,0);
  }
  return;
}

