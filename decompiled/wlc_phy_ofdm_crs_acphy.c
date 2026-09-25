
void wlc_phy_ofdm_crs_acphy(undefined8 param_1,char param_2)

{
  undefined8 uVar1;
  
  if (param_2 == '\0') {
    phy_reg_mod(param_1,0x2ed,0x10,0);
    phy_reg_mod(param_1,0x2f1,0x10,0);
    phy_reg_mod(param_1,0x2f5,0x10,0);
    uVar1 = 0;
  }
  else {
    phy_reg_mod(param_1,0x2ed,0x10,0x10);
    phy_reg_mod(param_1,0x2f1,0x10,0x10);
    phy_reg_mod(param_1,0x2f5,0x10,0x10);
    uVar1 = 0x10;
  }
  phy_reg_mod(param_1,0x2f9,0x10,uVar1);
  return;
}

