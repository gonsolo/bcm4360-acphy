
void FUN_001a1924(long param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined4 local_58 [12];
  
  bVar8 = 0;
  phy_reg_or(param_1,0x19e,0x1c0);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    phy_reg_write(param_1,0x3c4,0x668);
  }
  phy_reg_mod(param_1,0x19e,0x200,0x200);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
    phy_reg_mod(param_1,0x19e,0x3c,0);
    phy_reg_mod(param_1,0x19e,1,1);
    uVar3 = 0;
    uVar5 = 1;
  }
  else {
    uVar3 = 0x10;
    uVar5 = 0x3c;
  }
  phy_reg_mod(param_1,0x19e,uVar5,uVar3);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
    phy_reg_write(param_1,0x400,0);
  }
  phy_reg_write(param_1,0x1f2,200);
  if (*(uint *)(param_1 + 0x164) < 2) {
    phy_reg_write(param_1,0x26,0x92);
  }
  phy_reg_write(param_1,0x1ed,0x50);
  phy_reg_write(param_1,0x25,0x30);
  si_core_cflags(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),0x10,0x10);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
    uVar3 = 0x200;
  }
  else {
    uVar3 = 0;
  }
  phy_reg_mod(param_1,0x40f,0x200,uVar3);
  phy_reg_mod(param_1,0x2f1,0x20,0);
  phy_reg_mod(param_1,0x2ed,0x20,0);
  phy_reg_mod(param_1,0x2f9,0x20,0);
  phy_reg_mod(param_1,0x2f5,0x20,0);
  if (*(int *)(param_1 + 0x164) != 3) {
    phy_reg_mod(param_1,0x2ef,0xff,0x55);
    phy_reg_mod(param_1,0x2eb,0xff,0x55);
    phy_reg_mod(param_1,0x2f7,0xff,0x55);
    phy_reg_mod(param_1,0x2f3,0xff,0x55);
  }
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 != 5) && (iVar2 != 2)) && (iVar2 != 6)) goto LAB_001a1e69;
  puVar6 = &DAT_00559050;
  puVar7 = local_58;
  for (lVar4 = 10; lVar4 != 0; lVar4 = lVar4 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (ulong)bVar8 * -2 + 1;
    puVar7 = puVar7 + (ulong)bVar8 * -2 + 1;
  }
  phy_reg_mod(param_1,0x2ef,0xff,0x4d);
  phy_reg_mod(param_1,0x2eb,0xff,0x4d);
  phy_reg_mod(param_1,0x2f7,0xff,0x4d);
  phy_reg_mod(param_1,0x2f3,0xff,0x4d);
  phy_reg_mod(param_1,0x31c,0xffff,0x80);
  phy_reg_mod(param_1,0x31e,0xffff,0x80);
  phy_reg_mod(param_1,0x31d,0xffff,0x80);
  phy_reg_mod(param_1,799,0xffff,0x80);
  phy_reg_write(param_1,0x1e1,0x40);
  phy_reg_write(param_1,0x1e2,0x5c);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    cVar1 = *(char *)(*(long *)(param_1 + 0x138) + 0x346);
LAB_001a1c81:
    if (cVar1 == '\0') goto LAB_001a1c9c;
    phy_reg_write(param_1,0x1e3,0x3a);
    uVar3 = 0x14;
  }
  else {
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
      cVar1 = *(char *)(*(long *)(param_1 + 0x138) + 0x347);
      goto LAB_001a1c81;
    }
LAB_001a1c9c:
    phy_reg_write(param_1,0x1e3,0x48);
    uVar3 = 0x18;
  }
  phy_reg_write(param_1,0x197,uVar3);
  phy_reg_mod(param_1,0x29e,1,0);
  phy_reg_mod(param_1,0x29d,0x40,0x40);
  phy_reg_mod(param_1,0x363,0x3ff,0);
  phy_reg_mod(param_1,0x176,1,0);
  phy_reg_mod(param_1,0x176,2,2);
  phy_reg_mod(param_1,0x176,4,4);
  phy_reg_mod(param_1,0x164,0x2000,0x2000);
  wlc_phy_table_write_acphy(param_1,2,0x28,0,8,local_58);
  phy_reg_write(param_1,0x401,0x1111);
  phy_reg_write(param_1,0x1b0,0x9ee1);
  phy_reg_mod(param_1,0x2e0,0xf0,0xb0);
  phy_reg_mod(param_1,0x2e0,0xf,10);
  phy_reg_mod(param_1,0x2d7,0xf00,0x700);
  phy_reg_mod(param_1,0x2d7,0xf0,0x70);
  phy_reg_mod(param_1,0x2d7,0xf,7);
  phy_reg_mod(param_1,0x2d6,0xf000,0x7000);
  phy_reg_mod(param_1,0x2d6,0xf00,0x700);
  phy_reg_mod(param_1,0x2d6,0xf0,0x30);
  phy_reg_mod(param_1,0x2d6,0xf,2);
LAB_001a1e69:
  if (*(int *)(param_1 + 0x164) == 3) {
    FUN_00190fbd(param_1);
    phy_reg_mod(param_1,0x2d7,0xf00,0x700);
    phy_reg_mod(param_1,0x2d7,0xf0,0x70);
    phy_reg_mod(param_1,0x2d7,0xf,7);
    phy_reg_mod(param_1,0x2d6,0xf000,0x7000);
    phy_reg_mod(param_1,0x2d6,0xf00,0x700);
    phy_reg_mod(param_1,0x2d6,0xf0,0x30);
    phy_reg_mod(param_1,0x2d6,0xf,2);
  }
  phy_reg_write(param_1,0x400,0);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || ((iVar2 == 6 || (iVar2 == 3)))) {
    uVar3 = 0x1000;
  }
  else {
    uVar3 = 0;
  }
  phy_reg_mod(param_1,0x1ca,0x1000,uVar3);
  wlc_phy_resetcca_acphy(param_1);
  phy_reg_mod(param_1,0x72,4,4);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
    phy_reg_write(param_1,0x198,0x10);
  }
  phy_reg_mod(param_1,0x1b0,0x20,0);
  phy_reg_mod(param_1,0x1b1,0x1000,0x1000);
  phy_reg_mod(param_1,0x1b6,0x8000,0);
  for (bVar8 = 0; bVar8 < *(byte *)(param_1 + 0x168); bVar8 = bVar8 + 1) {
    uVar3 = 0x690;
    if ((bVar8 != 0) && (uVar3 = 0xa90, bVar8 == 1)) {
      uVar3 = 0x890;
    }
    phy_reg_mod(param_1,uVar3,0x200,0x200);
    uVar3 = 0x690;
    if ((bVar8 != 0) && (uVar3 = 0xa90, bVar8 == 1)) {
      uVar3 = 0x890;
    }
    phy_reg_mod(param_1,uVar3,0x400,0x400);
  }
  phy_reg_write(param_1,0x1e6,0x30);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
    phy_reg_write(param_1,0x160,0x29);
    phy_reg_write(param_1,0x400,0x111);
    FUN_00190879(param_1);
  }
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || ((iVar2 == 6 || (iVar2 == 3)))) {
    phy_reg_write(param_1,0x20,0x12);
    phy_reg_write(param_1,0x27,0x2a8);
  }
  if (((*(byte *)(*(long *)(param_1 + 0x20) + 0x84) & 2) == 0) &&
     ((*(byte *)(*(long *)(param_1 + 0x20) + 0x88) & 2) == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  wlc_phy_hwaci_setup_acphy(param_1,0,uVar3);
  phy_reg_write(param_1,0x358,0xc07f);
  return;
}

