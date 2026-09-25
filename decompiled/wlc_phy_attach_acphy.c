
undefined8 wlc_phy_attach_acphy(long param_1)

{
  ushort uVar1;
  undefined1 *puVar2;
  byte bVar3;
  undefined1 uVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  undefined2 uVar8;
  short sVar9;
  undefined4 uVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  undefined8 uVar15;
  int iVar16;
  short sVar17;
  char cVar18;
  int iVar19;
  bool bVar20;
  byte local_6a;
  char local_69;
  undefined1 local_68 [32];
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44;
  undefined1 local_43;
  ushort local_3a [5];
  
  phyhal_msg_level = phyhal_msg_level | 1;
  local_48 = 2;
  local_47 = 6;
  local_46 = 7;
  local_45 = 10;
  local_44 = 8;
  local_43 = 8;
  lVar12 = osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),0x920);
  *(long *)(param_1 + 0x138) = lVar12;
  if (lVar12 == 0) {
    return 0;
  }
  osl_memset(lVar12,0,0x920);
  puVar2 = *(undefined1 **)(param_1 + 0x138);
  puVar2[0x32c] = 0;
  puVar2[0x330] = (*(ushort *)(param_1 + 0x17e) & 0xc000) == 0;
  uVar1 = *(ushort *)(param_1 + 0x17e);
  puVar2[0x338] = 0;
  *puVar2 = 1;
  puVar2[0x339] = 0x80;
  puVar2[0x33a] = 0x80;
  puVar2[0x33b] = 0xc;
  *(uint *)(puVar2 + 0x334) = uVar1 & 0x3800;
  *(undefined2 *)(*(long *)(param_1 + 0x138) + 0x44a) = 0;
  *(undefined1 *)(param_1 + 0xf89) = 2;
  *(undefined2 *)(param_1 + 0xf8a) = 5;
  puVar2[0x8e1] = 0;
  *(undefined1 *)(param_1 + 0xc2b) = 0xff;
  puVar2[0x33c] = 1;
  puVar2[0x33d] = 0;
  puVar2[0x33e] = 0;
  puVar2[0x340] = 0;
  puVar2[0x341] = 0;
  puVar2[0x8de] = 1;
  puVar2[0x8df] = 1;
  puVar2[0x8e0] = 1;
  puVar2[0x8e4] = 1;
  puVar2[0x8e6] = 1;
  puVar2[0x8e7] = 1;
  puVar2[0x8e8] = 0;
  *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x42) = 0x36;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x739);
  *(undefined2 *)(lVar12 + 0x8ee) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x73a);
  *(undefined2 *)(lVar12 + 0x8f0) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x725);
  *(undefined2 *)(lVar12 + 0x8f2) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x729);
  *(undefined2 *)(lVar12 + 0x8ea) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x721);
  *(undefined2 *)(lVar12 + 0x8ec) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x728);
  *(undefined2 *)(lVar12 + 0x8f4) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x720);
  *(undefined2 *)(lVar12 + 0x8f6) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x408);
  *(undefined2 *)(lVar12 + 0x8f8) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x417);
  *(undefined2 *)(lVar12 + 0x8fa) = uVar8;
  lVar12 = *(long *)(param_1 + 0x138);
  uVar8 = phy_reg_read(param_1,0x416);
  *(undefined2 *)(lVar12 + 0x8fc) = uVar8;
  acphychipid = *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x3c);
  puVar2[0x8ff] = 1;
  puVar2[0x918] = 0;
  uVar11 = *(uint *)(param_1 + 0x164);
  puVar2[0x906] = 0;
  *(undefined2 *)(puVar2 + 0x908) = 5;
  puVar2[0x90e] = 0xf3;
  puVar2[0x90f] = 0xf1;
  *(undefined2 *)(puVar2 + 0x90a) = 0x1f;
  *(undefined2 *)(puVar2 + 0x90c) = 0x1f;
  puVar2[0x912] = uVar11 < 2;
  wlc_phy_hirssi_elnabypass_init_acphy(param_1);
  *(undefined1 *)(param_1 + 0x22a) = 0;
  puVar2[0x900] = 0;
  puVar2[0x901] = 1;
  *(undefined2 *)(puVar2 + 0x902) = 0x404e;
  *(undefined2 *)(puVar2 + 0x904) = 0xfff;
  uVar10 = si_alp_clock(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18));
  *(undefined4 *)(param_1 + 0xc24) = uVar10;
  puVar2[0x45a] = 0x80;
  puVar2[0x45b] = 0x80;
  puVar2[0x45c] = 0x80;
  puVar2[0x45d] = 0x80;
  puVar2[0x64a] = local_48;
  puVar2[0x64b] = local_47;
  puVar2[0x64c] = local_46;
  puVar2[0x64d] = local_45;
  puVar2[0x64f] = 8;
  puVar2[0x64e] = local_44;
  lVar13 = phy_getvar_fabid(param_1,"subband5gver");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined4 *)(lVar12 + 0x4c) = 4;
  }
  else {
    bVar3 = phy_getintvar(param_1,"subband5gver");
    *(uint *)(lVar12 + 0x4c) = (uint)bVar3;
  }
  lVar13 = phy_getvar_fabid(param_1,"extpagain2g");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined4 *)(lVar12 + 0xb0) = 0;
  }
  else {
    bVar3 = phy_getintvar(param_1,"extpagain2g");
    *(uint *)(lVar12 + 0xb0) = (uint)bVar3;
  }
  lVar13 = phy_getvar_fabid(param_1,"extpagain5g");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined4 *)(lVar12 + 0xac) = 0;
  }
  else {
    bVar3 = phy_getintvar(param_1,"extpagain5g");
    *(uint *)(lVar12 + 0xac) = (uint)bVar3;
  }
  lVar12 = phy_getvar_fabid(param_1,"femctrl");
  if (lVar12 == 0) {
    puVar2[0x342] = 0;
  }
  else {
    uVar4 = phy_getintvar(param_1,"femctrl");
    puVar2[0x342] = uVar4;
  }
  lVar12 = phy_getvar_fabid(param_1,"boardflags3");
  if (lVar12 == 0) {
    puVar2[0x343] = 0;
    puVar2[0x346] = 0;
    puVar2[0x347] = 0;
    puVar2[0x34c] = 0;
    puVar2[0x349] = 0;
    puVar2[0x348] = 0;
    puVar2[0x345] = 0;
    puVar2[0x34d] = 0;
    puVar2[0x34e] = 0;
    puVar2[0x34f] = 0;
    puVar2[0x354] = 0;
    puVar2[0x355] = 0;
  }
  else {
    uVar11 = phy_getintvar(param_1,"boardflags3");
    puVar2[0x343] = (byte)uVar11 & 7;
    puVar2[0x346] = (byte)(uVar11 >> 9) & 1;
    puVar2[0x347] = (byte)(uVar11 >> 10) & 1;
    puVar2[0x34c] = (byte)(uVar11 >> 8) & 1;
    puVar2[0x349] = (char)((uVar11 & 0x70) >> 4);
    puVar2[0x348] = (char)((uVar11 & 0x80) >> 7);
    puVar2[0x345] = (byte)(uVar11 >> 3) & 1;
    puVar2[0x34e] = (byte)(uVar11 >> 0xd) & 1;
    puVar2[0x34d] = (char)((uVar11 & 0x800) >> 0xb);
    puVar2[0x34f] = (byte)(uVar11 >> 0xc) & 1;
    puVar2[0x355] = (char)((uVar11 & 0x8000) >> 0xf);
    puVar2[0x354] = (char)((uVar11 & 0x4000) >> 0xe);
  }
  lVar13 = phy_getvar_fabid(param_1,"rpcal2g");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined2 *)(lVar12 + 0xcc) = 0;
  }
  else {
    uVar8 = phy_getintvar(param_1,"rpcal2g");
    *(undefined2 *)(lVar12 + 0xcc) = uVar8;
  }
  lVar13 = phy_getvar_fabid(param_1,"rpcal5gb0");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined2 *)(lVar12 + 0xce) = 0;
  }
  else {
    uVar8 = phy_getintvar(param_1,"rpcal5gb0");
    *(undefined2 *)(lVar12 + 0xce) = uVar8;
  }
  lVar13 = phy_getvar_fabid(param_1,"rpcal5gb1");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined2 *)(lVar12 + 0xd0) = 0;
  }
  else {
    uVar8 = phy_getintvar(param_1,"rpcal5gb1");
    *(undefined2 *)(lVar12 + 0xd0) = uVar8;
  }
  lVar13 = phy_getvar_fabid(param_1,"rpcal5gb2");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined2 *)(lVar12 + 0xd2) = 0;
  }
  else {
    uVar8 = phy_getintvar(param_1,"rpcal5gb2");
    *(undefined2 *)(lVar12 + 0xd2) = uVar8;
  }
  lVar13 = phy_getvar_fabid(param_1,"rpcal5gb3");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined2 *)(lVar12 + 0xd4) = 0;
  }
  else {
    uVar8 = phy_getintvar(param_1,"rpcal5gb3");
    *(undefined2 *)(lVar12 + 0xd4) = uVar8;
  }
  lVar13 = phy_getvar_fabid(param_1,"txidxcap2g");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined1 *)(lVar12 + 0xd6) = 0;
  }
  else {
    uVar4 = phy_getintvar(param_1,"txidxcap2g");
    *(undefined1 *)(lVar12 + 0xd6) = uVar4;
  }
  lVar13 = phy_getvar_fabid(param_1,"txidxcap5g");
  lVar12 = *(long *)(param_1 + 0x20);
  if (lVar13 == 0) {
    *(undefined1 *)(lVar12 + 0xd7) = 0;
  }
  else {
    uVar4 = phy_getintvar(param_1,"txidxcap5g");
    *(undefined1 *)(lVar12 + 0xd7) = uVar4;
  }
  puVar2[0x344] = (byte)(*(uint *)(*(long *)(param_1 + 0x20) + 0x68) >> 1) & 1;
  puVar2[0x34b] = (byte)*(undefined4 *)(*(long *)(param_1 + 0x20) + 100) & 1;
  puVar2[0x34a] = (byte)((uint)*(undefined4 *)(*(long *)(param_1 + 0x20) + 100) >> 0x1d) & 1;
  lVar12 = phy_getvar_fabid(param_1,"pdgain2g");
  if (lVar12 == 0) {
    puVar2[0x410] = 0;
  }
  else {
    uVar4 = phy_getintvar(param_1,"pdgain2g");
    puVar2[0x410] = uVar4;
  }
  lVar12 = phy_getvar_fabid(param_1,"pdgain5g");
  if (lVar12 == 0) {
    puVar2[0x411] = 0;
  }
  else {
    uVar4 = phy_getintvar(param_1,"pdgain5g");
    puVar2[0x411] = uVar4;
  }
  lVar12 = phy_getvar_fabid(param_1,"cckdigfilttype");
  if (lVar12 == 0) {
    puVar2[0x8fe] = 1;
  }
  else {
    uVar4 = phy_getintvar(param_1,"cckdigfilttype");
    puVar2[0x8fe] = uVar4;
  }
  bVar3 = phy_reg_read(param_1,0xb);
  *(byte *)(param_1 + 0x168) = bVar3 & 7;
  iVar16 = *(int *)(*(long *)(param_1 + 0x20) + 0x3c);
  if (iVar16 == 0x4360) {
    iVar16 = *(int *)(*(long *)(param_1 + 0x20) + 0x58);
    if (iVar16 != 0x137) {
      bVar20 = iVar16 == 0x117;
      goto LAB_001a2f21;
    }
  }
  else {
    bVar20 = iVar16 == 0x4352;
LAB_001a2f21:
    if (!bVar20) goto LAB_001a2f2a;
  }
  *(undefined1 *)(param_1 + 0x168) = 2;
