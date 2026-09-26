
uint wlc_lcn40phy_avg_tssi_reg_iovar(undefined8 param_1)

{
  uint uVar1;
  
  uVar1 = phy_reg_read(param_1,0x63e);
  return uVar1 & 0x1ff;
}

