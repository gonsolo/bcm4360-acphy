
void si_watchdog(long param_1,uint param_2)

{
  uint uVar1;
  sbyte sVar2;
  uint uVar3;
  undefined8 uVar4;
  
  if ((*(byte *)(param_1 + 0x1b) & 0x10) == 0) {
    if ((*(int *)(param_1 + 0x3c) != 0xcf1a) && (*(int *)(param_1 + 0x3c) != 0xcf12)) {
      si_clkctl_cc(param_1,-(param_2 == 0) & 2);
    }
    uVar4 = 0x80;
    uVar3 = 0xfffffff;
    if (param_2 < 0x10000000) {
      uVar3 = param_2;
    }
    goto LAB_00122b6e;
  }
  if (((*(int *)(param_1 + 0x3c) == 0x4319) && (param_2 != 0)) && (*(int *)(param_1 + 0x40) == 0)) {
    FUN_00122a5d(param_1,0x1e0,0xffffffff,2);
    si_setcore(param_1,0x81a,0);
    si_core_disable(param_1,1);
    si_setcore(param_1,0x800,0);
  }
  if (*(int *)(param_1 + 0x3c) == 0x5300) {
LAB_00122b17:
    uVar1 = 0xffffffff;
  }
  else {
    sVar2 = 0x10;
    if ((0x19 < *(int *)(param_1 + 0x14)) && (sVar2 = 0x18, 0x24 < *(int *)(param_1 + 0x14)))
    goto LAB_00122b17;
    uVar1 = (1 << sVar2) - 1;
  }
  uVar3 = 2;
  if ((param_2 != 1) && (uVar3 = param_2, uVar1 <= param_2)) {
    uVar3 = uVar1;
  }
  uVar4 = 0x634;
LAB_00122b6e:
  FUN_00122a5d(param_1,uVar4,0xffffffff,uVar3);
  return;
}

