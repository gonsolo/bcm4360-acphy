
void si_pmu_spuravoid(long param_1,undefined8 param_2,undefined1 param_3)

{
  int iVar1;
  undefined8 uVar2;
  bool bVar3;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  local_44 = 0;
  local_48 = 0;
  local_4c = 0;
  iVar1 = *(int *)(param_1 + 0x3c);
  if ((((((iVar1 == 0xa962) || (iVar1 == 0x4336)) || (iVar1 == 0xa8e7)) ||
       ((iVar1 == 0x4314 || (iVar1 == 0xa886)))) ||
      ((iVar1 == 0x4334 || ((iVar1 == 0xa8ea || (iVar1 == 0xa8eb)))))) || (iVar1 == 0x4335)) {
    bVar3 = true;
  }
  else {
    bVar3 = iVar1 == 0x4330;
  }
  uVar2 = si_switch_core(param_1,0x800,local_3c,&local_40);
  if (bVar3) {
    FUN_001133d7(param_1,param_2,uVar2,&local_44,&local_48,&local_4c);
  }
  FUN_00114b52(param_1,uVar2,param_2,param_3);
  if (bVar3) {
    FUN_00113316(param_1,param_2,uVar2,local_44,local_48,local_4c);
  }
  si_restore_core(param_1,local_3c[0],local_40);
  return;
}

