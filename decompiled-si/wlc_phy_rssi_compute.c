
void wlc_phy_rssi_compute(long param_1,long param_2)

{
  char *pcVar1;
  char cVar2;
  undefined1 uVar3;
  long lVar4;
  char cVar5;
  byte bVar6;
  short sVar7;
  ushort uVar8;
  uint uVar9;
  uint uVar10;
  byte bVar11;
  int iVar12;
  long lVar13;
  byte bVar14;
  short sVar15;
  int iVar16;
  ushort uVar17;
  bool bVar19;
  bool bVar20;
  byte local_49;
  ulong uVar18;
  
  uVar8 = *(ushort *)(param_2 + 4);
  uVar9 = *(uint *)(*(long *)(param_1 + 0x20) + 0x28);
  if ((10 < uVar9) &&
     (((*(ushort *)(param_2 + 0x12) & 0x100) == 0 ||
      ((uVar9 == 0x23 && ((*(ushort *)(param_2 + 0x12) & 0x20) != 0)))))) {
    *(undefined1 *)(param_2 + 0x1f) = 1;
    bVar14 = 0;
    uVar9 = 0;
    goto LAB_001baa5e;
  }
  bVar14 = (byte)*(undefined2 *)(param_2 + 6);
  uVar9 = (uint)bVar14;
  if (*(int *)(param_1 + 0x160) == 6) {
    uVar9 = wlc_sslpnphy_rssi_compute(param_1,bVar14,param_2);
  }
  bVar19 = *(int *)(param_1 + 0x160) == 8;
  bVar20 = *(int *)(param_1 + 0x160) == 10;
  if ((bVar20) || (bVar14 = 0, bVar19)) {
    uVar17 = *(ushort *)(param_2 + 8) >> 10;
    uVar18 = (ulong)uVar17;
    if ((bVar19) || (lVar13 = 0, bVar20)) {
      lVar13 = *(long *)(param_1 + 0x138);
    }
    cVar2 = *(char *)(lVar13 + 0x5f);
    if (0x7f < (int)uVar9) {
      uVar9 = uVar9 - 0x100;
    }
    if (bVar19) {
      if ((uVar8 & 0x800) == 0) {
        cVar5 = *(char *)(param_1 + 0x10fe);
      }
      else {
        cVar5 = *(char *)(param_1 + 0x10ff);
      }
      iVar16 = uVar9 + (int)(char)lcnphy_gain_index_offset_for_pkt_rssi
                                  [(byte)(*(ushort *)(param_2 + 8) >> 10)] + (int)cVar5;
      bVar14 = 0;
    }
    else {
      lVar13 = 0;
      if (bVar20) {
        lVar13 = *(long *)(param_1 + 0x138);
      }
      lVar4 = *(long *)(param_1 + 0x138);
      local_49 = 0;
      uVar8 = *(ushort *)(param_2 + 4) >> 0xc & 1;
      if ((*(ushort *)(param_2 + 4) & 0x800) != 0) {
        uVar18 = (ulong)(uVar17 + 0x40);
      }
      if (*(char *)(lVar4 + 0x85f) != '\0') {
        sVar7 = wlc_lcn40phy_get_rxpath_gain_by_index(param_1,uVar18,uVar8);
        iVar12 = ((*(ushort *)(param_2 + 4) >> 0xd & 1 |
                  (int)(*(ushort *)(param_2 + 4) & 0x400) >> 9) + *(char *)(lVar4 + 0x860) * 4 +
                 uVar9 * 4) - (int)sVar7;
        local_49 = (byte)iVar12 & 3;
        uVar9 = iVar12 >> 2;
      }
      if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
        cVar5 = phy_reg_read(param_1,0xa53);
      }
      else {
        uVar10 = phy_reg_read(param_1,0xa52);
        cVar5 = (char)((uVar10 & 0x1fe0) >> 5);
      }
      iVar12 = wlc_phy_chanspec_bandrange_get(param_1,*(undefined2 *)(param_1 + 0x17e));
      if (iVar12 == 1) {
        if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
          sVar7 = *(short *)(lVar13 + 0x2fa);
        }
        else {
          sVar7 = *(short *)(lVar13 + 0x302);
        }
      }
      else if (iVar12 < 2) {
        if (iVar12 == 0) {
          if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
            sVar7 = (short)*(undefined4 *)(lVar13 + 0x2f8);
          }
          else {
            sVar7 = (short)*(undefined4 *)(lVar13 + 0x300);
          }
        }
        else {
LAB_001ba7a8:
          sVar7 = (short)cVar5;
        }
      }
      else if (iVar12 == 2) {
        if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
          sVar7 = (short)*(undefined4 *)(lVar13 + 0x2fc);
        }
        else {
          sVar7 = (short)*(undefined4 *)(lVar13 + 0x304);
        }
      }
      else {
        if (iVar12 != 3) goto LAB_001ba7a8;
        if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
          sVar7 = *(short *)(lVar13 + 0x2fe);
        }
        else {
          sVar7 = *(short *)(lVar13 + 0x306);
        }
      }
      iVar12 = (uVar9 - (int)cVar5) + (int)sVar7;
      if (*(char *)(lVar4 + 0x85f) == '\0') {
        iVar16 = wlc_phy_chanspec_bandrange_get(param_1,*(undefined2 *)(param_1 + 0x17e));
        if (iVar16 == 0) {
          if ((iVar12 < -0x3c) && ((byte)((char)uVar18 - 1U) < 0x25)) {
            iVar12 = iVar12 + (char)lcn40phy_gain_index_offset_for_pkt_rssi_2g[uVar18];
          }
          cVar5 = *(char *)(param_1 + 0x1106);
          lVar13 = param_1 + 0x1106;
        }
        else {
          if ((iVar12 < -0x3c) && ((byte)((char)uVar18 - 1U) < 0x25)) {
            iVar12 = iVar12 + (char)lcn40phy_gain_index_offset_for_pkt_rssi_5g[uVar18];
          }
          lVar13 = param_1 + 0x110b;
          cVar5 = *(char *)(param_1 + 0x110b);
        }
        if (cVar5 < iVar12) {
          if (*(char *)(lVar13 + 1) < iVar12) {
            iVar16 = (int)*(char *)(lVar13 + 4);
          }
          else {
            iVar16 = (int)*(char *)(lVar13 + 3);
          }
        }
        else {
          iVar16 = (int)*(char *)(lVar13 + 2);
        }
        iVar12 = iVar12 + iVar16;
        iVar16 = wlc_phy_chanspec_bandrange_get(param_1,*(undefined2 *)(param_1 + 0x17e));
        if (iVar16 == 1) {
          iVar16 = (int)*(char *)(param_1 + 0x1100);
        }
        else if (iVar16 < 2) {
          if (iVar16 != 0) goto LAB_001ba8a9;
          iVar16 = (int)*(char *)(param_1 + 0x10fe);
        }
        else if (iVar16 == 2) {
          iVar16 = (int)*(char *)(param_1 + 0x1101);
        }
        else {
          if (iVar16 != 3) goto LAB_001ba8a9;
          iVar16 = (int)*(char *)(param_1 + 0x1102);
        }
        iVar12 = iVar12 + iVar16;
      }
