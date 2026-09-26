
undefined8 si_pcie_get_L1substate(long param_1)

{
  undefined8 uVar1;
  
  if ((*(int *)(param_1 + 4) == 1) && (*(int *)(param_1 + 8) == 0x83c)) {
    uVar1 = pcie_get_L1substate(*(undefined8 *)(param_1 + 0x90));
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

