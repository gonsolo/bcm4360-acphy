
void wlc_bmac_antsel_set(long param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x1a4) = param_2;
  return;
}

