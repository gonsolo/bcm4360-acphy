
void wlc_phy_stop_bt_toggle_acphy(long param_1)

{
  byte bVar1;
  byte bVar2;
  long lVar3;
  undefined8 uVar4;
  byte bVar5;
  
  lVar3 = *(long *)(param_1 + 0x20);
  bVar1 = *(byte *)(lVar3 + 0xa7);
  bVar2 = *(byte *)(lVar3 + 0xa6);
  if (((*(uint *)(lVar3 + 100) & 0x400000) != 0) &&
     (bVar5 = ~-((*(uint *)(lVar3 + 100) & 0x800000) == 0) + 2,
     *(char *)(*(long *)(param_1 + 0x138) + 0x32e) == -1)) {
    wlc_phyreg_enter();
    if (((bVar5 & bVar2) != 0) || (uVar4 = 1, (bVar5 & bVar1) != 0)) {
      uVar4 = 0xffffffff;
    }
    wlc_phy_set_femctrl_bt_wlan_ovrd_acphy(param_1,uVar4);
    wlc_phyreg_exit(param_1);
  }
  return;
}

