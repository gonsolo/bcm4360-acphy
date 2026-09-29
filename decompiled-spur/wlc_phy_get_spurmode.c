
void wlc_phy_get_spurmode(long param_1,short param_2)

{
  short sVar1;
  long lVar2;
  byte bVar3;
  undefined1 uVar4;
  uint uVar5;
  short *psVar6;
  short *psVar7;
  byte bVar8;
  short *psVar9;
  short *psVar10;
  short *psVar11;
  short *psVar12;
  short *psVar13;
  
  lVar2 = *(long *)(param_1 + 0x138);
  if (*(char *)(param_1 + 0x113e) == '\0') {
    if (*(char *)(lVar2 + 0x34f) == '\0') {
      if ((*(char *)(lVar2 + 0x8e4) == '\x02') ||
         ((*(char *)(lVar2 + 0x8e5) == '\x01' && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)))) {
        bVar3 = 1;
        psVar6 = (short *)0x676506;
        psVar9 = (short *)0x676500;
        psVar10 = (short *)0x6764fa;
        psVar12 = (short *)0x6764b0;
        psVar11 = (short *)0x6764aa;
        psVar7 = (short *)0x676460;
        psVar13 = (short *)0x67644e;
      }
      else {
        bVar3 = 0;
        psVar6 = (short *)0x6765cc;
        psVar9 = (short *)0x6765ca;
        psVar10 = (short *)0x6765c8;
        psVar12 = (short *)0x676580;
        psVar11 = (short *)0x676570;
        psVar7 = (short *)0x676510;
        psVar13 = (short *)0x6f3504;
      }
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559031)[(long)(int)(uint)bVar3 * 9]; bVar8 = bVar8 + 1)
      {
        sVar1 = *psVar13;
        psVar13 = psVar13 + 1;
        if (param_2 == sVar1) {
          uVar4 = 1;
          goto LAB_0018f668;
        }
      }
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559032)[(long)(int)(uint)bVar3 * 9]; bVar8 = bVar8 + 1)
      {
        sVar1 = *psVar7;
        psVar7 = psVar7 + 1;
        if (param_2 == sVar1) goto LAB_0018f666;
      }
      uVar5 = (uint)bVar3;
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559033)[(long)(int)uVar5 * 9]; bVar8 = bVar8 + 1) {
        sVar1 = *psVar12;
        psVar12 = psVar12 + 1;
        if (param_2 == sVar1) {
          uVar4 = 3;
          goto LAB_0018f668;
        }
      }
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559034)[(long)(int)uVar5 * 9]; bVar8 = bVar8 + 1) {
        sVar1 = *psVar11;
        psVar11 = psVar11 + 1;
        if (param_2 == sVar1) {
          uVar4 = 4;
          goto LAB_0018f668;
        }
      }
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559035)[(long)(int)uVar5 * 9]; bVar8 = bVar8 + 1) {
        sVar1 = *psVar10;
        psVar10 = psVar10 + 1;
        if (param_2 == sVar1) {
          uVar4 = 5;
          goto LAB_0018f668;
        }
      }
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559036)[(long)(int)uVar5 * 9]; bVar8 = bVar8 + 1) {
        sVar1 = *psVar9;
        psVar9 = psVar9 + 1;
        if (param_2 == sVar1) {
          uVar4 = 6;
          goto LAB_0018f668;
        }
      }
      for (bVar8 = 0; bVar8 < (byte)(&UNK_00559038)[(long)(int)(uint)bVar3 * 9]; bVar8 = bVar8 + 1)
      {
        sVar1 = *psVar6;
        psVar6 = psVar6 + 1;
        if (param_2 == sVar1) {
          uVar4 = 8;
          goto LAB_0018f668;
        }
      }
LAB_0018f666:
      uVar4 = 2;
LAB_0018f668:
      *(undefined1 *)(param_1 + 0x1164) = uVar4;
    }
    else {
      *(undefined1 *)(param_1 + 0x1164) = 8;
    }
  }
  else {
    *(short *)(param_1 + 0x1140) = param_2;
  }
  return;
}

