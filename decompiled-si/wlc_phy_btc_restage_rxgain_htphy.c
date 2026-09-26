
void wlc_phy_btc_restage_rxgain_htphy(long param_1,char param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  byte bVar4;
  byte bVar5;
  undefined2 uVar6;
  ushort uVar7;
  undefined8 uVar8;
  undefined2 local_78;
  undefined2 local_76;
  undefined2 local_74;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined2 local_3c;
  undefined1 local_39 [9];
  
  lVar2 = *(long *)(param_1 + 0x138);
  bVar4 = osl_readl(*(long *)(param_1 + 0x148) + 0x120);
  bVar4 = (bVar4 ^ 1) & 1;
  if (bVar4 == 0) {
    wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  lVar3 = *(long *)(param_1 + 0x20);
  if ((*(int *)(lVar3 + 0x3c) != 0xa9a7) && (*(int *)(lVar3 + 0x3c) != 0x4331)) goto LAB_001dcb80;
  iVar1 = *(int *)(lVar3 + 0x58);
  if ((iVar1 == 0xef) || (iVar1 == 0x5c6)) {
    if (param_2 != '\0') {
      local_39[0] = 0;
      wlc_phy_table_write_htphy(param_1,9,1,2,8,local_39);
      wlc_phy_table_write_htphy(param_1,9,1,10,8,local_39);
      wlc_phy_table_write_htphy(param_1,9,1,0x22,8,local_39);
      wlc_phy_table_write_htphy(param_1,9,1,0x2a,8,local_39);
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
        bVar5 = 0;
        local_3c = 0x9117;
        local_48 = 0xfc;
        local_47 = 0xfc;
        if (*(short *)(param_1 + 0x36e) == 0) {
          wlc_phy_table_read_htphy(param_1,7,3,0x106,0x10,lVar2 + 0x314);
          uVar6 = phy_reg_read(param_1,0x410);
          *(undefined2 *)(lVar2 + 0x304) = uVar6;
          uVar6 = phy_reg_read(param_1,0x411);
          *(undefined2 *)(lVar2 + 0x306) = uVar6;
          uVar6 = phy_reg_read(param_1,0x450);
          *(undefined2 *)(lVar2 + 0x308) = uVar6;
          uVar6 = phy_reg_read(param_1,0x451);
          *(undefined2 *)(lVar2 + 0x30a) = uVar6;
          uVar6 = phy_reg_read(param_1,0x490);
          *(undefined2 *)(lVar2 + 0x30c) = uVar6;
          uVar6 = phy_reg_read(param_1,0x491);
        }
        else {
          for (; bVar5 < *(byte *)(param_1 + 0x168); bVar5 = bVar5 + 1) {
            *(undefined2 *)(lVar2 + 0x314 + (ulong)bVar5 * 2) =
                 *(undefined2 *)(param_1 + 0x270 + (ulong)bVar5 * 2);
          }
          *(short *)(lVar2 + 0x304) = (short)*(undefined4 *)(param_1 + 0x260);
          *(undefined2 *)(lVar2 + 0x306) = *(undefined2 *)(param_1 + 0x266);
          *(undefined2 *)(lVar2 + 0x308) = *(undefined2 *)(param_1 + 0x262);
          *(short *)(lVar2 + 0x30a) = (short)*(undefined4 *)(param_1 + 0x268);
          *(short *)(lVar2 + 0x30c) = (short)*(undefined4 *)(param_1 + 0x264);
          uVar6 = *(undefined2 *)(param_1 + 0x26a);
        }
        *(undefined2 *)(lVar2 + 0x30e) = uVar6;
        uVar6 = phy_reg_read(param_1,0x40d);
        *(undefined2 *)(lVar2 + 0x31c) = uVar6;
        uVar6 = phy_reg_read(param_1,0x44d);
        *(undefined2 *)(lVar2 + 0x31e) = uVar6;
        uVar6 = phy_reg_read(param_1,0x48d);
        *(undefined2 *)(lVar2 + 800) = uVar6;
        wlc_phy_table_read_htphy(param_1,0,2,0,8,lVar2 + 0x324);
        wlc_phy_table_read_htphy(param_1,1,2,0,8,lVar2 + 0x326);
        wlc_phy_table_read_htphy(param_1,0x28,2,0,8,lVar2 + 0x328);
        wlc_phy_table_write_htphy(param_1,7,1,0x106,0x10,&local_3c);
        wlc_phy_table_write_htphy(param_1,7,1,0x108,0x10,&local_3c);
        phy_reg_write(param_1,0x410,0x2e);
        phy_reg_write(param_1,0x490,0x2e);
        phy_reg_write(param_1,0x411,0x914);
        phy_reg_write(param_1,0x491,0x914);
        phy_reg_write(param_1,0x40d,0x4b);
        phy_reg_write(param_1,0x48d,0x4b);
        wlc_phy_table_write_htphy(param_1,0,2,0,8,&local_48);
        wlc_phy_table_write_htphy(param_1,0x28,2,0,8,&local_48);
        if ((*(int *)(*(long *)(param_1 + 0x20) + 0x80) == 1) &&
           (*(undefined1 **)(param_1 + 0x380) != HTPHY_bphy_desense_lut_X29B_BTON)) {
          local_76 = *(undefined2 *)(param_1 + 0x272);
          local_78 = 0x9117;
          local_74 = 0x9117;
          FUN_001cc282(param_1,HTPHY_bphy_desense_lut_X29B_BTON,0xb,0xffffffaa,&local_78);
        }
      }
      else {
        local_3c = 0x8226;
        wlc_phy_table_read_htphy(param_1,2,4,8,8,lVar2 + 0x36c);
        wlc_phy_table_read_htphy(param_1,0x29,4,8,8,lVar2 + 0x374);
        wlc_phy_table_read_htphy(param_1,0,4,8,8,lVar2 + 0x34c);
        wlc_phy_table_read_htphy(param_1,0x28,4,8,8,lVar2 + 0x354);
        wlc_phy_table_read_htphy(param_1,2,4,0x10,8,lVar2 + 0x37c);
        wlc_phy_table_read_htphy(param_1,0x29,4,0x10,8,lVar2 + 900);
        wlc_phy_table_read_htphy(param_1,0,4,0x10,8,lVar2 + 0x35c);
        wlc_phy_table_read_htphy(param_1,0x28,4,0x10,8,lVar2 + 0x364);
        wlc_phy_table_read_htphy(param_1,7,1,0x106,0x10,lVar2 + 0x314);
        wlc_phy_table_read_htphy(param_1,7,1,0x108,0x10,lVar2 + 0x318);
        uVar6 = phy_reg_read(param_1,0x410);
        *(undefined2 *)(lVar2 + 0x304) = uVar6;
        uVar6 = phy_reg_read(param_1,0x411);
        *(undefined2 *)(lVar2 + 0x306) = uVar6;
        uVar6 = phy_reg_read(param_1,0x490);
        *(undefined2 *)(lVar2 + 0x30c) = uVar6;
        uVar6 = phy_reg_read(param_1,0x491);
        *(undefined2 *)(lVar2 + 0x30e) = uVar6;
        uVar6 = phy_reg_read(param_1,0x40d);
        *(undefined2 *)(lVar2 + 0x31c) = uVar6;
        uVar6 = phy_reg_read(param_1,0x48d);
        *(undefined2 *)(lVar2 + 800) = uVar6;
        uVar6 = phy_reg_read(param_1,0x412);
        *(undefined2 *)(lVar2 + 0x32c) = uVar6;
        uVar6 = phy_reg_read(param_1,0x413);
        *(undefined2 *)(lVar2 + 0x32e) = uVar6;
        uVar6 = phy_reg_read(param_1,0x492);
        *(undefined2 *)(lVar2 + 0x334) = uVar6;
        uVar6 = phy_reg_read(param_1,0x493);
        *(undefined2 *)(lVar2 + 0x336) = uVar6;
        uVar6 = phy_reg_read(param_1,0x416);
        *(undefined2 *)(lVar2 + 0x33c) = uVar6;
        uVar6 = phy_reg_read(param_1,0x417);
        *(undefined2 *)(lVar2 + 0x33e) = uVar6;
        uVar6 = phy_reg_read(param_1,0x496);
        *(undefined2 *)(lVar2 + 0x344) = uVar6;
        uVar6 = phy_reg_read(param_1,0x497);
        *(undefined2 *)(lVar2 + 0x346) = uVar6;
        local_78 = 0x100;
        local_76 = 0x202;
        local_68 = 0;
        local_67 = 1;
        local_66 = 1;
        local_65 = 1;
        local_48 = *(undefined1 *)(lVar2 + 0x34c);
        local_58 = *(undefined1 *)(lVar2 + 0x35c);
        local_47 = *(undefined1 *)(lVar2 + 0x34d);
        local_57 = *(undefined1 *)(lVar2 + 0x35d);
        local_46 = *(undefined1 *)(lVar2 + 0x34e);
        local_56 = *(undefined1 *)(lVar2 + 0x35d);
        local_45 = *(undefined1 *)(lVar2 + 0x34e);
        local_55 = *(undefined1 *)(lVar2 + 0x35d);
        wlc_phy_table_write_htphy(param_1,2,4,8,8,&local_78);
        wlc_phy_table_write_htphy(param_1,0,4,8,8,&local_48);
        wlc_phy_table_write_htphy(param_1,2,4,0x10,8,&local_68);
        wlc_phy_table_write_htphy(param_1,0,4,0x10,8,&local_58);
        local_68 = 0;
        local_67 = 1;
        local_66 = 2;
        local_65 = 2;
        local_78 = 0x100;
        local_76 = 0x101;
        local_48 = *(undefined1 *)(lVar2 + 0x354);
        local_58 = *(undefined1 *)(lVar2 + 0x364);
        local_47 = *(undefined1 *)(lVar2 + 0x355);
        local_57 = *(undefined1 *)(lVar2 + 0x365);
        local_46 = *(undefined1 *)(lVar2 + 0x356);
        local_56 = *(undefined1 *)(lVar2 + 0x365);
        local_45 = *(undefined1 *)(lVar2 + 0x356);
        local_55 = *(undefined1 *)(lVar2 + 0x365);
        wlc_phy_table_write_htphy(param_1,0x29,4,8,8,&local_68);
        wlc_phy_table_write_htphy(param_1,0x28,4,8,8,&local_48);
        wlc_phy_table_write_htphy(param_1,0x29,4,0x10,8,&local_78);
        wlc_phy_table_write_htphy(param_1,0x28,4,0x10,8,&local_58);
        wlc_phy_table_write_htphy(param_1,7,1,0x106,0x10,&local_3c);
        wlc_phy_table_write_htphy(param_1,7,1,0x108,0x10,&local_3c);
        phy_reg_write(param_1,0x410,0x4c);
        phy_reg_write(param_1,0x490,0x4c);
        phy_reg_write(param_1,0x411,0x824);
        phy_reg_write(param_1,0x491,0x824);
        phy_reg_write(param_1,0x40d,0x51);
        phy_reg_write(param_1,0x48d,0x51);
        phy_reg_write(param_1,0x412,0x4c);
        phy_reg_write(param_1,0x492,0x4c);
        phy_reg_write(param_1,0x413,0x34);
        phy_reg_write(param_1,0x493,0x34);
        phy_reg_write(param_1,0x416,0x2c);
        phy_reg_write(param_1,0x496,0x2c);
        phy_reg_write(param_1,0x417,0x38);
        phy_reg_write(param_1,0x497,0x38);
      }
LAB_001dca9b:
      *(undefined1 *)(lVar2 + 0x302) = 1;
      goto LAB_001dcb80;
    }
    local_39[0] = 2;
    wlc_phy_table_write_htphy(param_1,9,1,2,8,local_39);
    wlc_phy_table_write_htphy(param_1,9,1,10,8,local_39);
    wlc_phy_table_write_htphy(param_1,9,1,0x22,8,local_39);
    wlc_phy_table_write_htphy(param_1,9,1,0x2a,8,local_39);
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      wlc_phy_table_write_htphy(param_1,7,1,0x106,0x10,lVar2 + 0x314);
      wlc_phy_table_write_htphy(param_1,7,1,0x108,0x10,lVar2 + 0x318);
      phy_reg_write(param_1,0x410,*(undefined2 *)(lVar2 + 0x304));
      phy_reg_write(param_1,0x411,*(undefined2 *)(lVar2 + 0x306));
      phy_reg_write(param_1,0x490,*(undefined2 *)(lVar2 + 0x30c));
      phy_reg_write(param_1,0x491,*(undefined2 *)(lVar2 + 0x30e));
      phy_reg_write(param_1,0x40d,*(undefined2 *)(lVar2 + 0x31c));
      phy_reg_write(param_1,0x48d,*(undefined2 *)(lVar2 + 800));
      wlc_phy_table_write_htphy(param_1,0,2,0,8,lVar2 + 0x324);
      wlc_phy_table_write_htphy(param_1,0x28,2,0,8,lVar2 + 0x328);
      if (*(int *)(*(long *)(param_1 + 0x20) + 0x80) == 1) {
        FUN_001cc282(param_1,HTPHY_bphy_desense_lut_eLNA,0x19,0xffffff9c,param_1 + 0x270);
      }
    }
    else {
      wlc_phy_table_write_htphy(param_1,2,4,8,8,lVar2 + 0x36c);
      wlc_phy_table_write_htphy(param_1,0x29,4,8,8,lVar2 + 0x374);
      wlc_phy_table_write_htphy(param_1,0,4,8,8,lVar2 + 0x34c);
      wlc_phy_table_write_htphy(param_1,0x28,4,8,8,lVar2 + 0x354);
      wlc_phy_table_write_htphy(param_1,2,4,0x10,8,lVar2 + 0x37c);
      wlc_phy_table_write_htphy(param_1,0x29,4,0x10,8,lVar2 + 900);
      wlc_phy_table_write_htphy(param_1,0,4,0x10,8,lVar2 + 0x35c);
      wlc_phy_table_write_htphy(param_1,0x28,4,0x10,8,lVar2 + 0x364);
      wlc_phy_table_write_htphy(param_1,7,1,0x106,0x10,lVar2 + 0x314);
      wlc_phy_table_write_htphy(param_1,7,1,0x108,0x10,lVar2 + 0x318);
      phy_reg_write(param_1,0x410,*(undefined2 *)(lVar2 + 0x304));
      phy_reg_write(param_1,0x411,*(undefined2 *)(lVar2 + 0x306));
      phy_reg_write(param_1,0x490,*(undefined2 *)(lVar2 + 0x30c));
      phy_reg_write(param_1,0x491,*(undefined2 *)(lVar2 + 0x30e));
      phy_reg_write(param_1,0x40d,*(undefined2 *)(lVar2 + 0x31c));
      phy_reg_write(param_1,0x48d,*(undefined2 *)(lVar2 + 800));
      phy_reg_write(param_1,0x412,*(undefined2 *)(lVar2 + 0x32c));
      phy_reg_write(param_1,0x413,*(undefined2 *)(lVar2 + 0x32e));
      phy_reg_write(param_1,0x492,*(undefined2 *)(lVar2 + 0x334));
      phy_reg_write(param_1,0x493,*(undefined2 *)(lVar2 + 0x336));
      phy_reg_write(param_1,0x416,*(undefined2 *)(lVar2 + 0x33c));
      phy_reg_write(param_1,0x417,*(undefined2 *)(lVar2 + 0x33e));
      phy_reg_write(param_1,0x496,*(undefined2 *)(lVar2 + 0x344));
      phy_reg_write(param_1,0x497,*(undefined2 *)(lVar2 + 0x346));
    }
  }
  else if ((*(int *)(lVar3 + 0x60) == 0x106b) && (iVar1 == 0x10f)) {
    uVar7 = *(ushort *)(param_1 + 0x17e);
    if (param_2 != '\0') {
LAB_001dca3f:
      if ((uVar7 & 0xc000) != 0) goto LAB_001dcb80;
      local_39[0] = 0x7f;
      local_48 = 0x7f;
      local_47 = 0x7f;
      local_46 = 0x7f;
      wlc_phy_table_write_htphy(param_1,4,1,0xb,8,local_39);
      wlc_phy_table_write_htphy(param_1,4,3,0x11,8,&local_48);
      goto LAB_001dca9b;
    }
    if ((uVar7 & 0xc000) == 0) {
      local_39[0] = 0xf;
      local_48 = 0;
      local_47 = 0;
      local_46 = 3;
      wlc_phy_table_write_htphy(param_1,4,1,0xb,8,local_39);
      if ((*(byte *)(param_1 + 0xc0c) & 1) == 0) {
LAB_001dcb5c:
        uVar8 = 3;
      }
      else {
        uVar8 = 2;
      }
      wlc_phy_table_write_htphy(param_1,4,uVar8,0x11,8,&local_48);
    }
  }
  else {
    if ((iVar1 != 0xf4) && (iVar1 != 0x5da)) goto LAB_001dcb80;
    uVar7 = *(ushort *)(param_1 + 0x17e);
    if (param_2 != '\0') goto LAB_001dca3f;
    if ((uVar7 & 0xc000) == 0) {
      local_39[0] = 0xf;
      local_48 = 0;
      local_47 = 0;
      local_46 = 3;
      wlc_phy_table_write_htphy(param_1,4,1,0xb,8,local_39);
      goto LAB_001dcb5c;
    }
  }
  *(undefined1 *)(lVar2 + 0x302) = 0;
LAB_001dcb80:
  if (bVar4 == 0) {
    wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  return;
}

