
long FUN_0010ed6e(long param_1)

{
  long lVar1;
  short sVar2;
  uint uVar3;
  ulong uVar4;
  
  if (*(short *)(param_1 + 0xa4) != 0) {
    if (*(char *)(param_1 + 0x40) == '\0') {
      uVar3 = osl_readl(*(long *)(param_1 + 0x50) + 0xc);
      sVar2 = (short)((uVar3 & 0xfff) >> 3);
    }
    else {
      uVar3 = osl_readl(*(long *)(param_1 + 0x50) + 0x10);
      sVar2 = (short)(((uVar3 & *(uint *)(param_1 + 0x124)) - *(int *)(param_1 + 0xe0) &
                      *(uint *)(param_1 + 0x124)) >> 4);
    }
    *(short *)(param_1 + 0x128) = sVar2;
    for (uVar4 = (ulong)*(ushort *)(param_1 + 0xa6); (short)uVar4 != sVar2;
        uVar4 = (ulong)((int)uVar4 + 1U & *(int *)(param_1 + 0xa4) - 1U)) {
      lVar1 = *(long *)(*(long *)(param_1 + 0xb0) + (uVar4 & 0xffff) * 8);
      if (lVar1 != 0) {
        return lVar1;
      }
    }
  }
  return 0;
}

