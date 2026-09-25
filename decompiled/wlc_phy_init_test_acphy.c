
void wlc_phy_init_test_acphy(undefined8 param_1)

{
  wlc_btcx_override_enable();
  wlc_phy_txpwrctrl_enable_acphy(param_1,0);
  wlc_phy_cals_acphy(param_1,0);
  return;
}

