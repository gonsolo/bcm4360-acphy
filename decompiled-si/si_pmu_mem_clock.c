
undefined4 si_pmu_mem_clock(long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  uVar3 = 150000000;
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 != 0xd144) {
    if (((((*(int *)(param_1 + 0x20) < 5) || (uVar1 == 0x4319)) || (uVar1 == 0x4329)) ||
        ((((uVar1 == 0x4330 || (uVar1 == 0x4314)) ||
          ((uVar1 == 0xa886 || ((uVar1 == 0xa887 || (uVar1 == 0x4334)))))) || (uVar1 == 0x4336))))
       || ((((((uVar1 == 0xa962 || (uVar1 == 0xa8e2)) || (uVar1 == 0xa8e3)) ||
             ((uVar1 == 0xa8e4 || (uVar1 == 0xa8e6)))) ||
            ((uVar1 == 0xa8e5 || ((uVar1 == 0xa8e7 || (uVar1 == 0x4324)))))) ||
           ((uVar1 == 0xa8ea || (((uVar1 == 0xa8eb || (uVar1 == 0x4335)) || (uVar1 == 0x4350))))))))
    {
      uVar3 = si_pmu_si_clock(param_1,param_2);
    }
    else {
      if ((uVar1 == 0x4749) || ((0x4748 < uVar1 && (uVar1 - 0x5356 < 2)))) {
        uVar5 = 0;
      }
      else {
        uVar5 = 0xc;
      }
      uVar2 = si_coreidx(param_1);
      uVar4 = si_setcoreidx(param_1,0);
      if (*(int *)(param_1 + 0x3c) == 0x5300) {
        uVar3 = FUN_00116f3a(uVar4,2);
      }
      else {
        uVar3 = FUN_00112bf8(param_1,param_2,uVar4,uVar5,2);
      }
      si_setcoreidx(param_1,uVar2);
    }
  }
  return uVar3;
}

