
void wlc_bmac_set_txpwr_percent(long param_1,undefined1 param_2)

{
  wlc_phy_txpwr_percent_set(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),param_2);
  return;
}

