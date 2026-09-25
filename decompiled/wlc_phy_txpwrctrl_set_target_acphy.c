
void wlc_phy_txpwrctrl_set_target_acphy(undefined8 param_1,undefined1 param_2,char param_3)

{
  undefined8 uVar1;
  
  if (param_3 == '\x01') {
    uVar1 = 0x846;
  }
  else if (param_3 == '\0') {
    uVar1 = 0x646;
  }
  else {
    if (param_3 != '\x02') {
      return;
    }
    uVar1 = 0xa46;
  }
  phy_reg_mod(param_1,uVar1,0xff,param_2);
  return;
}

