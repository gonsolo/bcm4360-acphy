
void wlc_phy_populate_recipcoeffs_acphy(long param_1)

{
  short sVar1;
  byte bVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  long lVar6;
  ushort uVar7;
  short sVar8;
  uint uVar9;
  short sVar10;
  undefined4 *puVar11;
  short *psVar12;
  undefined4 *puVar13;
  ushort *puVar14;
  int iVar15;
  int iVar16;
  short local_128 [64];
  undefined4 local_a8 [20];
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  uint local_48;
  uint local_44;
  uint local_3c;
  ushort local_38 [8];
  
  local_58 = 0;
  local_56 = 0;
  puVar11 = &DAT_00558ce0;
  psVar12 = local_128;
  for (lVar6 = 0x20; lVar6 != 0; lVar6 = lVar6 + -1) {
    *(undefined4 *)psVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    psVar12 = psVar12 + 2;
  }
  local_54 = 0;
  puVar11 = &DAT_00558c90;
  puVar13 = local_a8;
  for (lVar6 = 0x12; lVar6 != 0; lVar6 = lVar6 + -1) {
    *puVar13 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar13 = puVar13 + 1;
  }
  if (1 < *(byte *)(*(long *)(param_1 + 0x20) + 0xa4)) {
    bVar2 = wlc_phy_get_chan_freq_range_acphy(param_1);
    if (bVar2 < 5) {
      lVar6 = *(long *)(param_1 + 0x20);
      switch(bVar2) {
      case 0:
        uVar5 = *(uint *)(lVar6 + 0xcc);
        break;
      case 1:
        uVar5 = (uint)*(ushort *)(lVar6 + 0xce);
        break;
      case 2:
        uVar5 = *(uint *)(lVar6 + 0xd0);
        break;
      case 3:
        uVar5 = (uint)*(ushort *)(lVar6 + 0xd2);
        break;
      case 4:
        uVar5 = *(uint *)(lVar6 + 0xd4);
      }
    }
    else {
      uVar5 = *(uint *)(*(long *)(param_1 + 0x20) + 0xcc);
    }
    uVar9 = uVar5 & 0xff;
    local_38[1] = (ushort)uVar5 >> 8;
    local_38[0] = (ushort)uVar9;
    if (*(uint *)(param_1 + 0x164) < 2) {
      uVar5 = local_48 >> 0x10;
      puVar14 = local_38;
      sVar10 = 0;
      uVar9 = local_44;
      do {
        uVar7 = *puVar14 & 0x3f;
        uVar3 = *puVar14 >> 6 & 3;
        sVar1 = local_128[(short)uVar7];
        sVar8 = local_128[(short)(0x3f - uVar7)];
        if (uVar3 == 0) {
          sVar4 = sVar8;
          sVar8 = -sVar1;
        }
        else if (uVar3 == 1) {
          sVar4 = -sVar1;
          sVar8 = -sVar8;
        }
        else {
          sVar4 = sVar1;
          if (uVar3 == 2) {
            sVar4 = -sVar8;
            sVar8 = sVar1;
          }
        }
        local_3c = (int)(short)((sVar4 >> 0xf & 0x800U) + sVar4) | 0x400000U |
                   (int)(short)((sVar8 >> 0xf & 0x800U) + sVar8) << 0xb;
        if (sVar10 == 0) {
          uVar5 = (uint)((ushort)(local_3c >> 0x10) & 0xff);
          local_48 = local_3c;
        }
        else {
          uVar9 = local_3c >> 8;
          uVar5 = uVar5 | local_3c << 8;
        }
        sVar10 = sVar10 + 1;
        puVar14 = puVar14 + 1;
      } while (sVar10 != 2);
      local_48 = CONCAT22((short)uVar5,(short)local_48);
      local_44 = CONCAT22(local_44._2_2_,(short)uVar9);
    }
    else if (*(uint *)(param_1 + 0x164) == 3) {
      local_3c = uVar9 << 8 | uVar9 << 0x10 | uVar9 | uVar9 << 0x18;
    }
    uVar5 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    if (*(uint *)(param_1 + 0x164) < 2) {
      puVar11 = local_a8;
      iVar15 = 0;
      do {
        iVar16 = iVar15 + 1;
        wlc_phy_table_write_acphy(param_1,0x11,1,iVar15,0x30,puVar11);
        puVar11 = (undefined4 *)((long)puVar11 + 6);
        iVar15 = iVar16;
      } while (iVar16 != 0xc);
      iVar15 = 0xc;
      do {
        iVar16 = iVar15 + 1;
        wlc_phy_table_write_acphy(param_1,0x11,1,iVar15,0x30,&local_48);
        iVar15 = iVar16;
      } while (iVar16 != 0x1cc);
      iVar15 = 0x1cc;
      do {
        iVar16 = iVar15 + 1;
        wlc_phy_table_write_acphy(param_1,0x11,1,iVar15,0x30,&local_58);
        iVar15 = iVar16;
      } while (iVar16 != 0x1d0);
    }
    else if (*(uint *)(param_1 + 0x164) == 3) {
      iVar15 = 0;
      do {
        iVar16 = iVar15 + 1;
        wlc_phy_table_write_acphy(param_1,0x1e,1,iVar15,0x20,&local_3c);
        iVar15 = iVar16;
      } while (iVar16 != 0x40);
    }
    phy_reg_mod(param_1,0x19e,2,(uVar5 >> 1 & 1) * 2);
  }
  return;
}

