
void si_pmu_res_minmax_update(long param_1)

{
  undefined4 uVar1;
  long lVar2;
  int local_30;
  int local_2c [3];
  
  local_2c[0] = 0;
  local_30 = 0;
  uVar1 = si_coreidx();
  lVar2 = si_setcoreidx(param_1,0);
  if (*(int *)(param_1 + 0x3c) == 0x4335) {
    local_2c[0] = 1;
  }
  else if (*(int *)(param_1 + 0x3c) == 0x4350) {
    FUN_00111ef0(param_1,local_2c,&local_30);
    local_30 = 0;
  }
  if (local_2c[0] != 0) {
    osl_writel(local_2c[0],lVar2 + 0x618);
  }
  if (local_30 != 0) {
    osl_writel(local_30,lVar2 + 0x61c);
  }
  si_setcoreidx(param_1,uVar1);
  return;
}

