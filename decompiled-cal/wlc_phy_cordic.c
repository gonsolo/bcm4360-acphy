
void wlc_phy_cordic(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  
  param_2[1] = 0x9b75;
  *param_2 = 0;
  uVar7 = param_1 >> 0x1f | 1;
  iVar9 = (int)(uVar7 * 0xb40000 + param_1) % 0x1680000 + uVar7 * -0xb40000;
  if (iVar9 < 0) {
    iVar4 = -((-iVar9 >> 0xf) + 1 >> 1);
  }
  else {
    iVar4 = (iVar9 >> 0xf) + 1 >> 1;
  }
  if (iVar4 < 0x5b) {
    if ((-1 < iVar9) || (-0x5b < -((-iVar9 >> 0xf) + 1 >> 1))) {
      iVar4 = 1;
      goto LAB_001b30dd;
    }
    iVar9 = iVar9 + 0xb40000;
  }
  else {
    iVar9 = iVar9 + -0xb40000;
  }
  iVar4 = -1;
LAB_001b30dd:
  piVar10 = &DAT_0055ae50;
  iVar8 = 0;
  iVar5 = 0;
  do {
    iVar1 = param_2[1];
    iVar2 = *param_2;
    bVar6 = (byte)iVar8;
    if (iVar5 < iVar9) {
      iVar3 = *piVar10;
      *param_2 = (iVar1 >> (bVar6 & 0x1f)) + iVar2;
      param_2[1] = iVar1 - (iVar2 >> (bVar6 & 0x1f));
    }
    else {
      iVar3 = -*piVar10;
      *param_2 = iVar2 - (iVar1 >> (bVar6 & 0x1f));
      param_2[1] = (iVar2 >> (bVar6 & 0x1f)) + iVar1;
    }
    iVar5 = iVar5 + iVar3;
    iVar8 = iVar8 + 1;
    piVar10 = piVar10 + 1;
  } while (iVar8 != 0x12);
  param_2[1] = param_2[1] * iVar4;
  *param_2 = iVar4 * *param_2;
  return;
}

