
void si_update_masks(long param_1)

{
  if (*(int *)(param_1 + 0x3c) == 0x4335) {
    if ((*(byte *)(param_1 + 0x1b) & 0x10) != 0) {
      si_pmu_res_minmax_update(param_1,*(undefined8 *)(param_1 + 0x58));
    }
    si_ccreg(param_1,0x68c,0xffffffff,0x7ffbfff);
    si_pmu_chipcontrol(param_1,2,0x1000000,0x1000000);
  }
  else if ((*(int *)(param_1 + 0x3c) == 0x4350) && ((*(byte *)(param_1 + 0x1b) & 0x10) != 0)) {
    si_pmu_res_minmax_update(param_1,*(undefined8 *)(param_1 + 0x58));
  }
  return;
}

