
void FUN_0016196f(long param_1,undefined4 *param_2,uint param_3)

{
  long lVar1;
  undefined4 uVar2;
  uint uVar3;
  long lVar4;
  
  lVar1 = *(long *)(param_1 + 0xd0) + 0x160;
  lVar4 = *(long *)(param_1 + 0xd0) + 0x164;
  osl_writel(0x301ea,lVar1);
  osl_readl(lVar1);
  osl_writel(0x4000,lVar4);
  osl_writel(0x301eb,lVar1);
  osl_readl(lVar1);
  for (uVar3 = 0; uVar3 < param_3 >> 2; uVar3 = uVar3 + 1) {
    uVar2 = *param_2;
    param_2 = param_2 + 1;
    osl_writel(uVar2,lVar4);
  }
  return;
}

