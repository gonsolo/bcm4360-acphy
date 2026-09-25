
void phy_reg_write_wide(long param_1,undefined2 param_2)

{
  osl_writew(param_2,*(long *)(param_1 + 0x148) + 0x3fe);
  return;
}

