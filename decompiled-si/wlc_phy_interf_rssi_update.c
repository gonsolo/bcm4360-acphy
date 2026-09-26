
void wlc_phy_interf_rssi_update(long param_1,undefined2 param_2,char param_3)

{
  if ((((5 < *(uint *)(param_1 + 0x164)) && (*(int *)(param_1 + 0x160) == 4)) ||
      (*(int *)(param_1 + 0x160) == 7)) && (*(char *)(param_1 + 0x240) == (char)param_2)) {
    *(short *)(*(long *)(param_1 + 0x138) + 0x28e) = (short)param_3;
    *(char *)(param_1 + 0x2d0) = param_3;
  }
  if (*(int *)(param_1 + 0x160) == 0xb) {
    wlc_phy_desense_aci_upd_chan_stats_acphy(param_1,param_2,(int)param_3);
  }
  return;
}

