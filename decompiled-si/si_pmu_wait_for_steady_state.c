
undefined8 si_pmu_wait_for_steady_state(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int local_3c [3];
  
  uVar3 = 0;
  local_3c[0] = 0;
  while( true ) {
    cVar2 = si_pmu_wait_for_res_pending(param_1,param_2,20000,1,local_3c);
    iVar1 = local_3c[0];
    if (cVar2 != '\0') {
      return 1;
    }
    cVar2 = si_pmu_wait_for_res_pending(param_1,param_2,0x40,0,local_3c);
    if (cVar2 != '\0') break;
    uVar3 = uVar3 + local_3c[0] + iVar1;
    if (19999 < uVar3) {
      return 1;
    }
  }
  return 0;
}

