
undefined8 wlc_phy_txpwr_srom9_read(long param_1)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  byte bVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  long lVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  byte bVar18;
  byte bVar19;
  byte bVar20;
  byte bVar21;
  int iVar22;
  byte local_44;
  
  lVar11 = FUN_001bdb2d(param_1,"elna2g");
  if ((lVar11 != 0) && (*(int *)(param_1 + 0x160) == 4)) {
    lVar11 = *(long *)(param_1 + 0x138);
    uVar3 = phy_getintvar(param_1,"elna2g");
    *(undefined1 *)(lVar11 + 0x2aa) = uVar3;
  }
  lVar11 = FUN_001bdb2d(param_1,"elna5g");
  if ((lVar11 != 0) && (*(int *)(param_1 + 0x160) == 4)) {
    lVar11 = *(long *)(param_1 + 0x138);
    uVar3 = phy_getintvar(param_1,"elna5g");
    *(undefined1 *)(lVar11 + 0x2ab) = uVar3;
  }
  uVar3 = phy_getintvar(param_1,"antswitch");
  *(undefined1 *)(param_1 + 0x22b) = uVar3;
  uVar3 = phy_getintvar(param_1,&DAT_0055a102);
  *(undefined1 *)(param_1 + 0x22c) = uVar3;
  uVar3 = phy_getintvar(param_1,&DAT_0055a107);
  *(undefined1 *)(param_1 + 0x22d) = uVar3;
  uVar3 = phy_getintvar(param_1,"tssipos2g");
  *(undefined1 *)(param_1 + 0x1d9) = uVar3;
  uVar3 = phy_getintvar(param_1,"extpagain2g");
  *(undefined1 *)(param_1 + 0x1da) = uVar3;
  uVar3 = phy_getintvar(param_1,"pdetrange2g");
  *(undefined1 *)(param_1 + 0x1db) = uVar3;
  uVar3 = phy_getintvar(param_1,"triso2g");
  *(undefined1 *)(param_1 + 0x1dc) = uVar3;
  uVar3 = phy_getintvar(param_1,"antswctl2g");
  *(undefined1 *)(param_1 + 0x1dd) = uVar3;
  uVar3 = phy_getintvar(param_1,"tssipos5g");
  *(undefined1 *)(param_1 + 0x1de) = uVar3;
  uVar3 = phy_getintvar(param_1,"extpagain5g");
  *(undefined1 *)(param_1 + 0x1df) = uVar3;
  uVar3 = phy_getintvar(param_1,"pdetrange5g");
  *(undefined1 *)(param_1 + 0x1e0) = uVar3;
  uVar3 = phy_getintvar(param_1,"triso5g");
  *(undefined1 *)(param_1 + 0x1e1) = uVar3;
  uVar3 = phy_getintvar(param_1,"antswctl5g");
  *(undefined1 *)(param_1 + 0x1e2) = uVar3;
  if (*(int *)(param_1 + 0x160) == 4) {
    if (*(uint *)(param_1 + 0x164) < 3) {
      *(undefined1 *)(param_1 + 0xf60) = 0;
      *(undefined1 *)(param_1 + 0xf61) = 0;
    }
    else {
      *(bool *)(param_1 + 0xf60) = *(char *)(param_1 + 0x1da) == '\x02';
      *(bool *)(param_1 + 0xf61) = *(char *)(param_1 + 0x1df) == '\x02';
    }
  }
  uVar6 = phy_getintvar(param_1,"pa2gw0a3");
  uVar7 = phy_getintvar(param_1,"pa2gw1a3");
  uVar8 = 0;
  if (*(int *)(param_1 + 0x160) == 7) {
    uVar8 = phy_getintvar(param_1,"pa2gw2a3");
  }
  iVar22 = 0;
  bVar12 = (byte)((uVar6 & 0xf0) >> 4);
  bVar13 = (byte)((uVar7 & 0xf0) >> 4);
  bVar14 = (byte)((uVar8 & 0xf0) >> 4);
  bVar15 = (byte)(uVar6 >> 8) & 0xf;
  bVar16 = (byte)(uVar7 >> 8) & 0xf;
  bVar17 = (byte)(uVar8 >> 8) & 0xf;
  local_44 = (byte)uVar6 & 0xf;
  bVar18 = (byte)((uVar6 & 0xf000) >> 0xc);
  bVar19 = (byte)((uVar7 & 0xf000) >> 0xc);
  bVar4 = (byte)uVar8 & 0xf;
  bVar20 = (byte)((uVar8 & 0xf000) >> 0xc);
  bVar2 = (byte)uVar8 & 0xf;
  bVar1 = (byte)uVar7 & 0xf;
  do {
    iVar9 = (*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) + 4;
    if (iVar9 <= iVar22) {
      if (8 < *(uint *)(*(long *)(param_1 + 0x20) + 0x48)) {
        uVar5 = phy_getintvar(param_1,"cckbw202gpo");
        *(undefined2 *)(param_1 + 0xc4c) = uVar5;
        uVar5 = phy_getintvar(param_1,"cckbw20ul2gpo");
        *(undefined2 *)(param_1 + 0xc4e) = uVar5;
        uVar10 = phy_getintvar(param_1,"legofdmbw202gpo");
        *(undefined4 *)(param_1 + 0xc54) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw20ul2gpo");
        *(undefined4 *)(param_1 + 0xc58) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw202gpo");
        *(undefined4 *)(param_1 + 0xc90) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw20ul2gpo");
        *(undefined4 *)(param_1 + 0xc94) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw402gpo");
        *(undefined4 *)(param_1 + 0xc98) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw205glpo");
        *(undefined4 *)(param_1 + 0xc60) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw20ul5glpo");
        *(undefined4 *)(param_1 + 0xc64) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw205gmpo");
        *(undefined4 *)(param_1 + 0xc6c) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw20ul5gmpo");
        *(undefined4 *)(param_1 + 0xc70) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw205ghpo");
        *(undefined4 *)(param_1 + 0xc78) = uVar10;
        uVar10 = phy_getintvar(param_1,"legofdmbw20ul5ghpo");
        *(undefined4 *)(param_1 + 0xc7c) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw205glpo");
        *(undefined4 *)(param_1 + 0xc9c) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw20ul5glpo");
        *(undefined4 *)(param_1 + 0xca0) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw405glpo");
        *(undefined4 *)(param_1 + 0xca4) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw205gmpo");
        *(undefined4 *)(param_1 + 0xca8) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw20ul5gmpo");
        *(undefined4 *)(param_1 + 0xcac) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw405gmpo");
        *(undefined4 *)(param_1 + 0xcb0) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw205ghpo");
        *(undefined4 *)(param_1 + 0xcb4) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw20ul5ghpo");
        *(undefined4 *)(param_1 + 0xcb8) = uVar10;
        uVar10 = phy_getintvar(param_1,"mcsbw405ghpo");
        *(undefined4 *)(param_1 + 0xcbc) = uVar10;
        if (*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) {
          uVar10 = phy_getintvar(param_1,"legofdmbw205ghpo");
          *(undefined4 *)(param_1 + 0xc84) = uVar10;
          uVar10 = phy_getintvar(param_1,"legofdmbw20ul5ghpo");
          *(undefined4 *)(param_1 + 0xc88) = uVar10;
          uVar10 = phy_getintvar(param_1,"mcsbw205ghpo");
          *(undefined4 *)(param_1 + 0xcc0) = uVar10;
          uVar10 = phy_getintvar(param_1,"mcsbw20ul5ghpo");
          *(undefined4 *)(param_1 + 0xcc4) = uVar10;
          uVar10 = phy_getintvar(param_1,"mcsbw405ghpo");
          *(undefined4 *)(param_1 + 0xcc8) = uVar10;
        }
        uVar5 = phy_getintvar(param_1,"mcs32po");
        *(undefined2 *)(param_1 + 0xc50) = uVar5;
        uVar5 = phy_getintvar(param_1);
        *(undefined2 *)(param_1 + 0xc52) = uVar5;
        *(undefined4 *)(param_1 + 0xc5c) = *(undefined4 *)(param_1 + 0xc58);
        for (iVar9 = 0; iVar9 < (int)((*(int *)(*(long *)(param_1 + 0x20) + 0x4c) == 4) + 4);
            iVar9 = iVar9 + 1) {
          iVar22 = 0;
          uVar7 = 0;
          uVar6 = *(ushort *)(param_1 + 0xc52) & 0xf;
          do {
            iVar22 = iVar22 + 1;
            uVar7 = uVar7 | uVar6;
            uVar6 = uVar6 << 4;
          } while (iVar22 != 8);
          if (iVar9 == 0) {
            *(uint *)(param_1 + 0xc5c) = uVar7 + *(int *)(param_1 + 0xc58);
          }
          else if (iVar9 == 1) {
            *(uint *)(param_1 + 0xc68) = uVar7 + *(int *)(param_1 + 0xc64);
          }
          else if (iVar9 == 2) {
            *(uint *)(param_1 + 0xc74) = uVar7 + *(int *)(param_1 + 0xc70);
          }
          else if (iVar9 == 3) {
            *(uint *)(param_1 + 0xc80) = uVar7 + *(int *)(param_1 + 0xc7c);
          }
          else {
            *(uint *)(param_1 + 0xc8c) = uVar7 + *(int *)(param_1 + 0xc88);
          }
        }
      }
      return CONCAT71((uint7)(uint3)((uint)iVar9 >> 8),1);
    }
    if (iVar22 == 2) {
      uVar3 = phy_getintvar(param_1,"maxp5ga0");
      *(undefined1 *)(param_1 + 0xdb6) = uVar3;
      uVar3 = phy_getintvar(param_1,"maxp5ga1");
      *(undefined1 *)(param_1 + 0xdbb) = uVar3;
      uVar5 = phy_getintvar(param_1,"pa5gw0a0");
      *(undefined2 *)(param_1 + 0xd40) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw0a1");
      *(undefined2 *)(param_1 + 0xd4a) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw1a0");
      *(undefined2 *)(param_1 + 0xd68) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw1a1");
      *(undefined2 *)(param_1 + 0xd72) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw2a0");
      *(undefined2 *)(param_1 + 0xd90) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw2a1");
      *(undefined2 *)(param_1 + 0xd9a) = uVar5;
      if ((bVar12 == 0xf) || (7 < bVar12)) {
        bVar21 = 0;
      }
      else {
        bVar21 = bVar12;
        if (3 < bVar12) {
          bVar21 = bVar12 - 8;
        }
      }
      *(byte *)(param_1 + 0xdca) = bVar21;
      if ((bVar13 == 0xf) || (7 < bVar13)) {
        bVar21 = 0;
      }
      else {
        bVar21 = bVar13;
        if (3 < bVar13) {
          bVar21 = bVar13 - 8;
        }
      }
      *(byte *)(param_1 + 0xdcf) = bVar21;
      if (*(int *)(param_1 + 0x160) == 7) {
        uVar3 = phy_getintvar(param_1,"maxp5ga2");
        *(undefined1 *)(param_1 + 0xdc0) = uVar3;
        uVar5 = phy_getintvar(param_1,"pa5gw0a2");
        *(undefined2 *)(param_1 + 0xd54) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5gw1a2");
        *(undefined2 *)(param_1 + 0xd7c) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5gw2a2");
        *(undefined2 *)(param_1 + 0xda4) = uVar5;
        if ((bVar14 == 0xf) || (7 < bVar14)) {
          bVar21 = 0;
        }
        else {
          bVar21 = bVar14;
          if (3 < bVar14) {
            bVar21 = bVar14 - 8;
          }
        }
        *(byte *)(param_1 + 0xdd4) = bVar21;
      }
    }
    else if (iVar22 < 3) {
      if (iVar22 == 1) {
        uVar3 = phy_getintvar(param_1,"maxp5gla0");
        *(undefined1 *)(param_1 + 0xdb5) = uVar3;
        uVar3 = phy_getintvar(param_1,"maxp5gla1");
        *(undefined1 *)(param_1 + 0xdba) = uVar3;
        uVar5 = phy_getintvar(param_1,"pa5glw0a0");
        *(undefined2 *)(param_1 + 0xd3e) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5glw0a1");
        *(undefined2 *)(param_1 + 0xd48) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5glw1a0");
        *(undefined2 *)(param_1 + 0xd66) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5glw1a1");
        *(undefined2 *)(param_1 + 0xd70) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5glw2a0");
        *(undefined2 *)(param_1 + 0xd8e) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5glw2a1");
        *(undefined2 *)(param_1 + 0xd98) = uVar5;
        if ((local_44 == 0xf) || (7 < local_44)) {
          bVar21 = 0;
        }
        else {
          bVar21 = local_44;
          if (3 < local_44) {
            bVar21 = local_44 - 8;
          }
        }
        *(byte *)(param_1 + 0xdc9) = bVar21;
        if ((bVar1 == 0xf) || (7 < bVar1)) {
          bVar21 = 0;
        }
        else {
          bVar21 = bVar1 - 8;
          if (bVar1 < 4) {
            bVar21 = bVar1;
          }
        }
        *(byte *)(param_1 + 0xdce) = bVar21;
        if (*(int *)(param_1 + 0x160) == 7) {
          uVar3 = phy_getintvar(param_1,"maxp5gla2");
          *(undefined1 *)(param_1 + 0xdbf) = uVar3;
          uVar5 = phy_getintvar(param_1,"pa5glw0a2");
          *(undefined2 *)(param_1 + 0xd52) = uVar5;
          uVar5 = phy_getintvar(param_1,"pa5glw1a2");
          *(undefined2 *)(param_1 + 0xd7a) = uVar5;
          uVar5 = phy_getintvar(param_1,"pa5glw2a2");
          *(undefined2 *)(param_1 + 0xda2) = uVar5;
          if ((bVar4 == 0xf) || (7 < bVar4)) {
            bVar21 = 0;
          }
          else {
            bVar21 = bVar2 - 8;
            if (bVar4 < 4) {
              bVar21 = bVar2;
            }
          }
          *(byte *)(param_1 + 0xdd3) = bVar21;
        }
      }
      else {
LAB_001be0f4:
        uVar3 = phy_getintvar(param_1,"maxp2ga0");
        *(undefined1 *)(param_1 + 0xdb4) = uVar3;
        uVar3 = phy_getintvar(param_1,"maxp2ga1");
        *(undefined1 *)(param_1 + 0xdb9) = uVar3;
        uVar5 = phy_getintvar(param_1,"pa2gw0a0");
        *(undefined2 *)(param_1 + 0xd3c) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa2gw0a1");
        *(undefined2 *)(param_1 + 0xd46) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa2gw1a0");
        *(undefined2 *)(param_1 + 0xd64) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa2gw1a1");
        *(undefined2 *)(param_1 + 0xd6e) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa2gw2a0");
        *(undefined2 *)(param_1 + 0xd8c) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa2gw2a1");
        *(undefined2 *)(param_1 + 0xd96) = uVar5;
        *(undefined1 *)(param_1 + 0xdc8) = 0;
        *(undefined1 *)(param_1 + 0xdcd) = 0;
        if (*(int *)(param_1 + 0x160) == 7) {
          uVar3 = phy_getintvar(param_1,"maxp2ga2");
          *(undefined1 *)(param_1 + 0xdbe) = uVar3;
          uVar5 = phy_getintvar(param_1,"pa2gw0a2");
          *(undefined2 *)(param_1 + 0xd50) = uVar5;
          uVar5 = phy_getintvar(param_1,"pa2gw1a2");
          *(undefined2 *)(param_1 + 0xd78) = uVar5;
          uVar5 = phy_getintvar(param_1,"pa2gw2a2");
          *(undefined1 *)(param_1 + 0xdd2) = 0;
          *(undefined2 *)(param_1 + 0xda0) = uVar5;
        }
      }
    }
    else if (iVar22 == 3) {
      uVar3 = phy_getintvar(param_1,"maxp5gha0");
      *(undefined1 *)(param_1 + 0xdb7) = uVar3;
      uVar3 = phy_getintvar(param_1,"maxp5gha1");
      *(undefined1 *)(param_1 + 0xdbc) = uVar3;
      uVar5 = phy_getintvar(param_1,"pa5ghw0a0");
      *(undefined2 *)(param_1 + 0xd42) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5ghw0a1");
      *(undefined2 *)(param_1 + 0xd4c) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5ghw1a0");
      *(undefined2 *)(param_1 + 0xd6a) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5ghw1a1");
      *(undefined2 *)(param_1 + 0xd74) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5ghw2a0");
      *(undefined2 *)(param_1 + 0xd92) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5ghw2a1");
      *(undefined2 *)(param_1 + 0xd9c) = uVar5;
      if ((bVar15 == 0xf) || (7 < bVar15)) {
        bVar21 = 0;
      }
      else {
        bVar21 = bVar15;
        if (3 < bVar15) {
          bVar21 = bVar15 - 8;
        }
      }
      *(byte *)(param_1 + 0xdcb) = bVar21;
      if ((bVar16 == 0xf) || (7 < bVar16)) {
        bVar21 = 0;
      }
      else {
        bVar21 = bVar16;
        if (3 < bVar16) {
          bVar21 = bVar16 - 8;
        }
      }
      *(byte *)(param_1 + 0xdd0) = bVar21;
      if (*(int *)(param_1 + 0x160) == 7) {
        uVar3 = phy_getintvar(param_1,"maxp5gha2");
        *(undefined1 *)(param_1 + 0xdc1) = uVar3;
        uVar5 = phy_getintvar(param_1,"pa5ghw0a2");
        *(undefined2 *)(param_1 + 0xd56) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5ghw1a2");
        *(undefined2 *)(param_1 + 0xd7e) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5ghw2a2");
        *(undefined2 *)(param_1 + 0xda6) = uVar5;
        if ((bVar17 == 0xf) || (7 < bVar17)) {
          bVar21 = 0;
        }
        else {
          bVar21 = bVar17;
          if (3 < bVar17) {
            bVar21 = bVar17 - 8;
          }
        }
        *(byte *)(param_1 + 0xdd5) = bVar21;
      }
    }
    else {
      if (iVar22 != 4) goto LAB_001be0f4;
      uVar3 = phy_getintvar(param_1,"maxp5ga3");
      *(undefined1 *)(param_1 + 0xdb8) = uVar3;
      uVar3 = phy_getintvar(param_1,"maxp5gla3");
      *(undefined1 *)(param_1 + 0xdbd) = uVar3;
      uVar5 = phy_getintvar(param_1,"pa5gw0a3");
      *(undefined2 *)(param_1 + 0xd44) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5glw0a3");
      *(undefined2 *)(param_1 + 0xd4e) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw1a3");
      *(undefined2 *)(param_1 + 0xd6c) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5glw1a3");
      *(undefined2 *)(param_1 + 0xd76) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5gw2a3");
      *(undefined2 *)(param_1 + 0xd94) = uVar5;
      uVar5 = phy_getintvar(param_1,"pa5glw2a3");
      *(undefined2 *)(param_1 + 0xd9e) = uVar5;
      if ((bVar18 == 0xf) || (7 < bVar18)) {
        bVar21 = 0;
      }
      else {
        bVar21 = bVar18;
        if (3 < bVar18) {
          bVar21 = bVar18 - 8;
        }
      }
      *(byte *)(param_1 + 0xdcc) = bVar21;
      if ((bVar19 == 0xf) || (7 < bVar19)) {
        bVar21 = 0;
      }
      else {
        bVar21 = bVar19;
        if (3 < bVar19) {
          bVar21 = bVar19 - 8;
        }
      }
      *(byte *)(param_1 + 0xdd1) = bVar21;
      if (*(int *)(param_1 + 0x160) == 7) {
        uVar3 = phy_getintvar(param_1,"maxp5gha3");
        *(undefined1 *)(param_1 + 0xdc2) = uVar3;
        uVar5 = phy_getintvar(param_1,"pa5ghw0a3");
        *(undefined2 *)(param_1 + 0xd58) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5ghw1a3");
        *(undefined2 *)(param_1 + 0xd80) = uVar5;
        uVar5 = phy_getintvar(param_1,"pa5ghw2a3");
        *(undefined2 *)(param_1 + 0xda8) = uVar5;
        if ((bVar20 == 0xf) || (7 < bVar20)) {
          bVar21 = 0;
        }
        else {
          bVar21 = bVar20;
          if (3 < bVar20) {
            bVar21 = bVar20 - 8;
          }
        }
        *(byte *)(param_1 + 0xdd6) = bVar21;
      }
    }
    iVar22 = iVar22 + 1;
  } while( true );
}

