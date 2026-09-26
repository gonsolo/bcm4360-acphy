
void si_pcie_set_maxpayload_size(long param_1,undefined2 param_2)

{
  if ((*(int *)(param_1 + 4) == 1) &&
     ((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)))) {
    pcie_set_maxpayload_size(*(undefined8 *)(param_1 + 0x90),param_2);
  }
  return;
}

