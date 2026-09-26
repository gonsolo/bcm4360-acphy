
void FUN_001105d7(long param_1)

{
  if (*(short *)(param_1 + 0xa4) != 0) {
    *(undefined2 *)(param_1 + 0x128) = 0;
    *(undefined2 *)(param_1 + 0xa8) = 0;
    *(undefined2 *)(param_1 + 0xa6) = 0;
    if (*(char *)(param_1 + 0x40) == '\0') {
      osl_memset(*(undefined8 *)(param_1 + 0x60),0,(ulong)*(ushort *)(param_1 + 0xa4) << 3);
      FUN_0010f330(param_1);
    }
    else {
      osl_memset(*(undefined8 *)(param_1 + 0x60),0,(ulong)*(ushort *)(param_1 + 0xa4) << 4);
      if (*(char *)(param_1 + 0x104) == '\0') {
        FUN_0010f3af(param_1,2,*(undefined8 *)(param_1 + 200));
      }
      FUN_0010f330(param_1);
      if (*(char *)(param_1 + 0x104) == '\0') {
        return;
      }
    }
    FUN_0010f3af(param_1,2,*(undefined8 *)(param_1 + 200));
  }
  return;
}

