
void FUN_0019bc45(long param_1,char param_2,char param_3)

{
  long lVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  ushort uVar5;
  undefined2 uVar6;
  uint uVar7;
  long lVar8;
  short sVar9;
  undefined1 uVar10;
  undefined8 uVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  byte bVar14;
  ulong uVar15;
  uint uVar16;
  undefined2 local_e8;
  uint local_d0;
  undefined1 local_c8 [16];
  undefined1 local_b8 [16];
  undefined1 local_a8;
  undefined1 local_a7;
  undefined1 local_a6;
  undefined1 local_a5;
  undefined1 local_a4;
  undefined1 local_a3;
  undefined1 local_a2;
  undefined1 local_a1;
  undefined1 local_a0;
  undefined1 local_9f;
  undefined1 local_98;
  undefined1 local_97;
  undefined1 local_96;
  undefined1 local_95;
  undefined1 local_94;
  undefined1 local_93;
  undefined1 local_92;
  undefined1 local_91;
  undefined1 local_90;
  undefined1 local_8f;
  undefined1 local_88;
  undefined1 local_87;
  undefined1 local_86;
  undefined1 local_85;
  undefined1 local_84;
  undefined1 local_83;
  undefined1 local_82;
  undefined1 local_81;
  undefined1 local_80;
  undefined1 local_7f;
  undefined1 local_78;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 local_72;
  undefined1 local_71;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_48;
  undefined1 local_47;
  
  local_58 = 3;
  local_57 = 3;
  local_56 = 3;
  local_55 = 3;
  local_54 = 3;
  local_53 = 3;
  local_52 = 3;
  local_51 = 3;
  local_50 = 3;
  local_4f = 3;
  local_68 = 2;
  local_67 = 2;
  local_66 = 2;
  local_65 = 2;
  local_64 = 2;
  local_63 = 2;
  local_62 = 2;
  local_61 = 2;
  local_60 = 2;
  local_5f = 2;
  local_78 = 7;
  local_77 = 7;
  local_76 = 7;
  local_75 = 7;
  local_74 = 7;
  local_73 = 7;
  local_72 = 7;
  local_71 = 7;
  local_70 = 7;
  local_6f = 7;
  local_88 = 2;
  local_87 = 2;
  local_86 = 2;
  local_85 = 2;
  local_84 = 2;
  local_83 = 2;
  local_82 = 2;
  local_81 = 2;
  local_80 = 2;
  local_7f = 2;
  local_98 = 0x10;
  local_97 = 0x10;
  local_96 = 0x10;
  local_95 = 0x10;
  local_94 = 0x10;
  local_93 = 0x10;
  local_92 = 0x10;
  local_91 = 0x10;
  local_90 = 0x10;
  local_8f = 0x10;
  local_a8 = 5;
  local_a7 = 5;
  local_a6 = 5;
  local_a5 = 5;
  local_a4 = 5;
  local_a3 = 5;
  local_a2 = 5;
  local_a1 = 5;
  local_a0 = 5;
  local_9f = 5;
  lVar3 = *(long *)(param_1 + 0x138);
  iVar2 = *(int *)(param_1 + 0x164);
  if (*(char *)(lVar3 + 0x341) == '\0') {
    osl_memcpy(local_b8,&local_98,*(undefined1 *)(lVar3 + 0x64d));
    uVar10 = *(undefined1 *)(lVar3 + 0x64d);
    puVar12 = &local_a8;
  }
  else {
    osl_memcpy(local_b8,&local_78,*(undefined1 *)(lVar3 + 0x64d));
    uVar10 = *(undefined1 *)(lVar3 + 0x64d);
    puVar12 = &local_88;
  }
  uVar15 = 0;
  osl_memcpy(local_c8,puVar12,uVar10);
  uVar5 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  uVar6 = phy_reg_read(param_1,0x16c);
  phy_reg_mod(param_1,0x16c,0x40,0x40);
  FUN_0019a398(param_1,1);
  FUN_0019a60c(param_1,1);
  FUN_0019a398(param_1,2);
  FUN_0019a60c(param_1,2);
  do {
    bVar14 = (byte)uVar15;
    if (*(byte *)(param_1 + 0x168) <= bVar14) {
      phy_reg_write(param_1,0x16c,uVar6);
      phy_reg_mod(param_1,0x19e,2,uVar5 & 2);
      return;
    }
    if (bVar14 == 0) {
      local_e8 = 0x45;
      uVar13 = 0x44;
    }
    else {
      local_e8 = 0x85;
      if (bVar14 == 1) {
        local_e8 = 0x65;
      }
      uVar13 = 0x84;
      if (bVar14 == 1) {
        uVar13 = 100;
      }
    }
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      lVar1 = lVar3 + (uVar15 & 0xff) * 3;
      local_47 = *(undefined1 *)(lVar1 + 0x3e0);
      lVar8 = lVar1 + 0x450;
      *(undefined1 *)(lVar1 + 0x45e) = local_47;
      *(undefined1 *)(lVar1 + 0x45f) = *(undefined1 *)(lVar1 + 0x3e1);
      uVar10 = *(undefined1 *)(lVar1 + 0x3e2);
    }
    else if ((byte)*(ushort *)(param_1 + 0x17e) < 100) {
      lVar1 = lVar3 + (uVar15 & 0xff) * 3;
      lVar8 = lVar1 + 0x450;
      local_47 = *(undefined1 *)(lVar1 + 0x3ec);
      *(undefined1 *)(lVar1 + 0x45e) = local_47;
      *(undefined1 *)(lVar1 + 0x45f) = *(undefined1 *)(lVar1 + 0x3ed);
      uVar10 = *(undefined1 *)(lVar1 + 0x3ee);
    }
    else {
      lVar1 = lVar3 + (uVar15 & 0xff) * 3;
      lVar8 = lVar1 + 0x450;
      local_47 = *(undefined1 *)(lVar1 + 0x404);
      *(undefined1 *)(lVar1 + 0x45e) = local_47;
      *(undefined1 *)(lVar1 + 0x45f) = *(undefined1 *)(lVar1 + 0x405);
      uVar10 = *(undefined1 *)(lVar1 + 0x406);
    }
    *(undefined1 *)(lVar8 + 0x10) = uVar10;
    uVar4 = (uint)uVar15;
    local_d0 = uVar4 & 0xff;
    uVar16 = *(byte *)(lVar3 + 0x45f + (long)(int)(uVar4 & 0xff) * 3) + 2;
    local_48 = local_47;
    if (*(char *)(lVar3 + 0x912) != '\0') {
      sVar9 = (short)(uVar4 << 9) + 0x73e;
      uVar7 = phy_reg_read(param_1,sVar9);
      phy_reg_write(param_1,sVar9,uVar7 & 0xfb3f);
    }
    if (bVar14 == 1) {
      if ((iVar2 != 0) && ((*(uint *)(param_1 + 0x164) == 3 || (*(uint *)(param_1 + 0x164) < 2)))) {
        phy_reg_mod(param_1,0x8f9,0x7f00,(uVar16 & 0xff) << 8);
        uVar11 = 0x8f9;
        goto LAB_0019c0f3;
      }
    }
    else {
      if (bVar14 == 0) {
        if (iVar2 == 0) {
          phy_reg_mod(param_1,0x289,0x7f00,(uVar16 & 0xff) << 8);
          uVar11 = 0x289;
        }
        else {
          if ((*(uint *)(param_1 + 0x164) != 3) && (1 < *(uint *)(param_1 + 0x164)))
          goto LAB_0019c0fb;
          phy_reg_mod(param_1,0x6f9,0x7f00,(uVar16 & 0xff) << 8);
          uVar11 = 0x6f9;
        }
      }
      else {
        if (((bVar14 != 2) || (iVar2 == 0)) ||
           ((*(uint *)(param_1 + 0x164) != 3 && (1 < *(uint *)(param_1 + 0x164)))))
        goto LAB_0019c0fb;
        phy_reg_mod(param_1,0xaf9,0x7f00,(uVar16 & 0xff) << 8);
        uVar11 = 0xaf9;
      }
LAB_0019c0f3:
      phy_reg_mod(param_1,uVar11,0x7f,2);
    }
LAB_0019c0fb:
    wlc_phy_table_write_acphy(param_1,uVar13,2,0,8,&local_48);
    lVar1 = lVar3 + 0x46a + (long)(int)local_d0 * 0x78;
    osl_memcpy(lVar1,&local_48,*(undefined1 *)(lVar3 + 0x64a));
    if ((param_3 != '\0') || (param_2 != '\0')) {
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           ((acphychipid == 0xaa06 || (uVar11 = 0x73b, acphychipid == 0x4350)))) {
          uVar11 = 0x173b;
        }
        phy_reg_write(param_1,uVar11,(-(ushort)(*(char *)(lVar3 + 0x66e) == '\0') & 0xfffc) + 0x1c);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 ||
            ((acphychipid == 0xaa06 || (uVar11 = 0x726, acphychipid == 0x4350)))))) {
          uVar11 = 0x1726;
        }
        phy_reg_write(param_1,uVar11,0xc);
        wlc_phy_table_write_acphy(param_1,uVar13,10,0x20,8,&local_58);
        wlc_phy_table_write_acphy(param_1,local_e8,10,0x20,8,&local_68);
        uVar10 = *(undefined1 *)(lVar3 + 0x64d);
        puVar12 = &local_58;
      }
      else {
        if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
           ((acphychipid == 0xaa06 || (uVar11 = 0x73b, acphychipid == 0x4350)))) {
          uVar11 = 0x173b;
        }
        phy_reg_write(param_1,uVar11,0x2c);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 ||
            ((acphychipid == 0xaa06 || (uVar11 = 0x726, acphychipid == 0x4350)))))) {
          uVar11 = 0x1726;
        }
        phy_reg_write(param_1,uVar11,0xc);
        wlc_phy_table_write_acphy(param_1,uVar13,10,0x20,8,local_b8);
        wlc_phy_table_write_acphy(param_1,local_e8,10,0x20,8,local_c8);
        uVar10 = *(undefined1 *)(lVar3 + 0x64d);
        puVar12 = local_b8;
      }
      osl_memcpy(lVar1 + 0x1e,puVar12,uVar10);
      if (param_2 != '\0') {
        lVar8 = lVar3 + 0x490 + (long)(int)local_d0 * 0x78;
        wlc_phy_table_read_acphy(param_1,local_e8,1,0,8,lVar8 + 0x16);
        wlc_phy_table_read_acphy(param_1,local_e8,10,0x20,8,lVar8 + 0x34);
        wlc_phy_table_read_acphy(param_1,uVar13,8,0x60,8,lVar1 + 0x28);
        wlc_phy_table_read_acphy(param_1,uVar13,8,0x70,8,lVar1 + 0x32);
        wlc_phy_table_read_acphy(param_1,local_e8,8,0x60,8,lVar8 + 0x3e);
        wlc_phy_table_read_acphy(param_1,local_e8,8,0x70,8,lVar8 + 0x48);
      }
    }
    uVar15 = (ulong)(uVar4 + 1);
  } while( true );
}

