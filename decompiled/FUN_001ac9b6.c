
int FUN_001ac9b6(long param_1,char param_2,char param_3,char param_4)

{
  byte bVar1;
  char cVar2;
  long lVar3;
  short sVar4;
  undefined1 uVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  ushort uVar10;
  ushort uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  undefined2 *puVar15;
  ulong uVar16;
  long lVar17;
  undefined1 uVar18;
  long lVar19;
  ushort uVar20;
  undefined8 uVar21;
  byte bVar22;
  byte bVar23;
  uint uVar24;
  int iVar25;
  undefined1 *puVar26;
  undefined1 uVar27;
  ushort uVar28;
  bool bVar29;
  byte local_18c;
  undefined2 *local_188;
  int local_17c;
  undefined1 *local_178;
  byte local_168;
  undefined2 *local_150;
  uint local_140;
  undefined1 local_138 [48];
  undefined1 local_108 [32];
  undefined2 local_e8;
  undefined2 local_e6;
  undefined2 local_e4;
  undefined2 local_e2;
  undefined2 local_e0;
  undefined2 local_de;
  undefined2 local_d8;
  undefined2 local_d6;
  undefined2 local_d4;
  undefined2 local_d2;
  undefined2 local_d0;
  undefined2 local_ce;
  undefined2 local_c8;
  undefined2 local_c6;
  undefined2 local_c4;
  undefined2 local_c2;
  undefined2 local_c0;
  undefined2 local_be;
  undefined2 local_b8;
  undefined2 local_b6;
  undefined2 local_b4;
  undefined2 local_b2;
  undefined2 local_b0;
  undefined2 local_ae;
  undefined1 local_a8;
  undefined1 local_a7;
  undefined1 local_a6;
  undefined1 local_a5;
  undefined1 local_a4;
  undefined1 local_a3;
  undefined1 local_a2 [10];
  undefined2 local_98;
  undefined2 local_96;
  undefined2 local_94;
  undefined2 local_88;
  undefined2 local_86;
  undefined2 local_78;
  undefined2 local_76;
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  undefined1 local_48 [14];
  undefined2 local_3a [5];
  
  local_3a[0] = 0;
  lVar3 = *(long *)(param_1 + 0xf58);
  local_b8 = 0x434;
  local_b6 = 0x334;
  local_b4 = 0x84;
  local_b2 = 0x267;
  local_b0 = 0x56;
  local_ae = 0x234;
  local_c8 = 0x423;
  local_c6 = 0x334;
  local_c4 = 0x73;
  local_c2 = 0x267;
  local_c0 = 0x45;
  local_be = 0x234;
  local_d8 = 0x434;
  local_d6 = 0x334;
  local_d4 = 0x84;
  local_d2 = 0x267;
  local_d0 = 0x56;
  local_ce = 0x234;
  local_e8 = 0x423;
  local_e6 = 0x334;
  local_e4 = 0x73;
  local_e2 = 0x267;
  local_e0 = 0x45;
  puVar26 = local_108;
  for (lVar17 = 0x1e; lVar17 != 0; lVar17 = lVar17 + -1) {
    *puVar26 = 0;
    puVar26 = puVar26 + 1;
  }
  local_de = 0x234;
  local_78 = 0x84;
  local_76 = 0x56;
  local_88 = 0x73;
  bVar1 = *(byte *)(param_1 + 0x168);
  local_86 = 0x45;
  local_98 = 0;
  local_96 = 0;
  local_94 = 0;
  wlc_phy_stay_in_carriersearch_acphy(param_1,1);
  local_168 = 2;
  uVar10 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar10 != 0x2000) {
    local_168 = uVar10 == 0x1800;
  }
  if ((((((*(char *)(param_1 + 0x16e) == '\x01') &&
         (cVar2 = *(char *)(param_1 + 0x16c), 2 < (byte)(cVar2 - 2U))) && (cVar2 != '\x12')) &&
       ((cVar2 != '\x18' && (cVar2 != '\x1a')))) && (cVar2 != '\"')) && (cVar2 != '\b')) {
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      local_48[0] = 0x87;
      local_48[1] = 0x77;
      local_48[2] = 0x77;
      local_58[0] = 0x79;
    }
    else {
      local_48[0] = 0x78;
      local_48[1] = 0x88;
      local_48[2] = 0x98;
      local_58[0] = 0x89;
    }
    local_c8 = 0x434;
    local_c4 = 0x84;
    local_c0 = 0x56;
    local_a7 = 0x2d;
    local_a6 = 0x1d;
    local_a5 = 0xd;
    local_a4 = 7;
    local_a3 = 3;
    local_a2[0] = 1;
  }
  else {
    local_48[0] = 0x76;
    local_48[1] = 0x87;
    local_48[2] = 0x98;
    local_58[0] = 0x79;
    local_c8 = 0x423;
    local_c4 = 0x73;
    local_c0 = 0x45;
    local_a7 = 0x1e;
    local_a6 = 0xf;
    local_a5 = 7;
    local_a4 = 3;
    local_a3 = 1;
  }
  local_58[2] = 0x79;
  local_58[1] = 0x79;
  local_a8 = 0x3d;
  local_be = 0x234;
  local_c2 = 0x267;
  local_c6 = 0x334;
  uVar8 = phy_reg_read(param_1,0x140);
  wlc_phy_classifier_acphy(param_1,7,4);
  FUN_0019454f(param_1);
  lVar17 = *(long *)(param_1 + 0x138);
  uVar9 = phy_reg_read(param_1,0x19e);
  *(undefined2 *)(lVar17 + 0x8c) = uVar9;
  uVar9 = phy_reg_read(param_1,0x40f);
  *(undefined2 *)(lVar17 + 0x8e) = uVar9;
  uVar10 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  uVar11 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  if (uVar11 == 0x2000) {
    bVar22 = 2;
    uVar28 = 0x7f8;
  }
  else {
    bVar22 = 0;
    uVar28 = 0xd5eb;
    if (uVar11 == 0x1800) {
      bVar22 = 1;
      uVar28 = (-(ushort)(*(char *)(param_1 + 0x116a) == '\0') & 0x201) + 0x43e9;
    }
  }
  iVar12 = *(int *)(param_1 + 0x164);
  if (((iVar12 == 5) || (iVar12 == 2)) || (iVar12 == 6)) {
    phy_reg_mod(param_1,0x19e,0x3c,0x10);
    phy_reg_mod(param_1,0x19e,1,1);
    phy_reg_mod(param_1,0x19e,1,0);
  }
  phy_reg_mod(param_1,0x40f,0x200,0);
  iVar12 = bVar22 + 3;
  for (uVar24 = 0; bVar22 = (byte)uVar24, bVar22 < *(byte *)(param_1 + 0x168); uVar24 = uVar24 + 1)
  {
    iVar25 = uVar24 * 0x200;
    local_140 = uVar24 & 0xff;
    uVar9 = phy_reg_read(param_1,iVar25 + 0x73eU & 0xffff);
    *(undefined2 *)(lVar17 + 0xa8 + (long)(int)local_140 * 2) = uVar9;
    phy_reg_write(param_1,iVar25 + 0x73eU & 0xffff,0);
    uVar21 = 0x73e;
    if ((bVar22 != 0) && (uVar21 = 0xb3e, bVar22 == 1)) {
      uVar21 = 0x93e;
    }
    phy_reg_mod(param_1,uVar21,0x10,0);
    uVar21 = 0x73e;
    if ((bVar22 != 0) && (uVar21 = 0xb3e, bVar22 == 1)) {
      uVar21 = 0x93e;
    }
    phy_reg_mod(param_1,uVar21,0x20,0);
    uVar21 = 0x73e;
    if ((bVar22 != 0) && (uVar21 = 0xb3e, bVar22 == 1)) {
      uVar21 = 0x93e;
    }
    phy_reg_mod(param_1,uVar21,0x40,0);
    uVar21 = 0x73e;
    if ((bVar22 != 0) && (uVar21 = 0xb3e, bVar22 == 1)) {
      uVar21 = 0x93e;
    }
    phy_reg_mod(param_1,uVar21,0x80,0);
    uVar21 = 0x73e;
    if ((bVar22 != 0) && (uVar21 = 0xb3e, bVar22 == 1)) {
      uVar21 = 0x93e;
    }
    phy_reg_mod(param_1,uVar21,0x1000,0x1000);
    uVar21 = 0x73e;
    if ((bVar22 != 0) && (uVar21 = 0xb3e, bVar22 == 1)) {
      uVar21 = 0x93e;
    }
    phy_reg_mod(param_1,uVar21,0x400,0x400);
    sVar4 = (short)iVar25;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x725);
    lVar19 = (long)(int)local_140;
    *(undefined2 *)(lVar17 + 0x90 + lVar19 * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x739);
    *(undefined2 *)(lVar17 + 8 + (lVar19 + 0x48) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x73a);
    *(undefined2 *)(lVar17 + 0x10 + (lVar19 + 0x48) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x721);
    *(undefined2 *)(lVar17 + 0xb0 + lVar19 * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x729);
    *(undefined2 *)(lVar17 + 8 + (lVar19 + 0x58) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x720);
    *(undefined2 *)(lVar17 + 0x10 + (lVar19 + 0x58) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x728);
    *(undefined2 *)(lVar17 + 8 + (lVar19 + 0x60) * 2) = uVar9;
    uVar13 = iVar25 + 0x724U & 0xffff;
    uVar9 = phy_reg_read(param_1,uVar13);
    *(undefined2 *)(lVar17 + 0x10 + (lVar19 + 0x60) * 2) = uVar9;
    uVar14 = iVar25 + 0x736U & 0xffff;
    uVar9 = phy_reg_read(param_1,uVar14);
    *(undefined2 *)(lVar17 + 8 + (lVar19 + 0x68) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x723);
    *(undefined2 *)(lVar17 + 0x10 + (lVar19 + 0x68) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x735);
    *(undefined2 *)(lVar17 + 8 + (lVar19 + 0x70) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x737);
    *(undefined2 *)(lVar17 + 0x10 + (lVar19 + 0x70) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x738);
    *(undefined2 *)(lVar17 + 8 + (lVar19 + 0x78) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x727);
    *(undefined2 *)(lVar17 + 0x10 + (lVar19 + 0x78) * 2) = uVar9;
    uVar9 = phy_reg_read(param_1,sVar4 + 0x73c);
    uVar21 = 0x720;
    *(undefined2 *)(lVar17 + 0x108 + lVar19 * 2) = uVar9;
    if ((bVar22 != 0) && (uVar21 = 0xb20, bVar22 == 1)) {
      uVar21 = 0x920;
    }
    phy_reg_mod(param_1,uVar21,2,2);
    uVar21 = 0x728;
    if ((bVar22 != 0) && (uVar21 = 0xb28, bVar22 == 1)) {
      uVar21 = 0x928;
    }
    phy_reg_mod(param_1,uVar21,2,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x40,0x40);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x40,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x80,0x80);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x80,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x20,0x20);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x20,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x2000,0x2000);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0xe000,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x800,0x800);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x800,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x400,0x400);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x400,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x4000,0x4000);
    uVar21 = 0x728;
    if ((bVar22 != 0) && (uVar21 = 0xb28, bVar22 == 1)) {
      uVar21 = 0x928;
    }
    phy_reg_mod(param_1,uVar21,0x3800,0);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x1000,0x1000);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x1000,0);
    uVar21 = 0x720;
    if ((bVar22 != 0) && (uVar21 = 0xb20, bVar22 == 1)) {
      uVar21 = 0x920;
    }
    phy_reg_mod(param_1,uVar21,0x20,0x20);
    uVar21 = 0x728;
    if ((bVar22 != 0) && (uVar21 = 0xb28, bVar22 == 1)) {
      uVar21 = 0x928;
    }
    phy_reg_mod(param_1,uVar21,0x20,0x20);
    uVar21 = 0x720;
    if ((bVar22 != 0) && (uVar21 = 0xb20, bVar22 == 1)) {
      uVar21 = 0x920;
    }
    phy_reg_mod(param_1,uVar21,0x40,0x40);
    uVar21 = 0x728;
    if ((bVar22 != 0) && (uVar21 = 0xb28, bVar22 == 1)) {
      uVar21 = 0x928;
    }
    phy_reg_mod(param_1,uVar21,0x40,0x40);
    uVar21 = 0x720;
    if ((bVar22 != 0) && (uVar21 = 0xb20, bVar22 == 1)) {
      uVar21 = 0x920;
    }
    phy_reg_mod(param_1,uVar21,0x10,0x10);
    uVar21 = 0x728;
    if ((bVar22 != 0) && (uVar21 = 0xb28, bVar22 == 1)) {
      uVar21 = 0x928;
    }
    phy_reg_mod(param_1,uVar21,0x10,0x10);
    uVar21 = 0x721;
    if ((bVar22 != 0) && (uVar21 = 0xb21, bVar22 == 1)) {
      uVar21 = 0x921;
    }
    phy_reg_mod(param_1,uVar21,0x100,0x100);
    uVar21 = 0x729;
    if ((bVar22 != 0) && (uVar21 = 0xb29, bVar22 == 1)) {
      uVar21 = 0x929;
    }
    phy_reg_mod(param_1,uVar21,0x100,0x100);
    uVar21 = 0x727;
    if ((bVar22 != 0) && (uVar21 = 0xb27, bVar22 == 1)) {
      uVar21 = 0x927;
    }
    phy_reg_mod(param_1,uVar21,4,4);
    uVar21 = 0x73c;
    if ((bVar22 != 0) && (uVar21 = 0xb3c, bVar22 == 1)) {
      uVar21 = 0x93c;
    }
    phy_reg_mod(param_1,uVar21,0x10,0x10);
    phy_reg_write(param_1,uVar13,0x3ff);
    uVar21 = 0x152;
    if (param_4 != '\0') {
      uVar21 = 0x22a;
    }
    phy_reg_write(param_1,uVar14,uVar21);
    uVar21 = 0x73a;
    if ((bVar22 != 0) && (uVar21 = 0xb3a, bVar22 == 1)) {
      uVar21 = 0x93a;
    }
    phy_reg_mod(param_1,uVar21,7,uVar28 & 7);
    uVar21 = 0x725;
    if ((bVar22 != 0) && (uVar21 = 0xb25, bVar22 == 1)) {
      uVar21 = 0x925;
    }
    phy_reg_mod(param_1,uVar21,0x20,0x20);
    uVar21 = 0x739;
    if ((bVar22 != 0) && (uVar21 = 0xb39, bVar22 == 1)) {
      uVar21 = 0x939;
    }
    phy_reg_mod(param_1,uVar21,0x7e,uVar28 >> 2 & 0x7e);
    uVar21 = 0x725;
    if ((bVar22 != 0) && (uVar21 = 0xb25, bVar22 == 1)) {
      uVar21 = 0x925;
    }
    phy_reg_mod(param_1,uVar21,2,2);
    uVar21 = 0x73a;
    if ((bVar22 != 0) && (uVar21 = 0xb3a, bVar22 == 1)) {
      uVar21 = 0x93a;
    }
    phy_reg_mod(param_1,uVar21,8,uVar28 >> 6 & 8);
    uVar21 = 0x725;
    if ((bVar22 != 0) && (uVar21 = 0xb25, bVar22 == 1)) {
      uVar21 = 0x925;
    }
    phy_reg_mod(param_1,uVar21,0x40,0x40);
    uVar21 = 0x73a;
    if ((bVar22 != 0) && (uVar21 = 0xb3a, bVar22 == 1)) {
      uVar21 = 0x93a;
    }
    phy_reg_mod(param_1,uVar21,0x10,uVar28 >> 6 & 0x10);
    uVar21 = 0x725;
    if ((bVar22 != 0) && (uVar21 = 0xb25, bVar22 == 1)) {
      uVar21 = 0x925;
    }
    phy_reg_mod(param_1,uVar21,0x80,0x80);
    uVar21 = 0x73a;
    if ((bVar22 != 0) && (uVar21 = 0xb3a, bVar22 == 1)) {
      uVar21 = 0x93a;
    }
    phy_reg_mod(param_1,uVar21,0x60,uVar28 >> 6 & 0x60);
    uVar21 = 0x725;
    if ((bVar22 != 0) && (uVar21 = 0xb25, bVar22 == 1)) {
      uVar21 = 0x925;
    }
    phy_reg_mod(param_1,uVar21,0x100,0x100);
    uVar21 = 0x723;
    if ((bVar22 != 0) && (uVar21 = 0xb23, bVar22 == 1)) {
      uVar21 = 0x923;
    }
    phy_reg_mod(param_1,uVar21,8,8);
    uVar21 = 0x723;
    if ((bVar22 != 0) && (uVar21 = 0xb23, bVar22 == 1)) {
      uVar21 = 0x923;
    }
    phy_reg_mod(param_1,uVar21,0x10,0x10);
    uVar21 = 0x723;
    if ((bVar22 != 0) && (uVar21 = 0xb23, bVar22 == 1)) {
      uVar21 = 0x923;
    }
    phy_reg_mod(param_1,uVar21,0x800,0x800);
    uVar21 = 0x735;
    if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
      uVar21 = 0x935;
    }
    phy_reg_mod(param_1,uVar21,0x700,iVar12 * 0x100);
    iVar25 = *(int *)(param_1 + 0x164);
    if ((((iVar25 == 5) || (iVar25 == 2)) || (iVar25 == 6)) || (iVar25 == 3)) {
      if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x2000) {
        uVar21 = 0x735;
        if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
          uVar21 = 0x935;
        }
        phy_reg_mod(param_1,uVar21,0x3800,0x3000);
        uVar21 = 0x738;
        if ((bVar22 != 0) && (uVar21 = 0xb38, bVar22 == 1)) {
          uVar21 = 0x938;
        }
        iVar25 = 6;
      }
      else {
        uVar21 = 0x735;
        if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
          uVar21 = 0x935;
        }
        phy_reg_mod(param_1,uVar21,0x3800,0x2800);
        uVar21 = 0x738;
        if ((bVar22 != 0) && (uVar21 = 0xb38, bVar22 == 1)) {
          uVar21 = 0x938;
        }
        iVar25 = 5;
      }
    }
    else {
      uVar21 = 0x735;
      if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
        uVar21 = 0x935;
      }
      phy_reg_mod(param_1,uVar21,0x3800,iVar12 * 0x800);
      uVar21 = 0x738;
      iVar25 = iVar12;
      if ((bVar22 != 0) && (uVar21 = 0xb38, bVar22 == 1)) {
        uVar21 = 0x938;
      }
    }
    phy_reg_mod(param_1,uVar21,7,iVar25);
    iVar25 = *(int *)(param_1 + 0x164);
    if (((iVar25 == 5) || (iVar25 == 2)) || (iVar25 == 6)) {
      uVar21 = 0x727;
      if ((bVar22 != 0) && (uVar21 = 0xb27, bVar22 == 1)) {
        uVar21 = 0x927;
      }
      phy_reg_mod(param_1,uVar21,8,8);
      uVar21 = 0x73c;
      if ((bVar22 != 0) && (uVar21 = 0xb3c, bVar22 == 1)) {
        uVar21 = 0x93c;
      }
      phy_reg_mod(param_1,uVar21,0x20,0);
    }
    uVar21 = 0x723;
    if ((bVar22 != 0) && (uVar21 = 0xb23, bVar22 == 1)) {
      uVar21 = 0x923;
    }
    phy_reg_mod(param_1,uVar21,1,1);
    uVar21 = 0x735;
    if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
      uVar21 = 0x935;
    }
    phy_reg_mod(param_1,uVar21,1,0);
    uVar21 = 0x723;
    if ((bVar22 != 0) && (uVar21 = 0xb23, bVar22 == 1)) {
      uVar21 = 0x923;
    }
    phy_reg_mod(param_1,uVar21,0x20,0x20);
    uVar21 = 0x735;
    if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
      uVar21 = 0x935;
    }
    phy_reg_mod(param_1,uVar21,0x4000,0);
    uVar21 = 0x723;
    if ((bVar22 != 0) && (uVar21 = 0xb23, bVar22 == 1)) {
      uVar21 = 0x923;
    }
    phy_reg_mod(param_1,uVar21,2,2);
    uVar21 = 0x735;
    if ((bVar22 != 0) && (uVar21 = 0xb35, bVar22 == 1)) {
      uVar21 = 0x935;
    }
    phy_reg_mod(param_1,uVar21,0x1e,8);
    if (*(int *)(param_1 + 0x164) != 3) {
      uVar21 = 0x727;
      if ((bVar22 != 0) && (uVar21 = 0xb27, bVar22 == 1)) {
        uVar21 = 0x927;
      }
      phy_reg_mod(param_1,uVar21,2,2);
      uVar21 = 0x73c;
      if ((bVar22 != 0) && (uVar21 = 0xb3c, bVar22 == 1)) {
        uVar21 = 0x93c;
      }
      phy_reg_mod(param_1,uVar21,0xe,4);
      uVar21 = 0x727;
      if ((bVar22 != 0) && (uVar21 = 0xb27, bVar22 == 1)) {
        uVar21 = 0x927;
      }
      phy_reg_mod(param_1,uVar21,1,1);
      uVar21 = 0x73c;
      if ((bVar22 != 0) && (uVar21 = 0xb3c, bVar22 == 1)) {
        uVar21 = 0x93c;
      }
      phy_reg_mod(param_1,uVar21,1,1);
    }
  }
  phy_reg_mod(param_1,0x19e,0x40,0x40);
  phy_reg_mod(param_1,0x19e,0x80,0x80);
  phy_reg_mod(param_1,0x19e,0x100,0x100);
  FUN_00193d3a(param_1);
  phy_reg_mod(param_1,0x19e,2,(uVar10 >> 1 & 1) * 2);
  FUN_0019d3ac(param_1,lVar3 + 0x92,local_138);
  if (*(int *)(param_1 + 0x164) == 3) {
    wlapi_bmac_phyclk_fgc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),1);
  }
  phy_reg_write(param_1,0x382,0x8a09);
  puVar26 = (undefined1 *)(lVar3 + 0x2c);
  if (*(byte *)(*(long *)(param_1 + 0xf58) + 1) < 3) {
    puVar26 = local_108;
    if (param_2 == '\x01') {
      puVar26 = (undefined1 *)(lVar3 + 4);
    }
    for (bVar22 = 0; (uint)bVar22 < (uint)bVar1 + (uint)bVar1 * 4; bVar22 = bVar22 + 1) {
      *(undefined2 *)(lVar3 + 0x2c + (long)(int)(uint)bVar22 * 2) =
           *(undefined2 *)(puVar26 + (ulong)bVar22 * 2);
    }
  }
  for (iVar12 = 0; (byte)iVar12 < bVar1; iVar12 = iVar12 + 1) {
    FUN_0019ccd9(param_1,1,puVar26,0,iVar12);
    if (param_4 == '\0') {
      FUN_0019ccd9(param_1,1,puVar26 + 4,1,iVar12);
      FUN_0019ccd9(param_1,1,puVar26 + 6,2,iVar12);
      FUN_0019ccd9(param_1,1,puVar26 + 8,3,iVar12);
    }
    puVar26 = puVar26 + 10;
  }
  if (param_2 == '\0') {
    local_150 = &local_78;
    if (param_4 != '\0') goto LAB_001ade57;
    puVar15 = &local_b8;
    local_150 = &local_d8;
    if (*(int *)(param_1 + 0x164) != 1) {
LAB_001ade73:
      local_150 = puVar15;
    }
LAB_001ade8a:
    bVar22 = 6;
  }
  else {
    if (param_4 == '\0') {
      if (*(int *)(param_1 + 0x164) != 1) {
        puVar15 = &local_c8;
        goto LAB_001ade73;
      }
      local_150 = &local_e8;
      goto LAB_001ade8a;
    }
    local_150 = &local_88;
LAB_001ade57:
    bVar22 = 2;
  }
  local_18c = bVar1 * bVar22;
  if (param_3 == '\0') {
    local_18c = local_18c - 1;
    local_140._0_1_ = 0;
  }
  else {
    if (param_4 == '\0') {
      local_140._0_1_ = *(char *)(*(long *)(param_1 + 0xf58) + 1) * '\x02' - 4;
    }
    else {
      local_140._0_1_ = *(char *)(*(long *)(param_1 + 0xf58) + 1) * '\x02' - 0x1c;
    }
    if ((byte)local_140 + 1 < (uint)local_18c) {
      local_18c = (byte)local_140 + 1;
    }
    else {
      local_18c = local_18c - 1;
    }
  }
  uVar11 = *(ushort *)(param_1 + 0x17e) & 0x3800;
  uVar10 = 8000;
  if (uVar11 != 0x2000) {
    uVar10 = 2000;
    if (uVar11 == 0x1800) {
      uVar10 = 4000;
    }
  }
  iVar12 = wlc_phy_tx_tone_acphy(param_1,uVar10 >> 1,0xfa,1,0,0);
  osl_delay(5);
  for (bVar23 = 0; bVar23 < bVar1; bVar23 = bVar23 + 1) {
    uVar21 = 0x73a;
    if ((bVar23 != 0) && (uVar21 = 0xb3a, bVar23 == 1)) {
      uVar21 = 0x93a;
    }
    phy_reg_mod(param_1,uVar21,0x100,0);
    uVar21 = 0x725;
    if ((bVar23 != 0) && (uVar21 = 0xb25, bVar23 == 1)) {
      uVar21 = 0x925;
    }
    phy_reg_mod(param_1,uVar21,0x400,0x400);
  }
  if (iVar12 != 0) goto LAB_001ae555;
  local_188 = &local_98;
  uVar27 = 0;
  uVar18 = 0;
  uVar5 = 0;
  for (; (byte)local_140 <= local_18c; local_140._0_1_ = (byte)local_140 + 1) {
    bVar6 = (byte)local_140 / bVar22;
    uVar28 = (ushort)bVar6;
    uVar10 = local_150[(byte)local_140 % bVar22];
    uVar11 = uVar10 | 0x8000;
    lVar17 = (long)(int)(uint)bVar6;
    bVar23 = (byte)(uVar11 >> 8) & 0xf;
    if (*(char *)(lVar3 + 0x65 + lVar17) == '\0') {
      FUN_0019d65d(param_1,*(undefined2 *)(lVar3 + 0x9a + lVar17 * 10));
      *(undefined1 *)(lVar3 + 0x65 + lVar17) = 1;
    }
    phy_reg_write(param_1,0x381,CONCAT11(local_58[local_168],local_48[local_168]));
    if ((byte)(bVar23 - 3) < 2) {
      FUN_0019ccd9(param_1,1,local_3a,1,uVar28);
    }
    if (bVar23 == 4) {
      FUN_0019ccd9(param_1,1,local_3a,2,uVar28);
    }
    local_178 = &local_a8;
    do {
      phy_reg_write(param_1,899,*local_178);
      phy_reg_write(param_1,0x380,uVar11 | uVar28 << 0xc);
      for (local_17c = 0x4e29;
          (uVar16 = phy_reg_read(param_1,0x380), (uVar16 & 0xc000) != 0 && (local_17c != 9));
          local_17c = local_17c + -10) {
        osl_delay(10);
      }
      if ((acphychipid == 0x4352) ||
         (((acphychipid == 0x4360 || (acphychipid == 0xa9c4)) ||
          (uVar20 = 0x156, acphychipid == 0xaa06)))) {
        uVar20 = 0x144;
      }
      uVar16 = read_radio_reg(param_1,uVar20 | (ushort)bVar6 << 9);
      if ((uVar16 & 4) == 0) break;
      uVar21 = 0x73a;
      if ((bVar6 != 0) && (uVar21 = 0xb3a, bVar6 == 1)) {
        uVar21 = 0x93a;
      }
      phy_reg_mod(param_1,uVar21,0x100,0x100);
      uVar21 = 0x73a;
      if ((bVar6 != 0) && (uVar21 = 0xb3a, bVar6 == 1)) {
        uVar21 = 0x93a;
      }
      phy_reg_mod(param_1,uVar21,0x100,0);
      local_178 = local_178 + 1;
    } while (local_178 != local_a2);
    if (bVar23 == 2) {
      uVar27 = 0xd;
      uVar18 = 1;
      uVar5 = 5;
    }
    else {
      if (bVar23 < 3) {
        bVar29 = (uVar10 & 0xf00) == 0;
        if (bVar29) {
          uVar27 = 0xc;
        }
        if (bVar29) {
          uVar18 = 0;
        }
        uVar7 = 4;
      }
      else {
        if (bVar23 == 3) {
          uVar27 = 0xe;
          uVar18 = 2;
          uVar5 = 6;
          goto LAB_001ae2db;
        }
        bVar29 = bVar23 == 4;
        if (bVar29) {
          uVar27 = 0xf;
        }
        if (bVar29) {
          uVar18 = 3;
        }
        uVar7 = 7;
      }
      if (bVar29) {
        uVar5 = uVar7;
      }
    }
LAB_001ae2db:
    FUN_0019ccd9(param_1,0,local_68,uVar5,uVar28);
    FUN_0019ccd9(param_1,1,local_68,uVar18,uVar28);
    if ((*(int *)(param_1 + 0x164) == 1) && (4 < (byte)local_140 % bVar22)) {
      *local_188 = (short)local_68._0_4_;
      local_188 = local_188 + 1;
    }
    FUN_0019ccd9(param_1,1,local_68,uVar27,uVar28);
  }
  if (param_4 == '\0') {
    if ((param_3 == '\0') || (*(char *)(*(long *)(param_1 + 0xf58) + 1) == '\f')) {
      for (iVar25 = 0; (byte)iVar25 < bVar1; iVar25 = iVar25 + 1) {
        FUN_0019ccd9(param_1,0,local_68,0xc,iVar25);
        FUN_0019ccd9(param_1,1,local_68,0x10,iVar25);
        FUN_0019ccd9(param_1,1,local_68,8,iVar25);
        FUN_0019ccd9(param_1,1,local_68,10,iVar25);
        FUN_0019ccd9(param_1,0,local_68,0xd,iVar25);
        FUN_0019ccd9(param_1,1,local_68,0x11,iVar25);
        FUN_0019ccd9(param_1,1,local_68,9,iVar25);
        FUN_0019ccd9(param_1,1,local_68,0xb,iVar25);
        FUN_0019ccd9(param_1,0,local_68,0xe,iVar25);
        FUN_0019ccd9(param_1,1,local_68,0x12,iVar25);
        FUN_0019ccd9(param_1,0,local_68,0xf,iVar25);
        FUN_0019ccd9(param_1,1,local_68,0x13,iVar25);
      }
LAB_001ae52a:
      *(undefined1 *)(lVar3 + 100) = 1;
      *(undefined2 *)(lVar3 + 0xba) = *(undefined2 *)(param_1 + 0x17e);
    }
  }
  else if ((param_4 == '\x01') &&
          ((param_3 == '\0' || (*(char *)(*(long *)(param_1 + 0xf58) + 1) == '\x10')))) {
    for (iVar25 = 0; (byte)iVar25 < bVar1; iVar25 = iVar25 + 1) {
      FUN_0019ccd9(param_1,0,local_68,0xc,iVar25);
      FUN_0019ccd9(param_1,2,local_68,0xc,iVar25);
    }
    goto LAB_001ae52a;
  }
  wlc_phy_stopplayback_acphy(param_1);
  phy_reg_write(param_1,0x382,0);
LAB_001ae555:
  if (*(int *)(param_1 + 0x164) == 3) {
    wlapi_bmac_phyclk_fgc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0);
  }
  if (*(int *)(param_1 + 0x164) == 1) {
    wlc_phy_populate_tx_loft_comp_tbl_acphy(param_1,&local_98);
  }
  FUN_0019d550(param_1,local_138);
  FUN_001982a2(param_1);
  FUN_00195603(param_1);
  phy_reg_write(param_1,0x140,uVar8);
  wlc_phy_stay_in_carriersearch_acphy(param_1,0);
  return iVar12;
}

