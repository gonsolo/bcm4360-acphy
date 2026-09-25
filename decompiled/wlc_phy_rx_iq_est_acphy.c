
void wlc_phy_rx_iq_est_acphy
               (long param_1,long param_2,undefined2 param_3,undefined1 param_4,undefined8 param_5,
               byte param_6)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  ushort uVar6;
  int iVar7;
  ulong uVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined7 uVar11;
  byte bVar12;
  uint uVar13;
  int iVar14;
  uint *puVar15;
  uint uVar16;
  short asStack_78 [36];
  
  uVar11 = (undefined7)((ulong)param_5 >> 8);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    bVar12 = *(byte *)(*(long *)(param_1 + 0x138) + 0x900);
  }
  else {
    bVar12 = *(byte *)(*(long *)(param_1 + 0x138) + 0x901);
  }
  FUN_00193d3a(param_1);
  phy_reg_write(param_1,0x272,param_3);
  phy_reg_mod(param_1,0x271,0xff,param_4);
  phy_reg_mod(param_1,0x270,2,
              (int)CONCAT71(uVar11,(char)param_5) + (int)CONCAT71(uVar11,(char)param_5) & 0x1fe);
  if ((bVar12 & param_6) == 0) {
    phy_reg_mod(param_1,0x270,1,1);
    for (iVar7 = 0x2719; (uVar9 = phy_reg_read(param_1,0x270), (uVar9 & 1) != 0 && (iVar7 != 9));
        iVar7 = iVar7 + -10) {
      osl_delay(10);
    }
    uVar16 = 0;
    uVar9 = phy_reg_read(param_1,0x270);
    if ((uVar9 & 1) == 0) {
      for (; (byte)uVar16 < *(byte *)(param_1 + 0x168); uVar16 = uVar16 + 1) {
        sVar1 = (short)(uVar16 << 9);
        puVar15 = (uint *)((ulong)(uVar16 & 0xff) * 0xc + param_2);
        iVar7 = phy_reg_read(param_1,sVar1 + 0x6c3);
        uVar6 = phy_reg_read(param_1,sVar1 + 0x6c2);
        puVar15[1] = iVar7 << 0x10 | (uint)uVar6;
        iVar7 = phy_reg_read(param_1,sVar1 + 0x6c5);
        uVar6 = phy_reg_read(param_1,sVar1 + 0x6c4);
        puVar15[2] = iVar7 << 0x10 | (uint)uVar6;
        iVar7 = phy_reg_read(param_1,sVar1 + 0x6c1);
        uVar6 = phy_reg_read(param_1,sVar1 + 0x6c0);
        *puVar15 = iVar7 << 0x10 | (uint)uVar6;
      }
    }
  }
  else {
    for (uVar16 = 0; (byte)uVar16 < *(byte *)(param_1 + 0x168); uVar16 = uVar16 + 1) {
      uVar9 = 0;
      for (uVar13 = 0; bVar12 = (byte)uVar13, bVar12 < *(byte *)(param_1 + 0x168);
          uVar13 = uVar13 + 1) {
        if (((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar13 & 0x1f) & 1) != 0) &&
           ((byte)uVar16 != bVar12)) {
          sVar1 = (short)(uVar13 << 9);
          sVar2 = phy_reg_read(param_1,sVar1 + 0x720);
          iVar7 = (int)uVar9;
          sVar3 = phy_reg_read(param_1,sVar1 + 0x728);
          sVar4 = phy_reg_read(param_1,sVar1 + 0x721);
          sVar5 = phy_reg_read(param_1,sVar1 + 0x729);
          uVar10 = 0x720;
          if ((bVar12 != 0) && (uVar10 = 0xb20, bVar12 == 1)) {
            uVar10 = 0x920;
          }
          phy_reg_mod(param_1,uVar10,1,1);
          uVar10 = 0x728;
          if ((bVar12 != 0) && (uVar10 = 0xb28, bVar12 == 1)) {
            uVar10 = 0x928;
          }
          phy_reg_mod(param_1,uVar10,1,0);
          uVar10 = 0x721;
          if ((bVar12 != 0) && (uVar10 = 0xb21, bVar12 == 1)) {
            uVar10 = 0x921;
          }
          phy_reg_mod(param_1,uVar10,4,4);
          uVar10 = 0x729;
          if ((bVar12 != 0) && (uVar10 = 0xb29, bVar12 == 1)) {
            uVar10 = 0x929;
          }
          asStack_78[uVar9 * 2 + 1] = sVar1 + 0x720;
          asStack_78[uVar9 * 2] = sVar2;
          asStack_78[(ulong)(iVar7 + 1) * 2] = sVar3;
          asStack_78[(ulong)(iVar7 + 1) * 2 + 1] = sVar1 + 0x728;
          asStack_78[(ulong)(iVar7 + 2) * 2] = sVar4;
          asStack_78[(ulong)(iVar7 + 2) * 2 + 1] = sVar1 + 0x721;
          asStack_78[(ulong)(iVar7 + 3) * 2] = sVar5;
          asStack_78[(ulong)(iVar7 + 3) * 2 + 1] = sVar1 + 0x729;
          uVar9 = (ulong)(iVar7 + 4);
          phy_reg_mod(param_1,uVar10,2,0);
        }
      }
      osl_delay(1);
      phy_reg_mod(param_1,0x270,1,1);
      for (iVar7 = 0x2719; (uVar8 = phy_reg_read(param_1,0x270), (uVar8 & 1) != 0 && (iVar7 != 9));
          iVar7 = iVar7 + -10) {
        osl_delay(10);
      }
      while ((int)uVar9 != 0) {
        uVar9 = (ulong)((int)uVar9 - 1);
        phy_reg_write(param_1,asStack_78[uVar9 * 2 + 1],asStack_78[uVar9 * 2]);
      }
      uVar9 = phy_reg_read(param_1,0x270);
      if ((uVar9 & 1) == 0) {
        iVar14 = uVar16 * 0x200;
        puVar15 = (uint *)((ulong)(uVar16 & 0xff) * 0xc + param_2);
        iVar7 = phy_reg_read(param_1,iVar14 + 0x6c3U & 0xffff);
        uVar6 = phy_reg_read(param_1,iVar14 + 0x6c2U & 0xffff);
        puVar15[1] = iVar7 << 0x10 | (uint)uVar6;
        iVar7 = phy_reg_read(param_1,iVar14 + 0x6c5U & 0xffff);
        uVar6 = phy_reg_read(param_1,iVar14 + 0x6c4U & 0xffff);
        puVar15[2] = iVar7 << 0x10 | (uint)uVar6;
        iVar7 = phy_reg_read(param_1,iVar14 + 0x6c1U & 0xffff);
        uVar6 = phy_reg_read(param_1,(short)iVar14 + 0x6c0);
        *puVar15 = iVar7 << 0x10 | (uint)uVar6;
      }
    }
  }
  return;
}

