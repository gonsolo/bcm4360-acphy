
void si_pcie_readreg(long param_1,undefined4 param_2,undefined4 param_3)

{
  pcie_readreg(param_1,*(long *)(param_1 + 0xb8) + 0x2000,param_2,param_3);
  return;
}

