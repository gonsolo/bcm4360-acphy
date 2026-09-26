
undefined8 si_intflag(int *param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    uVar2 = sb_intflag();
  }
  else {
    if ((iVar1 != 3) && (iVar1 != 1)) {
      return 0;
    }
    uVar2 = osl_readl(param_1[500] + 0x100);
  }
  return uVar2;
}

