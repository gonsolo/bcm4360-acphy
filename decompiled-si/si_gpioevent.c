
undefined8 si_gpioevent(long param_1,int param_2)

{
  undefined8 uVar1;
  
  if (*(int *)(param_1 + 0x14) < 0xb) {
LAB_00124a49:
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0x78;
    if ((param_2 != 0) && (uVar1 = 0x7c, param_2 != 1)) {
      if (param_2 != 2) goto LAB_00124a49;
      uVar1 = 0x84;
    }
    uVar1 = FUN_00122a5d(param_1,uVar1);
  }
  return uVar1;
}

