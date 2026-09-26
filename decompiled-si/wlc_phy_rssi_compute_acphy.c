
int wlc_phy_rssi_compute_acphy(long param_1,long param_2)

{
  long lVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  ushort *puVar5;
  ushort *puVar6;
  uint uVar7;
  long lVar8;
  short sVar9;
  ushort uVar10;
  int iVar11;
  bool bVar12;
  ushort local_48 [6];
  undefined1 local_3c [2];
  short local_3a [5];
  
  lVar1 = *(long *)(param_1 + 0x138);
  local_48[0] = (ushort)*(byte *)(param_2 + 9);
  bVar3 = *(byte *)(param_1 + 0x168);
  if (1 < bVar3) {
    local_48[1] = *(ushort *)(param_2 + 10) & 0xff;
    if (bVar3 != 2) {
      local_48[2] = *(ushort *)(param_2 + 10) >> 8;
    }
  }
  iVar11 = *(int *)(param_1 + 0x164);
  if ((((iVar11 == 5) || (iVar11 == 2)) || (iVar11 == 6)) && ((*(ushort *)(param_2 + 6) & 8) != 0))
  {
    puVar5 = local_48;
    puVar6 = puVar5 + bVar3;
    for (; puVar5 != puVar6; puVar5 = puVar5 + 1) {
      *puVar5 = 0;
    }
    bVar2 = wlc_phy_11b_rssi_WAR(param_1,param_2);
    local_48[0] = (ushort)bVar2;
  }
  puVar5 = local_48;
  for (puVar6 = puVar5; puVar6 != puVar5 + bVar3; puVar6 = puVar6 + 1) {
    if (0x7f < (short)*puVar6) {
      *puVar6 = *puVar6 - 0x100;
    }
  }
  wlc_phy_upd_gain_wrt_temp_phy(param_1,local_3a);
  bVar3 = *(byte *)(param_1 + 0x168);
  lVar8 = param_1;
  for (puVar6 = puVar5; puVar6 != puVar5 + bVar3; puVar6 = puVar6 + 1) {
    if (*puVar6 != 0) {
      sVar9 = *(char *)(lVar8 + 0x212) * 2 - local_3a[0];
      if (sVar9 < 0) {
        sVar9 = -(short)(2U - (int)sVar9 >> 2);
      }
      else {
        sVar9 = (short)((int)sVar9 + 2U >> 2);
      }
      *puVar6 = *puVar6 - sVar9;
    }
    lVar8 = lVar8 + 1;
  }
  for (iVar11 = 0; puVar6 = puVar5, lVar8 = param_2, iVar11 < (int)(uint)*(byte *)(param_1 + 0x168);
      iVar11 = iVar11 + 1) {
    bVar3 = wlc_phy_get_chan_freq_range_acphy(param_1,*(undefined1 *)(param_1 + 0x17e));
    if (bVar3 < 5) {
      uVar10 = *(ushort *)(param_1 + 0x17e);
      switch(bVar3) {
      case 0:
        if ((uVar10 & 0x3800) == 0x1800) {
          sVar9 = (short)*(char *)(lVar1 + 0x3a9 + (long)iVar11 * 2);
        }
        else {
          sVar9 = (short)*(char *)(lVar1 + 0x3a8 + (long)iVar11 * 2);
        }
        break;
      case 1:
        if ((uVar10 & 0x3800) == 0x2000) {
          sVar9 = (short)*(char *)(lVar1 + 0x3b2 + (long)iVar11 * 0xc);
        }
        else if ((uVar10 & 0x3800) == 0x1800) {
          sVar9 = (short)*(char *)(lVar1 + 0x3b1 + (long)iVar11 * 0xc);
        }
        else {
          sVar9 = (short)*(char *)(lVar1 + 0x3b0 + (long)iVar11 * 0xc);
        }
        break;
      case 2:
        if ((uVar10 & 0x3800) == 0x2000) {
          sVar9 = (short)*(char *)(lVar1 + 0x3b5 + (long)iVar11 * 0xc);
        }
        else if ((uVar10 & 0x3800) == 0x1800) {
          sVar9 = (short)*(char *)(lVar1 + 0x3b4 + (long)iVar11 * 0xc);
        }
        else {
          sVar9 = (short)*(char *)(lVar1 + 0x3b3 + (long)iVar11 * 0xc);
        }
        break;
      case 3:
        if ((uVar10 & 0x3800) == 0x2000) {
          sVar9 = (short)*(char *)(lVar1 + 0x3b8 + (long)iVar11 * 0xc);
        }
        else if ((uVar10 & 0x3800) == 0x1800) {
          sVar9 = (short)*(char *)(lVar1 + 0x3b7 + (long)iVar11 * 0xc);
        }
        else {
          sVar9 = (short)*(char *)(lVar1 + 0x3b6 + (long)iVar11 * 0xc);
        }
        break;
      case 4:
        if ((uVar10 & 0x3800) == 0x2000) {
          sVar9 = (short)*(char *)(lVar1 + 0x3bb + (long)iVar11 * 0xc);
        }
        else if ((uVar10 & 0x3800) == 0x1800) {
          sVar9 = (short)*(char *)(lVar1 + 0x3ba + (long)iVar11 * 0xc);
        }
        else {
          sVar9 = (short)*(char *)(lVar1 + 0x3b9 + (long)iVar11 * 0xc);
        }
      }
      local_48[iVar11] = local_48[iVar11] + sVar9;
    }
  }
  while ((int)lVar8 - (int)param_2 < (int)(uint)*(byte *)(param_1 + 0x168)) {
    uVar10 = 0xff80;
    if (-0x81 < (short)*puVar6) {
      uVar10 = *puVar6;
    }
    *puVar6 = uVar10;
    *(char *)(lVar8 + 0x20) = (char)uVar10;
    puVar6 = puVar6 + 1;
    lVar8 = lVar8 + 1;
  }
  *(undefined1 *)(param_2 + 0x1f) = 0;
  sVar9 = 0;
  uVar10 = 0;
  for (uVar7 = 0; lVar1 = *(long *)(param_1 + 0x20),
      (int)uVar7 < (int)(uint)*(byte *)(param_1 + 0x168); uVar7 = uVar7 + 1) {
    if ((*(byte *)(lVar1 + 0xa7) >> (uVar7 & 0x1f) & 1) != 0) {
      bVar12 = sVar9 == 0;
      sVar9 = sVar9 + 1;
      if (bVar12) {
        uVar10 = *puVar5;
      }
      else {
        cVar4 = *(char *)(lVar1 + 0xa8);
        if (cVar4 == '\x01') {
          if ((short)*puVar5 < (short)uVar10) {
            uVar10 = *puVar5;
          }
        }
        else if (cVar4 == '\0') {
          if ((short)uVar10 < (short)*puVar5) {
            uVar10 = *puVar5;
          }
        }
        else if (cVar4 == '\x02') {
          uVar10 = uVar10 + *puVar5;
        }
      }
    }
    puVar5 = puVar5 + 1;
  }
  if (*(char *)(lVar1 + 0xa8) == '\x02') {
    cVar4 = qm_div16((int)(short)uVar10,(int)sVar9,local_3c);
    uVar10 = (ushort)cVar4;
  }
  return (int)(short)uVar10;
}

