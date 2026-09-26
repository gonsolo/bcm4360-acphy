
void si_chipcontrl_epa4331_wowl(long param_1,char param_2)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  
  if ((*(int *)(param_1 + 0x44) == 9 || *(int *)(param_1 + 0x44) == 0xb) &&
      (*(int *)(param_1 + 0x3c) == 0x4331 || *(int *)(param_1 + 0x3c) == 0xa9a7)) {
    uVar1 = *(undefined4 *)(param_1 + 0x1c0);
    lVar3 = si_setcore(param_1,0x800,0);
    uVar2 = osl_readl(lVar3 + 0x28);
    if (param_2 == '\0') {
      uVar2 = uVar2 | 0x90;
    }
    else {
      uVar2 = uVar2 | 0x10;
    }
    osl_writel(uVar2,lVar3 + 0x28);
    si_setcoreidx(param_1,uVar1);
  }
  return;
}

