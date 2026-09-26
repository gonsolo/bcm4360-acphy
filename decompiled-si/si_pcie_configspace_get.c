
undefined8 si_pcie_configspace_get(long param_1,undefined8 param_2,uint param_3)

{
  undefined8 uVar1;
  
  if ((*(int *)(param_1 + 4) == 1) &&
     (((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)) && (param_3 < 0x101))))
  {
    uVar1 = pcie_configspace_get(*(undefined8 *)(param_1 + 0x90));
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

