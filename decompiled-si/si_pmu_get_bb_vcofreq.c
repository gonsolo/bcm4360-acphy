
int si_pmu_get_bb_vcofreq(long param_1,undefined8 param_2,int param_3)

{
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined1 local_40 [3];
  byte local_3d;
  int local_3c [3];
  
  iVar4 = *(int *)(param_1 + 0x3c);
  if ((((iVar4 == 0xa9c4) || (iVar4 == 0x4360)) || (iVar4 == 0xaa06)) || (iVar4 == 0x4352)) {
    uVar2 = si_pmu_pllcontrol(param_1,2,0,0);
    uVar5 = uVar2 >> 7;
    uVar2 = uVar2 >> 4 & 7;
    if (uVar2 != 0) {
      uVar7 = 1;
      uVar3 = si_pmu_pllcontrol(param_1,3,0,0);
      goto LAB_0011598a;
    }
    uVar7 = 1;
  }
  else {
    if (iVar4 != 0x4350) {
      return 0;
    }
    uVar2 = si_pmu_pllcontrol(param_1,2,0,0);
    uVar5 = uVar2 >> 0x17;
    uVar7 = uVar2 >> 0x10 & 0xf;
    uVar2 = uVar2 >> 0x14 & 7;
    if (uVar2 != 0) {
      uVar3 = si_pmu_pllcontrol(param_1,3,0,0);
      uVar3 = uVar3 & 0xffffff;
      goto LAB_0011598a;
    }
  }
  uVar3 = 0;
LAB_0011598a:
  uVar6 = 0;
  uVar1 = (ulong)(uint)(param_3 * 10000) / (ulong)uVar7;
  iVar4 = (int)uVar1;
  if (uVar2 != 0) {
    bcm_uint64_multiple_add(local_3c,local_40,uVar1,uVar3,0x800000);
    uVar6 = (uint)local_3d | local_3c[0] << 8;
  }
  if ((int)(~uVar6 / uVar5) < iVar4) {
    return 0;
  }
  return uVar6 + uVar5 * iVar4;
}

