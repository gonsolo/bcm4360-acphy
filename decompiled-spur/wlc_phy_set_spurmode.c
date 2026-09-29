
void wlc_phy_set_spurmode(long param_1,undefined2 param_2)

{
  wlc_phy_get_spurmode(param_1,param_2);
  if (*(char *)(*(long *)(param_1 + 0x138) + 0x338) != *(char *)(param_1 + 0x1164)) {
    wlc_phy_setup_spurmode(param_1);
    *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x338) = *(undefined1 *)(param_1 + 0x1164);
  }
  return;
}

