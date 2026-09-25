
void wlc_phy_cal_perical_mphase_reset(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0xf58);
  if (*(long *)(param_1 + 0x1088) != 0) {
    wlapi_del_timer(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  if (*(int *)(param_1 + 0x160) == 4) {
    *(undefined1 *)(*(long *)(param_1 + 0x138) + 0x382) = 0;
  }
  *(undefined1 *)(lVar1 + 1) = 0;
  *(undefined1 *)(lVar1 + 2) = 0;
  return;
}

