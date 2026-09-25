
void wlc_phy_desense_aci_upd_chan_stats_acphy
               (undefined8 param_1,undefined2 param_2,undefined1 param_3)

{
  long lVar1;
  
  lVar1 = FUN_00193c3b(param_1,param_2,0);
  if (lVar1 != 0) {
    *(undefined1 *)(lVar1 + 0x19) = param_3;
  }
  return;
}

