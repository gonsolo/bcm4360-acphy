
uint si_clock(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  
  if ((*(int *)(param_1 + 0x3c) == 0xcf1a) || (*(int *)(param_1 + 0x3c) == 0xcf12)) {
    uVar8 = (-(uint)(*(int *)(param_1 + 0x44) == 0) & 50000000) + 200000000;
  }
  else {
    if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
       (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) !=
        *(int *)(param_1 + 0x68))) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
    }
    if ((*(byte *)(param_1 + 0x1b) & 0x10) == 0) {
      uVar1 = *(undefined4 *)(param_1 + 0x1c0);
      lVar5 = si_setcore(param_1,0x800,0);
      uVar3 = osl_readl(lVar5 + 0x90);
      uVar7 = *(uint *)(param_1 + 0x18) & 0x38000;
      if (uVar7 == 0x28000) {
        lVar6 = lVar5 + 0xa0;
      }
      else {
        lVar6 = lVar5 + 0x9c;
        if (uVar7 != 0x30000) {
          lVar6 = lVar5 + 0x94;
        }
      }
      uVar4 = osl_readl(lVar6);
      uVar8 = si_clock_rate(uVar7,uVar3,uVar4);
      if (uVar7 == 0x30000) {
        uVar8 = uVar8 >> 1;
      }
      si_setcoreidx(param_1,uVar1);
    }
    else {
      uVar8 = si_pmu_si_clock(param_1,*(undefined8 *)(param_1 + 0x58));
    }
    if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
       (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) ==
        *(int *)(param_1 + 0x68))) {
      (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar2);
    }
  }
  return uVar8;
}

