
uint FUN_0010f291(long param_1,uint param_2,uint param_3)

{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (param_1 != 0) {
    uVar3 = ~param_2 & *(uint *)(param_1 + 0xc) | param_3;
    if ((uVar3 & 1) != 0) {
      uVar1 = osl_readl(*(undefined8 *)(param_1 + 0x48));
      osl_writel(uVar1 | 0x800,*(undefined8 *)(param_1 + 0x48));
      uVar2 = osl_readl(*(undefined8 *)(param_1 + 0x48));
      if ((uVar2 & 0x800) == 0) {
        uVar3 = uVar3 & 0xfffffffe;
      }
      else {
        osl_writel(uVar1,*(undefined8 *)(param_1 + 0x48));
      }
    }
    *(uint *)(param_1 + 0xc) = uVar3;
  }
  return uVar3;
}

