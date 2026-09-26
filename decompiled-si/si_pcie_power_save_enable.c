
void si_pcie_power_save_enable(long param_1,undefined1 param_2)

{
  if ((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x820)) {
    pcie_power_save_enable(*(undefined8 *)(param_1 + 0x90),param_2);
  }
  return;
}

