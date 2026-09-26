
undefined8 si_gpiopull(long param_1,char param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xffffffff;
  if (0x13 < *(int *)(param_1 + 0x14)) {
    uVar1 = FUN_00122a5d(param_1,(-(uint)(param_2 == '\0') & 0xfffffffc) + 0x5c);
  }
  return uVar1;
}

