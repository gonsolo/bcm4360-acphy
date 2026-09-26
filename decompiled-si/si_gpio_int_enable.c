
undefined8 si_gpio_int_enable(long param_1,char param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xffffffff;
  if (10 < *(int *)(param_1 + 0x14)) {
    uVar1 = FUN_00122a5d(param_1,0x24,1,param_2 != '\0');
  }
  return uVar1;
}

