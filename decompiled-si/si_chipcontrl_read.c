
undefined4 si_chipcontrl_read(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar3 = si_setcore(param_1,0x800,0);
  uVar2 = osl_readl(lVar3 + 0x28);
  si_setcoreidx(param_1,uVar1);
  return uVar2;
}

