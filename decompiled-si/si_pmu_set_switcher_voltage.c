
void si_pmu_set_switcher_voltage(undefined8 param_1,undefined8 param_2,byte param_3,byte param_4)

{
  undefined4 uVar1;
  long lVar2;
  
  uVar1 = si_coreidx();
  lVar2 = si_setcoreidx(param_1,0);
  osl_writel(1,lVar2 + 0x658);
  osl_writel((param_3 & 0x1f) << 0x16,lVar2 + 0x65c);
  osl_writel(0,lVar2 + 0x658);
  osl_writel((param_4 & 0x1f) << 0xe,lVar2 + 0x65c);
  si_setcoreidx(param_1,uVar1);
  return;
}

