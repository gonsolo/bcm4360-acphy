
void si_setint(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    sb_setint();
  }
  else if ((iVar1 == 3) || (iVar1 == 1)) {
    ai_setint();
  }
  return;
}

