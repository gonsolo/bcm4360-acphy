
long FUN_0010efd4(long param_1)

{
  long lVar1;
  short sVar2;
  uint uVar3;
  
  if (*(short *)(param_1 + 0x6a) != 0) {
    if (*(char *)(param_1 + 0x40) == '\0') {
      uVar3 = osl_readl(*(long *)(param_1 + 0x48) + 0xc);
      sVar2 = (short)((uVar3 & 0xfff) >> 3);
    }
    else {
      uVar3 = osl_readl(*(long *)(param_1 + 0x48) + 0x10);
      sVar2 = (short)(((uVar3 & *(uint *)(param_1 + 0x11c)) - *(int *)(param_1 + 0xa0) &
                      *(uint *)(param_1 + 0x11c)) >> 4);
    }
    *(short *)(param_1 + 0x12a) = sVar2;
    for (uVar3 = *(uint *)(param_1 + 0x6c); (short)uVar3 != sVar2;
        uVar3 = uVar3 + 1 & *(ushort *)(param_1 + 0x6a) - 1) {
      lVar1 = *(long *)(*(long *)(param_1 + 0x70) + (ulong)(uVar3 & 0xffff) * 8);
      if (lVar1 != 0) {
        return lVar1;
      }
    }
  }
  return 0;
}

