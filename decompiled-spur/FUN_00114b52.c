
void FUN_00114b52(long param_1,long param_2,undefined8 param_3,byte param_4)

{
  byte bVar1;
  byte extraout_AH;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  ulong extraout_RDX;
  ulong extraout_RDX_00;
  ulong extraout_RDX_01;
  ulong extraout_RDX_02;
  ulong extraout_RDX_03;
  ulong extraout_RDX_04;
  ulong extraout_RDX_05;
  ulong extraout_RDX_06;
  ulong extraout_RDX_07;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  uint *puVar9;
  long lVar10;
  char cVar11;
  bool bVar12;
  byte abStack_58 [16];
  byte abStack_48 [24];
  
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 == 0xa87b) goto LAB_001153ec;
  if (0xa87b < uVar3) {
    if (uVar3 == 0xa8df) {
LAB_001151ba:
      lVar8 = param_2 + 0x660;
      lVar10 = param_2 + 0x664;
      osl_writel(0,lVar8);
      osl_writel(0x11100070,lVar10);
      osl_writel(1,lVar8);
      osl_writel(0x1014140a,lVar10);
      osl_writel(5,lVar8);
      osl_writel(0x88888854,lVar10);
      if (param_4 == 1) {
        osl_writel(2,lVar8);
        uVar6 = 0x5201828;
        uVar5 = extraout_RDX_04;
      }
      else {
        osl_writel(2,lVar8);
        uVar6 = 0x5001828;
        uVar5 = extraout_RDX_05;
      }
      goto LAB_00115620;
    }
    if (uVar3 < 0xa8e0) {
      if (uVar3 == 0xa8d6) {
LAB_00114f68:
        lVar8 = param_2 + 0x664;
        lVar10 = param_2 + 0x660;
        if (param_4 != 1) {
          osl_writel(0,lVar10);
          osl_writel(0x11100008,lVar8);
          osl_writel(1,lVar10);
          osl_writel(0xc000c06,lVar8);
          osl_writel(2,lVar10);
          osl_writel(0x3000a08,lVar8);
          osl_writel(3,lVar10);
          osl_writel(0,lVar8);
          osl_writel(4,lVar10);
          osl_writel(0x200005c0,lVar8);
          osl_writel(5,lVar10);
          uVar6 = 0x88888855;
          uVar5 = extraout_RDX_03;
          goto LAB_00115620;
        }
        osl_writel(0,lVar10);
        osl_writel(0x11500008,lVar8);
        osl_writel(1,lVar10);
        uVar7 = 0xc000c06;
LAB_00114fa7:
        lVar10 = param_2 + 0x660;
        lVar8 = param_2 + 0x664;
        osl_writel(uVar7,lVar8);
        osl_writel(2,lVar10);
        osl_writel(0xf600a08,lVar8);
        osl_writel(3,lVar10);
        osl_writel(0,lVar8);
        osl_writel(4,lVar10);
        uVar7 = 0x2001e920;
LAB_0011547d:
        osl_writel(uVar7,param_2 + 0x664);
        osl_writel(5,param_2 + 0x660);
        uVar6 = 0x88888815;
        uVar5 = extraout_RDX_06;
        goto LAB_00115620;
      }
      if (uVar3 < 0xa8d7) {
        if (uVar3 == 0xa8d1) {
LAB_001153ec:
          lVar8 = param_2 + 0x664;
          lVar10 = param_2 + 0x660;
          if (param_4 != 1) {
            osl_writel(0,lVar10);
            osl_writel(0x11100014,lVar8);
            osl_writel(1,lVar10);
            uVar7 = 0x40c0c06;
            goto LAB_001154c8;
          }
          osl_writel(0,lVar10);
          osl_writel(0x1100014,lVar8);
          osl_writel(1,lVar10);
          osl_writel(0x40c0c06,lVar8);
          osl_writel(2,lVar10);
          osl_writel(0x3140a08,lVar8);
          osl_writel(3,lVar10);
          osl_writel(0x333333,lVar8);
          osl_writel(4,lVar10);
          uVar7 = 0x202c2820;
          goto LAB_0011547d;
        }
        if (uVar3 == 0xa8d5) goto LAB_001151ba;
        bVar12 = uVar3 == 0xa886;
LAB_00114c84:
        if (bVar12) goto LAB_00115518;
      }
      else if (0xa8d7 < uVar3) {
        if (uVar3 < 0xa8db) goto LAB_00114ef6;
        if (uVar3 < 0xa8dd) goto LAB_001153ec;
      }
    }
    else {
      if (uVar3 == 0xa99d) {
LAB_00114ef6:
        lVar8 = param_2 + 0x660;
        if (param_4 == 1) {
          osl_writel(0,lVar8);
          osl_writel(0x11500010,param_2 + 0x664);
          osl_writel(1,lVar8);
          uVar7 = 0xc0c06;
          goto LAB_00114fa7;
        }
        osl_writel(0,lVar8);
        osl_writel(0x11100010,param_2 + 0x664);
        osl_writel(1,lVar8);
        uVar7 = 0xc0c06;
LAB_001154c8:
        lVar10 = param_2 + 0x660;
        lVar8 = param_2 + 0x664;
        osl_writel(uVar7,lVar8);
        osl_writel(2,lVar10);
        osl_writel(0x3000a08,lVar8);
        osl_writel(3,lVar10);
        osl_writel(0,lVar8);
        osl_writel(4,lVar10);
        uVar7 = 0x200005c0;
        goto LAB_0011547d;
      }
      if (uVar3 < 0xa99e) {
        if (uVar3 == 0xa962) goto LAB_001152e0;
        if (uVar3 < 0xa963) {
          if (uVar3 - 0xa8e2 < 5) goto LAB_00114d7f;
        }
        else if (uVar3 == 0xa99c) goto LAB_00114f68;
      }
      else {
        if (uVar3 == 0xa9a7) {
LAB_00114e3c:
          if (param_4 == 2) {
            osl_writel(0,param_2 + 0x660);
            osl_writel(0x11500014,param_2 + 0x664);
            osl_writel(2,param_2 + 0x660);
            uVar6 = 0xfc00a08;
            uVar5 = extraout_RDX_00;
          }
          else {
            lVar8 = param_2 + 0x660;
            if (param_4 == 1) {
              osl_writel(0,lVar8);
              osl_writel(0x11500014,param_2 + 0x664);
              osl_writel(2,lVar8);
              uVar6 = 0xf600a08;
              uVar5 = extraout_RDX_01;
            }
            else {
              osl_writel(0,lVar8);
              osl_writel(0x11100014,param_2 + 0x664);
              osl_writel(2,lVar8);
              uVar6 = 0x3000a08;
              uVar5 = extraout_RDX_02;
            }
          }
          goto LAB_00115620;
        }
        if (0xa9a7 < uVar3) {
          if (uVar3 != 0xb83a) {
            bVar12 = uVar3 == 0xd144;
            goto LAB_00114d20;
          }
          goto LAB_0011508d;
        }
        if (uVar3 == 0xa9a4) goto LAB_001153ec;
      }
    }
LAB_00115627:
    uVar3 = 0;
    goto LAB_00115632;
  }
  if (uVar3 != 0x4335) {
    if (uVar3 < 0x4336) {
      if (uVar3 == 0x4322) goto LAB_001151ba;
      if (uVar3 < 0x4323) {
        if (uVar3 == 0x4314) {
LAB_00115518:
          puVar9 = (uint *)&UNK_00509fb0;
          uVar5 = si_pmu_alp_clock(param_1,param_3);
          if (param_4 == 1) {
            puVar9 = (uint *)&UNK_00509f80;
          }
          for (; (puVar9 != (uint *)0x0 && ((short)*puVar9 != 0)); puVar9 = puVar9 + 2) {
            if ((*puVar9 & 0xffff) == (uint)((uVar5 & 0xffffffff) / 1000)) {
              osl_writel(0,param_2 + 0x660);
              uVar3 = osl_readl(param_2 + 0x664);
              uVar5 = (ulong)(puVar9[1] << 2);
              uVar6 = (ulong)(uVar3 & 0xffc00003 | puVar9[1] << 2);
              goto LAB_00115620;
            }
          }
        }
        else if (uVar3 == 0x4319) {
          lVar8 = param_2 + 0x660;
          lVar10 = param_2 + 0x664;
          osl_writel(0,lVar8);
          osl_writel(0x11100070,lVar10);
          osl_writel(1,lVar8);
          osl_writel(0x1014140a,lVar10);
          osl_writel(5,lVar8);
          osl_writel(0x88888854,lVar10);
          if (param_4 == 1) {
            osl_writel(2,lVar8);
            uVar7 = 0x5201828;
          }
          else {
            osl_writel(2,lVar8);
            uVar7 = 0x5001828;
          }
          osl_writel(uVar7,lVar10);
        }
        else if (uVar3 == 0x10f6) goto LAB_001151ba;
      }
      else {
        if (uVar3 == 0x4330) {
LAB_001152e0:
          uVar5 = si_alp_clock(param_1);
          for (puVar9 = (uint *)func_0x00111664(param_1); puVar9 != (uint *)0x0; puVar9 = puVar9 + 3
              ) {
            if ((*(char *)((long)puVar9 + 2) == '\0') ||
               ((uint)(ushort)*puVar9 == (uint)((uVar5 & 0xffffffff) / 1000))) {
              if (*(char *)((long)puVar9 + 2) != '\0') goto LAB_00115329;
              break;
            }
          }
          puVar9 = (uint *)func_0x0011174a(param_1);
LAB_00115329:
          lVar8 = param_2 + 0x660;
          lVar10 = param_2 + 0x664;
          uVar3 = (*puVar9 & 0xffff) / 100;
          bVar1 = *(byte *)((long)puVar9 + 3);
          uVar4 = puVar9[1];
          osl_writel(1,lVar8,(short)((*puVar9 & 0xffff) % 100));
          osl_readl(lVar10);
          uVar4 = (uint)(byte)(bVar1 / (byte)uVar4) * 10 * (uint)extraout_AH *
                  (uint)(byte)((param_4 == 1) * '\x02' + 0x50);
          osl_writel(2,lVar8);
          uVar2 = osl_readl(lVar10);
          osl_writel(uVar4 / uVar3 << 0x14 | uVar2 & 0xe00fffff,lVar10);
          osl_writel(3,lVar8);
          uVar5 = (ulong)((uVar4 % uVar3) * 0x1000000 + (uVar3 >> 1));
          uVar6 = uVar5 / uVar3;
          uVar5 = uVar5 % (ulong)uVar3;
          goto LAB_00115620;
        }
        if (0x4330 < uVar3) {
          if (uVar3 != 0x4331) {
            bVar12 = uVar3 == 0x4334;
            goto LAB_00114c84;
          }
          goto LAB_00114e3c;
        }
        if (uVar3 == 0x4324) {
          if (2 < param_4) {
            param_4 = 0;
          }
          lVar8 = 0;
          do {
            if ((&UNK_00509ef0)[lVar8] == param_4) {
              osl_writel((&UNK_00509ef1)[lVar8],param_2 + 0x660);
              osl_writel(*(undefined4 *)(&UNK_00509ef4 + lVar8),param_2 + 0x664);
            }
            lVar8 = lVar8 + 8;
          } while (lVar8 != 0x90);
          goto LAB_0011562c;
        }
      }
    }
    else {
      if (uVar3 == 0x4749) {
LAB_00114d7f:
        if (uVar3 == 0x6362) {
LAB_00114d86:
          if (*(int *)(param_1 + 0x40) == 0) goto LAB_00114ef6;
        }
        if (((uVar3 == 0x4749) || (uVar3 == 0x5357)) || (cVar11 = '\0', uVar3 == 0xd144)) {
          cVar11 = '\x06';
        }
        lVar8 = param_2 + 0x664;
        if (2 < param_4) {
          param_4 = 0;
        }
        osl_writel(cVar11,param_2 + 0x660);
        uVar3 = osl_readl(lVar8);
        abStack_48[0] = 1;
        abStack_48[1] = 5;
        abStack_48[2] = 5;
        osl_writel((uint)abStack_48[param_4] << 0x14 | uVar3 & 0xff0fffff,lVar8);
        osl_writel(cVar11 + '\x02',param_2 + 0x660);
        uVar3 = osl_readl(lVar8);
        abStack_58[0] = 0x30;
        abStack_58[1] = 0xf6;
        abStack_58[2] = 0xfc;
        uVar6 = (ulong)((uint)abStack_58[param_4] << 0x14 | uVar3 & 0xe00fffff);
        uVar5 = extraout_RDX;
        goto LAB_00115620;
      }
      if (uVar3 < 0x474a) {
        if ((uVar3 == 0x4716) || (uVar3 == 0x4748)) {
LAB_0011508d:
          lVar8 = param_2 + 0x664;
          lVar10 = param_2 + 0x660;
          if (param_4 == 1) {
            osl_writel(0,lVar10);
            osl_writel(0x11500060,lVar8);
            osl_writel(1,lVar10);
            osl_writel(0x80c0c06,lVar8);
            osl_writel(2,lVar10);
            osl_writel(0xf600000,lVar8);
            osl_writel(3,lVar10);
            osl_writel(0,lVar8);
            osl_writel(4,lVar10);
            uVar7 = 0x2001e924;
          }
          else {
            osl_writel(0,lVar10);
            osl_writel(0x11100060,lVar8);
            osl_writel(1,lVar10);
            osl_writel(0x80c0c06,lVar8);
            osl_writel(2,lVar10);
            osl_writel(0x3000000,lVar8);
            osl_writel(3,lVar10);
            osl_writel(0,lVar8);
            osl_writel(4,lVar10);
            uVar7 = 0x200005c0;
          }
          osl_writel(uVar7,lVar8);
          osl_writel(5,lVar10);
          uVar3 = 0x600;
          osl_writel(0x88888815,lVar8);
          goto LAB_00115632;
        }
        if (uVar3 == 0x4336) goto LAB_001152e0;
      }
      else {
        if (uVar3 == 0x6362) goto LAB_00114d86;
        if (uVar3 < 0x6363) {
          bVar12 = uVar3 == 0x5357;
LAB_00114d20:
          if (bVar12) goto LAB_00114d7f;
        }
        else if (uVar3 - 0xa867 < 2) goto LAB_00114f68;
      }
    }
    goto LAB_00115627;
  }
  osl_writel(3,param_2 + 0x660);
  uVar5 = extraout_RDX_07;
  switch(param_4) {
  case 1:
    uVar6 = 0x80ab1f7d;
    break;
  case 2:
    uVar6 = 0x80b1f7c9;
    break;
  case 3:
    uVar6 = 0x80c680af;
    break;
  case 4:
    uVar6 = 0x80b8d016;
    break;
  case 5:
    uVar6 = 0x80cd58fc;
    break;
  case 6:
    uVar6 = 0x80d43149;
    break;
  case 7:
    uVar6 = 0x80db0995;
    break;
  case 8:
    uVar6 = 0x80e1e1e2;
    break;
  case 9:
    uVar6 = 0x80e8ba2f;
    break;
  default:
    goto LAB_0011562c;
  }
LAB_00115620:
  osl_writel(uVar6,param_2 + 0x664,uVar5);
LAB_0011562c:
  uVar3 = 0x400;
LAB_00115632:
  uVar4 = osl_readl(param_2 + 0x600);
  osl_writel(uVar4 | uVar3,param_2 + 0x600);
  return;
}

