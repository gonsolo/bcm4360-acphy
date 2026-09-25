
void FUN_001a08b2(long param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  undefined8 uVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  short sVar11;
  byte local_48;
  
  uVar1 = phy_reg_read(param_1,0x728);
  uVar2 = phy_reg_read(param_1,0x408);
  uVar2 = uVar2 & 0xfc38;
  phy_reg_write(param_1,0x415,0);
  phy_reg_write(param_1,0x40e,0);
  phy_reg_write(param_1,0x40c,0x2000);
  phy_reg_write(param_1,0x408,uVar2);
  phy_reg_write(param_1,0x417,0);
  phy_reg_write(param_1,0x416,0xd);
  phy_reg_write(param_1,0x728,uVar1 & 0x7e7f);
  uVar3 = phy_reg_read(param_1,0x720);
  phy_reg_write(param_1,0x720,uVar3 | 0x180);
  phy_reg_write(param_1,0x408,uVar2);
  phy_reg_write(param_1,0x408,uVar2 | 1);
  osl_delay(1);
  phy_reg_write(param_1,0x408,uVar2);
  if (*(short *)(param_1 + 0x16a) == 0x2069) {
    switch(*(char *)(param_1 + 0x16c)) {
    case '\x03':
      puVar8 = prefregs_2069_rev3;
      break;
    case '\x04':
    case '\b':
      puVar8 = prefregs_2069_rev4;
      break;
    default:
      goto switchD_001a09e8_caseD_5;
    case '\x10':
      puVar8 = prefregs_2069_rev16;
      break;
    case '\x11':
      puVar8 = prefregs_2069_rev17;
      break;
    case '\x12':
      puVar8 = prefregs_2069_rev18;
      break;
    case '\x17':
      puVar8 = prefregs_2069_rev23;
      break;
    case '\x18':
      puVar8 = prefregs_2069_rev24;
      break;
    case '\x19':
      puVar8 = prefregs_2069_rev25;
      break;
    case '\x1a':
      puVar8 = prefregs_2069_rev26;
      break;
    case ' ':
    case '!':
    case '\"':
    case '#':
    case '%':
    case '&':
      puVar8 = prefregs_2069_rev33_37;
    }
  }
  else {
    if (*(char *)(param_1 + 0x16c) != '\x01') goto switchD_001a09e8_caseD_5;
    puVar8 = (undefined1 *)&prefregs_20691_rev1;
  }
  wlc_phy_init_radio_prefregs_allbands(param_1,puVar8);
  if ((*(byte *)(*(long *)(param_1 + 0x20) + 100) & 2) != 0) {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar9 = 0x8f2, acphychipid == 0xaa06)) {
      uVar9 = 0x8ea;
    }
    mod_radio_reg(param_1,uVar9,0x100,0x100);
  }
  if (*(char *)(param_1 + 0x16e) == '\0') {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x97e, acphychipid == 0xaa06)))) {
      uVar9 = 0x96b;
    }
    mod_radio_reg(param_1,uVar9,0x800,0x800);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar9 = 0x97e, acphychipid == 0xaa06)) {
      uVar9 = 0x96b;
    }
    mod_radio_reg(param_1,uVar9,0x4000,0x4000);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x97f, acphychipid == 0xaa06)))) {
      uVar9 = 0x96c;
    }
    mod_radio_reg(param_1,uVar9,0x800,0x800);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x97e, acphychipid == 0xaa06)))) {
      uVar9 = 0x96b;
    }
    mod_radio_reg(param_1,uVar9,0x8000,0x8000);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar9 = 0x97e, acphychipid == 0xaa06)) {
      uVar9 = 0x96b;
    }
    mod_radio_reg(param_1,uVar9,0x1000,0x1000);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar10 = 0x97e, acphychipid == 0xaa06)))) {
      uVar10 = 0x96b;
    }
    uVar9 = 4;
    uVar6 = 4;
