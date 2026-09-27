
long wlc_phy_attach(long *param_1,undefined8 param_2,int param_3,undefined8 param_4)

{
  uint *puVar1;
  char cVar2;
  undefined1 uVar3;
  ushort uVar4;
  undefined2 uVar5;
  ushort uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  uint uVar12;
  ulong uVar13;
  undefined8 uVar14;
  byte bVar15;
  uint uVar16;
  int iVar17;
  bool bVar18;
  
  uVar7 = 3;
  lVar11 = param_1[2];
  if ((int)param_1[5] != 4) {
    uVar7 = si_core_sflags(param_1[3],0,0);
  }
  if ((param_3 == 1) && ((uVar7 & 10) == 0)) {
    return 0;
  }
  if (((uVar7 & 8) != 0) && (lVar10 = *param_1, lVar10 != 0)) {
    if ((*(int *)(lVar10 + 0x160) != 8) ||
       (((*(int *)(*(long *)(lVar10 + 0x20) + 0x58) == 0x551 &&
         (*(int *)(*(long *)(lVar10 + 0x20) + 0x3c) == 0x4330)) ||
        (cVar2 = wlc_phy_txpwr_srom_read_lcnphy(lVar10,param_3), cVar2 != '\0')))) {
      wlapi_bmac_corereset
                (*(undefined8 *)(*(long *)(lVar10 + 0x20) + 0x20),*(undefined4 *)(lVar10 + 0x170));
      *(int *)(lVar10 + 0x188) = *(int *)(lVar10 + 0x188) + 1;
      return lVar10;
    }
    goto LAB_001c00e9;
  }
  lVar10 = osl_malloc(lVar11,0x1170);
  if (lVar10 == 0) {
    return 0;
  }
  osl_memset(lVar10,0,0x1170);
  *(undefined4 *)(lVar10 + 0x1080) = 0;
  *(undefined8 *)(lVar10 + 0x148) = param_2;
  *(long **)(lVar10 + 0x20) = param_1;
  *(undefined1 *)(lVar10 + 0x185) = 1;
  *(long *)(lVar10 + 0xf58) = lVar10 + 0xfb8;
  if (((int)param_1[0xc] == 0x106b) && ((int)param_1[0xb] == 0x93)) {
    *(undefined2 *)(lVar10 + 0x228) = 1;
  }
  else {
    *(undefined2 *)(lVar10 + 0x228) = 0x18;
  }
  *(undefined1 *)(lVar10 + 0x184) = 100;
  *(undefined1 *)(lVar10 + 0xf9d) = 4;
  *(undefined1 *)(lVar10 + 3999) = 4;
  *(undefined1 *)(lVar10 + 0xf9e) = 0;
  *(undefined8 *)(lVar10 + 0x158) = param_4;
  FUN_001bf0bf(lVar10);
  if ((param_3 == 2) && ((uVar7 & 1) != 0)) {
    *(undefined4 *)(lVar10 + 0x170) = 0x2000;
  }
  wlapi_bmac_corereset
            (*(undefined8 *)(*(long *)(lVar10 + 0x20) + 0x20),*(undefined4 *)(lVar10 + 0x170));
  uVar4 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3e0);
  uVar5 = si_fabid(*(undefined8 *)(*(long *)(lVar10 + 0x20) + 0x18));
  *(undefined2 *)(lVar10 + 0x10fc) = uVar5;
  *(uint *)(lVar10 + 0x160) = (uVar4 & 0xf00) >> 8;
  *(uint *)(lVar10 + 0x164) = uVar4 & 0xf;
  iVar9 = *(int *)(*(long *)(lVar10 + 0x20) + 0x3c);
  if ((((iVar9 - 0xa8e3U < 2) || (iVar9 == 0xa8e6)) || (iVar9 == 0xa8e2)) &&
     (*(int *)(*(long *)(lVar10 + 0x20) + 0x40) - 2U < 2)) {
    *(undefined4 *)(lVar10 + 0x164) = 9;
  }
  if (*(int *)(lVar10 + 0x160) == 9) {
    *(int *)(lVar10 + 0x164) = *(int *)(lVar10 + 0x164) + 0x10;
    *(undefined4 *)(lVar10 + 0x160) = 4;
  }
  cVar2 = '\x03';
  if (*(int *)(lVar10 + 0x160) != 7) {
    cVar2 = (*(int *)(lVar10 + 0x160) == 4) + '\x01';
  }
  *(char *)(lVar10 + 0x168) = cVar2;
  uVar7 = *(uint *)(lVar10 + 0x160);
  *(uint *)(lVar10 + 0x174) = (uint)(uVar4 >> 0xc);
  bVar18 = uVar7 != 4;
  if (((((bVar18) && (2 < uVar7)) && ((uVar7 != 5 && ((uVar7 != 6 && (uVar7 != 8)))))) &&
      (uVar7 != 10)) && ((uVar7 != 0xb && (uVar7 != 7)))) goto LAB_001c00e9;
  if (param_3 == 1) {
    if (((uVar7 == 0) || (!bVar18)) || ((uVar7 == 5 || ((uVar7 == 6 || (uVar7 == 10))))))
    goto LAB_001bf432;
    if (uVar7 != 7) {
      if (uVar7 != 8) goto LAB_001bf429;
      goto LAB_001bf432;
    }
LAB_001bf441:
    uVar8 = 0xf;
  }
  else {
    if ((((uVar7 != 2) && (bVar18)) && (uVar7 != 5)) &&
       (((uVar7 != 6 && (uVar7 != 10)) && (uVar7 != 8)))) {
      if (uVar7 == 7) goto LAB_001bf441;
LAB_001bf429:
      if (uVar7 != 0xb) goto LAB_001c00e9;
    }
LAB_001bf432:
    if ((uVar7 == 7) || (uVar8 = 0x3c, uVar7 == 4)) goto LAB_001bf441;
  }
  *(undefined4 *)(lVar10 + 0xc04) = uVar8;
  *(undefined4 *)(lVar10 + 0xc08) = 0x10;
  *(undefined4 *)(lVar10 + 0xc0c) = 0;
  uVar5 = 0xd024;
  if (param_3 == 2) {
    uVar5 = 0x1001;
  }
  *(undefined2 *)(lVar10 + 0x182) = 0x1000;
  *(undefined2 *)(lVar10 + 0x17e) = uVar5;
  *(char *)(lVar10 + 0x240) = (char)uVar5;
  iVar9 = *(int *)(lVar10 + 0x160);
  if (iVar9 == 0xb) {
    *(undefined1 *)(*(long *)(lVar10 + 0x20) + 0x94) = 0;
    *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x84) = 0;
    *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x88) = 0;
    uVar7 = *(uint *)(lVar10 + 0x164);
    if ((((uVar7 < 2) || (uVar7 == 5)) || (uVar7 == 2)) || ((uVar7 == 6 || (uVar7 == 3)))) {
      *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x84) = 1;
      *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x88) = 1;
    }
    if (*(int *)(lVar10 + 0x164) == 1) {
      puVar1 = (uint *)(*(long *)(lVar10 + 0x20) + 0x84);
      *puVar1 = *puVar1 | 6;
      puVar1 = (uint *)(*(long *)(lVar10 + 0x20) + 0x88);
      *puVar1 = *puVar1 | 6;
    }
  }
  else if ((iVar9 == 7) || (iVar9 == 4)) {
    *(undefined1 *)(*(long *)(lVar10 + 0x20) + 0x94) = 0;
    uVar7 = *(uint *)(lVar10 + 0x164);
    if ((uVar7 < 3) && (*(int *)(lVar10 + 0x160) != 7)) {
LAB_001bf6fb:
      *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x80) = 3;
    }
    else {
      if (*(int *)(lVar10 + 0x160) == 7) {
        lVar11 = *(long *)(lVar10 + 0x20);
        iVar9 = *(int *)(lVar11 + 0x58);
        if (((iVar9 != 0xec) && (iVar9 != 0x59b)) && (iVar9 != 0xed)) {
          if (((*(int *)(lVar11 + 0x3c) != 0xa9a7) && (*(int *)(lVar11 + 0x3c) != 0x4331)) ||
             ((iVar9 != 0xef && (iVar9 != 0x5c6)))) goto LAB_001bf5b7;
          *(undefined4 *)(lVar11 + 0x84) = 1;
          goto LAB_001bf688;
        }
        *(undefined4 *)(lVar11 + 0x84) = 0;
LAB_001bf60e:
        *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x88) = 0;
      }
      else {
LAB_001bf5b7:
        if (uVar7 == 0x10) {
          *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x84) = 3;
          *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x88) = 4;
        }
        else {
          if (uVar7 == 0x12) {
            lVar11 = *(long *)(lVar10 + 0x20);
          }
          else {
            lVar11 = *(long *)(lVar10 + 0x20);
            if (uVar7 < 0x13) {
              iVar9 = *(int *)(lVar11 + 0x3c);
              if ((((iVar9 != 0x4748) && (iVar9 != 0x4716)) || (*(int *)(lVar11 + 0x44) != 10)) &&
                 (((2 < iVar9 - 0xa8e2U && (iVar9 != 0xa8e6)) && (iVar9 != 0xa8e5)))) {
                if (*(int *)(lVar10 + 0x160) == 7) {
                  *(uint *)(lVar11 + 0x84) =
                       (-(uint)((*(uint *)(lVar11 + 100) & 0x1000) == 0) & 3) + 1;
                }
                else {
                  *(undefined4 *)(lVar11 + 0x84) = 3;
                }
                goto LAB_001bf688;
              }
            }
            else if ((*(int *)(lVar11 + 0x3c) != 0x4324) ||
                    ((*(int *)(lVar11 + 0x40) != 5 && (*(int *)(lVar11 + 0x40) != 2)))) {
              *(undefined4 *)(lVar11 + 0x84) = 0;
              goto LAB_001bf60e;
            }
          }
          *(undefined4 *)(lVar11 + 0x84) = 4;
LAB_001bf688:
          *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x88) = 1;
        }
      }
      lVar11 = *(long *)(lVar10 + 0x20);
      if (param_3 == 2) {
        uVar8 = *(undefined4 *)(lVar11 + 0x84);
      }
      else {
        uVar8 = *(undefined4 *)(lVar11 + 0x88);
      }
      *(undefined4 *)(lVar11 + 0x80) = uVar8;
      *(undefined4 *)(lVar10 + 0x2cc) = 0;
      *(undefined1 *)(lVar10 + 0x2d1) = 0;
      *(undefined1 *)(lVar10 + 0x10dc) = 0;
      *(undefined1 *)(lVar10 + 0x10db) = 0;
      *(undefined1 *)(lVar10 + 0x2d0) = 0;
    }
  }
  else {
    if (iVar9 == 8) {
      if (*(int *)(*(long *)(lVar10 + 0x20) + 0x3c) == 0x4313) {
        *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x84) = 3;
        goto LAB_001bf6fb;
      }
    }
    else if ((iVar9 == 10) && (lVar11 = *(long *)(lVar10 + 0x20), *(int *)(lVar11 + 0x3c) == 0xa886)
            ) {
      *(undefined4 *)(lVar11 + 0x84) = 4;
      *(undefined4 *)(lVar11 + 0x80) = 4;
      goto LAB_001bf791;
    }
    if (*(long *)(lVar10 + 0x160) == 0x300000006) {
      *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x84) = 3;
      *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x88) = 3;
      *(undefined4 *)(*(long *)(lVar10 + 0x20) + 0x80) = 3;
      lVar11 = *(long *)(lVar10 + 0x20);
      if (param_3 == 2) {
        uVar8 = *(undefined4 *)(lVar11 + 0x84);
      }
      else {
        uVar8 = *(undefined4 *)(lVar11 + 0x88);
      }
      *(undefined4 *)(lVar11 + 0x80) = uVar8;
    }
  }
