
void wlc_phy_stay_in_carriersearch_acphy(long param_1,char param_2)

{
  long lVar1;
  short sVar2;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if (param_2 == '\0') {
    sVar2 = (short)*(undefined4 *)(lVar1 + 0xc) + -1;
    *(short *)(lVar1 + 0xc) = sVar2;
    if (sVar2 == 0) {
      wlc_phy_classifier_acphy(param_1,7,~-((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) + 7);
      wlc_phy_ofdm_crs_acphy(param_1,1);
      FUN_001986fc(param_1,1);
      phy_reg_write(param_1,0x339,*(undefined2 *)(lVar1 + 0x904));
    }
  }
  else {
    if (*(short *)(lVar1 + 0xc) == 0) {
      wlc_phy_classifier_acphy(param_1,7,4);
      wlc_phy_ofdm_crs_acphy(param_1,0);
      FUN_001986fc(param_1,0);
      phy_reg_write(param_1,0x339,0);
    }
    *(short *)(lVar1 + 0xc) = *(short *)(lVar1 + 0xc) + 1;
    wlc_phy_resetcca_acphy(param_1);
  }
  return;
}

