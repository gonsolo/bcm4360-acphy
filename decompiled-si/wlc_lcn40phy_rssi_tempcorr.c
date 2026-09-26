
uint wlc_lcn40phy_rssi_tempcorr(long param_1,undefined1 param_2)

{
  short sVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  short sVar5;
  
  lVar3 = wlc_phy_getlcnphy_common();
  sVar1 = wlc_lcn40phy_tempsense(param_1,param_2);
  iVar2 = wlc_phy_chanspec_bandrange_get(param_1,*(undefined2 *)(param_1 + 0x17e));
  if (iVar2 == 1) {
    sVar5 = (short)*(undefined4 *)(lVar3 + 0x534);
    goto LAB_001f9ea3;
  }
  if (iVar2 < 2) {
    if (iVar2 == 0) {
      sVar5 = *(short *)(lVar3 + 0x532);
      goto LAB_001f9ea3;
    }
  }
  else {
    if (iVar2 == 2) {
      sVar5 = *(short *)(lVar3 + 0x536);
      goto LAB_001f9ea3;
    }
    if (iVar2 == 3) {
      sVar5 = (short)*(undefined4 *)(lVar3 + 0x538);
      goto LAB_001f9ea3;
    }
  }
  sVar5 = 0;
LAB_001f9ea3:
  sVar5 = (sVar1 + -0x19) * sVar5;
  uVar4 = (int)sVar5 >> 0x1f;
  uVar4 = ((int)sVar5 ^ uVar4) - uVar4 >> 8;
  if (sVar5 < 0) {
    uVar4 = -uVar4;
  }
  return uVar4;
}

