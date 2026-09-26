
void si_restore_core(long param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 4) != 1) ||
     ((((iVar1 = *(int *)(param_1 + 8), iVar1 != 0x83c && (iVar1 != 0x820)) &&
       ((iVar1 != 0x804 || (*(uint *)(param_1 + 0xc) < 0xd)))) ||
      ((param_2 != 0x800 && (param_2 != *(int *)(param_1 + 8))))))) {
    si_setcoreidx(param_1);
    if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
       (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) ==
        *(int *)(param_1 + 0x68))) {
      (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),param_3);
    }
  }
  return;
}

