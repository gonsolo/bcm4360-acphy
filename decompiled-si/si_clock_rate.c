
undefined1  [16] si_clock_rate(int param_1,uint param_2,ulong param_3)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  undefined1 auVar13 [16];
  
  if (param_1 == 0x28000) {
    uVar3 = param_3 & 1;
    param_3 = param_3 & 0xffffffffffffff01;
    uVar2 = 120000000;
    uVar5 = param_3;
    if (uVar3 == 0) goto LAB_0011eea8;
LAB_0011eea3:
    uVar2 = 100000000;
    uVar5 = param_3;
    goto LAB_0011eea8;
  }
  uVar1 = param_2 & 0x3f;
  uVar6 = (param_2 & 0x3f00) >> 8;
  bVar11 = param_1 == 0x30000;
  bVar12 = param_1 != 0x10000;
  if (((!bVar12 || bVar11) || (param_1 == 0x38000)) || (param_1 == 0x8000)) {
    uVar8 = uVar1 - 2;
    uVar1 = 0;
    if (uVar8 < 0x20) {
      uVar1 = *(uint *)(&DAT_0050d600 + (ulong)uVar8 * 4);
    }
    uVar6 = uVar6 + 5;
  }
  else if (param_1 == 0x20000) {
    uVar1 = uVar1 + 2;
    uVar6 = uVar6 + 2;
  }
  else if (param_1 == 0x18000) goto LAB_0011eea3;
  if ((param_1 == 0x38000) || (bVar11)) {
    uVar1 = uVar1 * uVar6 * 12500000;
  }
  else {
    uVar1 = uVar1 * uVar6 * 24000000;
  }
  uVar2 = (ulong)uVar1;
  uVar5 = param_3;
  if (uVar1 == 0) goto LAB_0011eea8;
  uVar6 = (uint)param_3;
  uVar8 = (uVar6 & 0x3f00) >> 8;
  uVar10 = (uVar6 & 0x3f0000) >> 0x10;
  uVar1 = (uVar6 & 0x1f000000) >> 0x18;
  if (((bVar12 && !bVar11) && (param_1 != 0x8000)) && (param_1 != 0x38000)) {
    uVar3 = uVar2;
    if ((uVar1 & 1) == 0) {
      uVar5 = (ulong)((uVar6 & 0x3f) + 2);
      uVar3 = uVar2 / uVar5;
      uVar5 = uVar2 % uVar5;
    }
    uVar4 = uVar3;
    if ((uVar1 & 2) == 0) {
      uVar4 = uVar3 / (uVar8 + 3);
      uVar5 = uVar3 % (ulong)(uVar8 + 3);
    }
    uVar2 = uVar4;
    if ((param_3 & 0x4000000) == 0) {
      uVar5 = (ulong)(uVar10 + 2);
      uVar2 = uVar4 / uVar5;
      uVar5 = uVar4 % uVar5;
    }
    goto LAB_0011eea8;
  }
  uVar6 = (uVar6 & 0x3f) - 2;
  uVar7 = 0;
  if (uVar6 < 0x20) {
    uVar7 = *(uint *)(&DAT_0050d600 + (ulong)uVar6 * 4);
  }
  if (bVar12 && !bVar11) {
    iVar9 = 0;
    if (uVar8 - 2 < 0x20) {
      iVar9 = *(int *)(&DAT_0050d600 + (ulong)(uVar8 - 2) * 4);
    }
  }
  else {
    iVar9 = uVar8 + 5;
  }
  uVar10 = uVar10 - 2;
  uVar5 = 0;
  if (uVar10 < 0x20) {
    uVar5 = (ulong)*(uint *)(&DAT_0050d600 + (ulong)uVar10 * 4);
  }
  if (uVar1 != 4) {
    if (uVar1 < 5) {
      if (uVar1 != 1) {
        if (uVar1 != 2) {
LAB_0011ee62:
          uVar2 = 0;
          goto LAB_0011eea8;
        }
        uVar7 = uVar7 * iVar9;
        goto LAB_0011ee73;
      }
      uVar7 = uVar7 * iVar9;
    }
    else {
      if (uVar1 == 8) goto LAB_0011eea8;
      if (uVar1 != 0x11) goto LAB_0011ee62;
    }
    uVar7 = uVar7 * (int)uVar5;
  }
LAB_0011ee73:
  uVar5 = uVar2 % (ulong)uVar7;
  uVar2 = uVar2 / uVar7;
LAB_0011eea8:
  auVar13._8_8_ = uVar5;
  auVar13._0_8_ = uVar2;
  return auVar13;
}

