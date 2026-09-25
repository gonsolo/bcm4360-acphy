
void FUN_00195603(long param_1)

{
  undefined2 uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  
  lVar2 = *(long *)(param_1 + 0x138);
  for (uVar6 = 0; uVar6 < *(byte *)(param_1 + 0x168); uVar6 = uVar6 + 1) {
    uVar4 = (uint)uVar6;
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar3 = 0x1f, acphychipid == 0xaa06)) {
      uVar3 = 0x1a;
    }
    uVar5 = uVar4 << 9;
    write_radio_reg(param_1,uVar3 | uVar5 & 0xffff,
                    *(undefined2 *)(lVar2 + 0x48 + (long)(int)uVar4 * 2));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x20, acphychipid == 0xaa06)))) {
      uVar3 = 0x1b;
    }
    write_radio_reg(param_1,uVar3 | uVar5 & 0xffff,
                    *(undefined2 *)(lVar2 + 0x70 + (long)(int)uVar4 * 2));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x21, acphychipid == 0xaa06)))) {
      uVar3 = 0x1c;
    }
    write_radio_reg(param_1,uVar3 | uVar5 & 0xffff,
                    *(undefined2 *)(lVar2 + 0x78 + (long)(int)uVar4 * 2));
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar3 = 0x23, acphychipid == 0xaa06)) {
      uVar3 = 0x1e;
    }
    write_radio_reg(param_1,uVar3 | uVar5 & 0xffff,
                    *(undefined2 *)(lVar2 + 0x50 + (long)(int)uVar4 * 2));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x24, acphychipid == 0xaa06)))) {
      uVar3 = 0x1f;
    }
    write_radio_reg(param_1,uVar3 | uVar5 & 0xffff,
                    *(undefined2 *)(lVar2 + 0x68 + (long)(int)uVar4 * 2));
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x29, acphychipid == 0xaa06)))) {
      uVar3 = 0x24;
    }
    write_radio_reg(param_1,uVar3 | uVar5 & 0xffff,
                    *(undefined2 *)(lVar2 + 0x80 + (long)(int)uVar4 * 2));
    if (*(char *)(param_1 + 0x16e) == '\0') {
      uVar1 = *(undefined2 *)(lVar2 + 0x58 + (long)(int)uVar4 * 2);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar4 = 0x183, acphychipid == 0xaa06)) {
        uVar4 = 0x170;
      }
      uVar4 = uVar4 | uVar5 & 0xffff;
    }
    else {
      uVar1 = *(undefined2 *)(lVar2 + 0x60 + (long)(int)uVar4 * 2);
      uVar4 = (uint)(ushort)((ushort)uVar5 | 0x184);
    }
    write_radio_reg(param_1,uVar4,uVar1);
  }
  return;
}

