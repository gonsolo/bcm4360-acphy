
void si_pmu_sprom_enable(long param_1,undefined8 param_2,char param_3)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (((*(int *)(param_1 + 0x3c) == 0x4315) && (*(int *)(param_1 + 0x40) != 0)) &&
     ((*(byte *)(param_1 + 0x48) & 1) != 0)) {
    osl_writel(0,lVar3 + 0x650);
    uVar2 = osl_readl(lVar3 + 0x654);
    if (param_3 == '\0') {
      uVar2 = uVar2 | 0x80000000;
    }
    else {
      uVar2 = uVar2 & 0x7fffffff;
    }
    osl_writel(uVar2,lVar3 + 0x654);
  }
  si_setcoreidx(param_1,uVar1);
  return;
}

