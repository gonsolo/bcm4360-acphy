
undefined8 wlc_phy_txpwr_srom11_read(long param_1)

{
  uint uVar1;
  undefined1 uVar2;
  char cVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  uint uVar8;
  byte bVar9;
  
  uVar7 = 0;
  if (*(int *)(param_1 + 0x160) == 0xb) {
    bVar9 = 0;
    do {
      if (bVar9 == 2) {
        uVar2 = phy_getintvararray(param_1,"maxp5ga0",1);
        *(undefined1 *)(param_1 + 0xe7e) = uVar2;
        uVar2 = phy_getintvararray(param_1,"maxp5ga1",1);
        *(undefined1 *)(param_1 + 0xe83) = uVar2;
        uVar2 = phy_getintvararray(param_1,"maxp5ga2",1);
        *(undefined1 *)(param_1 + 0xe88) = uVar2;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",3);
        *(undefined2 *)(param_1 + 0xe08) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",4);
        *(undefined2 *)(param_1 + 0xe30) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",5);
        *(undefined2 *)(param_1 + 0xe58) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",3);
        *(undefined2 *)(param_1 + 0xe12) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",4);
        *(undefined2 *)(param_1 + 0xe3a) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",5);
        *(undefined2 *)(param_1 + 0xe62) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",3);
        *(undefined2 *)(param_1 + 0xe1c) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",4);
        *(undefined2 *)(param_1 + 0xe44) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",5);
        *(undefined2 *)(param_1 + 0xe6c) = uVar4;
        if ((*(int *)(param_1 + 0x164) == 3) &&
           (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",3);
          *(undefined2 *)(param_1 + 0xe26) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",4);
          *(undefined2 *)(param_1 + 0xe4e) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",5);
          *(undefined2 *)(param_1 + 0xe76) = uVar4;
        }
        uVar4 = phy_getintvararray(param_1,"tssifloor5g",1);
        *(undefined2 *)(param_1 + 0xeaa) = uVar4;
      }
      else if (bVar9 < 3) {
        if (bVar9 == 1) {
          uVar2 = phy_getintvararray(param_1,"maxp5ga0",0);
          *(undefined1 *)(param_1 + 0xe7d) = uVar2;
          uVar2 = phy_getintvararray(param_1,"maxp5ga1",0);
          *(undefined1 *)(param_1 + 0xe82) = uVar2;
          uVar2 = phy_getintvararray(param_1,"maxp5ga2",0);
          *(undefined1 *)(param_1 + 0xe87) = uVar2;
          uVar4 = phy_getintvararray(param_1,"pa5ga0",0);
          *(undefined2 *)(param_1 + 0xe06) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga0",1);
          *(undefined2 *)(param_1 + 0xe2e) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga0",2);
          *(undefined2 *)(param_1 + 0xe56) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga1",0);
          *(undefined2 *)(param_1 + 0xe10) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga1",1);
          *(undefined2 *)(param_1 + 0xe38) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga1",2);
          *(undefined2 *)(param_1 + 0xe60) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga2",0);
          *(undefined2 *)(param_1 + 0xe1a) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga2",1);
          *(undefined2 *)(param_1 + 0xe42) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5ga2",2);
          *(undefined2 *)(param_1 + 0xe6a) = uVar4;
          if ((*(int *)(param_1 + 0x164) == 3) &&
             (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
            uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",0);
            *(undefined2 *)(param_1 + 0xe24) = uVar4;
            uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",1);
            *(undefined2 *)(param_1 + 0xe4c) = uVar4;
            uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",2);
            *(undefined2 *)(param_1 + 0xe74) = uVar4;
          }
          uVar4 = phy_getintvararray(param_1,"tssifloor5g",0);
          *(undefined2 *)(param_1 + 0xea8) = uVar4;
        }
        else {
LAB_001c016f:
          uVar2 = phy_getintvar(param_1,"maxp2ga0");
          *(undefined1 *)(param_1 + 0xe7c) = uVar2;
          uVar2 = phy_getintvar(param_1,"maxp2ga1");
          *(undefined1 *)(param_1 + 0xe81) = uVar2;
          uVar2 = phy_getintvar(param_1,"maxp2ga2");
          *(undefined1 *)(param_1 + 0xe86) = uVar2;
          uVar4 = phy_getintvararray(param_1,"pa2ga0",0);
          *(undefined2 *)(param_1 + 0xe04) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga0",1);
          *(undefined2 *)(param_1 + 0xe2c) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga0",2);
          *(undefined2 *)(param_1 + 0xe54) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga1",0);
          *(undefined2 *)(param_1 + 0xe0e) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga1",1);
          *(undefined2 *)(param_1 + 0xe36) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga1",2);
          *(undefined2 *)(param_1 + 0xe5e) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga2",0);
          *(undefined2 *)(param_1 + 0xe18) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga2",1);
          *(undefined2 *)(param_1 + 0xe40) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa2ga2",2);
          *(undefined2 *)(param_1 + 0xe68) = uVar4;
          uVar4 = phy_getintvararray(param_1,"tssifloor2g",0);
          *(undefined2 *)(param_1 + 0xea6) = uVar4;
        }
      }
      else if (bVar9 == 3) {
        uVar2 = phy_getintvararray(param_1,"maxp5ga0",2);
        *(undefined1 *)(param_1 + 0xe7f) = uVar2;
        uVar2 = phy_getintvararray(param_1,"maxp5ga1",2);
        *(undefined1 *)(param_1 + 0xe84) = uVar2;
        uVar2 = phy_getintvararray(param_1,"maxp5ga2",2);
        *(undefined1 *)(param_1 + 0xe89) = uVar2;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",6);
        *(undefined2 *)(param_1 + 0xe0a) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",7);
        *(undefined2 *)(param_1 + 0xe32) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",8);
        *(undefined2 *)(param_1 + 0xe5a) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",6);
        *(undefined2 *)(param_1 + 0xe14) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",7);
        *(undefined2 *)(param_1 + 0xe3c) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",8);
        *(undefined2 *)(param_1 + 0xe64) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",6);
        *(undefined2 *)(param_1 + 0xe1e) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",7);
        *(undefined2 *)(param_1 + 0xe46) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",8);
        *(undefined2 *)(param_1 + 0xe6e) = uVar4;
        if ((*(int *)(param_1 + 0x164) == 3) &&
           (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",6);
          *(undefined2 *)(param_1 + 0xe28) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",7);
          *(undefined2 *)(param_1 + 0xe50) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",8);
          *(undefined2 *)(param_1 + 0xe78) = uVar4;
        }
        uVar4 = phy_getintvararray(param_1,"tssifloor5g",2);
        *(undefined2 *)(param_1 + 0xeac) = uVar4;
      }
      else {
        if (bVar9 != 4) goto LAB_001c016f;
        uVar2 = phy_getintvararray(param_1,"maxp5ga0",3);
        *(undefined1 *)(param_1 + 0xe80) = uVar2;
        uVar2 = phy_getintvararray(param_1,"maxp5ga1",3);
        *(undefined1 *)(param_1 + 0xe85) = uVar2;
        uVar2 = phy_getintvararray(param_1,"maxp5ga2",3);
        *(undefined1 *)(param_1 + 0xe8a) = uVar2;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",9);
        *(undefined2 *)(param_1 + 0xe0c) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",10);
        *(undefined2 *)(param_1 + 0xe34) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga0",0xb);
        *(undefined2 *)(param_1 + 0xe5c) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",9);
        *(undefined2 *)(param_1 + 0xe16) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",10);
        *(undefined2 *)(param_1 + 0xe3e) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga1",0xb);
        *(undefined2 *)(param_1 + 0xe66) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",9);
        *(undefined2 *)(param_1 + 0xe20) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",10);
        *(undefined2 *)(param_1 + 0xe48) = uVar4;
        uVar4 = phy_getintvararray(param_1,"pa5ga2",0xb);
        *(undefined2 *)(param_1 + 0xe70) = uVar4;
        if ((*(int *)(param_1 + 0x164) == 3) &&
           (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",9);
          *(undefined2 *)(param_1 + 0xe2a) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",10);
          *(undefined2 *)(param_1 + 0xe52) = uVar4;
          uVar4 = phy_getintvararray(param_1,"pa5gbw4080a1",0xb);
          *(undefined2 *)(param_1 + 0xe7a) = uVar4;
        }
        uVar4 = phy_getintvararray(param_1,"tssifloor5g",3);
        *(undefined2 *)(param_1 + 0xeae) = uVar4;
      }
      bVar9 = bVar9 + 1;
    } while (bVar9 != 5);
    if (10 < *(uint *)(*(long *)(param_1 + 0x20) + 0x48)) {
      uVar4 = phy_getintvar(param_1,"cckbw202gpo");
      *(undefined2 *)(param_1 + 0xc4c) = uVar4;
      uVar4 = phy_getintvar(param_1,"cckbw20ul2gpo");
      *(undefined2 *)(param_1 + 0xc4e) = uVar4;
      uVar4 = phy_getintvar(param_1,"ofdmlrbw202gpo");
      *(undefined2 *)(param_1 + 0xd14) = uVar4;
      iVar5 = phy_getintvar(param_1,"dot11agofdmhrbw202gpo");
      uVar1 = *(uint *)(param_1 + 0xd14);
      uVar8 = uVar1 >> 4 & 0xf;
      *(uint *)(param_1 + 0xc50) =
           iVar5 << 0x10 |
           uVar8 << 0xc | uVar8 << 8 | (uVar1 & 0xf) << 4 | (uint)((byte)uVar1 & 0xf);
      uVar6 = phy_getintvar(param_1,"mcsbw202gpo");
      *(undefined4 *)(param_1 + 0xc5c) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw402gpo");
      *(undefined4 *)(param_1 + 0xc64) = uVar6;
      uVar4 = phy_getintvar(param_1,"sb20in40lrpo");
      *(undefined2 *)(param_1 + 0xd16) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb20in40hrpo");
      *(undefined2 *)(param_1 + 0xd18) = uVar4;
      *(undefined4 *)(param_1 + 0xc54) = *(undefined4 *)(param_1 + 0xc50);
      *(undefined4 *)(param_1 + 0xc60) = *(undefined4 *)(param_1 + 0xc5c);
      uVar4 = phy_getintvar(param_1,"dot11agduphrpo");
      *(undefined2 *)(param_1 + 0xd1c) = uVar4;
      uVar4 = phy_getintvar(param_1,"dot11agduplrpo");
      *(undefined2 *)(param_1 + 0xd1a) = uVar4;
      *(undefined4 *)(param_1 + 0xc58) = *(undefined4 *)(param_1 + 0xc50);
      uVar6 = phy_getintvar(param_1,"mcsbw205glpo");
      *(undefined4 *)(param_1 + 0xc6c) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw205gmpo");
      *(undefined4 *)(param_1 + 0xc70) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw205ghpo");
      *(undefined4 *)(param_1 + 0xc74) = uVar6;
      *(undefined4 *)(param_1 + 0xcbc) = uVar6;
      *(undefined4 *)(param_1 + 0xcb4) = *(undefined4 *)(param_1 + 0xc6c);
      *(undefined4 *)(param_1 + 0xcb8) = *(undefined4 *)(param_1 + 0xc70);
      uVar4 = phy_getintvar(param_1,"mcslr5glpo");
      *(undefined2 *)(param_1 + 0xd1e) = uVar4;
      uVar4 = phy_getintvar(param_1,"mcslr5gmpo");
      *(undefined2 *)(param_1 + 0xd20) = uVar4;
      uVar4 = phy_getintvar(param_1,"mcslr5ghpo");
      *(undefined2 *)(param_1 + 0xd22) = uVar4;
      uVar6 = phy_getintvar(param_1,"mcsbw405glpo");
      *(undefined4 *)(param_1 + 0xcd8) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw405gmpo");
      *(undefined4 *)(param_1 + 0xcdc) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw405ghpo");
      *(undefined4 *)(param_1 + 0xce0) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw805glpo");
      *(undefined4 *)(param_1 + 0xcf0) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw805gmpo");
      *(undefined4 *)(param_1 + 0xcf4) = uVar6;
      uVar6 = phy_getintvar(param_1,"mcsbw805ghpo");
      *(undefined4 *)(param_1 + 0xcf8) = uVar6;
      *(undefined4 *)(param_1 + 0xcc0) = *(undefined4 *)(param_1 + 0xcb4);
      *(undefined4 *)(param_1 + 0xc78) = *(undefined4 *)(param_1 + 0xc6c);
      *(undefined4 *)(param_1 + 0xc7c) = *(undefined4 *)(param_1 + 0xc70);
      *(undefined4 *)(param_1 + 0xc84) = *(undefined4 *)(param_1 + 0xc6c);
      *(undefined4 *)(param_1 + 0xc88) = *(undefined4 *)(param_1 + 0xc70);
      *(undefined4 *)(param_1 + 0xcc4) = *(undefined4 *)(param_1 + 0xcb8);
      *(undefined4 *)(param_1 + 0xc80) = *(undefined4 *)(param_1 + 0xc74);
      *(undefined4 *)(param_1 + 0xc8c) = *(undefined4 *)(param_1 + 0xc74);
      *(undefined4 *)(param_1 + 0xcc8) = *(undefined4 *)(param_1 + 0xcbc);
      uVar4 = phy_getintvar(param_1,"sb20in80and160lr5glpo");
      *(undefined2 *)(param_1 + 0xd24) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb20in80and160hr5glpo");
      *(undefined2 *)(param_1 + 0xd2a) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb20in80and160lr5gmpo");
      *(undefined2 *)(param_1 + 0xd26) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb20in80and160hr5gmpo");
      *(undefined2 *)(param_1 + 0xd2c) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb20in80and160lr5ghpo");
      *(undefined2 *)(param_1 + 0xd28) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb20in80and160hr5ghpo");
      *(undefined2 *)(param_1 + 0xd2e) = uVar4;
      *(undefined4 *)(param_1 + 0xccc) = *(undefined4 *)(param_1 + 0xcb4);
      *(undefined4 *)(param_1 + 0xcd0) = *(undefined4 *)(param_1 + 0xcb8);
      *(undefined4 *)(param_1 + 0xcd4) = *(undefined4 *)(param_1 + 0xcbc);
      *(undefined4 *)(param_1 + 0xce4) = *(undefined4 *)(param_1 + 0xcd8);
      *(undefined4 *)(param_1 + 0xce8) = *(undefined4 *)(param_1 + 0xcdc);
      *(undefined4 *)(param_1 + 0xcec) = *(undefined4 *)(param_1 + 0xce0);
      uVar4 = phy_getintvar(param_1,"sb40and80lr5glpo");
      *(undefined2 *)(param_1 + 0xd30) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb40and80hr5glpo");
      *(undefined2 *)(param_1 + 0xd36) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb40and80lr5gmpo");
      *(undefined2 *)(param_1 + 0xd32) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb40and80hr5gmpo");
      *(undefined2 *)(param_1 + 0xd38) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb40and80lr5ghpo");
      *(undefined2 *)(param_1 + 0xd34) = uVar4;
      uVar4 = phy_getintvar(param_1,"sb40and80hr5ghpo");
      *(undefined2 *)(param_1 + 0xd3a) = uVar4;
      *(undefined4 *)(param_1 + 0xc98) = *(undefined4 *)(param_1 + 0xce0);
      *(undefined4 *)(param_1 + 0xca4) = *(undefined4 *)(param_1 + 0xce0);
      *(undefined4 *)(param_1 + 0xc90) = *(undefined4 *)(param_1 + 0xcd8);
      *(undefined4 *)(param_1 + 0xc94) = *(undefined4 *)(param_1 + 0xcdc);
      *(undefined4 *)(param_1 + 0xc9c) = *(undefined4 *)(param_1 + 0xcd8);
      *(undefined4 *)(param_1 + 0xca0) = *(undefined4 *)(param_1 + 0xcdc);
      *(undefined4 *)(param_1 + 0xca8) = *(undefined4 *)(param_1 + 0xcf0);
      *(undefined4 *)(param_1 + 0xcac) = *(undefined4 *)(param_1 + 0xcf4);
      *(undefined4 *)(param_1 + 0xcb0) = *(undefined4 *)(param_1 + 0xcf8);
    }
    uVar4 = phy_getintvar(param_1,"pdoffset40ma0");
    *(undefined2 *)(param_1 + 0xe90) = uVar4;
    uVar4 = phy_getintvar(param_1,"pdoffset40ma1");
    *(undefined2 *)(param_1 + 0xe92) = uVar4;
    uVar4 = phy_getintvar(param_1,"pdoffset40ma2");
    *(undefined2 *)(param_1 + 0xe94) = uVar4;
    uVar4 = phy_getintvar(param_1,"pdoffset80ma0");
    *(undefined2 *)(param_1 + 0xe98) = uVar4;
    uVar4 = phy_getintvar(param_1,"pdoffset80ma1");
    *(undefined2 *)(param_1 + 0xe9a) = uVar4;
    uVar4 = phy_getintvar(param_1,"pdoffset80ma2");
    *(undefined2 *)(param_1 + 0xe9c) = uVar4;
    uVar2 = phy_getintvar(param_1,"pdoffset2g40ma0");
    *(undefined1 *)(param_1 + 0xea0) = uVar2;
    uVar2 = phy_getintvar(param_1,"pdoffset2g40ma1");
    *(undefined1 *)(param_1 + 0xea1) = uVar2;
    uVar2 = phy_getintvar(param_1,"pdoffset2g40ma2");
    *(undefined1 *)(param_1 + 0xea2) = uVar2;
    uVar2 = phy_getintvar(param_1,"pdoffset2g40mvalid");
    *(undefined1 *)(param_1 + 0xea4) = uVar2;
    uVar2 = phy_getintvar(param_1,"pdoffsetcckma0");
    *(undefined1 *)(param_1 + 0xece) = uVar2;
    uVar2 = phy_getintvar(param_1,"pdoffsetcckma1");
    *(undefined1 *)(param_1 + 0xecf) = uVar2;
    uVar2 = phy_getintvar(param_1,"pdoffsetcckma2");
    *(undefined1 *)(param_1 + 0xed0) = uVar2;
    cVar3 = phy_getintvar(param_1,"tempoffset");
    *(char *)(param_1 + 0xc35) = cVar3;
    if (cVar3 == -1) {
      *(undefined1 *)(param_1 + 0xc35) = 0;
    }
    else if (cVar3 != '\0') {
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
    if (*(int *)(param_1 + 0x160) == 0xb) {
      *(undefined1 *)(param_1 + 0xf9e) = 0x28;
    }
    FUN_001bf0bf(param_1);
    uVar7 = 1;
  }
  return uVar7;
}

