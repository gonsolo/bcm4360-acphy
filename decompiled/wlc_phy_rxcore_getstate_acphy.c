
int wlc_phy_rxcore_getstate_acphy(undefined8 param_1)

{
  uint uVar1;
  
  uVar1 = phy_reg_read(param_1,0x401);
  return (int)(uVar1 & 0x70) >> 4;
}

