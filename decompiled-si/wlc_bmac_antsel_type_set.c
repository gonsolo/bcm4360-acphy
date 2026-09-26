
void wlc_bmac_antsel_type_set(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x1a1) = param_2;
  wlc_phy_antsel_type_set(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),param_2);
  return;
}