LAB_001ba8a9:
      sVar7 = wlc_lcn40phy_rssi_tempcorr(param_1,0);
      iVar12 = iVar12 * 4 + (int)sVar7 + (int)(char)local_49;
      if (*(char *)(lVar4 + 0x85f) != '\0') {
        sVar7 = wlc_lcn40phy_iqest_rssi_tempcorr(param_1,0,uVar8);
        iVar12 = iVar12 + sVar7;
      }
      iVar16 = iVar12 >> 2;
      bVar14 = (byte)iVar12 & 3;
    }
    uVar9 = iVar16 + cVar2;
  }
  sVar7 = *(short *)(param_1 + 10);
  if (sVar7 == 0x2050) {
    if ((*(byte *)(param_2 + 4) & 1) == 0) {
      if ((*(byte *)(*(long *)(param_1 + 0x20) + 100) & 8) == 0) {
        uVar9 = ((int)(uVar9 * 0x95 + -0x120b) >> 7) - 0x44;
      }
      else {
        uVar10 = 0x3f;
        if ((int)uVar9 < 0x40) {
          uVar10 = uVar9;
        }
        uVar9 = ((int)((uint)(byte)(&DAT_0055aed0)[(int)uVar10] * 0x83 + -0xfdd) >> 7) - 0x43;
      }
      if (*(int *)(param_1 + 0x160) == 2) {
        if ((*(byte *)(param_2 + 0xb) & 4) != 0) {
          uVar9 = uVar9 + 0x14;
        }
        uVar8 = *(ushort *)(param_2 + 8) >> 0xe;
        if (uVar8 == 1) {
          uVar9 = uVar9 - 0x13;
        }
        else if (uVar8 == 0) {
          uVar9 = uVar9 + 2;
        }
        else if (uVar8 == 2) {
          uVar9 = uVar9 - 0xd;
        }
        else if (uVar8 == 3) {
          uVar9 = uVar9 - 0x19;
        }
        uVar9 = uVar9 + 0x19;
      }
    }
    else {
      if (0x7f < (int)uVar9) {
        uVar9 = uVar9 - 0x100;
      }
      if ((*(byte *)(param_2 + 0xb) & 4) == 0) {
        uVar9 = uVar9 - 4;
      }
      else {
        uVar9 = uVar9 + 0x11;
      }
    }
  }
  else if ((sVar7 == 0x2060) || (iVar12 = *(int *)(param_1 + 0x160), iVar12 == 5)) {
    if (0x7f < (int)uVar9) {
      uVar9 = uVar9 - 0x100;
    }
  }
  else if (iVar12 != 6) {
    if ((iVar12 == 10) || (iVar12 == 8)) {
      *(undefined1 *)(param_2 + 0x1f) = 0;
      if (0x7f < (int)uVar9) {
        uVar9 = uVar9 - 0x100;
      }
      *(char *)(param_2 + 0x20) = (char)uVar9;
    }
    else if (iVar12 == 4) {
      if (((ushort)(sVar7 + 0xdfabU) < 3) || (sVar7 == 0x22e)) {
        uVar9 = wlc_phy_rssi_compute_nphy(param_1,param_2);
      }
    }
    else if (iVar12 == 7) {
      uVar9 = wlc_phy_rssi_compute_htphy(param_1,param_2);
    }
    else if (iVar12 == 0xb) {
      uVar9 = wlc_phy_rssi_compute_acphy(param_1,param_2);
    }
  }
