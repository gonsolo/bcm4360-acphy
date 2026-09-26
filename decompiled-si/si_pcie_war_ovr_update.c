
void si_pcie_war_ovr_update(long param_1,undefined1 param_2)

{
  if ((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x820)) {
    pcie_war_ovr_aspm_update(*(undefined8 *)(param_1 + 0x90),param_2);
  }
  return;
}

