
void FUN_0019b279(long param_1,char param_2)

{
  long lVar1;
  bool bVar2;
  ushort uVar3;
  long lVar4;
  undefined2 uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  undefined1 *puVar9;
  byte *pbVar10;
  undefined1 *puVar11;
  undefined2 *puVar12;
  byte *pbVar13;
  byte bVar14;
  byte bVar15;
  uint uVar16;
  undefined2 local_78 [16];
  byte local_58 [16];
  undefined1 local_48 [24];
  
  lVar1 = *(long *)(param_1 + 0x138);
  puVar9 = &DAT_00558c30;
  puVar11 = local_48;
  for (lVar4 = 0xd; lVar4 != 0; lVar4 = lVar4 + -1) {
    *puVar11 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar11 = puVar11 + 1;
  }
  puVar9 = &DAT_00558c10;
  puVar12 = local_78;
  for (lVar4 = 0x1a; lVar4 != 0; lVar4 = lVar4 + -1) {
    *(undefined1 *)puVar12 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar12 = (undefined2 *)((long)puVar12 + 1);
  }
  pbVar10 = &DAT_00558c00;
  pbVar13 = local_58;
  for (lVar4 = 0xd; lVar4 != 0; lVar4 = lVar4 + -1) {
    *pbVar13 = *pbVar10;
    pbVar10 = pbVar10 + 1;
    pbVar13 = pbVar13 + 1;
  }
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  uVar3 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  if (param_2 == '\0') {
    FUN_0019058d(param_1,0x36);
    FUN_001918b7(param_1,0);
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0) goto LAB_0019b585;
    phy_reg_write(param_1,0x299,0x4477);
    uVar5 = 0x10;
  }
  else {
    FUN_0019173d(param_1);
    bVar15 = 0x18;
    if (*(byte *)(lVar1 + 0x669) < 0x19) {
      bVar15 = *(byte *)(lVar1 + 0x669);
    }
    *(byte *)(lVar1 + 0x657) = bVar15;
    bVar14 = 0x30;
    if (*(byte *)(lVar1 + 0x668) < 0x31) {
      bVar14 = *(byte *)(lVar1 + 0x668);
    }
    *(byte *)(lVar1 + 0x656) = bVar14;
    FUN_001918b7(param_1,bVar14 != 0);
    bVar14 = (bVar14 - 1) + (bVar14 == 0);
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      uVar16 = (int)(bVar15 + 1) >> 1;
      if (0xc < uVar16) {
        uVar16 = 0xc;
      }
      bVar15 = local_58[uVar16];
    }
    else {
      uVar16 = 0;
      bVar15 = bVar14;
    }
    bVar7 = 0xc;
    if (bVar15 < 0xd) {
      bVar7 = bVar15;
    }
    uVar6 = (uint)bVar14 - (uint)bVar7;
    uVar8 = 0x1e;
    if (((int)uVar6 < 0x1f) && (uVar8 = 0, -1 < (int)uVar6)) {
      uVar8 = uVar6;
    }
    if (*(char *)(lVar1 + 0x65c) == *(char *)(lVar1 + 0x66e)) {
      bVar2 = false;
      if (*(char *)(lVar1 + 0x658) != *(char *)(lVar1 + 0x66a)) goto LAB_0019b41f;
    }
    else {
LAB_0019b41f:
      FUN_0019a398(param_1,1);
      bVar2 = true;
    }
    if ((*(char *)(lVar1 + 0x65c) != *(char *)(lVar1 + 0x66e)) ||
       (*(char *)(lVar1 + 0x659) != *(char *)(lVar1 + 0x66b))) {
      FUN_0019a398(param_1,2);
      bVar2 = true;
    }
    if (*(char *)(lVar1 + 0x65a) != *(char *)(lVar1 + 0x66c)) {
      FUN_0019a60c(param_1,1);
      bVar2 = true;
    }
    if (*(char *)(lVar1 + 0x65b) == *(char *)(lVar1 + 0x66d)) {
      if (bVar2) goto LAB_0019b4a7;
    }
    else {
      FUN_0019a60c(param_1,2);
LAB_0019b4a7:
      FUN_0019ae61(param_1);
    }
    for (bVar15 = 0; bVar15 < *(byte *)(param_1 + 0x168); bVar15 = bVar15 + 1) {
      if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (bVar15 & 0x1f) & 1) != 0) {
        FUN_0019ac69(param_1,0,'E' - bVar7,*(undefined1 *)(lVar1 + 0x66e));
      }
    }
    bVar15 = *(byte *)(*(long *)(param_1 + 0x138) + 0x42);
    bVar7 = (char)((int)((uVar8 & 0xff) * 0x58) >> 5) + 0x36;
    if (bVar7 < bVar15) {
      bVar7 = bVar15;
    }
    FUN_0019015b(param_1,bVar7,0,0);
    uVar8 = bVar14 - 0x15;
    if ((int)uVar8 < 0) {
      uVar8 = 0;
    }
    FUN_0019058d(param_1,((int)((uVar8 & 0xff) * 0x58) >> 5) + 0x36U & 0xff);
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0) goto LAB_0019b585;
    phy_reg_write(param_1,0x299,CONCAT11(0x44,local_48[uVar16]));
    uVar5 = local_78[uVar16];
  }
  phy_reg_write(param_1,0x3c1,uVar5);
LAB_0019b585:
  wlc_phy_aci_updsts_acphy(param_1);
  phy_reg_mod(param_1,0x19e,2,uVar3 & 2);
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return;
}

