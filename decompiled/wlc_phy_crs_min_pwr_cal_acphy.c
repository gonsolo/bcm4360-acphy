
void wlc_phy_crs_min_pwr_cal_acphy(long param_1,char param_2)

{
  char *pcVar1;
  char cVar2;
  byte bVar3;
  short sVar4;
  ushort uVar5;
  uint uVar6;
  long lVar7;
  byte bVar8;
  char cVar9;
  long lVar10;
  byte *pbVar11;
  uint uVar12;
  byte *pbVar13;
  ulong uVar14;
  char cVar15;
  char cVar16;
  char cVar17;
  char cVar18;
  char cVar19;
  uint uVar20;
  long lVar21;
  byte abStack_d8 [64];
  byte local_98 [16];
  byte local_88 [16];
  byte local_78 [16];
  byte abStack_68 [16];
  byte local_58 [16];
  char local_48 [24];
  
  pbVar11 = &DAT_00559018;
  pbVar13 = local_78;
  for (lVar7 = 0xf; lVar7 != 0; lVar7 = lVar7 + -1) {
    *pbVar13 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    pbVar13 = pbVar13 + 1;
  }
  pbVar11 = &DAT_00559008;
  pbVar13 = local_88;
  for (lVar7 = 0xf; lVar7 != 0; lVar7 = lVar7 + -1) {
    *pbVar13 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    pbVar13 = pbVar13 + 1;
  }
  pbVar11 = &DAT_00558ff8;
  pbVar13 = local_98;
  for (lVar7 = 0xf; lVar7 != 0; lVar7 = lVar7 + -1) {
    *pbVar13 = *pbVar11;
    pbVar11 = pbVar11 + 1;
    pbVar13 = pbVar13 + 1;
  }
  osl_memset(local_48,0,4);
  osl_memset(local_58,0,4);
  local_58[0] = 0x36;
  bVar3 = wlc_phy_get_chan_freq_range_acphy(param_1,0);
  uVar6 = 0;
  if (param_2 == '\0') {
    for (; (byte)uVar6 < *(byte *)(param_1 + 0x168); uVar6 = uVar6 + 1) {
      if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar6 & 0x1f) & 1) != 0) {
        lVar7 = *(long *)(param_1 + 0x138);
        *(char *)((long)(int)(uVar6 & 0xff) + 0x2c + lVar7 + (long)*(char *)(lVar7 + 0x3c) * 4) =
             *(char *)(lVar7 + 0x14 + (long)(int)(uVar6 & 0xff)) + '\x01';
      }
    }
    pcVar1 = (char *)(*(long *)(param_1 + 0x138) + 0x3c);
    *pcVar1 = *pcVar1 + '\x01';
    bVar8 = *(byte *)(*(long *)(param_1 + 0x138) + 0x3c) & 0x83;
    if ((char)bVar8 < '\0') {
      bVar8 = (bVar8 - 1 | 0xfc) + 1;
    }
    *(byte *)(*(long *)(param_1 + 0x138) + 0x3c) = bVar8;
  }
  uVar14 = 0;
  cVar15 = '\0';
  uVar6 = 0;
  cVar19 = '\0';
  cVar18 = '\0';
  cVar16 = '\x02';
  lVar7 = (ulong)bVar3 * 4;
  do {
    bVar3 = (byte)uVar6;
    if (*(byte *)(param_1 + 0x168) <= bVar3) {
      if (cVar15 == '\0') {
        if (param_2 == '\0') {
          return;
        }
      }
      else if (param_2 == '\0') {
        *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x33d) = 0;
      }
      *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x33e) = 1;
      if (local_58[1] < local_58[2]) {
        local_58[1] = local_58[2];
      }
      bVar3 = local_58[0];
      if (local_58[0] <= local_58[1]) {
        bVar3 = local_58[1];
      }
      *(byte *)(*(long *)(param_1 + 0x138) + 0x42) = bVar3;
      lVar7 = *(long *)(param_1 + 0x138);
      if (*(char *)(lVar7 + 0x670) == '\0') {
        *(char *)(lVar7 + 0x43) = *(char *)(lVar7 + 0x43) + '\x01';
        *(char *)(*(long *)(param_1 + 0x138) + 0x44) = (char)*(undefined2 *)(param_1 + 0x17e);
        for (bVar3 = 0; bVar3 < *(byte *)(param_1 + 0x168); bVar3 = bVar3 + 1) {
          uVar6 = (uint)bVar3;
          if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar6 & 0x1f) & 1) != 0) {
            *(char *)(*(long *)(param_1 + 0x138) + 0x3d + (long)(int)uVar6) = local_48[(int)uVar6];
          }
        }
        wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
        wlc_phyreg_enter(param_1);
        FUN_0019015b(param_1,local_58[0],(int)cVar18,(int)cVar19);
        wlc_phyreg_exit(param_1);
        wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
      }
      else {
        *(undefined1 *)(lVar7 + 0x33e) = 2;
      }
      return;
    }
    uVar12 = uVar6 & 0xff;
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar6 & 0x1f) & 1) != 0) {
      if (param_2 == '\0') {
        lVar21 = *(long *)(param_1 + 0x138);
        lVar10 = (long)(int)uVar12;
        cVar17 = *(char *)(lVar21 + 0x2c + lVar10);
        if (cVar17 == '\0') {
          return;
        }
        cVar9 = *(char *)(lVar21 + 0x30 + lVar10);
        sVar4 = (short)cVar17;
        cVar17 = '\x01';
        if (cVar9 != '\0') {
          sVar4 = sVar4 + cVar9;
          cVar9 = *(char *)(lVar21 + 0x34 + lVar10);
          cVar17 = '\x02';
          if (cVar9 != '\0') {
            cVar2 = *(char *)(lVar21 + 0x38 + lVar10);
            sVar4 = sVar4 + cVar9;
            cVar17 = '\x03';
            if (cVar2 != '\0') {
              cVar17 = '\x04';
              sVar4 = sVar4 + cVar2;
            }
          }
        }
        lVar21 = (long)(int)uVar12;
        cVar17 = (char)(sVar4 / (short)cVar17);
        uVar20 = *(uint *)(param_1 + 0x164);
        local_48[lVar21] = cVar17;
        if (uVar20 < 2) {
          cVar16 = '\x03';
        }
        uVar5 = *(ushort *)(param_1 + 0x17e) & 0x3800;
        if (uVar5 == 0x1000) {
          cVar9 = *(char *)(lVar21 + 0x18 + *(long *)(param_1 + 0x138) + lVar7);
        }
        else if (uVar5 == 0x1800) {
          cVar9 = *(char *)(lVar21 + 0x18 + *(long *)(param_1 + 0x138) + lVar7) + '\x03';
        }
        else {
          cVar9 = *(char *)(lVar21 + 0x18 + *(long *)(param_1 + 0x138) + lVar7) + '\a';
        }
        uVar20 = (int)(char)(cVar9 - cVar17) >> 0x1f;
        if (((uint)(int)cVar16 <= (((int)(char)(cVar9 - cVar17) ^ uVar20) - uVar20 & 0xff)) ||
           (*(char *)(*(long *)(param_1 + 0x138) + 0x33d) != '\0')) {
          cVar15 = cVar15 + '\x01';
          if (uVar5 == 0x1000) {
            lVar10 = (long)(int)uVar12;
            lVar21 = *(long *)(param_1 + 0x138) + lVar7;
          }
          else {
            lVar21 = (long)(int)uVar12;
            if (uVar5 == 0x1800) {
              lVar10 = *(long *)(param_1 + 0x138) + lVar7;
              cVar17 = cVar17 + -3;
            }
            else {
              lVar10 = *(long *)(param_1 + 0x138) + lVar7;
              cVar17 = cVar17 + -7;
            }
          }
          *(char *)(lVar10 + 0x18 + lVar21) = cVar17;
        }
      }
      else {
        uVar5 = *(ushort *)(param_1 + 0x17e) & 0x3800;
        if (uVar5 == 0x1000) {
          cVar17 = *(char *)((long)(int)uVar12 + 0x18 + *(long *)(param_1 + 0x138) + lVar7);
        }
        else if (uVar5 == 0x1800) {
          cVar17 = *(char *)(*(long *)(param_1 + 0x138) + lVar7 + 0x18 + (long)(int)uVar12) + '\x03'
          ;
        }
        else {
          cVar17 = *(char *)(*(long *)(param_1 + 0x138) + lVar7 + 0x18 + (long)(int)uVar12) + '\a';
        }
        local_48[(int)uVar12] = cVar17;
      }
      uVar5 = *(ushort *)(param_1 + 0x17e) & 0x3800;
      if (uVar5 == 0x1000) {
        abStack_68[uVar14 * 2] = local_48[(int)uVar12] + 0x22;
      }
      else {
        if (uVar5 == 0x1800) {
          bVar8 = local_48[(int)uVar12] + 0x21;
        }
        else {
          bVar8 = local_48[(int)uVar12] + 0x1e;
        }
        abStack_68[uVar14 * 2] = bVar8;
      }
      if (0xe < abStack_68[uVar14 * 2]) {
        abStack_68[uVar14 * 2] = ~((char)abStack_68[uVar14 * 2] >> 7) & 0xe;
      }
      abStack_68[uVar14 * 2 + 1] = bVar3;
      if (uVar5 == 0x1000) {
        bVar8 = local_78[(char)abStack_68[uVar14 * 2]];
LAB_00193a7c:
        local_58[(char)bVar3] = bVar8;
      }
      else {
        if (uVar5 == 0x1800) {
          bVar8 = local_88[(char)abStack_68[uVar14 * 2]];
          goto LAB_00193a7c;
        }
        if (uVar5 == 0x2000) {
          bVar8 = local_98[(char)abStack_68[uVar14 * 2]];
          goto LAB_00193a7c;
        }
      }
      if (bVar3 == 1) {
        cVar18 = local_58[1] - local_58[0];
      }
      else if (bVar3 == 2) {
        cVar19 = local_58[2] - local_58[0];
      }
      uVar14 = (ulong)((int)uVar14 + 1);
    }
    uVar6 = uVar6 + 1;
  } while( true );
}

