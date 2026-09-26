
uint FUN_0010ed06(long param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x40) == '\0') {
    uVar1 = osl_readl(*(long *)(param_1 + 0x48) + 0xc);
    uVar1 = (uVar1 & 0xfff) >> 3;
  }
  else {
    uVar1 = osl_readl(*(long *)(param_1 + 0x48) + 0x10);
    uVar1 = ((uVar1 & *(uint *)(param_1 + 0x11c)) - *(int *)(param_1 + 0xa0) &
            *(uint *)(param_1 + 0x11c)) >> 4;
  }
  *(short *)(param_1 + 0x12a) = (short)uVar1;
  return (uint)*(ushort *)(param_1 + 0x6e) - (uVar1 & 0xffff) & *(ushort *)(param_1 + 0x6a) - 1;
}