LAB_001bf791:
  lVar11 = FUN_001bdb2d(lVar10,"interference");
  if (lVar11 != 0) {
    lVar11 = *(long *)(lVar10 + 0x20);
    uVar8 = phy_getintvar(lVar10,"interference");
    *(undefined4 *)(lVar11 + 0x84) = uVar8;
    lVar11 = *(long *)(lVar10 + 0x20);
    uVar8 = phy_getintvar(lVar10,"interference");
    *(undefined4 *)(lVar11 + 0x88) = uVar8;
    lVar11 = *(long *)(lVar10 + 0x20);
    if (param_3 == 2) {
      uVar8 = *(undefined4 *)(lVar11 + 0x84);
    }
    else {
      uVar8 = *(undefined4 *)(lVar11 + 0x88);
    }
    *(undefined4 *)(lVar11 + 0x80) = uVar8;
  }
  iVar9 = *(int *)(lVar10 + 0x160);
  *(undefined1 *)(lVar10 + 0xf68) = 10;
  *(undefined1 *)(lVar10 + 0xf69) = 3;
  *(undefined1 *)(lVar10 + 0x1e7) = 0;
  *(undefined1 *)(lVar10 + 0x1ec) = 0;
  *(undefined1 *)(lVar10 + 0x1f1) = 0;
  *(undefined1 *)(lVar10 + 0x1f6) = 0;
  *(undefined1 *)(lVar10 + 0x1fb) = 0;
  *(undefined1 *)(lVar10 + 0x18c) = 1;
  *(undefined1 *)(lVar10 + 0xf82) = 0;
  if ((iVar9 == 7) || (iVar9 == 4)) {
    *(undefined1 *)(lVar10 + 0xc37) = 8;
  }
  else if ((iVar9 == 10) || (iVar9 != 0xb)) {
    *(undefined1 *)(lVar10 + 0xc37) = 9;
  }
  else {
    *(char *)(lVar10 + 0xc37) = (*(int *)(lVar10 + 0x164) == 3) * '\x04' + '\x01';
  }
  *(undefined1 *)(*(long *)(lVar10 + 0x20) + 0xa7) = 3;
  iVar9 = *(int *)(lVar10 + 0x160);
  *(undefined2 *)(lVar10 + 0x1084) = 0xffce;
  *(undefined4 *)(lVar10 + 0x1080) = 0;
  *(undefined1 *)(lVar10 + 0x198) = 1;
  if ((((iVar9 - 4U < 2) || (iVar9 == 10)) || (iVar9 == 8)) || ((iVar9 == 7 || (iVar9 == 0xb)))) {
    *(undefined1 *)(lVar10 + 0x198) = 0;
  }
  iVar9 = *(int *)(lVar10 + 0x160);
  *(undefined8 *)(lVar10 + 0x1c8) = 0;
  *(undefined1 *)(lVar10 + 0x1d6) = 0x7f;
  *(undefined2 *)(lVar10 + 0x236) = 0xffff;
  *(undefined1 *)(lVar10 + 0x140) = 0;
  if ((iVar9 == 2) || (iVar9 == 0)) {
    cVar2 = wlc_phy_attach_abgphy(lVar10,param_3);
    if (cVar2 == '\0') {
      return 0;
    }
  }
  else {
    if (((iVar9 == 7) || (iVar9 == 4)) || (iVar9 == 0xb)) {
      lVar11 = wlapi_init_timer(*(undefined8 *)(*(long *)(lVar10 + 0x20) + 0x20),&LAB_001b640e,
                                lVar10,"phycal");
      *(long *)(lVar10 + 0x1088) = lVar11;
      if (lVar11 == 0) goto LAB_001c00e9;
      iVar9 = *(int *)(lVar10 + 0x160);
      if (iVar9 == 4) {
        cVar2 = wlc_phy_attach_nphy(lVar10);
      }
      else if (iVar9 == 7) {
        cVar2 = wlc_phy_attach_htphy(lVar10);
      }
      else {
        if (iVar9 != 0xb) goto LAB_001bf9c5;
        cVar2 = wlc_phy_attach_acphy(lVar10);
      }
    }
    else if (iVar9 == 5) {
      cVar2 = wlc_phy_attach_lpphy(lVar10);
    }
    else if (iVar9 == 6) {
      cVar2 = wlc_phy_attach_sslpnphy(lVar10);
    }
    else if (iVar9 == 8) {
      cVar2 = wlc_phy_attach_lcnphy(lVar10,param_3);
    }
    else {
      if (iVar9 != 10) goto LAB_001bf9c5;
      cVar2 = wlc_phy_attach_lcn40phy(lVar10);
    }
    if (cVar2 == '\0') goto LAB_001c00e9;
  }
