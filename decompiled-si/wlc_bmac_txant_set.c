
void wlc_bmac_txant_set(long *param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0x20) = param_2;
  if ((*(char *)((long)param_1 + 0x10c) != '\0') &&
     (*(char *)(*(long *)(*param_1 + 0x550) + 0xf4) == '\0')) {
    FUN_001633c4();
  }
  return;
}

