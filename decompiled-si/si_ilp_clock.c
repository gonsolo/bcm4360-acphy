
undefined8 si_ilp_clock(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = 32000;
  if ((*(byte *)(param_1 + 0x1b) & 0x10) != 0) {
    uVar1 = si_pmu_ilp_clock(param_1,*(undefined8 *)(param_1 + 0x58));
  }
  return uVar1;
}

