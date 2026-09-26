
uint si_pmu_enb_ht_req(undefined8 param_1,undefined8 param_2,char param_3)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  uVar2 = osl_readl(lVar3 + 0x600);
  if (param_3 == '\0') {
    uVar4 = uVar2 & 0xfffffeff;
  }
  else {
    uVar4 = uVar2 | 0x100;
  }
  osl_writel(uVar4,lVar3 + 0x600);
  si_setcoreidx(param_1,uVar1);
  return uVar2;
}

