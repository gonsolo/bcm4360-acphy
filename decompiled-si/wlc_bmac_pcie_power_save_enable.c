
void wlc_bmac_pcie_power_save_enable(long param_1,undefined1 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0xb8);
  if ((*(int *)(lVar1 + 4) == 1) && (*(int *)(lVar1 + 8) == 0x820)) {
    si_pcie_power_save_enable(lVar1,param_2);
  }
  return;
}

