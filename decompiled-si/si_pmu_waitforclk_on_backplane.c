
uint si_pmu_waitforclk_on_backplane(undefined8 param_1,undefined8 param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (param_4 != 0) {
    uVar4 = param_4 + 9;
    while( true ) {
      uVar2 = osl_readl(lVar3 + 0x608);
      if (((uVar2 & param_3) == param_3) || (uVar4 < 10)) break;
      uVar4 = uVar4 - 10;
      osl_delay(10);
    }
  }
  si_setcoreidx(param_1,uVar1);
  uVar4 = osl_readl(lVar3 + 0x608);
  return uVar4 & param_3;
}

