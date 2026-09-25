
void phy_reg_mod(long param_1,undefined2 param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x148) + 0x3fe;
  osl_writew(param_2,*(long *)(param_1 + 0x148) + 0x3fc);
  uVar1 = osl_readw(lVar2);
  osl_writew(uVar1 & ~param_3 | param_3 & param_4,lVar2);
  *(undefined2 *)(param_1 + 0x226) = 0;
  return;
}

