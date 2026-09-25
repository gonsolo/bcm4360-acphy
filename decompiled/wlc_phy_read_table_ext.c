
void wlc_phy_read_table_ext
               (undefined8 param_1,long *param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5,undefined2 param_6,undefined2 param_7)

{
  uint *puVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  undefined1 uVar5;
  ushort uVar6;
  undefined2 uVar7;
  int iVar8;
  uint uVar9;
  uint local_44;
  
  lVar4 = param_2[2];
  uVar2 = *(uint *)((long)param_2 + 0x14);
  lVar3 = *param_2;
  phy_reg_write(param_1,param_3,*(undefined2 *)((long)param_2 + 0xc));
  local_44._0_2_ = (undefined2)(int)lVar4;
  phy_reg_write(param_1,param_4,(undefined2)local_44);
  local_44 = 0;
  for (uVar9 = 0; uVar9 < *(uint *)(param_2 + 1); uVar9 = uVar9 + 1) {
    if (uVar2 == 0x20) {
      puVar1 = (uint *)(lVar3 + (ulong)uVar9 * 4);
      uVar6 = phy_reg_read(param_1,param_7);
      *puVar1 = (uint)uVar6;
      iVar8 = phy_reg_read(param_1,param_6);
      *puVar1 = iVar8 << 0x10 | (uint)uVar6;
    }
    else if (uVar2 < 0x21) {
      if (uVar2 == 8) {
        uVar5 = phy_reg_read(param_1,param_7);
        *(undefined1 *)(lVar3 + (ulong)uVar9) = uVar5;
      }
      else if (uVar2 == 0x10) {
        uVar7 = phy_reg_read(param_1,param_7);
        *(undefined2 *)(lVar3 + (ulong)uVar9 * 2) = uVar7;
      }
    }
    else if ((uVar2 == 0x3c) || (uVar2 == 0x40)) {
      uVar6 = phy_reg_read(param_1,param_5);
      iVar8 = phy_reg_read_wide(param_1);
      *(uint *)(lVar3 + (ulong)local_44 * 4) = iVar8 << 0x10 | (uint)uVar6;
      uVar6 = phy_reg_read_wide(param_1);
      iVar8 = phy_reg_read_wide(param_1);
      *(uint *)(lVar3 + (ulong)(local_44 + 1) * 4) = iVar8 << 0x10 | (uint)uVar6;
    }
    else if (uVar2 == 0x30) {
      iVar8 = 0;
      do {
        if (iVar8 == 0) {
          uVar7 = phy_reg_read(param_1,param_5);
          *(undefined2 *)(lVar3 + (ulong)(uVar9 * 3) * 2) = uVar7;
        }
        else {
          uVar7 = phy_reg_read_wide(param_1);
          *(undefined2 *)(lVar3 + (ulong)(iVar8 + uVar9 * 3) * 2) = uVar7;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 3);
    }
    local_44 = local_44 + 2;
  }
  return;
}

