
int si_pmu_get_pmutime_diff(undefined8 param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_3;
  iVar2 = si_pmu_get_pmutimer();
  *param_3 = iVar2;
  return iVar2 - iVar1;
}

