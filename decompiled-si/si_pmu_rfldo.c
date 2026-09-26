
void si_pmu_rfldo(long param_1,char param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x3c);
  if (((iVar1 == 0x4360) || (iVar1 == 0xaa06)) || (iVar1 == 0x4352)) {
    si_pmu_regcontrol(param_1,0,2,-(param_2 == '\0') & 2);
  }
  return;
}

