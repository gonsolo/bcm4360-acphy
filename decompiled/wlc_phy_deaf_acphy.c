
void wlc_phy_deaf_acphy(long param_1,char param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = *(long *)(param_1 + 0x138);
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  if (param_2 == '\0') {
    if (*(short *)(lVar1 + 0xc) == 0) goto LAB_001988c7;
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
    if (*(short *)(lVar1 + 0xc) != 0) goto LAB_001988c7;
  }
  wlc_phy_stay_in_carriersearch_acphy(param_1,uVar2);
LAB_001988c7:
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return;
}

