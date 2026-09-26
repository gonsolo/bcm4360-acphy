
void si_core_disable(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    sb_core_disable();
  }
  else if ((iVar1 == 3) || (iVar1 == 1)) {
    ai_core_disable();
  }
  return;
}

