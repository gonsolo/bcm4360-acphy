
void wlc_phy_pwrctrl_shortwindow_upd_acphy(undefined8 param_1,char param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0x100;
  if (param_2 == '\0') {
    uVar1 = 0x400;
  }
  phy_reg_mod(param_1,0x71,0x700,uVar1);
  return;
}

