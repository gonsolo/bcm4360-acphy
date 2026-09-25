
byte wlc_phy_get_femctrl_bt_wlan_ovrd_acphy(long param_1)

{
  byte bVar1;
  ulong uVar2;
  byte bVar3;
  
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  bVar1 = phy_reg_read(param_1,0x418);
  uVar2 = phy_reg_read(param_1,0x418);
  bVar3 = 0xff;
  if ((uVar2 & 2) != 0) {
    bVar3 = bVar1 & 1;
  }
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return bVar3;
}

