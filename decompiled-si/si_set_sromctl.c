
undefined8 si_set_sromctl(long param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  undefined8 uVar4;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar3 = si_setcoreidx(param_1,0);
  uVar2 = si_corerev(param_1);
  uVar4 = 0xffffffe9;
  if (0x1f < uVar2) {
    osl_writel(param_2,lVar3 + 400);
    si_setcoreidx(param_1,uVar1);
    uVar4 = 0;
  }
  return uVar4;
}

