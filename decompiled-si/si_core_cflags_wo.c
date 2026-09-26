
void si_core_cflags_wo(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    sb_core_cflags_wo();
  }
  else if ((iVar1 == 3) || (iVar1 == 1)) {
    ai_core_cflags_wo();
  }
  return;
}

