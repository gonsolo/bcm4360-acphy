
void wlc_scb_ratesel_rssi_enable(long param_1)

{
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x114) + 1;
  return;
}

