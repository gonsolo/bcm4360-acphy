
void wlc_phy_set_femctrl_bt_wlan_ovrd_acphy(long param_1,char param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  uVar1 = 1;
  if (param_2 != '\x01') {
    if (param_2 != '\0') {
      phy_reg_mod(param_1,0x418,2,0);
      uVar1 = 0;
      uVar2 = 1;
      goto LAB_001906b1;
    }
    uVar1 = 0;
  }
  phy_reg_mod(param_1,0x418,1,uVar1);
  uVar1 = 2;
  uVar2 = 2;
LAB_001906b1:
  phy_reg_mod(param_1,0x418,uVar2,uVar1);
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return;
}

