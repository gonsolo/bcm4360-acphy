
void wlc_phy_hwaci_setup_acphy(long param_1,char param_2,char param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  undefined2 uVar7;
  uint uVar8;
  long lVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  ushort uVar12;
  undefined4 uVar13;
  undefined8 uVar14;
  ushort uVar15;
  int iVar16;
  uint uVar17;
  byte bVar18;
  short sVar19;
  
  uVar8 = *(uint *)(param_1 + 0x164);
  lVar9 = *(long *)(param_1 + 0x138);
  for (bVar18 = 0; bVar18 < *(byte *)(param_1 + 0x168); bVar18 = bVar18 + 1) {
    uVar14 = 0x728;
    if ((bVar18 != 0) && (uVar14 = 0xb28, bVar18 == 1)) {
      uVar14 = 0x928;
    }
    phy_reg_mod(param_1,uVar14,0x3800,(uint)(param_2 != '\0') << 0xb);
    uVar14 = 0x721;
    if ((bVar18 != 0) && (uVar14 = 0xb21, bVar18 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x4000,0x4000);
  }
  if (param_3 != '\0') {
    uVar6 = *(ushort *)(lVar9 + 0x672);
    uVar7 = *(undefined2 *)(lVar9 + 0x676);
    uVar10 = (undefined2)*(undefined4 *)(lVar9 + 0x674);
    uVar11 = (undefined2)*(undefined4 *)(lVar9 + 0x678);
    bVar18 = *(byte *)(lVar9 + 0x67a);
    bVar1 = *(byte *)(lVar9 + 0x67b);
    bVar2 = *(byte *)(lVar9 + 0x67c);
    bVar3 = *(byte *)(lVar9 + 0x67d);
    bVar4 = *(byte *)(lVar9 + 0x67e);
    bVar5 = *(byte *)(lVar9 + 0x67f);
    for (sVar19 = 0; (byte)sVar19 < *(byte *)(param_1 + 0x168); sVar19 = sVar19 + 1) {
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar12 = 0x4c, acphychipid == 0xaa06)) {
        uVar12 = 0x45;
      }
      uVar15 = sVar19 << 9;
      mod_radio_reg(param_1,uVar12 | uVar15,0x80,(uint)bVar2 << 7);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar12 = 0x50, acphychipid == 0xaa06)))) {
        uVar12 = 0x49;
      }
      mod_radio_reg(param_1,uVar12 | uVar15,0xe000,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar12 = 0x50, acphychipid == 0xaa06)))) {
        uVar12 = 0x49;
      }
      mod_radio_reg(param_1,uVar12 | uVar15,0x1800,0);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar12 = 0x50, acphychipid == 0xaa06)) {
        uVar12 = 0x49;
      }
      mod_radio_reg(param_1,uVar12 | uVar15,0x400,0);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar12 = 0x50, acphychipid == 0xaa06)))) {
        uVar12 = 0x49;
      }
      mod_radio_reg(param_1,uVar12 | uVar15,0x300,(uint)bVar3 << 8);
      if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
         ((acphychipid == 0xa9c4 || (uVar12 = 0x50, acphychipid == 0xaa06)))) {
        uVar12 = 0x49;
      }
      mod_radio_reg(param_1,uVar12 | uVar15,0x40,(uint)bVar4 << 6);
      if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
         (uVar12 = 0x50, acphychipid == 0xaa06)) {
        uVar12 = 0x49;
      }
      mod_radio_reg(param_1,uVar12 | uVar15,0x80,(uint)bVar5 << 7);
    }
    iVar16 = (-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a0;
    uVar12 = phy_reg_read(param_1,iVar16);
    phy_reg_write(param_1,iVar16,
                  (uVar12 & 0xff0f | 0xd | (ushort)bVar18 << 4) & 0xf0ff | (ushort)bVar18 << 8);
    iVar16 = (-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a1;
    uVar13 = phy_reg_read(param_1,iVar16);
    phy_reg_write(param_1,iVar16,
                  CONCAT31((int3)((uint)uVar13 >> 8),bVar1) & 0xff0f | (uint)bVar1 << 4);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a2,uVar11);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a3,uVar11);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a4,uVar10);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a5,uVar10);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a6,uVar7);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a7,uVar7);
    uVar17 = (int)((uint)uVar6 * 10000) >> 3;
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a8,uVar17 & 0xffff);
    phy_reg_write(param_1,(-(uint)(uVar8 < 2) & 0xffffffb0) + 0x5a9,uVar17 >> 0x10);
  }
  return;
}

