
void wlc_phy_set_femctrl_bt_wlan_ovrd(long param_1,char param_2)

{
  if (*(int *)(param_1 + 0x160) == 0xb) {
    *(char *)(*(long *)(param_1 + 0x138) + 0x32e) = param_2;
    wlc_phy_set_femctrl_bt_wlan_ovrd_acphy(param_1,(int)param_2);
  }
  return;
}

