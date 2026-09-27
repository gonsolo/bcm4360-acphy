
uint wlc_phy_classifier_acphy(undefined8 param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = phy_reg_read(param_1,0x140);
  uVar1 = uVar1 & ~param_2 | param_2 & param_3;
  phy_reg_write(param_1,0x140,uVar1 & 0xffff);
  return uVar1;
}

