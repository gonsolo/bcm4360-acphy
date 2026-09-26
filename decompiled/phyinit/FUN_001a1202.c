
void FUN_001a1202(long param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined1 *puVar8;
  uint uVar9;
  uint uVar10;
  
  if (*(int *)(param_1 + 0x164) != 3) {
    phy_reg_write(param_1,0x410,0x77);
  }
  iVar1 = *(int *)(param_1 + 0x164);
  if (((iVar1 == 5) || (iVar1 == 2)) || (iVar1 == 6)) {
    phy_reg_write(param_1,0x749,3);
  }
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x73e, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x173e;
  }
  phy_reg_write(param_1,uVar7,0);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x725, acphychipid == 0x4350)))) {
    uVar7 = 0x1725;
  }
  phy_reg_write(param_1,uVar7,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x722, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x1722;
  }
  phy_reg_write(param_1,uVar7,0);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x723, acphychipid == 0x4350)))) {
    uVar7 = 0x1723;
  }
  phy_reg_write(param_1,uVar7,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x724, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x1724;
  }
  phy_reg_write(param_1,uVar7,0);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x725, acphychipid == 0x4350)))) {
    uVar7 = 0x1725;
  }
  phy_reg_write(param_1,uVar7,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x726, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x1726;
  }
  phy_reg_write(param_1,uVar7,0);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x727, acphychipid == 0x4350)))) {
    uVar7 = 0x1727;
  }
  phy_reg_write(param_1,uVar7,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x750, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x1750;
  }
  phy_reg_write(param_1,uVar7,0);
  if (*(int *)(param_1 + 0x164) == 3) {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar7 = 0x728, acphychipid == 0x4350)))) {
      uVar7 = 0x1728;
    }
    phy_reg_write(param_1,uVar7,0x4080);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 ||
        ((acphychipid == 0xaa06 || (uVar7 = 0x720, acphychipid == 0x4350)))))) {
      uVar7 = 0x1720;
    }
    uVar6 = 0x380;
  }
  else {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar7 = 0x728, acphychipid == 0x4350)))) {
      uVar7 = 0x1728;
    }
    phy_reg_write(param_1,uVar7,0x80);
    if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
       ((acphychipid == 0xa9c4 ||
        ((acphychipid == 0xaa06 || (uVar7 = 0x720, acphychipid == 0x4350)))))) {
      uVar7 = 0x1720;
    }
    uVar6 = 0x180;
  }
  phy_reg_write(param_1,uVar7,uVar6);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x729, acphychipid == 0x4350)))) {
    uVar7 = 0x1729;
  }
  phy_reg_write(param_1,uVar7,0);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x721, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x1721;
  }
  phy_reg_write(param_1,uVar7,0x5000);
  uVar4 = phy_reg_read(param_1,0x73a);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x73a, acphychipid == 0x4350)))) {
    uVar7 = 0x173a;
  }
  phy_reg_write(param_1,uVar7,uVar4 | 0x100);
  uVar4 = phy_reg_read(param_1,0x725);
  if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
     ((acphychipid == 0xa9c4 || ((acphychipid == 0xaa06 || (uVar7 = 0x725, acphychipid == 0x4350))))
     )) {
    uVar7 = 0x1725;
  }
  phy_reg_write(param_1,uVar7,uVar4 | 0x400);
  uVar5 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  uVar3 = acphytbl_info_sz_rev0;
  uVar2 = acphytbl_info_sz_rev6;
  uVar9 = acphytbl_info_sz_rev2;
  uVar10 = acphytbl_info_sz_rev3;
  if (*(char *)(param_1 + 0x185) != '\0') {
    iVar1 = *(int *)(param_1 + 0x164);
    if (iVar1 == 3) {
      puVar8 = acphytbl_info_rev3;
      for (uVar9 = 0; uVar9 < uVar10; uVar9 = uVar9 + 1) {
        wlc_phy_write_table_ext(param_1,puVar8,0xd,0xe,0x11,0x10,0xf);
        puVar8 = puVar8 + 0x18;
      }
    }
    else {
      if ((iVar1 == 5) || (iVar1 == 2)) {
        if (iVar1 != 6) {
          puVar8 = acphytbl_info_rev2;
          for (uVar10 = 0; uVar10 < uVar9; uVar10 = uVar10 + 1) {
            wlc_phy_write_table_ext(param_1,puVar8,0xd,0xe,0x11,0x10,0xf);
            puVar8 = puVar8 + 0x18;
          }
          goto LAB_001a1819;
        }
      }
      else if (iVar1 != 6) {
        puVar8 = acphytbl_info_rev0;
        for (uVar10 = 0; uVar10 < uVar3; uVar10 = uVar10 + 1) {
          wlc_phy_write_table_ext(param_1,puVar8,0xd,0xe,0x11,0x10,0xf);
          puVar8 = puVar8 + 0x18;
        }
        goto LAB_001a1819;
      }
      puVar8 = acphytbl_info_rev6;
      for (uVar10 = 0; uVar10 < uVar2; uVar10 = uVar10 + 1) {
        wlc_phy_write_table_ext(param_1,puVar8,0xd,0xe,0x11,0x10,0xf);
        puVar8 = puVar8 + 0x18;
      }
    }
  }
LAB_001a1819:
  phy_reg_mod(param_1,0x19e,2,(uVar5 >> 1 & 1) * 2);
  if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
     ((acphychipid == 0xaa06 || (uVar7 = 0x645, acphychipid == 0x4350)))) {
    uVar7 = 0x1645;
  }
  phy_reg_write(param_1,uVar7,0x25c);
  iVar1 = *(int *)(param_1 + 0x164);
  if ((((iVar1 == 5) || (iVar1 == 2)) || ((iVar1 == 6 || (iVar1 == 3)))) &&
     (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       ((acphychipid == 0xaa06 || (uVar7 = 0x64c, acphychipid == 0x4350)))) {
      uVar7 = 0x164c;
    }
    phy_reg_write(param_1,uVar7,0x25c);
  }
  if (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0') {
    wlapi_bmac_mhf(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),1,0x80,0x80,3);
  }
  return;
}

