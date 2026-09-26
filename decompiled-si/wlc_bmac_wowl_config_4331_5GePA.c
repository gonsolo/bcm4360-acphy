
void wlc_bmac_wowl_config_4331_5GePA(long param_1,char param_2,char param_3)

{
  ushort *puVar1;
  
  si_chipcontrl_epa4331(*(undefined8 *)(param_1 + 0xb8),0);
  if (param_3 == '\0') {
    si_chipcontrl_epa4331(*(undefined8 *)(param_1 + 0xb8),1);
  }
  else {
    si_chipcontrl_epa4331_wowl(*(undefined8 *)(param_1 + 0xb8),1);
    if (param_2 != '\0') {
      puVar1 = (ushort *)(*(long *)(param_1 + 0xe8) + 8);
      *puVar1 = *puVar1 | 8;
      FUN_001634a6(param_1,*(long *)(param_1 + 0xe8) + 8);
      si_gpiocontrol(*(undefined8 *)(param_1 + 0xb8),4,4,0);
      si_gpioout(*(undefined8 *)(param_1 + 0xb8),4,0,0);
      si_gpioouten(*(undefined8 *)(param_1 + 0xb8),4,4,0);
    }
  }
  return;
}

