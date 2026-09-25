
void FUN_0019454f(long param_1)

{
  long lVar1;
  undefined2 uVar2;
  undefined8 uVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  uint uVar8;
  
  lVar1 = *(long *)(param_1 + 0x138);
  for (uVar7 = 0; uVar7 < *(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar5 = 0x1f, acphychipid == 0xaa06)) {
      uVar5 = 0x1a;
    }
    uVar8 = (uint)uVar7;
    uVar6 = uVar8 << 9;
    uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
    *(undefined2 *)(lVar1 + 0x48 + (long)(int)uVar8 * 2) = uVar2;
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar5 = 0x20, acphychipid == 0xaa06)))) {
      uVar5 = 0x1b;
    }
    uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
    *(undefined2 *)(lVar1 + 0x70 + (long)(int)uVar8 * 2) = uVar2;
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar5 = 0x21, acphychipid == 0xaa06)))) {
      uVar5 = 0x1c;
    }
    uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
    *(undefined2 *)(lVar1 + 0x78 + (long)(int)uVar8 * 2) = uVar2;
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar5 = 0x23, acphychipid == 0xaa06)) {
      uVar5 = 0x1e;
    }
    uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
    *(undefined2 *)(lVar1 + 0x50 + (long)(int)uVar8 * 2) = uVar2;
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar5 = 0x24, acphychipid == 0xaa06)))) {
      uVar5 = 0x1f;
    }
    uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
    *(undefined2 *)(lVar1 + 0x68 + (long)(int)uVar8 * 2) = uVar2;
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar5 = 0x29, acphychipid == 0xaa06)))) {
      uVar5 = 0x24;
    }
    uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
    *(undefined2 *)(lVar1 + 0x80 + (long)(int)uVar8 * 2) = uVar2;
    uVar4 = (ushort)uVar6;
    if (*(char *)(param_1 + 0x16e) == '\0') {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x183, acphychipid == 0xaa06)) {
        uVar5 = 0x170;
      }
      uVar2 = read_radio_reg(param_1,uVar5 | uVar6 & 0xffff);
      *(undefined2 *)(lVar1 + 0x58 + (long)(int)uVar8 * 2) = uVar2;
    }
    else {
      uVar2 = read_radio_reg(param_1,uVar4 | 0x184);
      *(undefined2 *)(lVar1 + 0x60 + (long)(int)uVar8 * 2) = uVar2;
    }
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x1f, acphychipid == 0xaa06)) {
        uVar5 = 0x1a;
      }
      mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0xf0,0xb0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x24, acphychipid == 0xaa06)))) {
        uVar5 = 0x1f;
      }
      mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,4,4);
      if (*(char *)(param_1 + 0x16e) == '\0') {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar5 = 0x183, acphychipid == 0xaa06)))) {
          uVar5 = 0x170;
        }
        mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0x100,0x100);
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (uVar5 = 0x183, acphychipid == 0xaa06)) {
          uVar5 = 0x170;
        }
        uVar5 = uVar5 | uVar6 & 0xffff;
      }
      else {
        mod_radio_reg(param_1,uVar4 | 0x184,0x100,0x100);
        uVar5 = (uint)(uVar4 | 0x184);
      }
      mod_radio_reg(param_1,uVar5,0x4000,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x23, acphychipid == 0xaa06)))) {
        uVar5 = 0x1e;
      }
      uVar3 = 0;
    }
    else {
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x1f, acphychipid == 0xaa06)))) {
        uVar5 = 0x1a;
      }
      mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0xf0,0x80);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x24, acphychipid == 0xaa06)))) {
        uVar5 = 0x1f;
      }
      mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,4,0);
      if (*(char *)(param_1 + 0x16e) == '\0') {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (uVar5 = 0x183, acphychipid == 0xaa06)) {
          uVar5 = 0x170;
        }
        mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0x100,0);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar5 = 0x183, acphychipid == 0xaa06)))) {
          uVar5 = 0x170;
        }
        uVar5 = uVar5 | uVar6 & 0xffff;
      }
      else {
        mod_radio_reg(param_1,uVar4 | 0x184,0x100,0);
        uVar5 = (uint)(uVar4 | 0x184);
      }
      mod_radio_reg(param_1,uVar5,0x4000,0x4000);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x23, acphychipid == 0xaa06)))) {
        uVar5 = 0x1e;
      }
      uVar3 = 4;
    }
    mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,4,uVar3);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar5 = 0x1f, acphychipid == 0xaa06)))) {
      uVar5 = 0x1a;
    }
    mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0x300,0);
    if (*(char *)(param_1 + 0x16e) == '\x01') {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar5 = 0x29, acphychipid == 0xaa06)) {
        uVar5 = 0x24;
      }
      mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0x30,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar5 = 0x29, acphychipid == 0xaa06)))) {
        uVar5 = 0x24;
      }
      mod_radio_reg(param_1,uVar5 | uVar6 & 0xffff,0xe,0);
    }
  }
  return;
}

