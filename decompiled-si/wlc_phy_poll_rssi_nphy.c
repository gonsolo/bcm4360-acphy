
uint wlc_phy_poll_rssi_nphy(long param_1,undefined1 param_2,uint *param_3,byte param_4)

{
  uint uVar1;
  char cVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  ulong uVar12;
  long lVar13;
  char *pcVar14;
  int iVar15;
  uint *puVar16;
  undefined8 uVar17;
  byte bVar18;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  char local_48 [4];
  char acStack_44 [20];
  
  if (*(uint *)(param_1 + 0x164) < 0x13) {
    uVar4 = phy_reg_read(param_1,0xa6);
    uVar5 = phy_reg_read(param_1,0xa7);
    if (*(uint *)(param_1 + 0x164) < 3) {
      uVar7 = 0;
      uVar8 = phy_reg_read(param_1,0xa5);
      local_58 = phy_reg_read(param_1,0x78);
      local_56 = phy_reg_read(param_1,0xec);
      local_54 = phy_reg_read(param_1,0x7a);
      uVar6 = 0;
      local_52 = phy_reg_read(param_1,0x7d);
      local_5a = 0;
      local_5c = 0;
      local_5e = 0;
    }
    else {
      uVar6 = phy_reg_read(param_1,0xf9);
      uVar7 = phy_reg_read(param_1,0xfb);
      uVar8 = phy_reg_read(param_1,0x8f);
      local_5e = phy_reg_read(param_1,0xa5);
      local_5c = phy_reg_read(param_1,0xe5);
      local_5a = phy_reg_read(param_1,0xe6);
      local_52 = 0;
      local_54 = 0;
      local_56 = 0;
      local_58 = 0;
    }
    wlc_phy_rssisel_nphy(param_1,5,param_2);
    uVar9 = phy_reg_read(param_1,0xca);
    if (*(uint *)(param_1 + 0x164) < 2) {
      phy_reg_write(param_1,0xca,5);
    }
    *param_3 = 0;
    param_3[1] = 0;
    param_3[2] = 0;
    param_3[3] = 0;
    for (bVar18 = 0; bVar18 < param_4; bVar18 = bVar18 + 1) {
      if (*(uint *)(param_1 + 0x164) < 2) {
        uVar10 = phy_reg_read(param_1,0x1c9);
        uVar17 = 0x1ca;
      }
      else {
        uVar10 = phy_reg_read(param_1,0x219);
        uVar17 = 0x21a;
      }
      uVar11 = phy_reg_read(param_1,uVar17);
      local_48[0] = (char)((char)uVar10 * '\x04') >> 2;
      local_48[1] = (char)((char)((ushort)uVar10 >> 8) << 2) >> 2;
      local_48[3] = (char)((char)((ushort)uVar11 >> 8) << 2) >> 2;
      pcVar14 = local_48;
      local_48[2] = (char)((char)uVar11 * '\x04') >> 2;
      puVar16 = param_3;
      do {
        cVar2 = *pcVar14;
        pcVar14 = pcVar14 + 1;
        *puVar16 = *puVar16 + (int)cVar2;
        puVar16 = puVar16 + 1;
      } while (pcVar14 != acStack_44);
    }
    uVar1 = param_3[3] & 0xff | *param_3 << 0x18 | (param_3[2] & 0xff) << 8 |
            (param_3[1] & 0xff) << 0x10;
    if (*(uint *)(param_1 + 0x164) < 2) {
      phy_reg_write(param_1,0xca,uVar9);
    }
    phy_reg_write(param_1,0xa6,uVar4);
    phy_reg_write(param_1,0xa7,uVar5);
    if (*(uint *)(param_1 + 0x164) < 3) {
      phy_reg_write(param_1,0xa5,uVar8);
      phy_reg_write(param_1,0x78,local_58);
      phy_reg_write(param_1,0xec,local_56);
      phy_reg_write(param_1,0x7a,local_54);
      uVar17 = 0x7d;
      local_5a = local_52;
    }
    else {
      phy_reg_write(param_1,0xf9,uVar6);
      phy_reg_write(param_1,0xfb,uVar7);
      phy_reg_write(param_1,0x8f,uVar8);
      phy_reg_write(param_1,0xa5,local_5e);
      phy_reg_write(param_1,0xe5,local_5c);
      uVar17 = 0xe6;
    }
    phy_reg_write(param_1,uVar17,local_5a);
  }
  else {
    wlc_phy_rev3_tssisel_nphy(param_1,5,param_2);
    *param_3 = 0;
    param_3[1] = 0;
    param_3[2] = 0;
    param_3[3] = 0;
    for (bVar18 = 0; bVar18 < param_4; bVar18 = bVar18 + 1) {
      uVar12 = phy_reg_read(param_1,0xb1);
      if ((uVar12 & 1) == 0) {
        uVar3 = phy_reg_read(param_1,0x219);
        *param_3 = (uint)uVar3;
        uVar3 = phy_reg_read(param_1,0x21a);
        param_3[1] = (uint)uVar3;
        uVar3 = phy_reg_read(param_1,0x21b);
        param_3[2] = (uint)uVar3;
        uVar3 = phy_reg_read(param_1,0x21c);
        param_3[3] = (uint)uVar3;
      }
      else {
        uVar3 = phy_reg_read(param_1,0x219);
        param_3[1] = (uint)uVar3;
        uVar3 = phy_reg_read(param_1,0x21a);
        *param_3 = (uint)uVar3;
        uVar3 = phy_reg_read(param_1,0x21b);
        param_3[3] = (uint)uVar3;
        uVar3 = phy_reg_read(param_1,0x21c);
        param_3[2] = (uint)uVar3;
      }
      lVar13 = 0;
      do {
        iVar15 = *(int *)((long)param_3 + lVar13);
        if (iVar15 < 0x201) {
          iVar15 = -iVar15;
        }
        else {
          iVar15 = 0x400 - iVar15;
        }
        *(int *)((long)param_3 + lVar13) = iVar15;
        lVar13 = lVar13 + 4;
      } while (lVar13 != 0x10);
    }
    wlc_phy_rev3_tssisel_nphy(param_1,5,0);
    uVar1 = 1;
  }
  return uVar1;
}