LAB_001bf9c5:
  bVar15 = *(byte *)(lVar10 + 0x168);
  cVar2 = phy_getintvar(lVar10,"tempthresh");
  *(char *)(lVar10 + 0xc2e) = cVar2;
  bVar15 = (char)(1 << (bVar15 & 0x1f)) - 1;
  if (0xfd < (byte)(cVar2 - 1U)) {
    if (*(int *)(lVar10 + 0x160) == 7) {
      *(undefined1 *)(lVar10 + 0xc2e) = 0x96;
    }
    else {
      uVar3 = 0x96;
      if (*(int *)(lVar10 + 0x160) != 0xb) {
        uVar3 = 0x73;
      }
      *(undefined1 *)(lVar10 + 0xc2e) = uVar3;
    }
  }
  if (((*(int *)(lVar10 + 0x160) == 0xb) && (*(int *)(*(long *)(lVar10 + 0x20) + 0x3c) == 0x4360))
     && ((iVar9 = *(int *)(*(long *)(lVar10 + 0x20) + 0x58), iVar9 == 0x117 || (iVar9 == 0x111)))) {
    *(undefined1 *)(lVar10 + 0xc2e) = 0x78;
  }
  *(undefined1 *)(lVar10 + 0xc2f) = *(undefined1 *)(lVar10 + 0xc2e);
  cVar2 = phy_getintvar(lVar10,"temps_hysteresis");
  *(char *)(lVar10 + 0xc30) = cVar2;
  if ((cVar2 == '\x0f') || (cVar2 == '\0')) {
    *(undefined1 *)(lVar10 + 0xc30) = 5;
  }
  *(undefined1 *)(lVar10 + 0xc32) = 0;
  *(undefined1 *)(lVar10 + 0xc34) = 0;
  *(undefined1 *)(lVar10 + 0xc35) = 0;
  *(char *)(lVar10 + 0xc31) = *(char *)(lVar10 + 0xc2e) - *(char *)(lVar10 + 0xc30);
  *(byte *)(lVar10 + 0xc33) = bVar15 * '\x10' | bVar15;
  FUN_001b8077(lVar10);
  if (*(int *)(lVar10 + 0x160) != 10) {
    wlc_phy_anacore(lVar10,1);
  }
  if (*(int *)(lVar10 + 0x160) == 4) {
    if (*(uint *)(lVar10 + 0x164) < 0x13) {
LAB_001bfbdf:
      uVar7 = *(uint *)(*(long *)(lVar10 + 0x20) + 0x28);
      if ((uVar7 == 0x1b) || (uVar7 < 0x18)) {
        osl_writew(1,*(long *)(lVar10 + 0x148) + 0x3f6);
        uVar7 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3fa);
        uVar7 = uVar7 & 0xffff;
        iVar9 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3f8);
        uVar12 = iVar9 << 0x10;
      }
      else {
        osl_writew(0,*(long *)(lVar10 + 0x148) + 0x3d8);
        uVar4 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
        osl_writew(1,*(long *)(lVar10 + 0x148) + 0x3d8);
        uVar6 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
        uVar7 = (uint)uVar6;
        if (*(int *)(lVar10 + 0x160) != 0xb) {
          osl_writew(2,*(long *)(lVar10 + 0x148) + 0x3d8);
          uVar6 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
          uVar7 = (uint)uVar6 << 8 | uVar7;
          uVar12 = uVar4 >> 4 & 0xf | (uint)uVar4 << 0x1c;
          goto LAB_001bfcab;
        }
        uVar12 = (uint)uVar4 << 0x10;
      }