LAB_001a2f2a:
  *(undefined1 *)(param_1 + 0xc40) = 1;
  *(undefined1 *)(param_1 + 4000) = 1;
  *(undefined1 *)(param_1 + 0x224) = 1;
  osl_memset(*(long *)(param_1 + 0x138) + 0x2c,0,0x10);
  osl_memset(*(long *)(param_1 + 0x138) + 0x3d,0,4);
  *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x43) = 0;
  *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x44) = 0;
  *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x3c) = 0;
  uVar11 = *(uint *)(param_1 + 0x164);
  if ((((uVar11 == 5) || (uVar11 == 2)) || (uVar11 == 6)) || (uVar11 == 3)) {
    iVar16 = 0;
    cVar6 = '\0';
    cVar5 = -0x1e;
    while( true ) {
      lVar12 = (long)iVar16;
      cVar6 = cVar6 + '\x01';
      *(char *)(*(long *)(param_1 + 0x138) + 0x18 + lVar12 * 4) = cVar5;
      *(char *)(*(long *)(param_1 + 0x138) + 0x19 + lVar12 * 4) = cVar5;
      *(char *)(*(long *)(param_1 + 0x138) + 0x1a + lVar12 * 4) = cVar5;
      if (cVar6 == '\x05') break;
      cVar5 = -0x1c;
      if (1 < (byte)iVar16) {
        cVar5 = (cVar6 != '\x03') + -0x1a;
      }
      iVar16 = iVar16 + 1;
    }
  }
  else if (uVar11 < 2) {
    iVar16 = 0;
    do {
      lVar12 = (long)iVar16;
      iVar16 = iVar16 + 1;
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x18 + lVar12 * 4) = 0xe2;
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x19 + lVar12 * 4) = 0xe2;
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x1a + lVar12 * 4) = 0xe2;
    } while (iVar16 != 5);
  }
  lVar12 = *(long *)(param_1 + 0x138);
  *(byte *)(lVar12 + 0x340) = (byte)(*(uint *)(*(long *)(param_1 + 0x20) + 100) >> 0xc) & 1;
  *(byte *)(lVar12 + 0x341) =
       (byte)((uint)*(undefined4 *)(*(long *)(param_1 + 0x20) + 100) >> 0x1c) & 1;
  for (local_6a = 0; local_6a < *(byte *)(param_1 + 0x168); local_6a = local_6a + 1) {
    lVar13 = lVar12 + (long)(int)(uint)local_6a * 3;
    *(undefined1 *)(lVar13 + 0x3e0) = 0;
    *(undefined1 *)(lVar13 + 0x3e1) = 0;
    *(undefined1 *)(lVar13 + 0x3e2) = 0;
    *(undefined1 *)(lVar13 + 0x3ec) = 0;
    *(undefined1 *)(lVar13 + 0x3ed) = 0;
    *(undefined1 *)(lVar13 + 0x3ee) = 0;
    *(undefined1 *)(lVar13 + 0x3f8) = 0;
    *(undefined1 *)(lVar13 + 0x3f9) = 0;
    *(undefined1 *)(lVar13 + 0x3fa) = 0;
    *(undefined1 *)(lVar13 + 0x404) = 0;
    *(undefined1 *)(lVar13 + 0x405) = 0;
    *(undefined1 *)(lVar13 + 0x406) = 0;
    uVar11 = (uint)local_6a;
    if (*(char *)(lVar12 + 0x340) != '\0') {
      osl_snprintf(local_68,0x1e,"rxgains2gelnagaina%d",(uint)local_6a);
      lVar14 = phy_getvar_fabid(param_1,local_68);
      if (lVar14 != 0) {
        cVar5 = phy_getintvar(param_1,local_68);
        *(char *)(lVar13 + 0x3e0) = cVar5 * '\x02' + '\x06';
      }
      osl_snprintf(local_68,0x1e,"rxgains2gtrelnabypa%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      if (lVar13 != 0) {
        uVar4 = phy_getintvar(param_1,local_68);
        *(undefined1 *)(lVar12 + 0x3e2 + (long)(int)uVar11 * 3) = uVar4;
      }
    }
    osl_snprintf(local_68,0x1e,"rxgains2gtrisoa%d",local_6a);
    lVar13 = phy_getvar_fabid(param_1,local_68);
    if (lVar13 != 0) {
      cVar5 = phy_getintvar(param_1,local_68);
      *(char *)(lVar12 + 0x3e1 + (long)(int)uVar11 * 3) = cVar5 * '\x02' + '\b';
    }
    if (*(char *)(lVar12 + 0x341) != '\0') {
      osl_snprintf(local_68,0x1e,"rxgains5gelnagaina%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      if (lVar13 != 0) {
        cVar5 = phy_getintvar(param_1,local_68);
        *(char *)(lVar12 + 0x3ec + (long)(int)uVar11 * 3) = cVar5 * '\x02' + '\x06';
      }
      osl_snprintf(local_68,0x1e,"rxgains5gtrelnabypa%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      if (lVar13 != 0) {
        uVar4 = phy_getintvar(param_1,local_68);
        *(undefined1 *)(lVar12 + 0x3ee + (long)(int)uVar11 * 3) = uVar4;
      }
    }
    osl_snprintf(local_68,0x1e,"rxgains5gtrisoa%d",local_6a);
    lVar13 = phy_getvar_fabid(param_1,local_68);
    if (lVar13 != 0) {
      cVar5 = phy_getintvar(param_1,local_68);
      *(char *)(lVar12 + 0x3ed + (long)(int)uVar11 * 3) = cVar5 * '\x02' + '\b';
    }
    if (*(char *)(lVar12 + 0x341) == '\0') {
      cVar5 = '\0';
      local_69 = '\0';
    }
    else {
      osl_snprintf(local_68,0x1e,"rxgains5gmelnagaina%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      local_69 = '\0';
      if (lVar13 != 0) {
        local_69 = phy_getintvar(param_1,local_68);
      }
      osl_snprintf(local_68,0x1e,"rxgains5gmtrelnabypa%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      cVar5 = '\0';
      if (lVar13 != 0) {
        cVar5 = phy_getintvar(param_1,local_68);
      }
    }
    osl_snprintf(local_68,0x1e,"rxgains5gmtrisoa%d",local_6a);
    lVar13 = phy_getvar_fabid(param_1,local_68);
    cVar6 = '\0';
    if (lVar13 != 0) {
      cVar6 = phy_getintvar(param_1,local_68);
    }
    if ((((cVar5 == '\0') && (local_69 == '\0')) && (cVar6 == '\0')) ||
       (((cVar6 == '\x0f' && (local_69 == '\a')) && (cVar5 == '\x01')))) {
      lVar14 = lVar12 + (long)(int)uVar11 * 3;
      lVar13 = lVar14 + 0x3f0;
      *(undefined1 *)(lVar14 + 0x3f8) = *(undefined1 *)(lVar14 + 0x3ec);
      *(undefined1 *)(lVar14 + 0x3fa) = *(undefined1 *)(lVar14 + 0x3ee);
      cVar6 = *(char *)(lVar14 + 0x3ed);
    }
    else {
      cVar6 = cVar6 * '\x02' + '\b';
      lVar13 = lVar12 + 0x3f0 + (long)(int)uVar11 * 3;
      *(char *)(lVar13 + 8) = local_69 * '\x02' + '\x06';
      *(char *)(lVar13 + 10) = cVar5;
    }
    *(char *)(lVar13 + 9) = cVar6;
    if (*(char *)(lVar12 + 0x341) == '\0') {
      cVar5 = '\0';
      local_69 = '\0';
    }
    else {
      osl_snprintf(local_68,0x1e,"rxgains5ghelnagaina%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      local_69 = '\0';
      if (lVar13 != 0) {
        local_69 = phy_getintvar(param_1,local_68);
      }
      osl_snprintf(local_68,0x1e,"rxgains5ghtrelnabypa%d",local_6a);
      lVar13 = phy_getvar_fabid(param_1,local_68);
      cVar5 = '\0';
      if (lVar13 != 0) {
        cVar5 = phy_getintvar(param_1,local_68);
      }
    }
    osl_snprintf(local_68,0x1e,"rxgains5ghtrisoa%d",local_6a);
    lVar13 = phy_getvar_fabid(param_1,local_68);
    cVar6 = '\0';
    if (lVar13 != 0) {
      cVar6 = phy_getintvar(param_1,local_68);
    }
    if ((((cVar5 == '\0') && (local_69 == '\0')) && (cVar6 == '\0')) ||
       (((cVar6 == '\x0f' && (local_69 == '\a')) && (cVar5 == '\x01')))) {
      lVar14 = lVar12 + (long)(int)uVar11 * 3;
      lVar13 = lVar14 + 0x400;
      *(undefined1 *)(lVar14 + 0x404) = *(undefined1 *)(lVar14 + 0x3f8);
      *(undefined1 *)(lVar14 + 0x406) = *(undefined1 *)(lVar14 + 0x3fa);
      cVar6 = *(char *)(lVar14 + 0x3f9);
    }
    else {
      cVar6 = cVar6 * '\x02' + '\b';
      lVar13 = lVar12 + 0x400 + (long)(int)uVar11 * 3;
      *(char *)(lVar13 + 4) = local_69 * '\x02' + '\x06';
      *(char *)(lVar13 + 6) = cVar5;
    }
    *(char *)(lVar13 + 5) = cVar6;
  }
  cVar5 = wlc_phy_txpwr_srom11_read(param_1);
  if (cVar5 == '\0') {
    return 0;
  }
  sVar9 = phy_getintvar(param_1,"rawtempsense");
  sVar17 = (short)(sVar9 << 7) >> 7;
  sVar9 = 0xff;
  if (sVar17 != -1) {
    sVar9 = sVar17;
  }
  *(short *)(param_1 + 0x210) = sVar9;
  *(short *)(*(long *)(param_1 + 0x138) + 0x8dc) = sVar9;
  cVar5 = phy_getintvar(param_1,"rxgainerr2ga0");
  cVar6 = phy_getintvar(param_1,"rxgainerr2ga1");
  cVar7 = phy_getintvar(param_1,"rxgainerr2ga2");
  cVar18 = (char)(cVar5 * '\x04') >> 2;
  cVar6 = (char)(cVar6 * '\b') >> 3;
  cVar5 = (char)(cVar7 << 3) >> 3;
  if (((cVar18 == -1) && (cVar6 == -1)) && ((cVar5 == -1 && (sVar17 == -1)))) {
    *(undefined1 *)(param_1 + 0x1e7) = 1;
    cVar18 = '\0';
    cVar6 = '\0';
    cVar5 = '\0';
  }
  else {
    *(undefined1 *)(param_1 + 0x1e7) = 0;
  }
  *(char *)(param_1 + 0x1e3) = cVar18;
  *(char *)(param_1 + 0x1e4) = cVar6 + cVar18;
  *(char *)(param_1 + 0x1e5) = cVar5 + cVar18;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga0",0);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga1",0);
  cVar7 = (char)(cVar5 * '\x04') >> 2;
  cVar6 = (char)(cVar6 * '\b') >> 3;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga2",0);
  cVar5 = (char)(cVar5 << 3) >> 3;
  if ((((cVar7 == -1) && (cVar6 == -1)) && (cVar5 == -1)) && (sVar17 == -1)) {
    *(undefined1 *)(param_1 + 0x1ec) = 1;
    cVar7 = '\0';
    cVar6 = '\0';
    cVar5 = '\0';
  }
  else {
    *(undefined1 *)(param_1 + 0x1ec) = 0;
  }
  *(char *)(param_1 + 0x1e8) = cVar7;
  *(char *)(param_1 + 0x1e9) = cVar6 + cVar7;
  *(char *)(param_1 + 0x1ea) = cVar5 + cVar7;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga0",1);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga1",1);
  cVar7 = (char)(cVar5 * '\x04') >> 2;
  cVar6 = (char)(cVar6 * '\b') >> 3;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga2",1);
  cVar5 = (char)(cVar5 << 3) >> 3;
  if (((cVar7 == -1) && (cVar6 == -1)) && ((cVar5 == -1 && (sVar17 == -1)))) {
    *(undefined1 *)(param_1 + 0x1f1) = 1;
    cVar7 = '\0';
    cVar6 = '\0';
    cVar5 = '\0';
  }
  else {
    *(undefined1 *)(param_1 + 0x1f1) = 0;
  }
  *(char *)(param_1 + 0x1ed) = cVar7;
  *(char *)(param_1 + 0x1ee) = cVar6 + cVar7;
  *(char *)(param_1 + 0x1ef) = cVar5 + cVar7;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga0",2);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga1",2);
  cVar7 = (char)(cVar5 * '\x04') >> 2;
  cVar6 = (char)(cVar6 * '\b') >> 3;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga2",2);
  cVar5 = (char)(cVar5 << 3) >> 3;
  if (((cVar7 == -1) && (cVar6 == -1)) && ((cVar5 == -1 && (sVar17 == -1)))) {
    *(undefined1 *)(param_1 + 0x1f6) = 1;
    cVar7 = '\0';
    cVar6 = '\0';
    cVar5 = '\0';
  }
  else {
    *(undefined1 *)(param_1 + 0x1f6) = 0;
  }
  *(char *)(param_1 + 0x1f2) = cVar7;
  *(char *)(param_1 + 499) = cVar6 + cVar7;
  *(char *)(param_1 + 500) = cVar5 + cVar7;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga0",3);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga1",3);
  cVar7 = (char)(cVar5 * '\x04') >> 2;
  cVar6 = (char)(cVar6 * '\b') >> 3;
  cVar5 = getintvararray(*(undefined8 *)(param_1 + 0x158),"rxgainerr5ga2",3);
  cVar5 = (char)(cVar5 << 3) >> 3;
  if ((((cVar7 == -1) && (cVar6 == -1)) && (cVar5 == -1)) && (sVar17 == -1)) {
    *(undefined1 *)(param_1 + 0x1fb) = 1;
    cVar7 = '\0';
    cVar6 = '\0';
    cVar5 = '\0';
  }
  else {
    *(undefined1 *)(param_1 + 0x1fb) = 0;
  }
  *(char *)(param_1 + 0x1f7) = cVar7;
  *(char *)(param_1 + 0x1f8) = cVar6 + cVar7;
  cVar6 = *(char *)(param_1 + 0x168);
  *(char *)(param_1 + 0x1f9) = cVar5 + cVar7;
  lVar12 = param_1;
  for (cVar5 = '\0'; cVar5 != cVar6; cVar5 = cVar5 + '\x01') {
    *(undefined1 *)(lVar12 + 0x1fc) = 0xba;
    lVar12 = lVar12 + 1;
  }
  cVar5 = *(char *)(param_1 + 0x1fc);
  cVar6 = phy_getintvar(param_1,"noiselvl2ga0");
  *(char *)(param_1 + 0x1fc) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x1fd);
  cVar6 = phy_getintvar(param_1,"noiselvl2ga1");
  *(char *)(param_1 + 0x1fd) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x1fe);
  cVar7 = phy_getintvar(param_1,"noiselvl2ga2");
  cVar6 = *(char *)(param_1 + 0x168);
  *(char *)(param_1 + 0x1fe) = cVar5 - cVar7;
  lVar12 = param_1;
  for (cVar5 = '\0'; cVar5 != cVar6; cVar5 = cVar5 + '\x01') {
    *(undefined1 *)(lVar12 + 0x200) = 0xba;
    lVar12 = lVar12 + 1;
  }
  cVar5 = *(char *)(param_1 + 0x200);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga0",0);
  *(char *)(param_1 + 0x200) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x201);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga1",0);
  *(char *)(param_1 + 0x201) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x202);
  cVar7 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga2",0);
  cVar6 = *(char *)(param_1 + 0x168);
  *(char *)(param_1 + 0x202) = cVar5 - cVar7;
  lVar12 = param_1;
  for (cVar5 = '\0'; cVar5 != cVar6; cVar5 = cVar5 + '\x01') {
    *(undefined1 *)(lVar12 + 0x204) = 0xba;
    lVar12 = lVar12 + 1;
  }
  cVar5 = *(char *)(param_1 + 0x204);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga0",1);
  *(char *)(param_1 + 0x204) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x205);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga1",1);
  *(char *)(param_1 + 0x205) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x206);
  cVar7 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga2",1);
  cVar6 = *(char *)(param_1 + 0x168);
  *(char *)(param_1 + 0x206) = cVar5 - cVar7;
  lVar12 = param_1;
  for (cVar5 = '\0'; cVar5 != cVar6; cVar5 = cVar5 + '\x01') {
    *(undefined1 *)(lVar12 + 0x208) = 0xba;
    lVar12 = lVar12 + 1;
  }
  cVar5 = *(char *)(param_1 + 0x208);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga0",2);
  *(char *)(param_1 + 0x208) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x209);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga1",2);
  *(char *)(param_1 + 0x209) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x20a);
  cVar7 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga2",2);
  cVar6 = *(char *)(param_1 + 0x168);
  *(char *)(param_1 + 0x20a) = cVar5 - cVar7;
  lVar12 = param_1;
  for (cVar5 = '\0'; cVar5 != cVar6; cVar5 = cVar5 + '\x01') {
    *(undefined1 *)(lVar12 + 0x20c) = 0xba;
    lVar12 = lVar12 + 1;
  }
  cVar5 = *(char *)(param_1 + 0x20c);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga0",3);
  *(char *)(param_1 + 0x20c) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x20d);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga1",3);
  *(char *)(param_1 + 0x20d) = cVar5 - cVar6;
  cVar5 = *(char *)(param_1 + 0x20e);
  cVar6 = getintvararray(*(undefined8 *)(param_1 + 0x158),"noiselvl5ga2",3);
  *(char *)(param_1 + 0x20e) = cVar5 - cVar6;
  lVar12 = *(long *)(param_1 + 0x138);
  if (*(char *)(lVar12 + 0x34c) != '\0') {
    lVar13 = phy_getvar_fabid(param_1,"swctrlmap_2g");
    if (lVar13 != 0) {
      lVar13 = lVar12;
      iVar16 = 0;
      do {
        iVar19 = iVar16 + 1;
        uVar10 = phy_getintvararray(param_1,"swctrlmap_2g",iVar16);
        *(undefined4 *)(lVar13 + 0x358) = uVar10;
        lVar13 = lVar13 + 4;
        iVar16 = iVar19;
      } while (iVar19 != 5);
    }
    lVar13 = phy_getvar_fabid(param_1,"swctrlmapext_2g");
    if (lVar13 != 0) {
      lVar13 = lVar12;
      iVar16 = 0;
      do {
        iVar19 = iVar16 + 1;
        uVar10 = phy_getintvararray(param_1,"swctrlmapext_2g",iVar16);
        *(undefined4 *)(lVar13 + 0x36c) = uVar10;
        lVar13 = lVar13 + 4;
        iVar16 = iVar19;
      } while (iVar19 != 5);
    }
    lVar13 = phy_getvar_fabid(param_1,"swctrlmap_5g");
    if (lVar13 != 0) {
      lVar13 = lVar12;
      iVar16 = 0;
      do {
        iVar19 = iVar16 + 1;
        uVar10 = phy_getintvararray(param_1,"swctrlmap_5g",iVar16);
        *(undefined4 *)(lVar13 + 0x380) = uVar10;
        lVar13 = lVar13 + 4;
        iVar16 = iVar19;
      } while (iVar19 != 5);
    }
    lVar13 = phy_getvar_fabid(param_1,"swctrlmapext_5g");
    if (lVar13 != 0) {
      iVar16 = 0;
      do {
        iVar19 = iVar16 + 1;
        uVar10 = phy_getintvararray(param_1,"swctrlmapext_5g",iVar16);
        *(undefined4 *)(lVar12 + 0x394) = uVar10;
        lVar12 = lVar12 + 4;
        iVar16 = iVar19;
      } while (iVar19 != 5);
    }
  }
  FUN_001a2344(param_1);
  local_3a[0] = 0;
  uVar11 = si_get_sromctl(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18));
  if ((uVar11 >> 4 & 1) == 0) {
    si_set_sromctl(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),uVar11 | 0x10);
  }
  otp_read_word(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),0x10,local_3a);
  if ((uVar11 >> 4 & 1) == 0) {
    si_set_sromctl(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),uVar11);
  }
  local_3a[0] = local_3a[0] >> 8 & 0x1f;
  *(ushort *)(*(long *)(param_1 + 0x138) + 0x8e2) = local_3a[0];
  iVar16 = *(int *)(param_1 + 0x164);
  if (((iVar16 == 5) || (iVar16 == 2)) || (iVar16 == 6)) {
    puVar2[0x8e5] = 1;
  }
  else {
    puVar2[0x8e5] = 0;
  }
  *(code **)(param_1 + 0x28) = FUN_001b0ecf;
  *(code **)(param_1 + 0x30) = FUN_0018f4ba;
  *(code **)(param_1 + 0x38) = FUN_001a7dc9;
  *(code **)(param_1 + 0x40) = FUN_0019a1df;
  *(code **)(param_1 + 0x100) = FUN_001980bd;
  *(undefined1 **)(param_1 + 0xc0) = &LAB_00198b6b;
  *(code **)(param_1 + 0xd0) = FUN_0019a268;
  *(undefined1 **)(param_1 + 200) = &LAB_00193ba7;
  *(code **)(param_1 + 0xf8) = wlc_phy_btc_adjust_acphy;
  *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x80) = 0;
  osl_memset(puVar2 + 0x656,0,9);
  osl_memset(puVar2 + 0x65f,0,9);
  osl_memset(puVar2 + 0x668,0,9);
  osl_memset(puVar2 + 0x8b4,0,9);
  puVar2[0x671] = 1;
  osl_memset(puVar2 + 0x6c8,0,0xf0);
  osl_memset(puVar2 + 0x7b8,0,0xf0);
  *(undefined8 *)(puVar2 + 0x8a8) = 0;
  *(undefined4 *)(puVar2 + 0x8b0) = 0;
  wlc_phy_hwaci_init_acphy(param_1);
  lVar12 = *(long *)(param_1 + 0x138);
  *(undefined1 *)(param_1 + 0x1165) = 0;
  if (*(char *)(lVar12 + 0x34e) == '\x01') {
    uVar15 = otp_read_word(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18),0x10,
                           *(long *)(param_1 + 0x20) + 0xf2);
    if ((int)uVar15 == 0) {
      lVar12 = *(long *)(param_1 + 0x20);
      *(ushort *)(lVar12 + 0xf2) = *(ushort *)(lVar12 + 0xf2) & 0xf;
    }
    else if (*(char *)(param_1 + 0x16e) == '\x02') {
      lVar12 = *(long *)(param_1 + 0x20);
      *(undefined2 *)(lVar12 + 0xf2) = 9;
    }
    else {
      cVar5 = *(char *)(param_1 + 0x16e) + -1;
      lVar12 = CONCAT71((int7)((ulong)uVar15 >> 8),cVar5);
      if (cVar5 == '\0') {
        lVar12 = *(long *)(param_1 + 0x20);
        *(undefined2 *)(lVar12 + 0xf2) = 10;
      }
    }
  }
  return CONCAT71((int7)((ulong)lVar12 >> 8),1);
}

