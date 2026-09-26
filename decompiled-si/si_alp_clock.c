
ulong si_alp_clock(long param_1)

{
  ulong uVar1;
  
  if ((*(byte *)(param_1 + 0x1b) & 0x10) == 0) {
    if ((*(int *)(param_1 + 0x3c) == 0xcf1a) ||
       (uVar1 = 20000000, *(int *)(param_1 + 0x3c) == 0xcf12)) {
      uVar1 = (ulong)((-(uint)(*(int *)(param_1 + 0x44) == 0) & 25000000) + 100000000);
    }
  }
  else {
    uVar1 = si_pmu_alp_clock(param_1,*(undefined8 *)(param_1 + 0x58));
  }
  return uVar1;
}

