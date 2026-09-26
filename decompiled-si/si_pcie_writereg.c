
void si_pcie_writereg(long param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  pcie_writereg(param_1,*(long *)(param_1 + 0xb8) + 0x2000,param_2,param_3,param_4);
  return;
}

