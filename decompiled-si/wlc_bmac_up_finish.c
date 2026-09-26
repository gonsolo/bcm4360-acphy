
undefined8 wlc_bmac_up_finish(long *param_1)

{
  *(undefined1 *)((long)param_1 + 0x10c) = 1;
  wlc_phy_hw_state_upd(*(undefined8 *)(param_1[0x1d] + 0x28),1);
  FUN_001655c7(param_1,2);
  wl_intrson(*(undefined8 *)(*param_1 + 0x10));
  wlc_bmac_ifsctl_edcrs_set(param_1,*(short *)(*(long *)(*param_1 + 0x40) + 8) == 7);
  return 0;
}

