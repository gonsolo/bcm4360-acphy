
undefined8 wlc_phy_tssi_cal(long param_1)

{
  undefined8 *puVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  ushort uVar14;
  int iVar15;
  char *pcVar16;
  byte *pbVar17;
  int *piVar18;
  byte *pbVar19;
  undefined8 *puVar20;
  int iVar21;
  byte *pbVar22;
  char *pcVar23;
  int *piVar24;
  ulong uVar25;
  long *plVar26;
  long lVar27;
  uint uVar28;
  
  uVar14 = 0;
  lVar4 = *(long *)(param_1 + 0x10b0);
  pcVar16 = (char *)osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),0x140);
  if (pcVar16 == (char *)0x0) goto LAB_001bede5;
  pbVar17 = (byte *)osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),0x140);
  if (pbVar17 == (byte *)0x0) {
    pbVar19 = (byte *)0x0;
    piVar18 = (int *)0x0;
  }
  else {
    piVar18 = (int *)osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),0x200);
    if (piVar18 == (int *)0x0) {
      pbVar19 = (byte *)0x0;
    }
    else {
      pbVar19 = (byte *)osl_malloc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),0x80);
      if ((pbVar19 != (byte *)0x0) && (*(code **)(param_1 + 0x108) != (code *)0x0)) {
        uVar14 = (**(code **)(param_1 + 0x108))(param_1,pcVar16,pbVar17);
        pbVar22 = pbVar19;
        piVar24 = piVar18;
        do {
          *piVar24 = -1;
          piVar24 = piVar24 + 1;
          *pbVar22 = 0;
          pbVar22 = pbVar22 + 1;
        } while (piVar24 != piVar18 + 0x80);
        pcVar23 = pcVar16;
        for (pbVar22 = pbVar17; pbVar22 != pbVar17 + uVar14; pbVar22 = pbVar22 + 1) {
          iVar15 = (int)*pcVar23;
          iVar21 = piVar18[*pbVar22];
          if (iVar21 != -1) {
            iVar15 = iVar21 + iVar15;
          }
          piVar18[*pbVar22] = iVar15;
          pcVar23 = pcVar23 + 1;
          pbVar19[*pbVar22] = pbVar19[*pbVar22] + 1;
        }
        uVar14 = 0;
        pbVar22 = pbVar19;
        piVar24 = piVar18;
        do {
          if (((*piVar24 != -1) && (iVar15 = *piVar24 / (int)(uint)*pbVar22, 0x1f < iVar15)) &&
             (iVar15 < 0x49)) {
            uVar25 = (ulong)uVar14;
            *(long *)(lVar4 + 0x38 + uVar25 * 8) = (long)iVar15;
            uVar14 = uVar14 + 1;
            *(long *)(lVar4 + 0x438 + uVar25 * 8) = (long)pbVar22 - (long)pbVar19;
          }
          piVar24 = piVar24 + 1;
          pbVar22 = pbVar22 + 1;
        } while (piVar24 != piVar18 + 0x80);
        goto LAB_001bf09b;
      }
    }
    uVar14 = 0;
  }
LAB_001bf09b:
  osl_mfree(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),pcVar16,0x140);
  if (pbVar17 != (byte *)0x0) {
    osl_mfree(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),pbVar17,0x140);
  }
  if (piVar18 != (int *)0x0) {
    osl_mfree(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),piVar18,0x200);
  }
  if (pbVar19 != (byte *)0x0) {
    osl_mfree(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x10),pbVar19,0x80);
  }
