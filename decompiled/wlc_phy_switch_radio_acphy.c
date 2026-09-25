
void wlc_phy_switch_radio_acphy(long param_1,char param_2)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  undefined8 uVar5;
  char cVar6;
  short sVar7;
  ushort uVar8;
  uint uVar9;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if (param_2 == '\0') {
    *(undefined1 *)(param_1 + 0xf88) = 0;
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar5 = 0x73e, acphychipid == 0x4350)))) {
      uVar5 = 0x173e;
    }
    phy_reg_write(param_1,uVar5,0x1c00);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 ||
        ((acphychipid == 0xaa06 || (uVar5 = 0x739, acphychipid == 0x4350)))))) {
      uVar5 = 0x1739;
    }
    phy_reg_write(param_1,uVar5,0);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar5 = 0x73a, acphychipid == 0x4350)))) {
      uVar5 = 0x173a;
    }
    phy_reg_write(param_1,uVar5,0);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 ||
        ((acphychipid == 0xaa06 || (uVar5 = 0x725, acphychipid == 0x4350)))))) {
      uVar5 = 0x1725;
    }
    phy_reg_write(param_1,uVar5,0x1fff);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar5 = 0x729, acphychipid == 0x4350)))) {
      uVar5 = 0x1729;
    }
    phy_reg_write(param_1,uVar5,0);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 ||
        ((acphychipid == 0xaa06 || (uVar5 = 0x721, acphychipid == 0x4350)))))) {
      uVar5 = 0x1721;
    }
    phy_reg_write(param_1,uVar5,0xffff);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar5 = 0x728, acphychipid == 0x4350)))) {
      uVar5 = 0x1728;
    }
    phy_reg_write(param_1,uVar5,0);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 ||
        ((acphychipid == 0xaa06 || (uVar5 = 0x720, acphychipid == 0x4350)))))) {
      uVar5 = 0x1720;
    }
    phy_reg_write(param_1,uVar5,0x3ff);
    phy_reg_mod(param_1,0x408,2,0);
    phy_reg_write(param_1,0x417,0);
    phy_reg_write(param_1,0x416,1);
    if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4335) {
      mod_radio_reg(param_1,0x97f,0x10,0x10);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x8f2, acphychipid == 0xaa06)) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,1,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,2,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x100,0);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x8f2, acphychipid == 0xaa06)) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x40,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x80,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x10,0);
    }
  }
  else if (*(char *)(param_1 + 0xf88) == '\0') {
    wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    if (*(char *)(param_1 + 0x16e) == '\x01') {
      FUN_00190879(param_1);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x80c, acphychipid == 0xaa06)) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x80,0x80);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x80c, acphychipid == 0xaa06)))) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x10,0x10);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x80c, acphychipid == 0xaa06)))) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,8,8);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x80c, acphychipid == 0xaa06)) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,4,4);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x80c, acphychipid == 0xaa06)))) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,2,2);
      osl_delay(100);
      mod_radio_reg(param_1,0x97f,0x10,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,1,1);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x8f2, acphychipid == 0xaa06)) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x100,0x100);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x10,0x10);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x80c, acphychipid == 0xaa06)))) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x20,0x20);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x80c, acphychipid == 0xaa06)) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x2000,0x2000);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x80c, acphychipid == 0xaa06)))) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x4000,0x4000);
      cVar6 = '\0';
      do {
        uVar3 = read_radio_reg(param_1,0x80b);
        if ((uVar3 & 1) != 0) break;
        cVar6 = cVar6 + '\x01';
        osl_delay(100);
      } while (cVar6 != 'e');
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x80c, acphychipid == 0xaa06)))) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x4000,0);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x80c, acphychipid == 0xaa06)) {
        uVar5 = 0x80b;
      }
      mod_radio_reg(param_1,uVar5,0x2000,0);
    }
    else if (*(char *)(param_1 + 0x16e) == '\x02') {
      cVar6 = '\0';
      FUN_00190fbd(param_1);
      write_radio_reg(param_1,0x60c,0x9e);
      osl_delay(100);
      write_radio_reg(param_1,0x60c,0xbe);
      write_radio_reg(param_1,0x60c,0x20be);
      write_radio_reg(param_1,0x60c,0x60be);
      do {
        uVar3 = read_radio_reg(param_1,0xb);
        if (((uVar3 & 1) != 0) && (uVar3 = read_radio_reg(param_1,0x20b), (uVar3 & 1) != 0)) break;
        cVar6 = cVar6 + '\x01';
        osl_delay(100);
      } while (cVar6 != 'e');
      write_radio_reg(param_1,0x60c,0xbe);
    }
    FUN_001a08b2(param_1);
    phy_reg_mod(param_1,0x16b,0x400,0);
    osl_delay(3);
    phy_reg_write(param_1,0x175,0);
    osl_delay(3);
    if (*(char *)(*(long *)(param_1 + 0x138) + 0x34e) == '\x01') {
      uVar9 = (uint)*(ushort *)(*(long *)(param_1 + 0x20) + 0xf2);
    }
    else if (*(char *)(*(long *)(param_1 + 0x138) + 0x345) == '\x01') {
      uVar9 = 9;
      if ((*(char *)(param_1 + 0x16e) != '\x02') &&
         (uVar9 = 10, *(char *)(param_1 + 0x16e) != '\x01')) {
        uVar9 = 0;
      }
    }
    else {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x40,0x40);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x80,0x80);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x8f5, acphychipid == 0xaa06)) {
        uVar5 = 0x8ed;
      }
      mod_radio_reg(param_1,uVar5,0x600,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f5, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ed;
      }
      mod_radio_reg(param_1,uVar5,0x1800,0);
      sVar7 = 0;
      if (*(char *)(param_1 + 0x16e) == '\x02') {
        for (; (byte)sVar7 < *(byte *)(param_1 + 0x168); sVar7 = sVar7 + 1) {
          mod_radio_reg(param_1,sVar7 << 9 | 0x15b,1,1);
        }
        write_radio_reg(param_1,0x75c,0);
        write_radio_reg(param_1,0x75d,0);
        write_radio_reg(param_1,0x75e,0);
        write_radio_reg(param_1,0x75f,0);
        write_radio_reg(param_1,0x960,0);
        write_radio_reg(param_1,0x961,0);
        write_radio_reg(param_1,0x963,0);
        uVar4 = 0x965;
      }
      else {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar2 = 0x148;
          uVar4 = 0x400;
        }
        else {
          uVar2 = 0x15b;
          uVar4 = 0x800;
        }
        mod_radio_reg(param_1,uVar4 | uVar2,1,1);
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (acphychipid == 0xaa06)) {
          uVar2 = 0x149;
          uVar4 = 0x400;
        }
        else {
          uVar2 = 0x15c;
          uVar4 = 0x800;
        }
        write_radio_reg(param_1,uVar4 | uVar2,0);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar2 = 0x14a;
          uVar4 = 0x400;
        }
        else {
          uVar2 = 0x15d;
          uVar4 = 0x800;
        }
        write_radio_reg(param_1,uVar4 | uVar2,0);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar2 = 0x14b;
          uVar4 = 0x400;
        }
        else {
          uVar2 = 0x15e;
          uVar4 = 0x800;
        }
        write_radio_reg(param_1,uVar4 | uVar2,0);
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (acphychipid == 0xaa06)) {
          uVar2 = 0x14c;
          uVar4 = 0x400;
        }
        else {
          uVar2 = 0x15f;
          uVar4 = 0x800;
        }
        uVar4 = uVar4 | uVar2;
      }
      write_radio_reg(param_1,uVar4,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar2 = 0x10, acphychipid == 0xaa06)))) {
        uVar2 = 0xb;
      }
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar4 = 0x400;
      }
      else {
        uVar4 = 0x800;
        if (acphychipid == 0x4350) {
          uVar4 = 0;
        }
      }
      mod_radio_reg(param_1,uVar2 | uVar4,1,0);
      osl_delay(1);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar2 = 0x10, acphychipid == 0xaa06)) {
        uVar2 = 0xb;
      }
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar4 = 0x400;
      }
      else {
        uVar4 = 0x800;
        if (acphychipid == 0x4350) {
          uVar4 = 0;
        }
      }
      sVar7 = 0;
      mod_radio_reg(param_1,uVar2 | uVar4,1,1);
      do {
        osl_delay(10);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar2 = 0x10, acphychipid == 0xaa06)))) {
          uVar2 = 0xb;
        }
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (acphychipid == 0xaa06)) {
          uVar4 = 0x400;
        }
        else {
          uVar4 = 0x800;
          if (acphychipid == 0x4350) {
            uVar4 = 0;
          }
        }
        uVar3 = read_radio_reg(param_1,uVar4 | uVar2);
      } while (((uVar3 & 8) == 0) && (sVar7 = sVar7 + 1, sVar7 != 100));
      if (((acphychipid == 0x4352) || ((acphychipid == 0x4360 || (acphychipid == 0xa9c4)))) ||
         (uVar2 = 0x10, acphychipid == 0xaa06)) {
        uVar2 = 0xb;
      }
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (acphychipid == 0xaa06)) {
        uVar4 = 0x400;
      }
      else {
        uVar4 = 0x800;
        if (acphychipid == 0x4350) {
          uVar4 = 0;
        }
      }
      sVar7 = 0;
      read_radio_reg(param_1,uVar2 | uVar4);
      if (*(char *)(param_1 + 0x16e) == '\x02') {
        for (; (byte)sVar7 < *(byte *)(param_1 + 0x168); sVar7 = sVar7 + 1) {
          mod_radio_reg(param_1,sVar7 << 9 | 0x15b,1,0);
        }
      }
      else {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar2 = 0x148;
          uVar4 = 0x400;
        }
        else {
          uVar2 = 0x15b;
          uVar4 = 0x800;
        }
        mod_radio_reg(param_1,uVar4 | uVar2,1,0);
      }
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x8f2, acphychipid == 0xaa06)))) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x40,0);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x8f2, acphychipid == 0xaa06)) {
        uVar5 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar5,0x80,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar2 = 0x10, acphychipid == 0xaa06)))) {
        uVar2 = 0xb;
      }
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar4 = 0x400;
      }
      else {
        uVar4 = 0x800;
        if (acphychipid == 0x4350) {
          uVar4 = 0;
        }
      }
      uVar9 = 0;
      mod_radio_reg(param_1,uVar2 | uVar4,1,0);
    }
    if ((*(char *)(*(long *)(param_1 + 0x138) + 0x345) == '\x01') ||
       (*(char *)(*(long *)(param_1 + 0x138) + 0x34e) == '\x01')) {
      if (*(char *)(param_1 + 0x16e) == '\x02') {
        for (sVar7 = 0; (byte)sVar7 < *(byte *)(param_1 + 0x168); sVar7 = sVar7 + 1) {
          uVar8 = sVar7 << 9 | 0x171;
          mod_radio_reg(param_1,sVar7 << 9 | 7,0xf0,(uVar9 & 0xfff) << 4);
          mod_radio_reg(param_1,uVar8,4,4);
          mod_radio_reg(param_1,uVar8,2,0);
        }
      }
      else if (*(char *)(param_1 + 0x16e) == '\x01') {
        mod_radio_reg(param_1,0x807,0xf0,(uVar9 & 0xfff) << 4);
        mod_radio_reg(param_1,0x971,4,4);
        mod_radio_reg(param_1,0x971,2,0);
      }
    }
    FUN_0019665e(param_1);
    if (*(char *)(lVar1 + 0x32d) != '\0') {
      FUN_001a1202(param_1);
      FUN_001a7dc9(param_1,*(undefined2 *)(param_1 + 0x17e));
    }
    *(undefined1 *)(param_1 + 0xf88) = 1;
    wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  lVar1 = *(long *)(param_1 + 0x20);
  if (*(int *)(lVar1 + 0x3c) == 0x4335) {
    if ((*(byte *)(*(long *)(lVar1 + 0x18) + 0x48) & 4) != 0) {
      return;
    }
  }
  else {
    if (*(int *)(lVar1 + 0x3c) != 0x4350) {
      return;
    }
    if ((*(uint *)(*(long *)(lVar1 + 0x18) + 0x48) & 0x700000) == 0x100000) {
      return;
    }
  }
  if (*(char *)(param_1 + 0x16e) != '\0') {
    mod_radio_reg(param_1,0x8f2,0x200,0);
  }
  return;
}

