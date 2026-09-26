
void si_chipcontrl_srom4360(long param_1,char param_2)

{
  undefined4 uVar1;
  long lVar2;
  uint uVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar2 = si_setcore(param_1,0x800,0);
  uVar3 = osl_readl(lVar2 + 0x28);
  if (param_2 != '\0') {
    osl_writel(uVar3 & 0xffdffcf3,lVar2 + 0x28);
  }
  si_setcoreidx(param_1,uVar1);
  return;
}

