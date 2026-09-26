
undefined8 wlc_bmac_set_btswitch(long param_1,char param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  
  iVar1 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c);
  if (((iVar1 == 0xa9a7) || (iVar1 == 0x4331)) &&
     (((iVar1 = *(int *)(*(long *)(param_1 + 0xb8) + 0x28), iVar1 == 0x10e ||
       (((iVar1 == 0xe4 || (iVar1 == 0x5c6)) || (iVar1 == 0xef)))) || (iVar1 == 0x10f)))) {
    if (param_2 == -1) {
      if (*(char *)(param_1 + 0x10c) != '\0') {
        wlc_bmac_set_ctrl_bt_shd0(param_1,1);
      }
      si_gpioout(*(undefined8 *)(param_1 + 0xb8),0x10,0,0);
      uVar3 = *(undefined8 *)(param_1 + 0xb8);
      uVar2 = 0;
    }
    else {
      uVar4 = 0x10;
      if (param_2 != '\x01') {
        uVar4 = 0;
      }
      wlc_bmac_set_ctrl_bt_shd0(param_1,0);
      si_gpioout(*(undefined8 *)(param_1 + 0xb8),0x10,uVar4,0);
      uVar3 = *(undefined8 *)(param_1 + 0xb8);
      uVar2 = 0x10;
    }
    si_gpioouten(uVar3,0x10,uVar2,0);
  }
  else {
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) != 0xb) {
      return 0xffffffe9;
    }
    if (*(char *)(param_1 + 0x10c) == '\0') {
      return 0xfffffffc;
    }
    wlc_phy_set_femctrl_bt_wlan_ovrd(*(undefined8 *)(*(long *)(param_1 + 0xe8) + 0x28),(int)param_2)
    ;
  }
  *(char *)(param_1 + 0x1bc) = param_2;
  return 0;
}

