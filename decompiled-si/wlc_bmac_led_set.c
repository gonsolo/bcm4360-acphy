
void wlc_bmac_led_set(long param_1,int param_2,undefined1 param_3)

{
  *(undefined1 *)((long)param_2 * 0x18 + 0xc + *(long *)(param_1 + 0x198)) = param_3;
  return;
}

