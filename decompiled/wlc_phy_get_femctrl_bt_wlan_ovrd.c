
undefined1 wlc_phy_get_femctrl_bt_wlan_ovrd(long param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0xff;
  if (*(int *)(param_1 + 0x160) == 0xb) {
    uVar1 = wlc_phy_get_femctrl_bt_wlan_ovrd_acphy();
  }
  return uVar1;
}

