
void phy_reg_read_wide(long param_1)

{
  *(undefined2 *)(param_1 + 0x226) = 0;
  osl_readw(*(long *)(param_1 + 0x148) + 0x3fe);
  return;
}

