
void FUN_0019a2eb(long param_1,char param_2)

{
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  
  if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) != 0x4352) {
    return;
  }
  if (param_2 != '\0') {
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      local_18 = 0xf8;
      local_17 = 0xf8;
      local_16 = 0xf8;
      local_15 = 0xf8;
      goto LAB_0019a33e;
    }
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000) {
      return;
    }
  }
  local_18 = 0;
  local_17 = 0;
  local_16 = 0;
  local_15 = 0;
LAB_0019a33e:
  FUN_0019a268(param_1,&local_18);
  return;
}

