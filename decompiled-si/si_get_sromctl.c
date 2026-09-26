
undefined4 si_get_sromctl(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar3 = si_setcoreidx(param_1,0);
  uVar2 = osl_readl(lVar3 + 400);
  si_setcoreidx(param_1,uVar1);
  return uVar2;
}

