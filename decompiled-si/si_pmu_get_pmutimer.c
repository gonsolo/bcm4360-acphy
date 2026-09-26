
int si_pmu_get_pmutimer(undefined8 param_1,long param_2)

{
  int iVar1;
  int iVar2;
  
  param_2 = param_2 + 0x614;
  iVar1 = osl_readl(param_2);
  iVar2 = osl_readl(param_2);
  if (iVar1 != iVar2) {
    iVar1 = osl_readl(param_2);
  }
  return iVar1;
}

