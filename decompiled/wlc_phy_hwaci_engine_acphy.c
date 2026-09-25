
void wlc_phy_hwaci_engine_acphy(long param_1)

{
  long lVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  long lVar5;
  bool bVar6;
  byte bVar7;
  byte bVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  undefined8 uVar17;
  ulong uVar18;
  uint uVar19;
  ulong extraout_RDX;
  ulong extraout_RDX_00;
  bool bVar20;
  bool bVar21;
  byte local_58;
  sbyte local_57;
  long local_50;
  byte local_41;
  uint local_40;
  uint local_3c;
  
  uVar10 = *(ushort *)(param_1 + 0x17e);
  lVar5 = *(long *)(param_1 + 0x138);
  uVar16 = *(uint *)(param_1 + 0x164);
  if ((-((uVar10 & 0xc000) == 0) & 0xfdU) == 0xfd) {
    local_58 = *(byte *)(lVar5 + 0x6c2);
    local_50 = lVar5 + 0x682;
  }
  else {
    local_58 = *(byte *)(lVar5 + 0x6c3);
    local_50 = lVar5 + 0x6a2;
  }
  local_57 = 0;
  if ((uVar10 & 0x3800) != 0x1000) {
    local_57 = ((uVar10 & 0x3800) != 0x1800) + 1;
  }
  uVar19 = *(uint *)(*(long *)(param_1 + 0x20) + 0x80);
  uVar12 = uVar19 >> 2;
  uVar19 = uVar19 >> 1;
  if (((uVar12 & 1) != 0) || ((uVar19 & 1) != 0)) {
    if (*(long *)(lVar5 + 0x8a8) == 0) {
      uVar17 = FUN_00193c3b(param_1,uVar10,1);
      *(undefined8 *)(lVar5 + 0x8a8) = uVar17;
    }
    lVar5 = *(long *)(lVar5 + 0x8a8);
    if (*(char *)(lVar5 + 0x49) == '\0') {
      bVar2 = *(byte *)(lVar5 + 0x46);
      iVar13 = *(byte *)(lVar5 + 0x48) - 1;
      if (iVar13 < 0) {
        iVar13 = 0;
      }
      bVar6 = false;
      *(char *)(lVar5 + 0x48) = (char)iVar13;
      wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
      uVar18 = extraout_RDX;
      if ((uVar19 & 1) != 0) {
        uVar18 = 0;
        local_41 = 0;
        uVar15 = 0;
        uVar14 = 0;
        local_3c = 0;
        local_40 = 0;
        for (bVar7 = 0; bVar7 < *(byte *)(param_1 + 0x168); bVar7 = bVar7 + 1) {
          if (bVar7 == 0) {
            uVar10 = phy_reg_read(param_1,(-(uint)(uVar16 < 2) & 5) + 0x7aa);
            uVar11 = phy_reg_read(param_1);
            uVar9 = phy_reg_read(param_1);
            iVar13 = (-(uint)(uVar16 < 2) & 6) + 0x7ab;
LAB_0019a95e:
            local_3c = local_3c + uVar11;
            local_40 = local_40 + uVar10;
            uVar14 = uVar14 + uVar9;
            uVar10 = phy_reg_read(param_1,iVar13);
            local_41 = local_41 + 1;
            uVar15 = uVar15 + uVar10;
            uVar18 = extraout_RDX_00;
          }
          else {
            if (bVar7 == 1) {
              uVar10 = phy_reg_read(param_1,(-(uint)(uVar16 < 3) & 5) + 0x9aa);
              uVar11 = phy_reg_read(param_1);
              uVar9 = phy_reg_read(param_1);
              iVar13 = (-(uint)(uVar16 < 3) & 6) + 0x9ab;
              goto LAB_0019a95e;
            }
            if (bVar7 == 2) {
              uVar10 = phy_reg_read(param_1,0xbaf);
              uVar11 = phy_reg_read(param_1,0xbab);
              uVar9 = phy_reg_read(param_1,0xbb3);
              iVar13 = 0xbb1;
              goto LAB_0019a95e;
            }
          }
        }
        if (1 < local_41) {
          local_40 = local_40 / local_41;
          local_3c = local_3c / local_41;
          uVar14 = uVar14 / local_41;
          uVar18 = (ulong)uVar15;
          uVar15 = uVar15 / local_41;
          uVar18 = uVar18 % (ulong)local_41;
        }
        if (uVar15 < 200) {
          if (199 < local_3c) {
            uVar15 = local_3c;
          }
          uVar14 = 0;
          if (199 < local_3c) {
            uVar14 = local_40;
          }
        }
        bVar6 = uVar15 < uVar14 * 4 && uVar14 != 0;
      }
      bVar20 = false;
      if ((uVar12 & 1) != 0) {
        uVar10 = phy_reg_read(param_1,0x523,uVar18);
        uVar11 = phy_reg_read(param_1,0x529);
        uVar12 = phy_reg_read(param_1,0x528);
        uVar15 = phy_reg_read(param_1,0x527);
        lVar1 = local_50 + (ulong)bVar2 * 8;
        bVar20 = (byte)((int)(uVar10 & 0x7f) >> local_57) <= *(byte *)(lVar1 + 6);
        bVar2 = *(byte *)(lVar1 + 5);
        bVar8 = (byte)((int)(uVar12 & 0x7f) >> local_57);
        bVar7 = (byte)((int)(uVar15 & 0x7f) >> local_57);
        if (*(char *)(lVar1 + 4) == '\0') {
          if (((byte)((int)(uVar11 & 0x7f) >> local_57) < bVar2) && (bVar8 == 0)) {
            bVar21 = bVar7 != 0;
          }
          else {
            bVar21 = true;
          }
          bVar20 = (bool)(bVar20 & bVar21);
        }
        else if (*(char *)(lVar1 + 4) == '\x01') {
          bVar20 = bVar20 && (bVar2 <= bVar8 || bVar7 != 0);
        }
        else {
          bVar20 = bVar2 <= bVar7 && bVar20;
        }
      }
      bVar2 = *(byte *)(lVar5 + 0x46);
      bVar7 = *(byte *)(lVar5 + 0x47);
      if (bVar2 == 0) {
        *(undefined1 *)(lVar5 + 0x46) = 1;
      }
      else if ((bVar20) || (bVar6)) {
        uVar3 = *(undefined1 *)(lVar5 + 0x46);
        *(undefined1 *)(lVar5 + 0x48) = 8;
        *(char *)(lVar5 + 0x46) = *(char *)(lVar5 + 0x46) + '\x01';
        *(undefined1 *)(lVar5 + 0x47) = uVar3;
      }
      else if (*(char *)(lVar5 + 0x48) == '\0') {
        iVar13 = bVar2 - 1;
        if (iVar13 < 0) {
          iVar13 = 0;
        }
        bVar8 = (byte)iVar13;
        *(byte *)(lVar5 + 0x46) = bVar8;
        if (bVar8 < *(byte *)(lVar5 + 0x47)) {
          *(byte *)(lVar5 + 0x47) = bVar8;
        }
      }
      uVar12 = local_58 - 1;
      if ((int)(uint)*(byte *)(lVar5 + 0x46) < (int)(local_58 - 1)) {
        uVar12 = (uint)*(byte *)(lVar5 + 0x46);
      }
      bVar8 = (byte)uVar12;
      if ((int)uVar12 < 1) {
        bVar8 = 1;
      }
      *(byte *)(lVar5 + 0x46) = bVar8;
      if (bVar2 != bVar8) {
        *(undefined1 *)(lVar5 + 0x48) = 8;
        *(undefined1 *)(lVar5 + 0x49) = 2;
        if ((uVar19 & 1) != 0) {
          uVar4 = *(undefined2 *)(local_50 + (ulong)bVar8 * 8);
          phy_reg_write(param_1,(-(uint)(uVar16 < 2) & 0xffffffb0) + 0x5a4,uVar4);
          phy_reg_write(param_1,(-(uint)(uVar16 < 2) & 0xffffffb0) + 0x5a5,uVar4);
        }
      }
      if (bVar7 != *(byte *)(lVar5 + 0x47)) {
        local_50 = local_50 + (ulong)*(byte *)(lVar5 + 0x47) * 8;
        bVar2 = *(byte *)(local_50 + 3);
        iVar13 = 5 - (uint)*(byte *)(local_50 + 2);
        if (iVar13 < 0) {
          iVar13 = 0;
        }
        *(char *)(lVar5 + 0x14) = (char)iVar13;
        iVar13 = 6 - (uint)bVar2;
        if (iVar13 < 0) {
          iVar13 = 0;
        }
        *(char *)(lVar5 + 0x15) = (char)iVar13;
        uVar16 = phy_reg_read(param_1,0x19e);
        phy_reg_mod(param_1,0x19e,2,2);
        FUN_0019173d(param_1);
        FUN_0019a60c(param_1,1);
        FUN_0019a60c(param_1,2);
        phy_reg_mod(param_1,0x19e,2,(uVar16 >> 1 & 1) * 2);
        wlc_phy_aci_updsts_acphy(param_1);
      }
      wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    }
    else {
      *(char *)(lVar5 + 0x49) = *(char *)(lVar5 + 0x49) + -1;
    }
  }
  return;
}

