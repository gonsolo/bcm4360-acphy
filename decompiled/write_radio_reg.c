
long write_radio_reg(long param_1,undefined2 param_2,undefined2 param_3)

{
  uint uVar1;
  ushort uVar2;
  long lVar3;
  
  if ((*(int *)(*(long *)(param_1 + 0x20) + 0x6c) == 1) &&
     (uVar2 = *(short *)(param_1 + 0x226) + 1, *(ushort *)(param_1 + 0x226) = uVar2,
     *(ushort *)(param_1 + 0x228) <= uVar2)) {
    osl_readl(*(long *)(param_1 + 0x148) + 0x120);
    *(undefined2 *)(param_1 + 0x226) = 0;
  }
  uVar1 = *(uint *)(*(long *)(param_1 + 0x20) + 0x28);
  if (((uVar1 == 0x1b) || (uVar1 < 0x18)) && ((uVar1 != 0x16 || (*(int *)(param_1 + 0x160) == 6))))
  {
    osl_writew(param_2,*(long *)(param_1 + 0x148) + 0x3f6);
    lVar3 = *(long *)(param_1 + 0x148) + 0x3fa;
  }
  else {
    osl_writew(param_2,*(long *)(param_1 + 0x148) + 0x3d8);
    lVar3 = *(long *)(param_1 + 0x148) + 0x3da;
  }
  osl_writew(param_3,lVar3);
  lVar3 = *(long *)(param_1 + 0x20);
  if ((*(int *)(lVar3 + 0x6c) == 2) && (*(uint *)(lVar3 + 0x70) < 4)) {
    lVar3 = osl_readw(*(long *)(param_1 + 0x148) + 0x3e0);
  }
  return lVar3;
}

