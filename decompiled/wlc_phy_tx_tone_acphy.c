
undefined8
wlc_phy_tx_tone_acphy
          (long param_1,int param_2,ushort param_3,char param_4,char param_5,char param_6)

{
  long lVar1;
  ushort uVar2;
  undefined2 uVar3;
  uint *puVar4;
  uint *puVar5;
  ulong uVar6;
  int iVar7;
  undefined8 uVar8;
  int iVar9;
  uint uVar10;
  uint *puVar11;
  undefined8 uVar12;
  byte bVar13;
  ushort uVar14;
  int iVar15;
  int iVar16;
  uint *puVar17;
  undefined2 local_3a [5];
  
  iVar15 = 1;
  lVar1 = *(long *)(param_1 + 0x138);
  if (param_3 != 0) {
    uVar2 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    iVar16 = 0x50;
    if (uVar2 != 0x2000) {
      iVar16 = 0x14;
      if (uVar2 == 0x1800) {
        iVar16 = 0x28;
      }
    }
    iVar15 = iVar16 * 2;
    puVar4 = (uint *)osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),iVar16 << 4);
    if (puVar4 == (uint *)0x0) {
      return 0xffffffff;
    }
    iVar7 = 0;
    puVar5 = puVar4;
    for (uVar2 = 0; uVar14 = (ushort)iVar15, uVar2 < uVar14; uVar2 = uVar2 + 1) {
      wlc_phy_cordic(iVar7,puVar5);
      iVar9 = (uint)param_3 * *puVar5;
      if (iVar9 < 0) {
        uVar10 = -((-iVar9 >> 0xf) + 1 >> 1);
      }
      else {
        uVar10 = (iVar9 >> 0xf) + 1 >> 1;
      }
      *puVar5 = uVar10;
      iVar9 = (uint)param_3 * puVar5[1];
      if (iVar9 < 0) {
        uVar10 = -((-iVar9 >> 0xf) + 1 >> 1);
      }
      else {
        uVar10 = (iVar9 >> 0xf) + 1 >> 1;
      }
      iVar7 = iVar7 + ((param_2 * 0x24) / iVar16 << 0x10) / 100;
      puVar5[1] = uVar10;
      puVar5 = puVar5 + 2;
    }
    uVar2 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    puVar5 = (uint *)osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),iVar16 << 3);
    if (puVar5 != (uint *)0x0) {
      puVar11 = puVar5;
      for (puVar17 = puVar4; puVar17 != puVar4 + (ulong)uVar14 * 2; puVar17 = puVar17 + 2) {
        *puVar11 = (puVar17[1] & 0x3ff) << 10 | *puVar17 & 0x3ff;
        puVar11 = puVar11 + 1;
      }
      wlc_phy_table_write_acphy(param_1,0xe,iVar15,0,0x20,puVar5);
      osl_mfree(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),puVar5,iVar16 << 3);
      phy_reg_mod(param_1,0x19e,2,uVar2 & 2);
    }
    osl_mfree(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),puVar4,iVar16 << 4);
    if (uVar14 == 0) {
      return 0xffffffff;
    }
  }
  bVar13 = 0;
  if (*(char *)(lVar1 + 10) == '\0') {
    for (; bVar13 < *(byte *)(param_1 + 0x168); bVar13 = bVar13 + 1) {
      FUN_00199491(param_1,lVar1 + 2 + (ulong)bVar13 * 2,bVar13);
    }
    *(undefined1 *)(lVar1 + 10) = 1;
  }
  if (param_6 == '\0') {
    if (param_3 != 0) goto LAB_001ac81a;
LAB_001ac7e8:
    local_3a[0] = 0;
  }
  else {
    if (param_3 == 0) goto LAB_001ac7e8;
    local_3a[0] = 0x40;
  }
  for (bVar13 = 0; bVar13 < *(byte *)(param_1 + 0x168); bVar13 = bVar13 + 1) {
    FUN_0019d224(param_1,local_3a,bVar13);
  }
LAB_001ac81a:
  if (param_4 == '\0') {
    wlc_phy_stay_in_carriersearch_acphy(param_1,1);
  }
  if (param_5 == '\x01') {
    phy_reg_or(param_1,0x471,1);
    uVar8 = 6;
    uVar2 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    if ((uVar2 != 0x2000) && (uVar8 = 4, uVar2 != 0x1800)) {
      uVar8 = 2;
    }
    phy_reg_or(param_1,0x471,uVar8);
    wlc_phy_force_rfseq_acphy(param_1,0);
  }
  else {
    phy_reg_and(param_1,0x471,0xfffe);
    phy_reg_write(param_1,0x463,iVar15 - 1U & 0xffff);
    phy_reg_write(param_1,0x461,0xffff);
    phy_reg_write(param_1,0x462,0x3c);
    uVar3 = phy_reg_read(param_1,0x400);
    phy_reg_or(param_1,0x400,1);
    phy_reg_and(param_1,0x460,0xfffb);
    phy_reg_and(param_1,0x460,0xfffe);
    phy_reg_and(param_1,0x382,0x3fff);
    if (param_4 == '\0') {
      uVar8 = 1;
      uVar12 = 0x460;
    }
    else {
      uVar8 = 0x8000;
      uVar12 = 0x382;
    }
    phy_reg_or(param_1,uVar12,uVar8);
    for (iVar15 = 0x3f1; (uVar6 = phy_reg_read(param_1,0x403), (uVar6 & 1) != 0 && (iVar15 != 9));
        iVar15 = iVar15 + -10) {
      osl_delay(10);
    }
    phy_reg_write(param_1,0x400,uVar3);
  }
  if (param_4 == '\0') {
    wlc_phy_stay_in_carriersearch_acphy(param_1,0);
  }
  return 0;
}

