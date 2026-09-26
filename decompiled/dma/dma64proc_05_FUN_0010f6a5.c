
undefined8 FUN_0010f6a5(long param_1)

{
  undefined8 uVar1;
  uint uVar2;
  undefined8 uStack_18;
  
  if (*(short *)(param_1 + 0x6a) != 0) {
    uVar1 = *(undefined8 *)(param_1 + 0x48);
    uVar2 = osl_readl(uVar1);
    osl_writel(uVar2 & 0xfffffffd,uVar1);
  }
  return uStack_18;
}

