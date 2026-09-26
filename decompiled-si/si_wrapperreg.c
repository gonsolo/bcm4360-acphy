
undefined8 si_wrapperreg(int *param_1)

{
  undefined8 uVar1;
  
  if ((*param_1 != 3) && (*param_1 != 1)) {
    return 0;
  }
  uVar1 = ai_wrap_reg();
  return uVar1;
}

