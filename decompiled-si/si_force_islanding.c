
void si_force_islanding(long param_1,char param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (*(int *)(param_1 + 0x3c) == 0x4335) {
    if (param_2 == '\0') {
      uVar1 = 0x3c0000;
      uVar2 = 0x3c0000;
    }
    else {
      si_pmu_chipcontrol(param_1,2,0x1c0000,0);
      uVar1 = 0x100000;
      uVar2 = 0x100000;
    }
    si_pmu_chipcontrol(param_1,2,uVar2,uVar1);
  }
  return;
}

