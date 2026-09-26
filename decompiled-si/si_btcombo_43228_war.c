
void si_btcombo_43228_war(long param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar2 = si_setcore(param_1,0x800,0);
  osl_writel(0xc0,lVar2 + 0x68);
  osl_writel(0x80,lVar2 + 100);
  si_setcoreidx(param_1,uVar1);
  return;
}