LAB_001bede5:
  lVar4 = *(long *)(param_1 + 0x10b0);
  puVar1 = (undefined8 *)(lVar4 + 0x838);
  plVar26 = (long *)(lVar4 + 0x38);
  for (puVar20 = puVar1; puVar20 != puVar1 + (ulong)uVar14 * 3; puVar20 = puVar20 + 3) {
    *puVar20 = 1;
    puVar20[1] = plVar26[0x80];
    lVar3 = *plVar26;
    plVar2 = plVar26 + 0x80;
    plVar26 = plVar26 + 1;
    puVar20[2] = 2 - lVar3 * *plVar2 >> 2;
  }
  lVar3 = lVar4 + 0x1438;
  iVar15 = 0;
  while( true ) {
    uVar28 = (uint)uVar14;
    if ((int)uVar28 <= iVar15) break;
    puVar20 = puVar1 + iVar15 * 3;
    iVar21 = 0;
    do {
      uVar5 = *puVar20;
      lVar27 = (long)iVar21;
      puVar20 = puVar20 + 1;
      iVar21 = iVar21 + (uint)uVar14;
      *(undefined8 *)(lVar3 + (lVar27 + iVar15) * 8) = uVar5;
    } while (puVar20 != (undefined8 *)(lVar4 + 0x850 + (long)(iVar15 * 3) * 8));
    iVar15 = iVar15 + 1;
  }
  FUN_001beb83(lVar3,puVar1,lVar4 + 0x2038,uVar28,3);
  lVar27 = *(long *)(lVar4 + 0x2070);
  lVar6 = *(long *)(lVar4 + 0x2078);
  lVar7 = *(long *)(lVar4 + 0x2058);
  lVar8 = *(long *)(lVar4 + 0x2060);
  lVar9 = *(long *)(lVar4 + 0x2040);
  lVar10 = *(long *)(lVar4 + 0x2048);
  lVar11 = *(long *)(lVar4 + 0x2050);
  lVar12 = *(long *)(lVar4 + 0x2038);
  lVar13 = *(long *)(lVar4 + 0x2068);
  *(long *)(lVar4 + 0x2080) = lVar6 * lVar7 - lVar27 * lVar8;
  *(long *)(lVar4 + 0x2088) = lVar27 * lVar10 - lVar6 * lVar9;
  *(long *)(lVar4 + 0x2090) = lVar8 * lVar9 - lVar7 * lVar10;
  *(long *)(lVar4 + 0x2098) = lVar13 * lVar8 - lVar6 * lVar11;
  *(long *)(lVar4 + 0x20a8) = lVar10 * lVar11 - lVar8 * lVar12;
  *(long *)(lVar4 + 0x20a0) = lVar6 * lVar12 - lVar13 * lVar10;
  *(long *)(lVar4 + 0x20b0) = lVar27 * lVar11 - lVar13 * lVar7;
  *(long *)(lVar4 + 0x20b8) = lVar13 * lVar9 - lVar27 * lVar12;
  *(long *)(lVar4 + 0x20c0) = lVar12 * lVar7 - lVar9 * lVar11;
  plVar26 = (long *)(lVar4 + 0x2cc8);
  *(long *)(lVar4 + 0x2ce0) =
       (((*(long *)(lVar4 + 0x2060) * *(long *)(lVar4 + 0x2040) * *(long *)(lVar4 + 0x2068) +
          *(long *)(lVar4 + 0x2058) * *(long *)(lVar4 + 0x2078) * *(long *)(lVar4 + 0x2038) +
         *(long *)(lVar4 + 0x2050) * *(long *)(lVar4 + 0x2048) * *(long *)(lVar4 + 0x2070)) -
        *(long *)(lVar4 + 0x2048) * *(long *)(lVar4 + 0x2058) * *(long *)(lVar4 + 0x2068)) -
       *(long *)(lVar4 + 0x2070) * *(long *)(lVar4 + 0x2060) * *(long *)(lVar4 + 0x2038)) -
       *(long *)(lVar4 + 0x2040) * *(long *)(lVar4 + 0x2050) * *(long *)(lVar4 + 0x2078);
  FUN_001beb83(lVar4 + 0x2080,lVar3,lVar4 + 0x20c8,3,uVar28);
  FUN_001beb83(lVar4 + 0x20c8,lVar4 + 0x38,plVar26,(uint)uVar14,1);
  do {
    *plVar26 = *plVar26 + 2 >> 2;
    plVar26 = plVar26 + 1;
  } while (plVar26 != (long *)(lVar4 + 0x2ce0));
  return 0;
}

