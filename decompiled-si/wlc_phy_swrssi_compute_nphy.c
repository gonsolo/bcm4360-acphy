
undefined1  [16]
wlc_phy_swrssi_compute_nphy(long param_1,short *param_2,short *param_3,ulong param_4)

{
  short *psVar1;
  undefined1 uVar2;
  char cVar3;
  short sVar4;
  long lVar5;
  byte bVar6;
  ushort uVar7;
  uint uVar8;
  short sVar9;
  int iVar10;
  undefined6 uVar12;
  long lVar13;
  uint uVar14;
  uint uVar15;
  undefined1 auVar16 [16];
  ulong uVar11;
  
  lVar13 = *(long *)(param_1 + 0x20);
  lVar5 = *(long *)(param_1 + 0x138);
  uVar7 = *(ushort *)(param_1 + 0x17e);
  uVar2 = *(undefined1 *)(lVar13 + 0xa8);
  if (*(int *)(lVar13 + 0x3c) == 0x4324) {
    uVar14 = *(uint *)(lVar13 + 0x40);
    param_4 = (ulong)uVar14;
    if ((uVar14 == 5) || (uVar14 == 2)) {
      *(undefined1 *)(lVar13 + 0xa8) = 1;
    }
  }
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    uVar14 = *(uint *)(*(long *)(param_1 + 0x20) + 0xbc);
    sVar9 = *(short *)(*(long *)(param_1 + 0x20) + 0xbe);
  }
  else {
    uVar7 = uVar7 & 0xff;
    if (uVar7 < 0x41) {
      uVar14 = *(uint *)(*(long *)(param_1 + 0x20) + 0xc0);
      sVar9 = *(short *)(*(long *)(param_1 + 0x20) + 0xc6);
    }
    else {
      lVar13 = *(long *)(param_1 + 0x20);
      if (uVar7 < 0x71) {
        uVar14 = (uint)*(ushort *)(lVar13 + 0xc2);
        sVar9 = (short)*(undefined4 *)(lVar13 + 200);
      }
      else {
        uVar14 = *(uint *)(lVar13 + 0xc4);
        sVar9 = *(short *)(lVar13 + 0xca);
      }
    }
  }
  lVar13 = *(long *)(param_1 + 0x20);
  cVar3 = *(char *)(lVar13 + 0xa7);
  uVar12 = (undefined6)(param_4 >> 0x10);
  if (cVar3 == '\x01') {
    uVar14 = (uint)(short)uVar14;
    uVar8 = (uint)sVar9;
    if (-0x1e < *param_2) {
      uVar14 = uVar14 >> 8;
      uVar8 = uVar8 >> 8;
    }
    iVar10 = (int)CONCAT62(uVar12,*param_2) + ((int)((uVar14 & 0xff) - (uVar8 & 0xff)) >> 1);
    sVar9 = (short)iVar10 + *(short *)(lVar5 + 0x5c2);
    uVar11 = (ulong)CONCAT22((short)((uint)iVar10 >> 0x10),sVar9);
    *param_2 = sVar9;
  }
  else if (cVar3 == '\x02') {
    uVar8 = (uint)(short)uVar14;
    uVar14 = (uint)sVar9;
    if (-0x1e < *param_3) {
      uVar14 = uVar14 >> 8;
      uVar8 = uVar8 >> 8;
    }
    uVar14 = (int)CONCAT62(uVar12,*param_3) + ((int)((uVar14 & 0xff) - (uVar8 & 0xff)) >> 1) +
             *(int *)(lVar5 + 0x5c4);
    uVar11 = (ulong)uVar14;
    *param_3 = (short)uVar14;
  }
  else {
    if (cVar3 != *(char *)(lVar13 + 0xa5)) {
LAB_00212bef:
      uVar11 = 0;
      goto LAB_00212bc9;
    }
    if (((*param_3 < -0x27) && (*param_2 < -0x27)) ||
       (uVar8 = (int)*param_2 - (int)*param_3, uVar15 = (int)uVar8 >> 0x1f,
       (int)((uVar8 ^ uVar15) - uVar15) < 5)) {
      uVar14 = uVar14 & 0xff;
      bVar6 = (byte)sVar9;
      iVar10 = (int)(uVar14 - bVar6) >> 1;
      *param_2 = *param_2 + (short)iVar10;
    }
    else {
      uVar14 = uVar14 >> 8 & 0xff;
      bVar6 = (byte)((ushort)sVar9 >> 8);
      iVar10 = (int)CONCAT62((int6)((ulong)lVar13 >> 0x10),*param_2) + ((int)(uVar14 - bVar6) >> 1);
      *param_2 = (short)iVar10;
    }
    *param_3 = *param_3 + (short)((int)(bVar6 - uVar14) >> 1);
    *param_2 = *param_2 + *(short *)(lVar5 + 0x5c2);
    uVar14 = CONCAT22((short)((int)(bVar6 - uVar14) >> 0x11),*param_3) + *(int *)(lVar5 + 0x5c4);
    sVar9 = (short)uVar14;
    *param_3 = sVar9;
    lVar13 = *(long *)(param_1 + 0x20);
    cVar3 = *(char *)(lVar13 + 0xa8);
    param_3 = (short *)CONCAT71((int7)((ulong)lVar13 >> 8),cVar3);
    if (cVar3 == '\0') {
      sVar4 = *param_2;
      uVar11 = (ulong)CONCAT22((short)((uint)iVar10 >> 0x10),sVar4);
LAB_00212b4c:
      if (sVar4 <= sVar9) {
        uVar11 = (ulong)uVar14;
      }
    }
    else if (cVar3 == '\x01') {
      sVar4 = *param_2;
      param_3 = (short *)CONCAT62((int6)((ulong)lVar13 >> 0x10),sVar4);
      uVar11 = (ulong)param_3 & 0xffffffff;
      if (sVar9 <= sVar4) {
        uVar11 = (ulong)uVar14;
      }
      if ((short)uVar11 < -0x5f) {
        uVar11 = (ulong)param_3 & 0xffffffff;
        goto LAB_00212b4c;
      }
    }
    else {
      if (cVar3 != '\x02') goto LAB_00212bef;
      param_3 = (short *)(ulong)(uint)(int)*param_2;
      uVar11 = (ulong)((uint)((int)sVar9 + (int)*param_2) >> 1);
    }
  }
  sVar9 = (short)uVar11;
  if (sVar9 < -0x14) {
    *(short *)(lVar5 + 0x26c + (long)*(short *)(lVar5 + 0x28c) * 2) = sVar9;
    uVar14 = *(int *)(lVar5 + 0x28c) + 1;
    iVar10 = 0;
    *(short *)(lVar5 + 0x28c) =
         (short)((int)((uint)(ushort)((short)uVar14 >> 0xf) << 0x10 | uVar14 & 0xffff) % 0x10);
    lVar13 = 0;
    do {
      psVar1 = (short *)(lVar5 + 0x26c + lVar13);
      lVar13 = lVar13 + 2;
      iVar10 = iVar10 + *psVar1;
    } while (lVar13 != 0x20);
    param_3 = (short *)((long)iVar10 % 0x10 & 0xffffffff);
    *(short *)(lVar5 + 0x28e) = (short)(iVar10 / 0x10);
    if (sVar9 < -0x5a) {
      uVar11 = (ulong)((int)uVar11 - 2);
    }
  }
LAB_00212bc9:
  lVar13 = *(long *)(param_1 + 0x20);
  if (*(int *)(lVar13 + 0x3c) == 0x4324) {
    uVar14 = *(uint *)(lVar13 + 0x40);
    param_3 = (short *)(ulong)uVar14;
    if ((uVar14 == 5) || (uVar14 == 2)) {
      *(undefined1 *)(lVar13 + 0xa8) = uVar2;
    }
  }
  auVar16._8_8_ = param_3;
  auVar16._0_8_ = uVar11;
  return auVar16;
}

