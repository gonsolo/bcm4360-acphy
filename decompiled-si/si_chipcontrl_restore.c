
void si_chipcontrl_restore(long param_1,undefined4 param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar2 = si_setcore(param_1,0x800,0);
  osl_writel(param_2,lVar2 + 0x28);
  si_setcoreidx(param_1,uVar1);
  return;
}

