
ulong si_pll_reset(long param_1)

{
  undefined4 uVar1;
  ulong uVar2;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar2 = si_pll_minresmask_reset(param_1,*(undefined8 *)(param_1 + 0x58));
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar1);
    uVar2 = uVar2 & 0xffffffff;
  }
  return uVar2;
}

