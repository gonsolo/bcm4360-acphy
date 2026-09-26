
long si_switch_core(long param_1,ulong param_2,int *param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  
  iVar4 = (int)param_2;
  if ((*(int *)(param_1 + 4) == 1) &&
     (((iVar1 = *(int *)(param_1 + 8), iVar1 == 0x83c || (iVar1 == 0x820)) ||
      ((iVar1 == 0x804 && (0xc < *(uint *)(param_1 + 0xc))))))) {
    *param_3 = iVar4;
    if (iVar4 == 0x800) {
      return *(long *)(param_1 + 0xb8) + 0x3000;
    }
    if (iVar4 == *(int *)(param_1 + 8)) {
      return *(long *)(param_1 + 0xb8) + 0x2000;
    }
  }
  if ((*(code **)(param_1 + 0x78) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    uVar2 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
    param_2 = param_2 & 0xffffffff;
    *param_4 = uVar2;
  }
  *param_3 = *(int *)(param_1 + 0x1c0);
  lVar3 = si_setcore(param_1,param_2,0);
  return lVar3;
}

