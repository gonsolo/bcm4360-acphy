
undefined8 wlc_bmac_4331_epa_init(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = *(long *)(param_1 + 0xb8);
  if ((*(int *)(lVar1 + 4) == 1) &&
     (((*(int *)(lVar1 + 0x3c) == 0xa9a7 || (*(int *)(lVar1 + 0x3c) == 0x4331)) &&
      (*(int *)(lVar1 + 0x44) == 9 || *(int *)(lVar1 + 0x44) == 0xb)))) {
    si_gpiopull(lVar1,0,0x20,0);
    si_gpiopull(*(undefined8 *)(param_1 + 0xb8),1,0x20,0x20);
    si_gpiocontrol(*(undefined8 *)(param_1 + 0xb8),4,0,0);
    si_gpioout(*(undefined8 *)(param_1 + 0xb8),4,0,0);
    si_gpioouten(*(undefined8 *)(param_1 + 0xb8),4,0,0);
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

