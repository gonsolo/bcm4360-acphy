
void wlc_set_rcmta(long *param_1,undefined4 param_2,undefined8 param_3)

{
  wlc_bmac_set_rcmta(param_1[4]);
  if (*(char *)(*param_1 + 0xe8) != '\0') {
    wlc_txfbf_update_amt_idx(param_1[0x102],param_2,param_3);
  }
  return;
}

