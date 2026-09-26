
void si_pmu_spuravoid_isdone
               (long param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined1 param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  bool bVar6;
  int local_4c;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  iVar1 = *(int *)(param_1 + 0x3c);
  if ((((((iVar1 == 0xa962) || (iVar1 == 0x4336)) || (iVar1 == 0xa8e7)) ||
       ((iVar1 == 0x4314 || (iVar1 == 0xa886)))) ||
      ((iVar1 == 0x4334 || ((iVar1 == 0xa8ea || (iVar1 == 0xa8eb)))))) || (iVar1 == 0x4335)) {
    bVar6 = true;
  }
  else {
    bVar6 = iVar1 == 0x4330;
  }
  lVar4 = si_switch_core(param_1,0x800,local_3c,&local_40);
  if (bVar6) {
    uVar2 = FUN_0011192d(param_1);
    for (local_4c = 0x4e29;
        (uVar3 = osl_readl(lVar4 + 0x60c), (uVar2 & uVar3) != 0 && (local_4c != 9));
        local_4c = local_4c + -10) {
      osl_delay(10);
    }
    for (local_4c = 0x4e29;
        (uVar5 = osl_readl(lVar4 + 0x1e0), (uVar5 & 0x20000) != 0 && (local_4c != 9));
        local_4c = local_4c + -10) {
      osl_delay(10);
    }
  }
  FUN_00114b52(param_1,lVar4,param_2,param_6);
  if (bVar6) {
    FUN_00113316(param_1,param_2,lVar4,param_3,param_4,param_5);
  }
  si_restore_core(param_1,local_3c[0],local_40);
  return;
}

