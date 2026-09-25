
void wlc_phy_cal_perical_mphase_restart(long param_1)

{
  *(undefined1 *)(*(long *)(param_1 + 0xf58) + 1) = 1;
  *(undefined1 *)(*(long *)(param_1 + 0xf58) + 2) = 0;
  return;
}

