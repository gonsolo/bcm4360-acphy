
int si_pmu_si_clock(long param_1,undefined8 param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  short *psVar4;
  ulong uVar5;
  undefined8 uVar6;
  short *extraout_RDX;
  short *extraout_RDX_00;
  short *extraout_RDX_01;
  bool bVar7;
  
  uVar1 = si_coreidx();
  psVar4 = (short *)si_setcoreidx(param_1,0);
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 == 0x5357) {
LAB_0011732a:
    uVar6 = 0;
LAB_00117332:
    iVar2 = FUN_00112bf8(param_1,param_2,psVar4,uVar6,3);
    psVar4 = extraout_RDX_00;
    goto LAB_0011735f;
  }
  if (uVar3 < 0x5358) {
    if (uVar3 == 0x4334) goto LAB_001172b6;
    if (uVar3 < 0x4335) {
      if (uVar3 != 0x4324) {
        if (uVar3 < 0x4325) {
          if (uVar3 != 0x4315) {
            if (uVar3 < 0x4316) {
              if (uVar3 == 0x10f6) goto LAB_00117359;
              if (uVar3 == 0x4314) goto LAB_00117296;
            }
            else {
              if (uVar3 == 0x4319) goto LAB_00117286;
              bVar7 = uVar3 == 0x4322;
LAB_001171a6:
              if (bVar7) goto LAB_00117359;
            }
LAB_0011721b:
            iVar2 = 80000000;
            goto LAB_0011735f;
          }
        }
        else if (uVar3 == 0x4329) {
          iVar2 = 38400000;
          if (*(int *)(param_1 + 0x40) == 0) goto LAB_0011735f;
        }
        else if (uVar3 < 0x432a) {
          if (uVar3 != 0x4325) {
            if (uVar3 == 0x4328) {
              osl_writel(0,psVar4 + 0x330);
              uVar3 = osl_readl(psVar4 + 0x332);
              uVar5 = (ulong)(((uVar3 & 0x38) >> 3) + 8);
              psVar4 = (short *)(880000 % uVar5);
              iVar2 = (int)(880000 / uVar5) * 1000;
              goto LAB_0011735f;
            }
            goto LAB_0011721b;
          }
        }
        else if (uVar3 != 0x4330) {
          bVar7 = uVar3 == 0x4331;
          goto LAB_001171a6;
        }
      }
    }
    else {
      if (uVar3 == 0x4716) {
LAB_00117266:
        uVar6 = 0xc;
        goto LAB_00117332;
      }
      if (0x4716 < uVar3) {
        if (uVar3 == 0x5300) {
          iVar2 = FUN_00116f3a(psVar4,3);
          psVar4 = extraout_RDX_01;
          goto LAB_0011735f;
        }
        if (uVar3 < 0x5301) {
          if (uVar3 == 0x4748) goto LAB_00117266;
          bVar7 = uVar3 == 0x4749;
        }
        else {
          if (uVar3 == 0x5354) goto LAB_00117351;
          bVar7 = uVar3 == 0x5356;
        }
        if (!bVar7) goto LAB_0011721b;
        goto LAB_0011732a;
      }
      if (uVar3 != 0x4350) {
        if (uVar3 < 0x4351) {
          if (0x4336 < uVar3) goto LAB_0011721b;
        }
        else if (uVar3 != 0x4352) {
          bVar7 = uVar3 == 0x4360;
          goto LAB_001171fc;
        }
      }
    }
    goto LAB_00117286;
  }
  if (uVar3 < 0xa8e7) {
    if (uVar3 < 0xa8e2) {
      if (uVar3 < 0xa888) {
        if (uVar3 < 0xa886) {
          if (uVar3 != 0x6362) {
            if (uVar3 < 0x6362) goto LAB_0011721b;
            uVar3 = uVar3 - 0xa867;
LAB_00117197:
            if (1 < uVar3) goto LAB_0011721b;
          }
        }
        else {
LAB_00117296:
          if (uVar3 == 0x4334) {
LAB_001172b6:
            osl_writel(0,psVar4 + 0x330);
            uVar3 = osl_readl(psVar4 + 0x332);
            uVar3 = (uVar3 & 0x3ffffc) >> 2;
          }
          else {
            if (uVar3 < 0x4335) {
              if (uVar3 == 0x4314) goto LAB_001172b6;
            }
            else if (uVar3 - 0xa886 < 2) goto LAB_001172b6;
            uVar3 = 0;
          }
          psVar4 = &DAT_0050a450;
          do {
            if (*psVar4 == 0) break;
            if (*(uint *)(psVar4 + 2) == uVar3) goto LAB_00117359;
            psVar4 = psVar4 + 4;
          } while (psVar4 != (short *)0x0);
          psVar4 = &DAT_00509fb0;
          do {
            if (*psVar4 == 0) break;
            if (*(uint *)(psVar4 + 2) == uVar3) {
              iVar2 = 97000000;
              goto LAB_0011735f;
            }
            psVar4 = psVar4 + 4;
          } while (psVar4 != (short *)0x0);
        }
      }
      else {
        if (0xa8da < uVar3) {
          bVar7 = uVar3 == 0xa8df;
          goto LAB_001171a6;
        }
        if (uVar3 < 0xa8d8) {
          uVar3 = uVar3 - 0xa8d5;
          goto LAB_00117197;
        }
      }
    }
    else if ((*(uint *)(psVar4 + 0x16) & 0x200) != 0) {
LAB_00117351:
      iVar2 = 120000000;
      goto LAB_0011735f;
    }
  }
  else if (uVar3 < 0xa99e) {
    if (uVar3 < 0xa99c) {
      if (uVar3 < 0xa8ec) {
        if (0xa8e9 < uVar3) goto LAB_00117286;
        bVar7 = uVar3 == 0xa8e7;
      }
      else {
        bVar7 = uVar3 == 0xa962;
      }
LAB_001171fc:
      if (!bVar7) goto LAB_0011721b;
LAB_00117286:
      iVar2 = FUN_001127a4(param_1,param_2);
      psVar4 = extraout_RDX;
      goto LAB_0011735f;
    }
  }
  else {
    if (uVar3 == 0xaa06) goto LAB_00117286;
    if (0xaa06 < uVar3) {
      if (uVar3 != 0xb83a) {
        iVar2 = 75000000;
        if (uVar3 == 0xd144) goto LAB_0011735f;
        goto LAB_0011721b;
      }
      goto LAB_00117266;
    }
    if (uVar3 != 0xa9a7) {
      bVar7 = uVar3 == 0xa9c4;
      goto LAB_001171fc;
    }
  }
LAB_00117359:
  iVar2 = 96000000;
LAB_0011735f:
  si_setcoreidx(param_1,uVar1,psVar4);
  return iVar2;
}

