
void wlc_write_amtinfo_by_idx(long *param_1,int param_2,undefined2 param_3)

{
  if (0x27 < *(uint *)(*param_1 + 0x14)) {
    wlc_bmac_write_shm(param_1[4],param_2 * 2 + 0x668,param_3);
  }
  return;
}

