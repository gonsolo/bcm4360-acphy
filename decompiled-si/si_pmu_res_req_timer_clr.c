
void si_pmu_res_req_timer_clr(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = 0x3000000;
  if (*(int *)(param_1 + 0x3c) == 0x4328) {
    uVar1 = 0xc00;
  }
  FUN_00122a5d(param_1,0x644,uVar1,0);
  FUN_00122a5d(param_1,0x644,0,0);
  return;
}

