
undefined8 wlc_phy_txpwr_srom8_read(long param_1)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  byte bVar4;
  ushort uVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  long lVar8;
  int iVar9;
  
  uVar2 = phy_getintvar(param_1,"antswitch");
  *(undefined1 *)(param_1 + 0x22b) = uVar2;
  uVar2 = phy_getintvar(param_1,&DAT_0055a102);
  *(undefined1 *)(param_1 + 0x22c) = uVar2;
  uVar2 = phy_getintvar(param_1,&DAT_0055a107);
  *(undefined1 *)(param_1 + 0x22d) = uVar2;
  uVar2 = phy_getintvar(param_1,"tssipos2g");
  *(undefined1 *)(param_1 + 0x1d9) = uVar2;
  uVar2 = phy_getintvar(param_1,"extpagain2g");
  *(undefined1 *)(param_1 + 0x1da) = uVar2;
  uVar2 = phy_getintvar(param_1,"pdetrange2g");
  *(undefined1 *)(param_1 + 0x1db) = uVar2;
  uVar2 = phy_getintvar(param_1,"triso2g");
  *(undefined1 *)(param_1 + 0x1dc) = uVar2;
  uVar2 = phy_getintvar(param_1,"antswctl2g");
  *(undefined1 *)(param_1 + 0x1dd) = uVar2;
  uVar2 = phy_getintvar(param_1,"tssipos5g");
  *(undefined1 *)(param_1 + 0x1de) = uVar2;
  uVar2 = phy_getintvar(param_1,"extpagain5g");
  *(undefined1 *)(param_1 + 0x1df) = uVar2;
  uVar2 = phy_getintvar(param_1,"pdetrange5g");
  *(undefined1 *)(param_1 + 0x1e0) = uVar2;
  uVar2 = phy_getintvar(param_1,"triso5g");
  *(undefined1 *)(param_1 + 0x1e1) = uVar2;
  uVar7 = phy_getintvar(param_1,"antswctl2g");
  uVar2 = phy_getintvar_default(param_1,"antswctl5g",uVar7);
  *(undefined1 *)(param_1 + 0x1e2) = uVar2;
  lVar8 = FUN_001bdb2d(param_1,"elna2g");
  if ((lVar8 != 0) && (*(int *)(param_1 + 0x160) == 4)) {
    lVar8 = *(long *)(param_1 + 0x138);
    uVar2 = phy_getintvar(param_1,"elna2g");
    *(undefined1 *)(lVar8 + 0x2aa) = uVar2;
  }
  lVar8 = FUN_001bdb2d(param_1,"elna5g");
  if ((lVar8 != 0) && (*(int *)(param_1 + 0x160) == 4)) {
    lVar8 = *(long *)(param_1 + 0x138);
    uVar2 = phy_getintvar(param_1,"elna5g");
    *(undefined1 *)(lVar8 + 0x2ab) = uVar2;
  }
  if (*(uint *)(param_1 + 0x164) < 3) {
    *(undefined1 *)(param_1 + 0xf60) = 0;
    *(undefined1 *)(param_1 + 0xf61) = 0;
  }
  else {
    *(bool *)(param_1 + 0xf60) = *(char *)(param_1 + 0x1da) == '\x02';
    *(bool *)(param_1 + 0xf61) = *(char *)(param_1 + 0x1df) == '\x02';
  }
  cVar3 = phy_getintvar(param_1,"tempoffset");
  *(char *)(param_1 + 0xc35) = cVar3;
  if (cVar3 != '\0') {
    if (cVar3 < '1') {
      if (cVar3 < '\x10') {
        *(undefined1 *)(param_1 + 0xc35) = 0xf0;
      }
      else {
        *(char *)(param_1 + 0xc35) = cVar3 + -0x20;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0xc35) = 0x10;
    }
  }
  FUN_001bf0bf(param_1);
  lVar8 = *(long *)(param_1 + 0x138);
  uVar5 = phy_getintvar(param_1,"bw40po");
  *(byte *)(param_1 + 0xc60) = (byte)uVar5 & 0xf;
  bVar1 = (byte)(uVar5 >> 8);
  bVar4 = bVar1 >> 4;
  *(byte *)(param_1 + 0xc63) = bVar4;
  *(byte *)(param_1 + 0xc62) = bVar1 & 0xf;
  *(char *)(param_1 + 0xc61) = (char)((int)(uVar5 & 0xf0) >> 4);
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) {
    *(byte *)(param_1 + 0xc64) = bVar4;
  }
  uVar5 = phy_getintvar(param_1,"cddpo");
  *(byte *)(param_1 + 0xc6f) = (byte)uVar5 & 0xf;
  bVar1 = (byte)(uVar5 >> 8);
  bVar4 = bVar1 >> 4;
  *(byte *)(param_1 + 0xc72) = bVar4;
  *(byte *)(param_1 + 0xc71) = bVar1 & 0xf;
  *(char *)(param_1 + 0xc70) = (char)((int)(uVar5 & 0xf0) >> 4);
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) {
    *(byte *)(param_1 + 0xc73) = bVar4;
  }
  uVar5 = phy_getintvar(param_1,"stbcpo");
  *(byte *)(param_1 + 0xc65) = (byte)uVar5 & 0xf;
  bVar1 = (byte)(uVar5 >> 8);
  bVar4 = bVar1 >> 4;
  *(byte *)(param_1 + 0xc68) = bVar4;
  *(byte *)(param_1 + 0xc67) = bVar1 & 0xf;
  *(char *)(param_1 + 0xc66) = (char)((int)(uVar5 & 0xf0) >> 4);
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) {
    *(byte *)(param_1 + 0xc69) = bVar4;
  }
  uVar5 = phy_getintvar(param_1,"bwduppo");
  *(byte *)(param_1 + 0xc6a) = (byte)uVar5 & 0xf;
  bVar1 = (byte)(uVar5 >> 8);
  bVar4 = bVar1 >> 4;
  *(byte *)(param_1 + 0xc6d) = bVar4;
  *(byte *)(param_1 + 0xc6c) = bVar1 & 0xf;
  *(char *)(param_1 + 0xc6b) = (char)((int)(uVar5 & 0xf0) >> 4);
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) {
    *(byte *)(param_1 + 0xc6e) = bVar4;
  }
  iVar9 = 0;
  do {
    if ((int)((*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) + 4) <= iVar9) {
      return 1;
    }
    if (iVar9 == 2) {
      if (*(int *)(param_1 + 0x160) == 4) {
        uVar2 = phy_getintvar(param_1,"txpid5ga0");
        *(undefined1 *)(lVar8 + 0x1b5) = uVar2;
        uVar2 = phy_getintvar(param_1,"txpid5ga1");
        *(undefined1 *)(lVar8 + 0x1b6) = uVar2;
      }
      uVar2 = phy_getintvar(param_1,"maxp5ga0");
      *(undefined1 *)(param_1 + 0xdb6) = uVar2;
      uVar2 = phy_getintvar(param_1,"maxp5ga1");
      *(undefined1 *)(param_1 + 0xdbb) = uVar2;
      uVar6 = phy_getintvar(param_1,"pa5gw0a0");
      *(undefined2 *)(param_1 + 0xd40) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5gw0a1");
      *(undefined2 *)(param_1 + 0xd4a) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5gw1a0");
      *(undefined2 *)(param_1 + 0xd68) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5gw1a1");
      *(undefined2 *)(param_1 + 0xd72) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5gw2a0");
      *(undefined2 *)(param_1 + 0xd90) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5gw2a1");
      *(undefined2 *)(param_1 + 0xd9a) = uVar6;
      if (*(int *)(param_1 + 0x160) == 4) {
        uVar2 = phy_getintvar(param_1,"itt5ga0");
        *(undefined1 *)(lVar8 + 0x23d) = uVar2;
        uVar2 = phy_getintvar(param_1,"itt5ga1");
        *(undefined1 *)(lVar8 + 0x24f) = uVar2;
      }
      uVar7 = phy_getintvar(param_1,"ofdm5gpo");
      *(undefined4 *)(param_1 + 0xc54) = uVar7;
      uVar6 = phy_getintvar(param_1,"mcs5gpo0");
      *(undefined2 *)(param_1 + 0xc94) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo1");
      *(undefined2 *)(param_1 + 0xc96) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo2");
      *(undefined2 *)(param_1 + 0xc98) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo3");
      *(undefined2 *)(param_1 + 0xc9a) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo4");
      *(undefined2 *)(param_1 + 0xc9c) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo5");
      *(undefined2 *)(param_1 + 0xc9e) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo6");
      *(undefined2 *)(param_1 + 0xca0) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5gpo7");
      *(undefined2 *)(param_1 + 0xca2) = uVar6;
    }
    else if (iVar9 < 3) {
      if (iVar9 == 1) {
        if (*(int *)(param_1 + 0x160) == 4) {
          uVar2 = phy_getintvar(param_1,"txpid5gla0");
          *(undefined1 *)(lVar8 + 0x1b0) = uVar2;
          uVar2 = phy_getintvar(param_1,"txpid5gla1");
          *(undefined1 *)(lVar8 + 0x1b1) = uVar2;
        }
        uVar2 = phy_getintvar(param_1,"maxp5gla0");
        *(undefined1 *)(param_1 + 0xdb5) = uVar2;
        uVar2 = phy_getintvar(param_1,"maxp5gla1");
        *(undefined1 *)(param_1 + 0xdba) = uVar2;
        uVar6 = phy_getintvar(param_1,"pa5glw0a0");
        *(undefined2 *)(param_1 + 0xd3e) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa5glw0a1");
        *(undefined2 *)(param_1 + 0xd48) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa5glw1a0");
        *(undefined2 *)(param_1 + 0xd66) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa5glw1a1");
        *(undefined2 *)(param_1 + 0xd70) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa5glw2a0");
        *(undefined2 *)(param_1 + 0xd8e) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa5glw2a1");
        *(undefined2 *)(param_1 + 0xd98) = uVar6;
        if (*(int *)(param_1 + 0x160) == 4) {
          *(undefined1 *)(lVar8 + 0x23c) = 0;
          *(undefined1 *)(lVar8 + 0x24e) = 0;
        }
        uVar7 = phy_getintvar(param_1,"ofdm5glpo");
        *(undefined4 *)(param_1 + 0xc50) = uVar7;
        uVar6 = phy_getintvar(param_1,"mcs5glpo0");
        *(undefined2 *)(param_1 + 0xc84) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo1");
        *(undefined2 *)(param_1 + 0xc86) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo2");
        *(undefined2 *)(param_1 + 0xc88) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo3");
        *(undefined2 *)(param_1 + 0xc8a) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo4");
        *(undefined2 *)(param_1 + 0xc8c) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo5");
        *(undefined2 *)(param_1 + 0xc8e) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo6");
        *(undefined2 *)(param_1 + 0xc90) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs5glpo7");
        *(undefined2 *)(param_1 + 0xc92) = uVar6;
      }
      else {
LAB_001c1365:
        if (*(int *)(param_1 + 0x160) == 4) {
          uVar2 = phy_getintvar(param_1,"txpid2ga0");
          *(undefined1 *)(lVar8 + 0x1a7) = uVar2;
          uVar2 = phy_getintvar(param_1,"txpid2ga1");
          *(undefined1 *)(lVar8 + 0x1a8) = uVar2;
        }
        uVar2 = phy_getintvar(param_1,"maxp2ga0");
        *(undefined1 *)(param_1 + 0xdb4) = uVar2;
        uVar2 = phy_getintvar(param_1,"maxp2ga1");
        *(undefined1 *)(param_1 + 0xdb9) = uVar2;
        uVar6 = phy_getintvar(param_1,"pa2gw0a0");
        *(undefined2 *)(param_1 + 0xd3c) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa2gw0a1");
        *(undefined2 *)(param_1 + 0xd46) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa2gw1a0");
        *(undefined2 *)(param_1 + 0xd64) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa2gw1a1");
        *(undefined2 *)(param_1 + 0xd6e) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa2gw2a0");
        *(undefined2 *)(param_1 + 0xd8c) = uVar6;
        uVar6 = phy_getintvar(param_1,"pa2gw2a1");
        *(undefined2 *)(param_1 + 0xd96) = uVar6;
        if (*(int *)(param_1 + 0x160) == 4) {
          uVar2 = phy_getintvar(param_1,"itt2ga0");
          *(undefined1 *)(lVar8 + 0x23a) = uVar2;
          uVar2 = phy_getintvar(param_1,"itt2ga1");
          *(undefined1 *)(lVar8 + 0x24c) = uVar2;
        }
        uVar6 = phy_getintvar(param_1,"cck2gpo");
        *(undefined2 *)(param_1 + 0xcc4) = uVar6;
        uVar7 = phy_getintvar(param_1,"ofdm2gpo");
        *(undefined4 *)(param_1 + 0xc4c) = uVar7;
        uVar6 = phy_getintvar(param_1,"mcs2gpo0");
        *(undefined2 *)(param_1 + 0xc74) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo1");
        *(undefined2 *)(param_1 + 0xc76) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo2");
        *(undefined2 *)(param_1 + 0xc78) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo3");
        *(undefined2 *)(param_1 + 0xc7a) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo4");
        *(undefined2 *)(param_1 + 0xc7c) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo5");
        *(undefined2 *)(param_1 + 0xc7e) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo6");
        *(undefined2 *)(param_1 + 0xc80) = uVar6;
        uVar6 = phy_getintvar(param_1,"mcs2gpo7");
        *(undefined2 *)(param_1 + 0xc82) = uVar6;
      }
    }
    else if (iVar9 == 3) {
      if (*(int *)(param_1 + 0x160) == 4) {
        uVar2 = phy_getintvar(param_1,"txpid5gha0");
        *(undefined1 *)(lVar8 + 0x1ba) = uVar2;
        uVar2 = phy_getintvar(param_1,"txpid5gha1");
        *(undefined1 *)(lVar8 + 0x1bb) = uVar2;
      }
      uVar2 = phy_getintvar(param_1,"maxp5gha0");
      *(undefined1 *)(param_1 + 0xdb7) = uVar2;
      uVar2 = phy_getintvar(param_1,"maxp5gha1");
      *(undefined1 *)(param_1 + 0xdbc) = uVar2;
      uVar6 = phy_getintvar(param_1,"pa5ghw0a0");
      *(undefined2 *)(param_1 + 0xd42) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw0a1");
      *(undefined2 *)(param_1 + 0xd4c) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw1a0");
      *(undefined2 *)(param_1 + 0xd6a) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw1a1");
      *(undefined2 *)(param_1 + 0xd74) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw2a0");
      *(undefined2 *)(param_1 + 0xd92) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw2a1");
      *(undefined2 *)(param_1 + 0xd9c) = uVar6;
      if (*(int *)(param_1 + 0x160) == 4) {
        *(undefined1 *)(lVar8 + 0x23e) = 0;
        *(undefined1 *)(lVar8 + 0x250) = 0;
      }
      uVar7 = phy_getintvar(param_1,"ofdm5ghpo");
      *(undefined4 *)(param_1 + 0xc58) = uVar7;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo0");
      *(undefined2 *)(param_1 + 0xca4) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo1");
      *(undefined2 *)(param_1 + 0xca6) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo2");
      *(undefined2 *)(param_1 + 0xca8) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo3");
      *(undefined2 *)(param_1 + 0xcaa) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo4");
      *(undefined2 *)(param_1 + 0xcac) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo5");
      *(undefined2 *)(param_1 + 0xcae) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo6");
      *(undefined2 *)(param_1 + 0xcb0) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo7");
      *(undefined2 *)(param_1 + 0xcb2) = uVar6;
    }
    else {
      if (iVar9 != 4) goto LAB_001c1365;
      if (*(int *)(param_1 + 0x160) == 4) {
        uVar2 = phy_getintvar(param_1,"txpid5gha0");
        *(undefined1 *)(lVar8 + 0x1af) = uVar2;
        uVar2 = phy_getintvar(param_1,"txpid5gha1");
        *(undefined1 *)(lVar8 + 0x1b4) = uVar2;
      }
      uVar2 = phy_getintvar(param_1,"maxp5gha0");
      *(undefined1 *)(param_1 + 0xdb8) = uVar2;
      uVar2 = phy_getintvar(param_1,"maxp5gha1");
      *(undefined1 *)(param_1 + 0xdbd) = uVar2;
      uVar6 = phy_getintvar(param_1,"pa5ghw0a0");
      *(undefined2 *)(param_1 + 0xd44) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw0a1");
      *(undefined2 *)(param_1 + 0xd4e) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw1a0");
      *(undefined2 *)(param_1 + 0xd6c) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw1a1");
      *(undefined2 *)(param_1 + 0xd76) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw2a0");
      *(undefined2 *)(param_1 + 0xd94) = uVar6;
      uVar6 = phy_getintvar(param_1,"pa5ghw2a1");
      *(undefined2 *)(param_1 + 0xd9e) = uVar6;
      if (*(int *)(param_1 + 0x160) == 4) {
        *(undefined1 *)(lVar8 + 0x23f) = 0;
        *(undefined1 *)(lVar8 + 0x251) = 0;
      }
      uVar7 = phy_getintvar(param_1,"ofdm5ghpo");
      *(undefined4 *)(param_1 + 0xc5c) = uVar7;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo0");
      *(undefined2 *)(param_1 + 0xcb4) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo1");
      *(undefined2 *)(param_1 + 0xcb6) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo2");
      *(undefined2 *)(param_1 + 0xcb8) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo3");
      *(undefined2 *)(param_1 + 0xcba) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo4");
      *(undefined2 *)(param_1 + 0xcbc) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo5");
      *(undefined2 *)(param_1 + 0xcbe) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo6");
      *(undefined2 *)(param_1 + 0xcc0) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcs5ghpo7");
      *(undefined2 *)(param_1 + 0xcc2) = uVar6;
    }
    iVar9 = iVar9 + 1;
  } while( true );
}

