
void wlc_bmac_pcie_war_ovr_update(long param_1,undefined1 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0xb8);
  if ((*(int *)(lVar1 + 4) == 1) && (*(int *)(lVar1 + 8) == 0x820)) {
    si_pcie_war_ovr_update(lVar1,param_2);
  }
  return;
}