LAB_001baa5e:
  *(char *)(param_2 + 0x1c) = (char)uVar9;
  *(byte *)(param_2 + 0x24) = bVar14;
  if (*(int *)(param_1 + 0x160) == 8) {
    wlc_phy_lcn_updatemac_rssi(param_1,(int)(char)uVar9,*(ushort *)(param_2 + 4) >> 0xe & 1);
  }
  if ((*(int *)(param_1 + 0x160) == 7) || (*(int *)(param_1 + 0x160) == 4)) {
    uVar3 = *(undefined1 *)(param_2 + 0x21);
    *(undefined1 *)(param_1 + 0x10b9 + (long)*(char *)(param_1 + 0x10db)) =
         *(undefined1 *)(param_2 + 0x20);
    *(undefined1 *)(param_1 + 0x10c9 + (long)*(char *)(param_1 + 0x10dc)) = uVar3;
    bVar14 = *(char *)(param_1 + 0x10db) + 1;
    bVar11 = *(char *)(param_1 + 0x10dc) + 1U & 0x8f;
    *(byte *)(param_1 + 0x10db) = bVar14;
    if ((char)bVar11 < '\0') {
      bVar11 = (bVar11 - 1 | 0xf0) + 1;
    }
    bVar6 = bVar14 & 0x8f;
    *(byte *)(param_1 + 0x10dc) = bVar11;
    if ((char)bVar14 < '\0') {
      bVar6 = (bVar6 - 1 | 0xf0) + 1;
    }
    *(byte *)(param_1 + 0x10db) = bVar6;
    sVar15 = 0;
    sVar7 = 0;
    lVar13 = param_1;
    do {
      sVar7 = sVar7 + *(char *)(lVar13 + 0x10b9);
      pcVar1 = (char *)(lVar13 + 0x10c9);
      lVar13 = lVar13 + 1;
      sVar15 = sVar15 + *pcVar1;
    } while (lVar13 != param_1 + 0x10);
    *(char *)(param_1 + 0x10d9) = (char)(sVar7 / 0x10);
    *(char *)(param_1 + 0x10da) = (char)(sVar15 / 0x10);
  }
  return;
}

