
undefined8 si_flag_alt(int *param_1)

{
  undefined8 uVar1;
  
  if ((*param_1 != 3) && (*param_1 != 1)) {
    return 0;
  }
  uVar1 = ai_flag_alt();
  return uVar1;
}

