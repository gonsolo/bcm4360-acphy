
uint si_has_flops(long param_1)

{
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  undefined1 auVar4 [16];
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  lVar3 = si_setcore(param_1,0x83e,0);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = si_corerev(param_1);
    auVar4 = si_setcoreidx(param_1,uVar1);
    uVar2 = (uint)CONCAT71(auVar4._1_7_,2 < uVar2) | (uint)CONCAT71(auVar4._9_7_,uVar2 == 1);
  }
  return uVar2;
}

