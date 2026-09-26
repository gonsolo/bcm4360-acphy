
uint FUN_0010ec1c(long param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = osl_readl(*(long *)(param_1 + 0x50) + 0x10);
  uVar1 = *(uint *)(param_1 + 0x124);
  iVar2 = *(int *)(param_1 + 0xe0);
  uVar4 = osl_readl(*(long *)(param_1 + 0x50) + 4);
  return (((uVar4 & *(uint *)(param_1 + 0x124)) - *(int *)(param_1 + 0xe0) &
          *(uint *)(param_1 + 0x124)) >> 4 & 0xffff) -
         (((uVar3 & uVar1) - iVar2 & uVar1) >> 4 & 0xffff) & *(ushort *)(param_1 + 0xa4) - 1;
}

