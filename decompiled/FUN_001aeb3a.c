
undefined8 FUN_001aeb3a(long param_1)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  ushort uVar4;
  undefined2 uVar5;
  ushort uVar6;
  int iVar7;
  ulong uVar8;
  short sVar9;
  long lVar10;
  undefined8 uVar11;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  ulong uVar15;
  ulong extraout_RDX;
  int iVar16;
  long lVar17;
  undefined4 *puVar18;
  long lVar19;
  byte bVar20;
  uint uVar21;
  uint uVar22;
  ushort uVar23;
  bool bVar24;
  char acStack_13f8 [4572];
  byte local_21c;
  char local_1f8 [4];
  int aiStack_1f4 [4];
  int aiStack_1e4 [51];
  undefined8 local_118;
  int aiStack_110 [10];
  undefined8 local_e8;
  int aiStack_e0 [10];
  ushort local_b8 [8];
  undefined8 local_a8;
  int local_a0;
  int local_98 [4];
  int local_88 [4];
  undefined4 local_78 [4];
  undefined4 local_68;
  undefined8 local_58;
  int local_50;
  char local_48 [8];
  int local_40;
  ushort local_3a [5];
  
  puVar18 = &local_68;
  for (lVar10 = 4; lVar10 != 0; lVar10 = lVar10 + -1) {
    *puVar18 = 0;
    puVar18 = puVar18 + 1;
  }
  puVar18 = local_78;
  for (lVar10 = 4; lVar10 != 0; lVar10 = lVar10 + -1) {
    *puVar18 = 0;
    puVar18 = puVar18 + 1;
  }
  lVar10 = *(long *)(param_1 + 0x138);
  lVar19 = *(long *)(param_1 + 0xf58);
  *(undefined1 *)(lVar10 + 0x8d8) = 1;
  iVar2 = *(int *)(param_1 + 0x164);
  if ((((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) || (iVar2 == 3)) {
    *(undefined1 *)(lVar10 + 0x8d8) = 0;
  }
  if ((*(int *)(param_1 + 0x164) == 1) && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000)) {
    *(undefined1 *)(lVar10 + 0x8d8) = 0;
  }
  wlc_phy_stay_in_carriersearch_acphy(param_1,1);
  wlc_phy_force_rfseq_acphy(param_1,2);
  for (bVar20 = 0; bVar20 < *(byte *)(param_1 + 0x168); bVar20 = bVar20 + 1) {
    FUN_00191d0b(param_1,2,0,bVar20);
  }
  FUN_00191dbb(param_1,0);
  for (uVar21 = 0; (byte)uVar21 < *(byte *)(param_1 + 0x168); uVar21 = uVar21 + 1) {
    uVar22 = uVar21 & 0xff;
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar21 & 0x1f) & 1) != 0) {
      FUN_0019ccd9(param_1,0,local_78 + (uVar21 & 0xff),8,uVar22);
      local_68._0_2_ = *(undefined2 *)(lVar19 + 0x54 + (long)(int)(uVar22 * 2) * 2);
      local_68._2_2_ = *(undefined2 *)(lVar19 + 0x56 + (long)(int)(uVar22 * 2) * 2);
      FUN_0019ccd9(param_1,1,&local_68,8,uVar22);
    }
  }
  lVar19 = *(long *)(param_1 + 0x138);
  uVar4 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar6 == 0x2000) {
    local_21c = 2;
    uVar23 = 0x7f8;
  }
  else {
    local_21c = 0;
    uVar23 = 0xd5eb;
    if (uVar6 == 0x1800) {
      local_21c = 1;
      uVar23 = (-(ushort)(*(char *)(param_1 + 0x116a) == '\0') & 0x201) + 0x43e9;
    }
  }
  *(undefined1 *)(lVar19 + 0x14c) = 1;
  uVar5 = phy_reg_read(param_1,0x40f);
  *(undefined2 *)(lVar19 + 0x24c) = uVar5;
  phy_reg_mod(param_1,0x40f,0x200,0);
  iVar2 = *(int *)(param_1 + 0x164);
  if (((iVar2 == 5) || (iVar2 == 2)) || (iVar2 == 6)) {
    phy_reg_mod(param_1,0x19e,0x3c,0x10);
    phy_reg_mod(param_1,0x19e,1,1);
    phy_reg_mod(param_1,0x19e,1,0);
  }
  for (uVar15 = 0; (byte)uVar15 < *(byte *)(param_1 + 0x168); uVar15 = (ulong)((uint)uVar15 + 1)) {
    uVar21 = (uint)uVar15 & 0xff;
    lVar17 = (long)(int)uVar21;
    sVar9 = (short)uVar15 * 0x200;
    *(undefined1 *)(lVar19 + 0x24e + lVar17) =
         *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x10 + lVar17);
    uVar5 = phy_reg_read(param_1,sVar9 + 0x720);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xa0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x721);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xa8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x722);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xb0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x723);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 200) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x724);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xd8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x725);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xe0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x726);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xf0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x727);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xf8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x728);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xa0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x729);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xa8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x732);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xb8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x733);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xb8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x730);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xc0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x731);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xc0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x734);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 200) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x735);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xd0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x737);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xd0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x738);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xd8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x736);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xe0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x739);
    *(undefined2 *)(lVar19 + 0xe + (lVar17 + 0xe8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x73a);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xe8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x73b);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xf0) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x73c);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xf8) * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x73d);
    *(undefined2 *)(lVar19 + 0x20e + lVar17 * 2) = uVar5;
    uVar5 = phy_reg_read(param_1,sVar9 + 0x747);
    *(undefined2 *)(lVar19 + 0x16 + (lVar17 + 0xb0) * 2) = uVar5;
    uVar8 = uVar15 & 0xff;
    FUN_00199491(param_1,lVar19 + 0x21a + uVar8 * 2,uVar21);
    wlc_phy_table_read_acphy(param_1,7,1,uVar21 + 0x100,0x10,lVar19 + 0x222 + uVar8 * 2);
    wlc_phy_table_read_acphy(param_1,7,1,uVar21 + 0x103,0x10,lVar19 + 0x228 + uVar8 * 2);
    wlc_phy_table_read_acphy(param_1,7,1,uVar21 + 0x106,0x10,lVar19 + 0x22e + uVar8 * 2);
    uVar5 = phy_reg_read(param_1,sVar9 + 0x73e);
    *(undefined2 *)(lVar19 + 0x23c + lVar17 * 2) = uVar5;
  }
  uVar5 = phy_reg_read(param_1,0x401);
  *(undefined2 *)(lVar19 + 0x23a) = uVar5;
  phy_reg_mod(param_1,0x401,7,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa5));
  phy_reg_mod(param_1,0x401,0x7000,0);
  for (uVar21 = 0; bVar20 = (byte)uVar21, bVar20 < *(byte *)(param_1 + 0x168); uVar21 = uVar21 + 1)
  {
    uVar14 = 0x73e;
    if ((bVar20 != 0) && (uVar14 = 0xb3e, bVar20 == 1)) {
      uVar14 = 0x93e;
    }
    phy_reg_mod(param_1,uVar14,0x10,0);
    uVar14 = 0x73e;
    if ((bVar20 != 0) && (uVar14 = 0xb3e, bVar20 == 1)) {
      uVar14 = 0x93e;
    }
    phy_reg_mod(param_1,uVar14,0x20,0);
    uVar14 = 0x73e;
    if ((bVar20 != 0) && (uVar14 = 0xb3e, bVar20 == 1)) {
      uVar14 = 0x93e;
    }
    phy_reg_mod(param_1,uVar14,0x1000,0x1000);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,1,1);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,1,1);
    uVar14 = 0x73a;
    if ((bVar20 != 0) && (uVar14 = 0xb3a, bVar20 == 1)) {
      uVar14 = 0x93a;
    }
    phy_reg_mod(param_1,uVar14,7,uVar23 & 7);
    uVar14 = 0x725;
    if ((bVar20 != 0) && (uVar14 = 0xb25, bVar20 == 1)) {
      uVar14 = 0x925;
    }
    phy_reg_mod(param_1,uVar14,0x20,0x20);
    uVar14 = 0x739;
    if ((bVar20 != 0) && (uVar14 = 0xb39, bVar20 == 1)) {
      uVar14 = 0x939;
    }
    phy_reg_mod(param_1,uVar14,0x7e,uVar23 >> 2 & 0x7e);
    uVar14 = 0x725;
    if ((bVar20 != 0) && (uVar14 = 0xb25, bVar20 == 1)) {
      uVar14 = 0x925;
    }
    phy_reg_mod(param_1,uVar14,2,2);
    uVar14 = 0x73a;
    if ((bVar20 != 0) && (uVar14 = 0xb3a, bVar20 == 1)) {
      uVar14 = 0x93a;
    }
    phy_reg_mod(param_1,uVar14,8,uVar23 >> 6 & 8);
    uVar14 = 0x725;
    if ((bVar20 != 0) && (uVar14 = 0xb25, bVar20 == 1)) {
      uVar14 = 0x925;
    }
    phy_reg_mod(param_1,uVar14,0x40,0x40);
    uVar14 = 0x73a;
    if ((bVar20 != 0) && (uVar14 = 0xb3a, bVar20 == 1)) {
      uVar14 = 0x93a;
    }
    phy_reg_mod(param_1,uVar14,0x10,uVar23 >> 6 & 0x10);
    uVar14 = 0x725;
    if ((bVar20 != 0) && (uVar14 = 0xb25, bVar20 == 1)) {
      uVar14 = 0x925;
    }
    phy_reg_mod(param_1,uVar14,0x80,0x80);
    uVar14 = 0x73a;
    if ((bVar20 != 0) && (uVar14 = 0xb3a, bVar20 == 1)) {
      uVar14 = 0x93a;
    }
    phy_reg_mod(param_1,uVar14,0x60,uVar23 >> 6 & 0x60);
    uVar14 = 0x725;
    if ((bVar20 != 0) && (uVar14 = 0xb25, bVar20 == 1)) {
      uVar14 = 0x925;
    }
    phy_reg_mod(param_1,uVar14,0x100,0x100);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0x20,0);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x20,0x20);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0x40,0);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x40,0x40);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0x800,0);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x800,0x800);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0x1000,0);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x1000,0x1000);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0xe000,0);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x2000,0x2000);
    uVar14 = 0x728;
    if ((bVar20 != 0) && (uVar14 = 0xb28, bVar20 == 1)) {
      uVar14 = 0x928;
    }
    phy_reg_mod(param_1,uVar14,0x3800,0);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x4000,0x4000);
    cVar1 = *(char *)(param_1 + 0x16c);
    if (((((byte)(cVar1 - 2U) < 3) || (cVar1 == '\x12')) || (cVar1 == '\x18')) ||
       (((cVar1 == '\x1a' || (cVar1 == '\"')) || (cVar1 == '\b')))) {
      uVar14 = 0x728;
      if ((bVar20 != 0) && (uVar14 = 0xb28, bVar20 == 1)) {
        uVar14 = 0x928;
      }
      uVar11 = 0;
    }
    else {
      uVar14 = 0x728;
      if ((bVar20 != 0) && (uVar14 = 0xb28, bVar20 == 1)) {
        uVar14 = 0x928;
      }
      uVar11 = 2;
    }
    phy_reg_mod(param_1,uVar14,2,uVar11);
    uVar14 = 0x720;
    if ((bVar20 != 0) && (uVar14 = 0xb20, bVar20 == 1)) {
      uVar14 = 0x920;
    }
    phy_reg_mod(param_1,uVar14,2,2);
    if (((*(int *)(param_1 + 0x160) == 0xb) && (*(int *)(param_1 + 0x164) != 0)) &&
       ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000)) {
      uVar14 = 0x729;
      if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
        uVar14 = 0x929;
      }
      phy_reg_mod(param_1,uVar14,0x20,0x20);
    }
    if ((*(char *)(param_1 + 0x16e) == '\x01') &&
       (((cVar1 = *(char *)(param_1 + 0x16c), (byte)(cVar1 - 2U) < 3 || (cVar1 == '\x12')) ||
        ((cVar1 == '\x18' || (((cVar1 == '\x1a' || (cVar1 == '\"')) || (cVar1 == '\b')))))))) {
      uVar14 = 0x729;
      if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
        uVar14 = 0x929;
      }
      phy_reg_mod(param_1,uVar14,0x20,0x20);
    }
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0x200,0x200);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x200,0x200);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,0x80,0);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,0x80,0x80);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,4,0);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,4,4);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,2,0);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,2,2);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,0x40,0);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,0x40,0x40);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,0x100,0);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,0x100,0x100);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,0x10,0);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,0x10,0x10);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,0x200,0x200);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,0x200,0x200);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,0x20,0x20);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,0x20,0x20);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,8,8);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,8,8);
    uVar14 = 0x736;
    if ((bVar20 != 0) && (uVar14 = 0xb36, bVar20 == 1)) {
      uVar14 = 0x936;
    }
    phy_reg_mod(param_1,uVar14,1,1);
    uVar14 = 0x724;
    if ((bVar20 != 0) && (uVar14 = 0xb24, bVar20 == 1)) {
      uVar14 = 0x924;
    }
    phy_reg_mod(param_1,uVar14,1,1);
    if (local_21c == 2) {
      sVar9 = ((ushort)uVar21 & 0xff) * 2 + 0x441;
    }
    else {
      sVar9 = ((ushort)uVar21 & 0xff) * 0x10 + 0x140 + (ushort)local_21c;
    }
    wlc_phy_table_read_acphy(param_1,7,1,sVar9,0x10,local_3a);
    uVar14 = 0x735;
    if ((bVar20 != 0) && (uVar14 = 0xb35, bVar20 == 1)) {
      uVar14 = 0x935;
    }
    phy_reg_mod(param_1,uVar14,0x700,(local_3a[0] & 7) << 8);
    uVar14 = 0x723;
    if ((bVar20 != 0) && (uVar14 = 0xb23, bVar20 == 1)) {
      uVar14 = 0x923;
    }
    phy_reg_mod(param_1,uVar14,8,8);
    uVar14 = 0x735;
    if ((bVar20 != 0) && (uVar14 = 0xb35, bVar20 == 1)) {
      uVar14 = 0x935;
    }
    phy_reg_mod(param_1,uVar14,0x3800,(local_3a[0] & 0x38) << 8);
    uVar14 = 0x723;
    if ((bVar20 != 0) && (uVar14 = 0xb23, bVar20 == 1)) {
      uVar14 = 0x923;
    }
    phy_reg_mod(param_1,uVar14,0x10,0x10);
    uVar14 = 0x737;
    if ((bVar20 != 0) && (uVar14 = 0xb37, bVar20 == 1)) {
      uVar14 = 0x937;
    }
    phy_reg_mod(param_1,uVar14,0xff,(char)(local_3a[0] >> 6));
    uVar14 = 0x723;
    if ((bVar20 != 0) && (uVar14 = 0xb23, bVar20 == 1)) {
      uVar14 = 0x923;
    }
    phy_reg_mod(param_1,uVar14,0x200,0x200);
    uVar14 = 0x735;
    if ((bVar20 != 0) && (uVar14 = 0xb35, bVar20 == 1)) {
      uVar14 = 0x935;
    }
    phy_reg_mod(param_1,uVar14,0x4000,0);
    uVar14 = 0x723;
    if ((bVar20 != 0) && (uVar14 = 0xb23, bVar20 == 1)) {
      uVar14 = 0x923;
    }
    phy_reg_mod(param_1,uVar14,0x20,0x20);
    uVar14 = 0x735;
    if ((bVar20 != 0) && (uVar14 = 0xb35, bVar20 == 1)) {
      uVar14 = 0x935;
    }
    phy_reg_mod(param_1,uVar14,1,1);
    uVar14 = 0x723;
    if ((bVar20 != 0) && (uVar14 = 0xb23, bVar20 == 1)) {
      uVar14 = 0x923;
    }
    phy_reg_mod(param_1,uVar14,1,1);
    uVar14 = 0x729;
    if ((bVar20 != 0) && (uVar14 = 0xb29, bVar20 == 1)) {
      uVar14 = 0x929;
    }
    phy_reg_mod(param_1,uVar14,0x100,0x100);
    uVar14 = 0x721;
    if ((bVar20 != 0) && (uVar14 = 0xb21, bVar20 == 1)) {
      uVar14 = 0x921;
    }
    phy_reg_mod(param_1,uVar14,0x100,0x100);
    uVar5 = phy_reg_read(param_1,(short)(uVar21 << 9) + 0x678);
    uVar14 = 0x678;
    *(undefined2 *)(lVar19 + 0x244 + (ulong)(uVar21 & 0xff) * 2) = uVar5;
    if ((bVar20 != 0) && (uVar14 = 0xa78, bVar20 == 1)) {
      uVar14 = 0x878;
    }
    phy_reg_mod(param_1,uVar14,1,0);
  }
  phy_reg_mod(param_1,0x19e,2,uVar4 & 2);
  FUN_0019585a(param_1);
  FUN_001ae5da(param_1);
  local_48[0] = '\b';
  uVar4 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar4 != 0x2000) {
    local_48[0] = (uVar4 == 0x1800) * '\x02' + '\x02';
  }
  local_48[1] = -local_48[0];
  bVar24 = true;
  if ((uVar4 != 0x2000) && (bVar24 = false, uVar4 == 0x1800)) {
    bVar24 = *(int *)(param_1 + 0x164) == 3;
  }
  uVar4 = 2;
  *(bool *)(*(long *)(param_1 + 0x138) + 0x8c4) = bVar24;
  if (*(char *)(*(long *)(param_1 + 0x138) + 0x8c4) != '\0') {
    uVar4 = *(ushort *)(param_1 + 0x17e) & 0x3800;
    if (uVar4 == 0x2000) {
      local_48[2] = 0x18;
      local_48[3] = 0xe8;
      uVar4 = 6;
      local_48[4] = 0x20;
      local_48[5] = 0xe0;
    }
    else {
      if (uVar4 == 0x1800) {
        local_48[2] = 0xf;
        local_48[3] = 0xf1;
      }
      else {
        local_48[2] = 7;
        local_48[3] = 0xf9;
      }
      uVar4 = 4;
    }
  }
  uVar21 = 0;
  do {
    if (uVar4 <= ((ushort)uVar21 & 0xff)) {
      lVar19 = (ulong)*(byte *)(param_1 + 0x168) << 2;
      for (lVar10 = 0; lVar10 != lVar19; lVar10 = lVar10 + 4) {
        *(undefined4 *)((long)local_88 + lVar10) = 0;
        *(undefined4 *)((long)local_98 + lVar10) = 0;
        *(undefined4 *)((long)&local_a8 + lVar10) = 0;
      }
      iVar2 = 0;
      for (uVar15 = 0; (int)(char)uVar15 < (int)(uint)uVar4; uVar15 = (ulong)((int)uVar15 + 1)) {
        lVar17 = (long)(char)uVar15 * 0x24;
        iVar7 = (int)local_1f8[lVar17];
        for (lVar10 = 0; lVar10 != lVar19; lVar10 = lVar10 + 4) {
          iVar13 = *(int *)((long)aiStack_1f4 + lVar10 + lVar17);
          *(int *)((long)local_98 + lVar10) = *(int *)((long)local_98 + lVar10) + iVar13;
          *(int *)((long)local_88 + lVar10) = *(int *)((long)local_88 + lVar10) + iVar7 * iVar13;
          *(int *)((long)&local_a8 + lVar10) =
               *(int *)((long)&local_a8 + lVar10) + *(int *)((long)aiStack_1e4 + lVar10 + lVar17);
        }
        iVar2 = iVar2 + iVar7 * iVar7;
      }
      for (bVar20 = 0; bVar20 < *(byte *)(param_1 + 0x168); bVar20 = bVar20 + 1) {
        uVar21 = (uint)bVar20;
        lVar19 = (long)(int)uVar21;
        uVar22 = (uint)uVar4;
        iVar7 = (int)(*(int *)((long)&local_a8 + lVar19 * 4) + (uint)(uVar4 >> 1)) / (int)uVar22;
        lVar10 = (long)(int)((local_98[lVar19] >> 0x1f | 1U) * (uint)(uVar4 >> 1) + local_98[lVar19]
                            );
        wlc_phy_cordic(lVar10 / (long)(int)uVar22 & 0xffffffff,&local_58,
                       lVar10 % (long)(int)uVar22 & 0xffffffff);
        iVar13 = (iVar7 * (int)local_58 >> 0xf) + 1;
        uVar15 = (ulong)CONCAT22((short)(iVar13 >> 0x11),(short)(iVar13 >> 1)) & 0xffffffffffff03ff;
        local_b8[lVar19 * 2 + 1] = (ushort)((iVar7 * local_58._4_4_ >> 0xf) + 1 >> 1) & 0x3ff;
        local_b8[lVar19 * 2] = (ushort)uVar15;
        if (*(char *)(*(long *)(param_1 + 0x138) + 0x8c4) != '\0') {
          iVar7 = 0x1e;
          uVar6 = *(ushort *)(param_1 + 0x17e) & 0x3800;
          if ((uVar6 != 0x2000) && (iVar7 = 8, uVar6 == 0x1800)) {
            iVar7 = 0xf;
          }
          uVar15 = (long)(-local_88[(int)uVar21] * iVar7) % (long)iVar2 & 0xffffffff;
          *(int *)(*(long *)(param_1 + 0x138) + 0x8c8 + (long)(int)uVar21 * 4) =
               ((-local_88[(int)uVar21] * iVar7) / iVar2 >> 0xe) + 1 >> 1;
        }
      }
      for (bVar20 = 0; bVar20 < *(byte *)(param_1 + 0x168); bVar20 = bVar20 + 1) {
        FUN_00191d0b(param_1,1,local_b8 + (ulong)bVar20 * 2,bVar20);
        uVar15 = extraout_RDX;
      }
      if (*(char *)(*(long *)(param_1 + 0x138) + 0x8c4) != '\0') {
        FUN_00191dbb(param_1,1,uVar15);
      }
      FUN_00196251(param_1);
      FUN_0019dc93(param_1);
      for (bVar20 = 0; bVar20 < *(byte *)(param_1 + 0x168); bVar20 = bVar20 + 1) {
        if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (bVar20 & 0x1f) & 1) != 0) {
          FUN_0019ccd9(param_1,1,local_78 + bVar20,8);
        }
      }
      wlc_phy_stay_in_carriersearch_acphy(param_1,0);
      return 0;
    }
    uVar22 = uVar21 & 0xff;
    cVar1 = local_48[(int)uVar22];
    local_1f8[(long)(int)uVar22 * 0x24] = cVar1;
    wlc_phy_tx_tone_acphy(param_1,(int)((short)(cVar1 * 1000) >> 1),0xb5,0,0,0);
    if (*(char *)(*(long *)(param_1 + 0x138) + 0x8c4) == '\0') {
      uVar14 = 0x4000;
    }
    else {
      uVar14 = 0x3000;
    }
    wlc_phy_rx_iq_est_acphy(param_1,&local_e8,uVar14);
    if (*(char *)(lVar10 + 0x8d8) == '\x01') {
      FUN_00196251(param_1);
      wlc_phy_rx_iq_est_acphy(param_1,&local_118,0x4000);
      FUN_0019585a(param_1);
    }
    wlc_phy_stopplayback_acphy(param_1);
    for (bVar20 = 0; bVar20 < *(byte *)(param_1 + 0x168); bVar20 = bVar20 + 1) {
      lVar19 = (long)(int)(uint)bVar20;
      local_58 = *(undefined8 *)((long)&local_e8 + lVar19 * 0xc);
      local_50 = aiStack_e0[lVar19 * 3];
      local_a8 = *(undefined8 *)((long)&local_118 + lVar19 * 0xc);
      local_a0 = aiStack_110[lVar19 * 3];
      lVar19 = *(long *)(param_1 + 0x138);
      FUN_00198549(&local_58,local_98);
      iVar2 = local_98[1];
      if (*(char *)(lVar19 + 0x8d8) == '\x01') {
        FUN_00198549(&local_a8,local_88);
        iVar13 = local_88[2];
        iVar7 = local_98[2];
        iVar12 = local_a0 + local_a8._4_4_;
        iVar16 = local_50 + local_58._4_4_;
        bVar3 = wlc_phy_nbits(iVar12);
        uVar6 = (ushort)bVar3 + (bVar3 & 1);
        cVar1 = (char)uVar6;
        if (uVar6 < 0xb) {
          iVar16 = iVar16 << (10U - cVar1 & 0x1f);
        }
        else {
          iVar16 = iVar16 >> (cVar1 - 10U & 0x1f);
        }
        if (iVar16 == 0) goto LAB_001b0264;
        lVar19 = (long)((iVar16 >> 1) + (iVar12 << (0x1eU - cVar1 & 0x1f)));
        iVar12 = wlc_phy_sqrt_int(lVar19 / (long)iVar16 & 0xffffffff,iVar16,
                                  lVar19 % (long)iVar16 & 0xffffffff);
        if (iVar12 < 0x2a) goto LAB_001b0264;
        iVar7 = (iVar12 * (iVar7 - iVar13) >> 10) + iVar7;
        iVar13 = iVar7 >> 1;
        iVar13 = wlc_phy_sqrt_int(0x40000000 - iVar13 * iVar13);
        wlc_phy_inv_cordic(CONCAT44(iVar13 * 2,iVar7),&local_40);
      }
      else {
LAB_001b0264:
        local_40 = local_98[0];
      }
      lVar19 = (long)(int)(uint)bVar20 + (long)(int)uVar22 * 9;
      aiStack_1f4[lVar19] = local_40;
      aiStack_1e4[lVar19] = iVar2;
    }
    uVar21 = uVar21 + 1;
  } while( true );
}

