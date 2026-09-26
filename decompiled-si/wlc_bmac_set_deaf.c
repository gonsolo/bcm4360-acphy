
void wlc_bmac_set_deaf(long param_1,undefined1 param_2)

{
  wlc_phy_set_deaf(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),param_2);
  return;
}

