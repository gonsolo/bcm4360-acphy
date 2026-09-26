
undefined1 wlc_bmac_txstatus(long *param_1,char param_2,char *param_3)

{
  long *plVar1;
  long lVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  ulong uVar10;
  undefined1 uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  undefined1 local_68 [2];
  undefined2 local_66;
  byte local_63;
  byte local_62;
  undefined1 local_60;
  byte local_5f;
  ushort local_5e;
  short local_5c;
  ushort local_5a;
  ushort local_58;
  undefined4 local_56;
  undefined4 local_52;
  uint local_4e;
  undefined4 local_4a;
  undefined4 local_46;
  undefined2 local_42;
  undefined4 local_40;
  ushort local_3c;
  
  plVar1 = (long *)*param_1;
  if (*(uint *)((long)param_1 + 0x84) == 4) {
    cVar3 = FUN_00164dd3(plVar1[4]);
    *param_3 = cVar3;
    if (cVar3 != '\0') {
      return 0;
    }
  }
  else {
    if (*(uint *)((long)param_1 + 0x84) < 0x28) {
      uVar14 = 0xffffffff;
      if (param_2 != '\0') {
        uVar14 = *(uint *)(*(long *)(*plVar1 + 0x38) + 0x3c);
      }
      lVar2 = param_1[0x1a];
      uVar13 = 0;
      uVar4 = osl_readl(lVar2 + 0x180);
      do {
        if (*param_3 != '\0') break;
        uVar10 = osl_readl(lVar2 + 0x170);
        uVar8 = (uint)uVar10;
        if ((uVar10 & 1) == 0) break;
        if (uVar8 == 0xffffffff) {
          return 0;
        }
        uVar5 = osl_readl(lVar2 + 0x174);
        local_42 = (undefined2)uVar5;
        uVar12 = uVar8 & 0xffff;
        local_58 = (ushort)uVar10;
        local_5f = (byte)(uVar12 >> 1) & 1;
        local_63 = (byte)(uVar12 >> 6) & 1;
        local_62 = (byte)(uVar12 >> 7) & 1;
        local_60 = (undefined1)((int)(uVar8 & 0x1c) >> 2);
        local_5e = (ushort)(uVar10 >> 8) & 0xf;
        local_66 = (undefined2)(uVar10 >> 0x10);
        local_5c = (short)((uVar8 & 0xf000) >> 0xc);
        local_3c = (ushort)((uint)uVar5 >> 0x10) & 0xff;
        local_40 = uVar4;
        if ((0x27 < *(uint *)((long)param_1 + 0x84)) || (cVar3 = '\0', (uVar8 & 0x60) != 0x40)) {
          cVar3 = wlc_dotxstatus(*param_1,local_68);
        }
        uVar13 = uVar13 + 1;
        *param_3 = cVar3;
      } while (uVar13 < uVar14);
    }
    else {
      uVar14 = 0xffffffff;
      if (param_2 != '\0') {
        uVar14 = *(uint *)(*(long *)(*plVar1 + 0x38) + 0x3c);
      }
      lVar2 = param_1[0x1a];
      uVar13 = 0;
      uVar4 = osl_readl(lVar2 + 0x180);
      do {
        if (*param_3 != '\0') break;
        uVar10 = osl_readl(lVar2 + 0x170);
        uVar8 = (uint)uVar10;
        if ((uVar10 & 1) == 0) break;
        if (uVar8 == 0xffffffff) {
          return 0;
        }
        uVar5 = osl_readl(lVar2 + 0x174);
        uVar6 = osl_readl(lVar2 + 0x178);
        uVar7 = osl_readl(lVar2 + 0x17c);
        local_58 = (ushort)uVar10;
        local_42 = (undefined2)uVar5;
        local_66 = (undefined2)(uVar10 >> 0x10);
        local_3c = (ushort)((uint)uVar5 >> 0x10) & 0xff;
        local_63 = (byte)((uVar8 & 0xffff) >> 2) & 1;
        local_62 = (byte)((uVar8 & 0xffff) >> 3) & 1;
        local_60 = (undefined1)((int)(uVar8 & 0xf0) >> 4);
        local_5f = 1 < ((ushort)(uVar10 >> 8) & 0x7f) | (byte)((short)local_58 >> 0xf) >> 7;
        local_5c = ((ushort)uVar7 & 0xff) + ((ushort)uVar6 & 0xff) +
                   ((ushort)((uint)uVar6 >> 0x10) & 0xff) + ((ushort)((uint)uVar7 >> 0x10) & 0xff);
        local_40 = uVar4;
        uVar8 = osl_readl(lVar2 + 0x170);
        uVar5 = osl_readl(lVar2 + 0x174);
        uVar9 = osl_readl(lVar2 + 0x178);
        osl_readl(lVar2 + 0x17c);
        if ((uVar8 & 1) == 0) {
          return 0;
        }
        local_5e = (ushort)(uVar8 >> 0x10) & 0xff;
        local_5a = (ushort)(byte)(uVar8 >> 0x18);
        local_56 = uVar6;
        local_52 = uVar7;
        local_4e = uVar8;
        local_4a = uVar5;
        local_46 = uVar9;
        if ((0x27 < *(uint *)((long)param_1 + 0x84)) || (cVar3 = '\0', (local_58 & 0x60) != 0x40)) {
          cVar3 = wlc_dotxstatus(*param_1,local_68);
        }
        uVar13 = uVar13 + 1;
        *param_3 = cVar3;
      } while (uVar13 < uVar14);
    }
    if (*param_3 != '\0') {
      return 0;
    }
    uVar11 = 1;
    if (uVar14 <= uVar13) goto LAB_0016523b;
  }
  uVar11 = 0;
LAB_0016523b:
  if (plVar1[0xd5] == 0) {
    return uVar11;
  }
  if (*(short *)(plVar1[0xd5] + 0xe) != 0) {
    wlc_send_q(plVar1);
    return uVar11;
  }
  return uVar11;
}

