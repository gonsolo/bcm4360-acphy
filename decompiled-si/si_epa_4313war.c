
void si_epa_4313war(long param_1)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar3 = si_setcore(param_1,0x800,0);
  uVar2 = osl_readl(lVar3 + 0x6c);
  osl_writel(uVar2 | 0x40,lVar3 + 0x6c);
  si_setcoreidx(param_1,uVar1);
  return;
}

