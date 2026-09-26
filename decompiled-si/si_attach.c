
long si_attach(undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
              undefined8 param_5,undefined8 *param_6,undefined4 *param_7)

{
  undefined4 uVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  
  lVar2 = osl_malloc(param_2,0x7d8);
  lVar3 = 0;
  if (lVar2 != 0) {
    lVar3 = FUN_00123850(lVar2,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    if (lVar3 == 0) {
      osl_mfree(param_2,lVar2,0x7d8);
      lVar3 = 0;
    }
    else {
      uVar4 = 0;
      if (param_6 != (undefined8 *)0x0) {
        uVar4 = *param_6;
      }
      *(undefined8 *)(lVar2 + 0xa8) = uVar4;
      uVar1 = 0;
      if (param_7 != (undefined4 *)0x0) {
        uVar1 = *param_7;
      }
      *(undefined4 *)(lVar2 + 0xb0) = uVar1;
      lVar3 = lVar2;
    }
  }
  return lVar3;
}

