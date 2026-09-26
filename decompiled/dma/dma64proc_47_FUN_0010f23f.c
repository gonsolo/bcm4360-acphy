
uint FUN_0010f23f(long param_1,int param_2)

{
  undefined8 uVar1;
  uint uVar2;
  
  uVar1 = *(undefined8 *)(param_1 + 0x50);
  if (param_2 == 0) {
    uVar2 = osl_readl(uVar1);
    osl_writel(uVar2 & 0xffffbfff,uVar1);
    uVar2 = 1;
  }
  else {
    uVar2 = osl_readl(uVar1);
    osl_writel(uVar2 | 0x4000,uVar1);
    uVar2 = osl_readl(uVar1);
    uVar2 = uVar2 >> 0xe & 1;
  }
  return uVar2;
}

