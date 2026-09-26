
undefined8 si_pmu_def_alp_clock(long param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 != 0x4350) {
    if (uVar1 < 0x4351) {
      if ((uVar1 != 0x4324) && (uVar1 != 0x4335)) {
        return 20000000;
      }
    }
    else if (1 < uVar1 - 0xa8ea) {
      return 20000000;
    }
  }
  return 37400000;
}

