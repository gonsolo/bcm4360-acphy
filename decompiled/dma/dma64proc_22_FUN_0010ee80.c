
bool FUN_0010ee80(long param_1)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  bVar3 = true;
  if (*(short *)(param_1 + 0xa4) != 0) {
    uVar1 = osl_readl(*(long *)(param_1 + 0x50) + 0x10);
    uVar2 = osl_readl(*(long *)(param_1 + 0x50) + 4);
    bVar3 = (*(uint *)(param_1 + 0x124) & (uVar2 ^ uVar1)) == 0;
  }
  return bVar3;
}

