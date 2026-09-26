
undefined8 si_clkctl_cc(long param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  if (*(int *)(param_1 + 0x14) < 6) {
    return 0;
  }
  if (*(int *)(param_1 + 4) == 1) {
    iVar1 = *(int *)(param_1 + 8);
    if (((iVar1 == 0x820) && (*(int *)(param_1 + 0x3c) == 0x4311)) &&
       (uVar3 = 0x820, *(uint *)(param_1 + 0x40) < 2)) {
LAB_00122270:
      return CONCAT71((int7)(uVar3 >> 8),param_2 == 0);
    }
    if ((iVar1 == 0x820) || (iVar1 == 0x804)) {
      uVar2 = *(uint *)(param_1 + 0x3c);
      uVar3 = (ulong)uVar2;
      if ((uVar2 == 0x4321) || ((iVar1 == 0x820 && ((uVar2 == 0x4716 || (uVar2 == 0x4748))))))
      goto LAB_00122270;
    }
  }
  uVar4 = FUN_00121d9c();
  return uVar4;
}

