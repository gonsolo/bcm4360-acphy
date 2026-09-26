
void wlc_phy_rssi_cal_nphy(long param_1)

{
  if (*(uint *)(param_1 + 0x164) < 0x13) {
    if (*(uint *)(param_1 + 0x164) < 3) {
      FUN_0023fb30(param_1,2);
      FUN_0023fb30(param_1,0);
      FUN_0023fb30(param_1,1);
    }
    else {
      FUN_00240133();
    }
  }
  return;
}

