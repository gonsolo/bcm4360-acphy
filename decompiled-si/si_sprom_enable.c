
void si_sprom_enable(long param_1,undefined1 param_2)

{
  if ((*(byte *)(param_1 + 0x1b) & 0x10) != 0) {
    si_pmu_sprom_enable(param_1,*(undefined8 *)(param_1 + 0x58),param_2);
  }
  return;
}

