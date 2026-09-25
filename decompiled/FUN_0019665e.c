
void FUN_0019665e(long param_1)

{
  long lVar1;
  bool bVar2;
  undefined1 uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  char cVar10;
  byte *pbVar11;
  undefined2 *puVar12;
  byte *local_98;
  byte *local_90;
  ushort local_88;
  undefined2 local_78 [8];
  byte local_68 [16];
  byte local_58 [16];
  byte local_48 [24];
  
  local_48[0] = 1;
  local_48[1] = 0;
  local_48[2] = 0;
  local_58[0] = 0;
  local_58[1] = 2;
  local_58[2] = 1;
  local_68[0] = 0x1c;
  local_68[1] = 0x70;
  local_68[2] = 0x40;
  local_78[0] = 0x14a;
  local_78[1] = 0x101;
  local_78[2] = 0x11a;
  lVar1 = *(long *)(param_1 + 0x138);
  local_88 = 0xc1;
  if (*(char *)(param_1 + 0x16e) != '\0') {
    if ((*(int *)(param_1 + 0xc24) == 40000000) || (*(int *)(param_1 + 0xc24) != 37400000)) {
      local_88 = 0xa0;
    }
    else {
      local_78[0] = 0x22d;
      local_78[1] = 0xf0;
      local_78[2] = 0x10a;
      local_88 = 0x9e;
    }
  }
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     (uVar9 = 0x8f2, acphychipid == 0xaa06)) {
    uVar9 = 0x8ea;
  }
  mod_radio_reg(param_1,uVar9,0x80,0x80);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || (uVar9 = 0x8f5, acphychipid == 0xaa06)))) {
    uVar9 = 0x8ed;
  }
  mod_radio_reg(param_1,uVar9,0x600,0x400);
  local_98 = local_68;
  local_90 = local_58;
  pbVar11 = local_48;
  puVar12 = local_78;
  cVar10 = '\0';
  uVar6 = (uint)local_88;
  do {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar8 = 0x10;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x15;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,0x1000,(*pbVar11 & 0xf) << 0xc);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar8 = 0x10;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x15;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,0x18,(uint)*local_90 << 3);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar8 = 0x11;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x16;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,0xff00,(uint)*local_98 << 8);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar8 = 0x12;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x17;
      uVar7 = 0x800;
    }
    write_radio_reg(param_1,uVar8 | uVar7,*puVar12);
    local_88 = 0;
    if (cVar10 == '\x02') {
      while ((byte)local_88 < *(byte *)(param_1 + 0x168)) {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (uVar7 = 0x12f, acphychipid == 0xaa06)) {
          uVar7 = 0x11d;
        }
        mod_radio_reg(param_1,uVar7 | ((byte)local_88 & 0x7f) << 9,4,0);
        if (*(char *)(param_1 + 0x16e) == '\0') {
          if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
             ((acphychipid == 0xa9c4 || (uVar4 = 0x184, acphychipid == 0xaa06)))) {
            uVar4 = 0x171;
          }
          uVar4 = uVar4 | local_88 << 9;
        }
        else {
          uVar4 = local_88 << 9 | 0x185;
        }
        mod_radio_reg(param_1,uVar4,0x2000,0x2000);
        local_88 = (ushort)(byte)((byte)local_88 + 1);
      }
    }
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar8 = 0x10;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x15;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,1,0);
    osl_delay(1);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar8 = 0x10;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x15;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,1,1);
    osl_delay(0x23);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar8 = 0x11;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x16;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,1,1);
    local_88 = 0;
    do {
      osl_delay(100);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
        uVar8 = 0x13;
        uVar7 = 0x400;
      }
      else {
        uVar8 = 0x18;
        uVar7 = 0x800;
      }
      uVar7 = read_radio_reg(param_1,uVar8 | uVar7);
      bVar2 = true;
      if ((char)((uVar7 & 0x10) >> 4) == '\x01') goto LAB_00196aeb;
      local_88 = local_88 + 1;
    } while (local_88 != 100);
    bVar2 = false;
