
void wlc_ratesel_rssi_attach(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  *(undefined8 *)(param_1 + 0x90) = param_2;
  *(undefined8 *)(param_1 + 0x98) = param_3;
  *(undefined8 *)(param_1 + 0xa0) = param_4;
  return;
}

