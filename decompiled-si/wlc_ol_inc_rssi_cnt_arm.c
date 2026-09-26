
void wlc_ol_inc_rssi_cnt_arm(undefined8 *param_1)

{
  if ((((param_1 != (undefined8 *)0x0) && ((*(byte *)(*(long *)*param_1 + 0xec) & 1) != 0)) &&
      (*(char *)((long)param_1 + 0x8c) != '\0')) && ((*(byte *)(param_1 + 4) & 1) != 0)) {
    *(int *)((long)param_1 + 0x494) = *(int *)((long)param_1 + 0x494) + 1;
  }
  return;
}

