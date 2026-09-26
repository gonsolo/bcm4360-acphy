
undefined1 si_is_sprom_enabled(long param_1)

{
  undefined1 uVar1;
  
  uVar1 = 1;
  if ((*(byte *)(param_1 + 0x1b) & 0x10) != 0) {
    uVar1 = si_pmu_is_sprom_enabled(param_1,*(undefined8 *)(param_1 + 0x58));
  }
  return uVar1;
}

