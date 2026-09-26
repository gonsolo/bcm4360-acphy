
undefined2 wlc_lcnphy_idle_tssi_est_iovar(undefined8 param_1,char param_2)

{
  undefined2 uVar1;
  
  if (param_2 == '\0') {
    FUN_001ed17c();
  }
  else {
    wlc_lcnphy_tx_pwr_ctrl_init();
  }
  wlc_lcnphy_set_tx_pwr_ctrl(param_1,0);
  wlc_lcnphy_set_tx_pwr_ctrl(param_1,0xc000);
  uVar1 = phy_reg_read(param_1,0x4a6);
  return uVar1;
}

