
undefined8 si_gpioled(long param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  
  uVar1 = 0xffffffff;
  if (0xf < *(int *)(param_1 + 0x14)) {
    uVar1 = FUN_00122a5d(param_1,0x8c,param_2,param_3);
  }
  return uVar1;
}

