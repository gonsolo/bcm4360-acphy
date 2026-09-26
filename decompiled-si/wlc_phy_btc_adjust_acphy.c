
void wlc_phy_btc_adjust_acphy(long param_1,undefined1 param_2)

{
  if (*(uint *)(param_1 + 0x164) < 2) {
    wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    FUN_00190029(param_1,param_2);
    FUN_0019a2eb(param_1,param_2);
    wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  return;
}

