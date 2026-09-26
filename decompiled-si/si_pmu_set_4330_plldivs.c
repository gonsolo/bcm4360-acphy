
void si_pmu_set_4330_plldivs(long param_1,byte param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  
  uVar4 = FUN_00111849();
  uVar4 = (uVar4 & 0xffffffff) / 1000;
  uVar1 = (uint)uVar4;
  uVar2 = (uint)(uVar4 / 0x50);
  uVar3 = uVar2;
  if (5 < (*(uint *)(param_1 + 0x48) & 7)) {
    uVar3 = uVar1 / 0x5a;
  }
  si_pmu_pllcontrol(param_1,1,0xffffffff,uVar2 << 0x10 | uVar2 << 8 | uVar2 << 0x18 | uVar3);
  uVar3 = si_pmu_pllcontrol(param_1,2,0,0);
  si_pmu_pllcontrol(param_1,2,0xffffffff,uVar1 / param_2 | uVar2 << 8 | uVar3 & 0xffff0000);
  return;
}

