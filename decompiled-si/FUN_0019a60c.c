
void FUN_0019a60c(long param_1,char param_2)

{
  uint uVar1;
  long lVar2;
  undefined8 uVar3;
  byte bVar4;
  undefined *puVar5;
  undefined1 *puVar6;
  undefined1 auStack_28 [16];
  undefined1 auStack_18 [16];
  
  auStack_18[0] = 0xb;
  auStack_18[1] = 0xc;
  puVar5 = &UNK_00558c3d;
  puVar6 = auStack_28;
  for (lVar2 = 7; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  auStack_18[2] = 0xe;
  auStack_18[3] = 0x20;
  auStack_18[4] = 0x24;
  auStack_18[5] = 0x28;
  lVar2 = *(long *)(param_1 + 0x138);
  if (param_2 == '\x01') {
    *(byte *)(lVar2 + 0x65a) = *(byte *)(lVar2 + 0x66c);
    bVar4 = 6;
    uVar1 = 5 - *(byte *)(lVar2 + 0x66c);
    if ((int)uVar1 < 0) {
      uVar1 = 0;
    }
  }
  else {
    *(byte *)(lVar2 + 0x65b) = *(byte *)(lVar2 + 0x66d);
    bVar4 = 7;
    uVar1 = 6 - *(byte *)(lVar2 + 0x66d);
    if ((int)uVar1 < 0) {
      uVar1 = 0;
    }
  }
  while (uVar1 = uVar1 + 1, (byte)uVar1 < bVar4) {
    if (param_2 == '\x01') {
      auStack_18[uVar1 & 0xff] = 0x7f;
    }
    else {
      auStack_28[uVar1 & 0xff] = 0x7f;
    }
  }
  if (param_2 == '\x01') {
    puVar6 = auStack_18;
    uVar3 = 8;
  }
  else {
    puVar6 = auStack_28;
    uVar3 = 0x10;
  }
  wlc_phy_table_write_acphy(param_1,0xb,bVar4,uVar3,8,puVar6);
  return;
}

