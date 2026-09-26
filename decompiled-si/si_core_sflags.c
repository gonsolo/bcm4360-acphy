
undefined8 si_core_sflags(int *param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    uVar2 = sb_core_sflags();
  }
  else {
    if ((iVar1 != 3) && (iVar1 != 1)) {
      return 0;
    }
    uVar2 = ai_core_sflags();
  }
  return uVar2;
}

