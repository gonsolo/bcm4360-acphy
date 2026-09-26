
void si_pcie_set_L1substate(long param_1)

{
  if ((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x83c)) {
    pcie_set_L1substate(*(undefined8 *)(param_1 + 0x90));
  }
  return;
}

