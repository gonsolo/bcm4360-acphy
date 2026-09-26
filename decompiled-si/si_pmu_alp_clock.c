
int si_pmu_alp_clock(long param_1,undefined8 param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  uint *puVar5;
  ushort *puVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  
  uVar1 = si_coreidx();
  lVar4 = si_setcoreidx(param_1,0);
  uVar3 = *(uint *)(param_1 + 0x3c);
  if (uVar3 == 0x4350) goto LAB_00112b15;
  if (0x4350 < uVar3) {
    if (uVar3 < 0xa888) {
      if (uVar3 < 0xa886) {
        if (uVar3 != 0x5300) {
          if (uVar3 < 0x5301) {
            if (uVar3 != 0x4352) {
              bVar8 = uVar3 == 0x4360;
              goto LAB_00112a82;
            }
            goto LAB_00112b00;
          }
          if (uVar3 == 0x5354) {
            uVar3 = osl_readl(lVar4 + 0x600);
            for (puVar5 = &DAT_0050a480;
                (uVar7 = *puVar5, (short)uVar7 != 0 &&
                ((uint)*(byte *)((long)puVar5 + 2) != (uVar3 & 0x7c) >> 2)); puVar5 = puVar5 + 2) {
            }
            goto LAB_00112af7;
          }
          if (uVar3 != 0x5356) goto LAB_00112bd9;
        }
        iVar2 = 25000000;
        goto LAB_00112bdf;
      }
LAB_00112b28:
      osl_writel(0,lVar4 + 0x660);
      uVar3 = osl_readl(lVar4 + 0x664);
      puVar6 = &DAT_0050a450;
      uVar3 = (uVar3 & 0x3ffffc) >> 2;
      do {
        if ((*puVar6 == 0) || (*(uint *)(puVar6 + 2) == uVar3)) {
          if (*puVar6 != 0) {
            if (puVar6 == (ushort *)0x0) goto LAB_00112b9b;
            goto LAB_00112b95;
          }
          break;
        }
        puVar6 = puVar6 + 4;
      } while (puVar6 != (ushort *)0x0);
      puVar6 = &DAT_00509fb0;
      do {
        if ((*puVar6 == 0) || (*(uint *)(puVar6 + 2) == uVar3)) goto LAB_00112b95;
        puVar6 = puVar6 + 4;
      } while (puVar6 != (ushort *)0x0);
      goto LAB_00112b9b;
    }
    if (uVar3 == 0xa962) {
LAB_00112b15:
      iVar2 = FUN_00112909(param_1,param_2);
    }
    else {
      if (uVar3 < 0xa963) {
        bVar8 = uVar3 == 0xa8ea;
        bVar9 = uVar3 == 0xa8eb;
LAB_00112a67:
        if (bVar8 || bVar9) goto LAB_00112b15;
      }
      else {
        if (uVar3 != 0xa9c4) {
          bVar8 = uVar3 == 0xaa06;
LAB_00112a82:
          if (!bVar8) goto LAB_00112bd9;
        }
LAB_00112b00:
        iVar2 = 40000000;
        if ((*(byte *)(param_1 + 0x48) & 1) != 0) goto LAB_00112bdf;
      }
LAB_00112bd9:
      iVar2 = 20000000;
    }
    goto LAB_00112bdf;
  }
  if (uVar3 != 0x4328) {
    if (uVar3 < 0x4329) {
      if (uVar3 != 0x4319) {
        if (uVar3 < 0x431a) {
          if (uVar3 == 0x4314) goto LAB_00112b28;
          bVar8 = uVar3 == 0x4315;
        }
        else {
          if (uVar3 == 0x4324) goto LAB_00112b15;
          bVar8 = uVar3 == 0x4325;
        }
LAB_001129fb:
        if (!bVar8) goto LAB_00112bd9;
      }
    }
    else {
      if (uVar3 == 0x4334) goto LAB_00112b28;
      if (0x4334 < uVar3) {
        bVar8 = uVar3 < 0x4336;
        bVar9 = uVar3 == 0x4336;
        goto LAB_00112a67;
      }
      if (uVar3 != 0x4329) {
        bVar8 = uVar3 == 0x4330;
        goto LAB_001129fb;
      }
    }
    goto LAB_00112b15;
  }
  uVar3 = osl_readl(lVar4 + 0x600);
  for (puVar5 = &DAT_0050a480;
      (uVar7 = *puVar5, (short)uVar7 != 0 &&
      ((uint)*(byte *)((long)puVar5 + 2) != (uVar3 & 0x7c) >> 2)); puVar5 = puVar5 + 2) {
  }
LAB_00112af7:
  uVar7 = uVar7 & 0xffff;
  goto LAB_00112bd0;
LAB_00112b95:
  if (*puVar6 == 0) {
LAB_00112b9b:
    uVar3 = *(uint *)(param_1 + 0x3c);
    puVar6 = &DAT_00509fc8;
    if (uVar3 != 0x4334) {
      if (uVar3 < 0x4335) {
        if (uVar3 != 0x4314) {
LAB_00112bca:
          puVar6 = (ushort *)0x0;
          goto LAB_00112bcc;
        }
      }
      else if (1 < uVar3 - 0xa886) goto LAB_00112bca;
      puVar6 = &DAT_00509fb8;
    }
  }
LAB_00112bcc:
  uVar7 = (uint)*puVar6;
LAB_00112bd0:
  iVar2 = uVar7 * 1000;
LAB_00112bdf:
  si_setcoreidx(param_1,uVar1);
  return iVar2;
}

