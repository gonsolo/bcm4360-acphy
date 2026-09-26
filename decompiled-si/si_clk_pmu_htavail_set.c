
void si_clk_pmu_htavail_set(long param_1,undefined1 param_2)

{
  si_pmu_minresmask_htavail_set(param_1,*(undefined8 *)(param_1 + 0x58),param_2);
  return;
}

