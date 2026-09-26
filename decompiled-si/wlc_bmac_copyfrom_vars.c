
void wlc_bmac_copyfrom_vars(long param_1,long *param_2,undefined4 *param_3)

{
  if (*(long *)(param_1 + 0xc0) != 0) {
    *param_2 = *(long *)(param_1 + 0xc0);
    *param_3 = *(undefined4 *)(param_1 + 200);
  }
  return;
}

