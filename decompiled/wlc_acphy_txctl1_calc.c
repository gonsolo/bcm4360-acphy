
uint wlc_acphy_txctl1_calc(long *param_1,uint param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  undefined2 uVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  uint uVar10;
  uint uVar11;
  
  uVar10 = param_2 & 0x70000;
  uVar1 = *(uint *)(param_1 + 0xa3);
  uVar5 = wlc_stf_spatial_expansion_get();
  bVar2 = wlc_stf_get_pwrperrate(param_1,param_2,uVar5);
  uVar11 = (uint)bVar2;
  if (*(int *)(*(long *)(*param_1 + 0x100) + 0x3c) != 0x4360) goto LAB_00131e68;
  bVar3 = wlc_phy_txpower_get_target_max(*(undefined8 *)(param_1[8] + 0x10));
  iVar6 = wlc_phy_tssivisible_thresh(*(undefined8 *)(param_1[8] + 0x10));
  if ((int)((uint)bVar3 + (uint)bVar2 * -2) < iVar6) {
    if (uVar10 == 0x20000) {
      uVar8 = 0x1800;
      uVar9 = *(undefined8 *)(param_1[8] + 0x10);
    }
    else if (uVar10 == 0x30000) {
      uVar8 = 0x2000;
      uVar9 = *(undefined8 *)(param_1[8] + 0x10);
    }
    else {
      if (uVar10 != 0x10000) goto LAB_00131e3c;
      uVar8 = 0x1000;
      uVar9 = *(undefined8 *)(param_1[8] + 0x10);
    }
    cVar4 = wlc_phy_get_olpc_pwroffset(uVar9,uVar8);
  }
  else {
LAB_00131e3c:
    cVar4 = '\0';
  }
  bVar3 = (char)(cVar4 << 2) >> 2;
  if (bVar3 != 0) {
    uVar11 = (uint)bVar3 + (uint)(byte)((char)(bVar2 << 2) >> 2);
    uVar7 = 0xe0;
    if (-0x21 < (char)uVar11) {
      uVar7 = uVar11;
    }
    uVar11 = 0x1f;
    if ((char)uVar7 < ' ') {
      uVar11 = uVar7;
    }
    uVar11 = uVar11 & 0x3f;
  }
LAB_00131e68:
  return (uVar11 & 0x3f) * 8 | (int)((uVar1 & 0x700) >> 8) >> ((char)(uVar10 >> 0x10) - 1U & 0x1f);
}

