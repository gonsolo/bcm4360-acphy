
void wlc_phy_radio_override_acphy(long param_1,char param_2)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  short sVar4;
  undefined1 *puVar5;
  
  puVar5 = (undefined1 *)&ovr_regs_2069_rev32;
  if ((*(char *)(param_1 + 0x16e) != '\x02') &&
     (puVar5 = ovr_regs_2069_rev2, *(char *)(param_1 + 0x16e) == '\x01')) {
    puVar5 = (undefined1 *)&ovr_regs_2069_rev16;
  }
  while( true ) {
    sVar4 = *(short *)puVar5;
    puVar5 = (undefined1 *)((long)puVar5 + 2);
    if (sVar4 == -1) break;
    write_radio_reg(param_1,sVar4,~-(ushort)(param_2 == '\0'));
  }
  sVar4 = 0;
  if (*(char *)(param_1 + 0x16e) == '\x02') {
    for (; (byte)sVar4 < *(byte *)(param_1 + 0x168); sVar4 = sVar4 + 1) {
      mod_radio_reg(param_1,sVar4 << 9 | 0x171,2,0);
    }
  }
  else {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (acphychipid == 0xaa06)) {
      uVar2 = 0x15e;
      uVar1 = 0x400;
    }
    else {
      uVar2 = 0x171;
      uVar1 = 0x800;
    }
    mod_radio_reg(param_1,uVar2 | uVar1,2,0);
  }
  if (*(char *)(param_1 + 0x16e) == '\0') {
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 || (uVar3 = 0x97e, acphychipid == 0xaa06)))) {
      uVar3 = 0x96b;
    }
  }
  else {
    uVar3 = 0x97f;
  }
  mod_radio_reg(param_1,uVar3,0x200,0);
  return;
}

