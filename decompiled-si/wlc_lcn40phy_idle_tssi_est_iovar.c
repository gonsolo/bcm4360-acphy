
undefined2 wlc_lcn40phy_idle_tssi_est_iovar(undefined8 param_1,char param_2)

{
  undefined2 uVar1;
  
  if (param_2 == '\0') {
    FUN_001fc94a();
  }
  else {
    FUN_001fceb7();
  }
  FUN_001fbec7(param_1,0);
  FUN_001fbec7(param_1,0xe000);
  uVar1 = phy_reg_read(param_1,0x4a6);
  return uVar1;
}

