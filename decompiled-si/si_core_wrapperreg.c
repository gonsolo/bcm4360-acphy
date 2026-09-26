
undefined4
si_core_wrapperreg(long param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  si_setcoreidx();
  uVar2 = si_wrapperreg(param_1,param_3,param_4,param_5);
  si_setcoreidx(param_1,uVar1);
  return uVar2;
}