LAB_001a0d9d:
    mod_radio_reg(param_1,uVar10,uVar6,uVar9);
  }
  else {
    if (*(char *)(param_1 + 0x16e) == '\x01') {
      mod_radio_reg(param_1,0x97f,0x4000,0x4000);
      mod_radio_reg(param_1,0x980,0x800,0x800);
      mod_radio_reg(param_1,0x97f,0x800,0x800);
      mod_radio_reg(param_1,0x97f,0x8000,0x8000);
      mod_radio_reg(param_1,0x97f,0x1000,0x1000);
      mod_radio_reg(param_1,0x97f,4,4);
    }
    if (*(char *)(param_1 + 0x16e) == '\x02') {
      mod_radio_reg(param_1,0x970,0x10,0x10);
    }
    write_radio_reg(param_1,0x792,1);
    mod_radio_reg(param_1,0x992,1,1);
    if (*(char *)(param_1 + 0x16e) == '\x02') {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar7 = 0xc;
        uVar5 = 0x400;
      }
      else {
        uVar7 = 0x11;
        uVar5 = 0x800;
      }
      mod_radio_reg(param_1,uVar7 | uVar5,1,1);
      mod_radio_reg(param_1,0x970,1,1);
      si_pmu_chipcontrol(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),0,0xffc00,0x66800);
      uVar9 = 1;
      uVar6 = 1;
      uVar10 = 0x98a;
      goto LAB_001a0d9d;
    }
  }
  if (*(byte *)(param_1 + 0x16e) < 2) {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar9 = 0x807, acphychipid == 0xaa06)))) {
      uVar9 = 0x407;
    }
    mod_radio_reg(param_1,uVar9,2,2);
  }
  if (*(byte *)(param_1 + 0x16e) < 2) {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar7 = 0x15e;
      uVar5 = 0x400;
    }
    else {
      uVar7 = 0x171;
      uVar5 = 0x800;
    }
    mod_radio_reg(param_1,uVar7 | uVar5,0x10,0x10);
  }
  for (local_48 = 0; local_48 < *(byte *)(param_1 + 0x168); local_48 = local_48 + 1) {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x138, acphychipid == 0xaa06)))) {
      uVar3 = 0x126;
    }
    uVar4 = (ushort)local_48 << 9;
    mod_radio_reg(param_1,uVar3 | uVar4,0x300,0x100);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x139, acphychipid == 0xaa06)))) {
      uVar3 = 0x127;
    }
    mod_radio_reg(param_1,uVar3 | uVar4,3,2);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar3 = 0x76, acphychipid == 0xaa06)) {
      uVar3 = 0x6f;
    }
    mod_radio_reg(param_1,uVar3 | uVar4,4,0);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x76, acphychipid == 0xaa06)))) {
      uVar3 = 0x6f;
    }
    mod_radio_reg(param_1,uVar3 | uVar4,1,0);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x76, acphychipid == 0xaa06)))) {
      uVar3 = 0x6f;
    }
    mod_radio_reg(param_1,uVar3 | uVar4,2,0);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar3 = 0x6c, acphychipid == 0xaa06)) {
      uVar3 = 0x65;
    }
    mod_radio_reg(param_1,uVar3 | uVar4,1,0);
  }
  sVar11 = 0;
  if ((byte)(*(char *)(param_1 + 0x16c) - 7U) < 2) {
    for (; (byte)sVar11 < *(byte *)(param_1 + 0x168); sVar11 = sVar11 + 1) {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar3 = 0x43, acphychipid == 0xaa06)))) {
        uVar3 = 0x3c;
      }
      uVar4 = sVar11 << 9;
      mod_radio_reg(param_1,uVar3 | uVar4,2,2);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar3 = 0x16e;
      }
      else {
        uVar3 = 0x181;
        uVar4 = 0x800;
      }
      mod_radio_reg(param_1,uVar3 | uVar4,8,8);
    }
  }
switchD_001a09e8_caseD_5:
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (acphychipid == 0xaa06)) {
    uVar7 = 0xc;
    uVar5 = 0x400;
  }
  else {
    uVar7 = 0x11;
    uVar5 = 0x800;
  }
  mod_radio_reg(param_1,uVar7 | uVar5,0x10,0);
  phy_reg_write(param_1,0x408,uVar2 | 6);
  osl_delay(100);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
    uVar7 = 0xc;
    uVar5 = 0x400;
  }
  else {
    uVar7 = 0x11;
    uVar5 = 0x800;
  }
  mod_radio_reg(param_1,uVar7 | uVar5,0x10,0x10);
  phy_reg_write(param_1,0x417,0xd);
  phy_reg_write(param_1,0x408,uVar2 | 2);
  phy_reg_write(param_1,0x728,uVar1 | 0x180);
  osl_delay(100);
  phy_reg_write(param_1,0x417,4);
  phy_reg_write(param_1,0x728,uVar1 & 0xfeff);
  return;
}

