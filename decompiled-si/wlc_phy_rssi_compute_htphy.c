
int wlc_phy_rssi_compute_htphy(long param_1,long param_2)

{
  byte bVar1;
  char cVar2;
  ushort *puVar3;
  ushort *puVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  ushort *puVar8;
  short sVar9;
  ushort uVar10;
  bool bVar11;
  ushort local_38 [6];
  undefined1 local_2c [2];
  short local_2a [5];
  
  local_38[0] = (ushort)*(byte *)(param_2 + 9);
  bVar1 = *(byte *)(param_1 + 0x168);
  if (1 < bVar1) {
    local_38[1] = *(ushort *)(param_2 + 10) & 0xff;
    if (bVar1 != 2) {
      local_38[2] = local_38[1];
    }
  }
  puVar8 = local_38;
  for (puVar3 = puVar8; puVar3 != puVar8 + bVar1; puVar3 = puVar3 + 1) {
    if (0x7f < (short)*puVar3) {
      *puVar3 = *puVar3 - 0x100;
    }
  }
  wlc_phy_upd_gain_wrt_temp_phy(param_1,local_2a);
  bVar1 = *(byte *)(param_1 + 0x168);
  lVar6 = param_1;
  for (puVar3 = puVar8; puVar4 = puVar8, lVar7 = param_2, puVar3 != puVar8 + bVar1;
      puVar3 = puVar3 + 1) {
    sVar9 = *(char *)(lVar6 + 0x212) * 2 - local_2a[0];
    if (sVar9 < 0) {
      sVar9 = -(short)(2U - (int)sVar9 >> 2);
    }
    else {
      sVar9 = (short)((int)sVar9 + 2U >> 2);
    }
    *puVar3 = *puVar3 - sVar9;
    lVar6 = lVar6 + 1;
  }
  while ((int)lVar7 - (int)param_2 < (int)(uint)*(byte *)(param_1 + 0x168)) {
    uVar10 = 0xff80;
    if (-0x81 < (short)*puVar4) {
      uVar10 = *puVar4;
    }
    *puVar4 = uVar10;
    *(char *)(lVar7 + 0x20) = (char)uVar10;
    puVar4 = puVar4 + 1;
    lVar7 = lVar7 + 1;
  }
  *(undefined1 *)(param_2 + 0x1f) = 0;
  sVar9 = 0;
  uVar10 = 0;
  for (uVar5 = 0; lVar6 = *(long *)(param_1 + 0x20),
      (int)uVar5 < (int)(uint)*(byte *)(param_1 + 0x168); uVar5 = uVar5 + 1) {
    if ((*(byte *)(lVar6 + 0xa7) >> (uVar5 & 0x1f) & 1) != 0) {
      bVar11 = sVar9 == 0;
      sVar9 = sVar9 + 1;
      if (bVar11) {
        uVar10 = *puVar8;
      }
      else {
        cVar2 = *(char *)(lVar6 + 0xa8);
        if (cVar2 == '\x01') {
          if ((short)*puVar8 < (short)uVar10) {
            uVar10 = *puVar8;
          }
        }
        else if (cVar2 == '\0') {
          if ((short)uVar10 < (short)*puVar8) {
            uVar10 = *puVar8;
          }
        }
        else if (cVar2 == '\x02') {
          uVar10 = uVar10 + *puVar8;
        }
      }
    }
    puVar8 = puVar8 + 1;
  }
  if (*(char *)(lVar6 + 0xa8) == '\x02') {
    cVar2 = qm_div16((int)(short)uVar10,(int)sVar9,local_2c);
    uVar10 = (ushort)cVar2;
  }
  return (int)(short)uVar10;
}

