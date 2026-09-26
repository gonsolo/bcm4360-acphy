
undefined8 si_gpiotimerval(long param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  
  uVar1 = 0xffffffff;
  if (0xf < *(int *)(param_1 + 0x14)) {
    uVar1 = FUN_00122a5d(param_1,0x88,param_2,param_3);
  }
  return uVar1;
}

