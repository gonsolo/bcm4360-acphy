
void wlc_bmac_led_hw_deinit(long param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = *(char *)(param_1 + 0x187) == '\0';
  if (bVar1) {
    wlc_bmac_xtal(param_1,1);
  }
  if (*(long *)(param_1 + 0xb8) != 0) {
    si_gpioout(*(long *)(param_1 + 0xb8),param_2,0,0);
    si_gpioouten(*(undefined8 *)(param_1 + 0xb8),param_2,0,0);
    si_gpioled(*(undefined8 *)(param_1 + 0xb8),param_2,0);
  }
  if (bVar1) {
    wlc_bmac_xtal(param_1,0);
  }
  return;
}

