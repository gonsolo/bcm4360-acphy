
uint si_gpioreserve(long param_1,uint param_2,char param_3)

{
  uint uVar1;
  
  if ((((param_3 == '\0') || (*(int *)(param_1 + 4) != 0)) || (param_2 == 0)) ||
     (((param_2 - 1 & param_2) != 0 || ((param_2 & DAT_006f07b4) != 0)))) {
    uVar1 = 0xffffffff;
  }
  else {
    DAT_006f07b4 = DAT_006f07b4 | param_2;
    uVar1 = DAT_006f07b4;
  }
  return uVar1;
}

