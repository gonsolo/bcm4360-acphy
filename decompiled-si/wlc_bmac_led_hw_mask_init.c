
void wlc_bmac_led_hw_mask_init(long param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x180) = param_2;
  return;
}

