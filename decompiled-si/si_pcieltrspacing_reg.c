
undefined8 si_pcieltrspacing_reg(long param_1)

{
  undefined8 uVar1;
  
  if ((*(int *)(param_1 + 4) == 1) &&
     ((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)))) {
    uVar1 = pcieltrspacing_reg(*(undefined8 *)(param_1 + 0x90));
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