LAB_001bfcfc:
      uVar13 = (ulong)(uVar12 | uVar7);
    }
    else {
      osl_writew(0,*(long *)(lVar10 + 0x148) + 0x3d8);
      uVar4 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
      osl_writew(1,*(long *)(lVar10 + 0x148) + 0x3d8);
      uVar6 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
      uVar7 = (uint)uVar6;
      uVar12 = (uint)uVar4 << 0x1c;
LAB_001bfcab:
      uVar13 = (ulong)(uVar12 | uVar7 << 0xc);
    }
  }
  else {
    if (*(int *)(lVar10 + 0x160) != 10) goto LAB_001bfbdf;
    osl_writew(0,*(long *)(lVar10 + 0x148) + 0x3d8);
    uVar4 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
    uVar16 = uVar4 >> 4 & 0xf;
    uVar7 = uVar4 & 0xf;
    osl_writew(1,*(long *)(lVar10 + 0x148) + 0x3d8);
    uVar4 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3da);
    uVar12 = (uint)uVar4;
    if ((uVar16 == 6) || ((uVar7 == 2 && (uVar12 == 0x2065)))) {
      uVar12 = uVar12 << 0xc;
      goto LAB_001bfcfc;
    }
    uVar13 = (ulong)(uVar12 << 0xc | uVar16);
  }
  *(undefined2 *)(lVar10 + 0x226) = 0;
  if (*(int *)(lVar10 + 0x160) == 0xb) {
    *(short *)(lVar10 + 0x16a) = (short)uVar13;
    *(undefined1 *)(lVar10 + 0x16d) = 0;
    bVar15 = (byte)(uVar13 >> 0x10);
    *(byte *)(lVar10 + 0x16c) = bVar15;
    *(char *)(lVar10 + 0x16e) = (char)(uVar13 >> 0x14);
    *(byte *)(lVar10 + 0x16f) = bVar15 & 0xf;
  }
  else {
    *(short *)(lVar10 + 0x16a) = (short)(uVar13 >> 0xc);
    *(char *)(lVar10 + 0x16c) = (char)(uVar13 >> 0x1c);
    if (*(int *)(lVar10 + 0x164) != 0x14) {
      *(byte *)(lVar10 + 0x16d) = (byte)uVar13 & 0xf;
    }
  }
  iVar9 = *(int *)(lVar10 + 0x160);
  if (iVar9 == 2) {
    bVar18 = *(short *)(lVar10 + 0x16a) == 0x2050;
LAB_001bfe42:
    uVar7 = (uint)!bVar18;
  }
  else {
    if (iVar9 == 0) {
      bVar18 = *(short *)(lVar10 + 0x16a) == 0x2060;
      goto LAB_001bfe42;
    }
    if (iVar9 == 4) {
      uVar7 = (uint)(2 < (ushort)(*(short *)(lVar10 + 0x16a) + 0xdfabU));
      bVar18 = *(short *)(lVar10 + 0x16a) == 0x22e;
    }
    else {
      if (iVar9 == 6) {
        bVar18 = *(short *)(lVar10 + 0x16a) == 0x2063;
        goto LAB_001bfe42;
      }
      if (iVar9 == 8) {
        uVar7 = (uint)(*(short *)(lVar10 + 0x16a) != 0x2066);
        bVar18 = *(short *)(lVar10 + 0x16a) == 0x2064;
      }
      else {
        if (iVar9 != 10) {
          if (iVar9 == 7) {
            bVar18 = *(short *)(lVar10 + 0x16a) == 0x2059;
          }
          else {
            if (iVar9 == 0xb) {
              uVar7 = (uint)(*(short *)(lVar10 + 0x16a) != 0x30b);
              bVar18 = *(short *)(lVar10 + 0x16a) == 0x2069;
              goto LAB_001bfe22;
            }
            bVar18 = 0x2063 - (*(uint *)(lVar10 + 0x164) < 2) == (uint)*(ushort *)(lVar10 + 0x16a);
          }
          goto LAB_001bfe42;
        }
        uVar7 = (uint)(*(short *)(lVar10 + 0x16a) != 0x2065);
        bVar18 = *(short *)(lVar10 + 0x16a) == 0x2067;
      }
    }
LAB_001bfe22:
    uVar7 = !bVar18 & uVar7;
  }
  wlc_phy_switch_radio(lVar10,0);
  if (-1 < (int)(uVar7 << 0x1f)) {
    if ((*(int *)(lVar10 + 0x160) != 10) ||
       (uVar14 = 4, *(int *)(*(long *)(lVar10 + 0x20) + 0x3c) == 0xa887)) {
      uVar14 = 6;
    }
    uVar3 = phy_getintvar_default(lVar10,"txpwrbckof",uVar14);
    *(undefined1 *)(lVar10 + 0x10a0) = uVar3;
    uVar3 = phy_getintvar_default(lVar10,"tssilimucod",1);
    *(undefined1 *)(lVar10 + 0x10b8) = uVar3;
    uVar3 = phy_getintvar_default(lVar10,"rssicorrnorm",0);
    *(undefined1 *)(lVar10 + 0x10fe) = uVar3;
    uVar3 = phy_getintvar_default(lVar10,"rssicorratten",7);
    *(undefined1 *)(lVar10 + 0x10ff) = uVar3;
    if (*(int *)(lVar10 + 0x160) == 10) {
      uVar3 = phy_getintvar_default(lVar10,"rssicorratten",0);
      *(undefined1 *)(lVar10 + 0x10ff) = uVar3;
    }
    lVar11 = lVar10;
    iVar9 = 0;
    do {
      uVar3 = phy_getintvararray_default(lVar10,"rssicorrnorm5g",iVar9,0);
      *(undefined1 *)(lVar11 + 0x1100) = uVar3;
      iVar17 = iVar9 + 1;
      uVar3 = phy_getintvararray_default(lVar10,"rssicorratten5g",iVar9);
      *(undefined1 *)(lVar11 + 0x1103) = uVar3;
      lVar11 = lVar11 + 1;
      iVar9 = iVar17;
    } while (iVar17 != 3);
    uVar3 = phy_getintvararray_default(lVar10,"rssicorrperrg2g",0,0xffffff6a);
    *(undefined1 *)(lVar10 + 0x1106) = uVar3;
    uVar3 = phy_getintvararray_default(lVar10,"rssicorrperrg2g",1,0xffffff6a);
    *(undefined1 *)(lVar10 + 0x1107) = uVar3;
    uVar3 = phy_getintvararray_default(lVar10,"rssicorrperrg5g",0,0xffffff6a);
    *(undefined1 *)(lVar10 + 0x110b) = uVar3;
    uVar3 = phy_getintvararray_default(lVar10,"rssicorrperrg5g",1,0xffffff6a);
    *(undefined1 *)(lVar10 + 0x110c) = uVar3;
    lVar11 = lVar10;
    iVar9 = 2;
    do {
      uVar3 = phy_getintvararray_default(lVar10,"rssicorrperrg2g",iVar9,0);
      *(undefined1 *)(lVar11 + 0x1108) = uVar3;
      iVar17 = iVar9 + 1;
      uVar3 = phy_getintvararray_default(lVar10,"rssicorrperrg5g",iVar9);
      *(undefined1 *)(lVar11 + 0x110d) = uVar3;
      lVar11 = lVar11 + 1;
      iVar9 = iVar17;
    } while (iVar17 != 5);
    lVar11 = lVar10;
    iVar9 = 0;
    do {
      iVar17 = iVar9 + 1;
      uVar3 = phy_getintvararray(lVar10,"5g_cga",iVar9);
      *(undefined1 *)(lVar11 + 0x1110) = uVar3;
      lVar11 = lVar11 + 1;
      iVar9 = iVar17;
    } while (iVar17 != 0x18);
    lVar11 = lVar10;
    iVar9 = 0;
    do {
      iVar17 = iVar9 + 1;
      uVar3 = phy_getintvararray(lVar10,"2g_cga",iVar9);
      *(undefined1 *)(lVar11 + 0x1128) = uVar3;
      lVar11 = lVar11 + 1;
      iVar9 = iVar17;
    } while (iVar17 != 0xe);
    *(int *)(lVar10 + 0x188) = *(int *)(lVar10 + 0x188) + 1;
    *(undefined4 *)(lVar10 + 0x1144) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x1148) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x114c) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x1150) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x1154) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x1158) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x115c) = 0xffffffff;
    *(undefined4 *)(lVar10 + 0x1160) = 0xffffffff;
    *(undefined8 *)(lVar10 + 0x150) = **(undefined8 **)(lVar10 + 0x20);
    *param_1 = lVar10;
    *(long *)(lVar10 + 0x158) = lVar10 + 0x158;
    osl_memcpy(lVar10,lVar10 + 0x160,0x1c);
    return lVar10;
  }
LAB_001c00e9:
  if (*(long *)(lVar10 + 0x1c8) != 0) {
    ppr_delete(*(undefined8 *)(*(long *)(lVar10 + 0x20) + 0x10));
  }
  osl_mfree(param_1[2],lVar10,0x1170);
  return 0;
}