LAB_00196aeb:
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar8 = 0x11;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x16;
      uVar7 = 0x800;
    }
    mod_radio_reg(param_1,uVar8 | uVar7,1,0);
    if (bVar2) {
      if (cVar10 == '\0') {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (acphychipid == 0xaa06)) {
          uVar8 = 0x14;
          uVar7 = 0x400;
        }
        else {
          uVar8 = 0x19;
          uVar7 = 0x800;
        }
        uVar4 = read_radio_reg(param_1,uVar8 | uVar7);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar8 = 0x15;
          uVar7 = 0x400;
        }
        else {
          uVar8 = 0x1a;
          uVar7 = 0x800;
        }
        uVar5 = read_radio_reg(param_1,uVar8 | uVar7);
        uVar3 = (undefined1)(((uint)uVar5 - (uint)uVar4) * uVar6 >> 8);
        *(undefined1 *)(lVar1 + 0x339) = uVar3;
        *(undefined1 *)(lVar1 + 0x33a) = uVar3;
      }
      else if (cVar10 == '\x01') {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           (acphychipid == 0xaa06)) {
          uVar8 = 0x16;
          uVar7 = 0x400;
        }
        else {
          uVar8 = 0x1b;
          uVar7 = 0x800;
        }
        uVar7 = read_radio_reg(param_1,uVar8 | uVar7);
        local_88 = 0;
        while ((byte)local_88 < *(byte *)(param_1 + 0x168)) {
          if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
             ((acphychipid == 0xa9c4 || (uVar4 = 0x138, acphychipid == 0xaa06)))) {
            uVar4 = 0x126;
          }
          mod_radio_reg(param_1,uVar4 | local_88 << 9,0x1f,uVar7 & 0x1f);
          if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
             ((acphychipid == 0xa9c4 || (uVar4 = 0x4a, acphychipid == 0xaa06)))) {
            uVar4 = 0x43;
          }
          mod_radio_reg(param_1,uVar4 | local_88 << 9,0x1f,uVar7 & 0x1f);
          local_88 = (ushort)(byte)((byte)local_88 + 1);
        }
      }
      else {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
          uVar8 = 0x16;
          uVar7 = 0x400;
        }
        else {
          uVar8 = 0x1b;
          uVar7 = 0x800;
        }
        uVar7 = read_radio_reg(param_1,uVar8 | uVar7);
        *(char *)(lVar1 + 0x33b) = (char)((int)(uVar7 & 0x3e0) >> 5);
        for (uVar7 = 0; (byte)uVar7 < *(byte *)(param_1 + 0x168); uVar7 = (uVar7 & 0xff) + 1) {
          if (*(char *)(param_1 + 0x16e) == '\0') {
            if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
               ((acphychipid == 0xa9c4 || (uVar8 = 0x184, acphychipid == 0xaa06)))) {
              uVar8 = 0x171;
            }
            uVar8 = uVar7 << 9 | uVar8;
          }
          else {
            uVar8 = (uint)(ushort)((ushort)(uVar7 << 9) | 0x185);
          }
          mod_radio_reg(param_1,uVar8 & 0xffff,0x2000,0);
        }
      }
    }
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (acphychipid == 0xaa06)))) {
      uVar8 = 0x10;
      uVar7 = 0x400;
    }
    else {
      uVar8 = 0x15;
      uVar7 = 0x800;
    }
    cVar10 = cVar10 + '\x01';
    mod_radio_reg(param_1,uVar8 | uVar7,1,0);
    pbVar11 = pbVar11 + 1;
    puVar12 = puVar12 + 1;
    local_98 = local_98 + 1;
    local_90 = local_90 + 1;
    if (cVar10 == '\x03') {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar9 = 0x8f2, acphychipid == 0xaa06)) {
        uVar9 = 0x8ea;
      }
      mod_radio_reg(param_1,uVar9,0x80,0);
      return;
    }
  } while( true );
}

