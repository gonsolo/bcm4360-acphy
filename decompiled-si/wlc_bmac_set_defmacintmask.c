
void wlc_bmac_set_defmacintmask(long param_1,uint param_2,uint param_3)

{
  *(uint *)(param_1 + 0x9c) = param_3 & param_2 | ~param_2 & *(uint *)(param_1 + 0x9c);
  return;
}

