
void phy_reg_write(long param_1,uint param_2,int param_3)

{
  long lVar1;
  ushort uVar2;
  
  lVar1 = *(long *)(param_1 + 0x148);
  if ((*(int *)(*(long *)(param_1 + 0x20) + 0x6c) == 1) &&
     (uVar2 = *(short *)(param_1 + 0x226) + 1, *(ushort *)(param_1 + 0x226) = uVar2,
     *(ushort *)(param_1 + 0x228) <= uVar2)) {
    *(undefined2 *)(param_1 + 0x226) = 0;
    osl_readw(lVar1 + 0x3e0);
  }
  osl_writel(param_3 << 0x10 | param_2 & 0xffff,lVar1 + 0x3fc);
  return;
}

