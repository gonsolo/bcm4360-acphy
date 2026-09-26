
void si_pcie_set_error_injection(long param_1)

{
  if ((*(int *)(param_1 + 4) == 1) &&
     ((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)))) {
    pcie_set_error_injection(*(undefined8 *)(param_1 + 0x90));
  }
  return;
}

