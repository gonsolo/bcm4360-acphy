
void si_pmu_paref_ldo_enable(long param_1,undefined8 param_2,char param_3)

{
  sbyte sVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x3c);
  if ((iVar2 == 0x4328) || (iVar2 == 0x5354)) {
    sVar1 = 8;
  }
  else {
    sVar1 = 2;
    if (iVar2 != 0x4312) {
      return;
    }
  }
  iVar2 = 0;
  if (param_3 != '\0') {
    iVar2 = 1 << sVar1;
  }
  si_corereg(param_1,0,0x618,1 << sVar1,iVar2);
  return;
}

