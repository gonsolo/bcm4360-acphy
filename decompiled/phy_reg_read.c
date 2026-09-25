
void phy_reg_read(long param_1,undefined2 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x148);
  osl_writew(param_2,lVar1 + 0x3fc);
  *(undefined2 *)(param_1 + 0x226) = 0;
  osl_readw(lVar1 + 0x3fe);
  return;
}

