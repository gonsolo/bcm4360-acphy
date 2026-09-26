
void FUN_0010f309(long param_1)

{
  undefined8 uVar1;
  uint uVar2;
  
  uVar1 = *(undefined8 *)(param_1 + 0x48);
  uVar2 = osl_readl(uVar1);
  osl_writel(uVar2 | 4,uVar1);
  return;
}

