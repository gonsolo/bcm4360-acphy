
void wlc_phy_trigger_cals_for_btc_adjust(long param_1)

{
  wlc_phy_cal_perical_mphase_reset();
  if (*(int *)(param_1 + 0x160) == 4) {
    *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x382) = 1;
  }
  FUN_001b37d0(param_1,0);
  return;
}

