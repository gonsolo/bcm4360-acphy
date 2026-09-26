
void wlapi_bmac_btc_period_get(long *param_1,undefined2 *param_2,undefined1 *param_3)

{
  *param_2 = (short)*(undefined4 *)(*(long *)(*param_1 + 0xb0) + 0x1c);
  *param_3 = *(undefined1 *)(*(long *)(*param_1 + 0xb0) + 0x16);
  return;
}

