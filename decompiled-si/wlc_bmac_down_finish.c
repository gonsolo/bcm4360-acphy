
undefined4 wlc_bmac_down_finish(long *param_1)

{
  char cVar1;
  undefined4 uVar2;
  ulong uVar3;
  
  uVar2 = 0;
  if (*(char *)((long)param_1 + 0x10c) != '\0') {
    *(undefined1 *)((long)param_1 + 0x10c) = 0;
    wlc_phy_hw_state_upd(*(undefined8 *)(param_1[0x1d] + 0x28),0);
    cVar1 = wlc_hw_deviceremoved(*(undefined8 *)(*param_1 + 0x20));
    if (cVar1 == '\0') {
      uVar2 = 0;
      cVar1 = si_iscoreup(param_1[0x17]);
      if (cVar1 != '\0') {
        uVar3 = osl_readl(param_1[0x1a] + 0x120);
        if ((uVar3 & 1) != 0) {
          wlc_bmac_suspend_mac_and_wait(param_1);
        }
        uVar2 = wl_reset(*(undefined8 *)(*param_1 + 0x10));
        wlc_coredisable(param_1);
      }
      if (*(char *)((long)param_1 + 0x184) == '\0') {
        wlc_bmac_hw_down(param_1);
      }
    }
    else {
      *(undefined1 *)((long)param_1 + 0x187) = 0;
      *(undefined1 *)((long)param_1 + 0x186) = 0;
      uVar2 = 0;
      wlc_phy_hw_clk_state_upd(*(undefined8 *)(param_1[0x1d] + 0x28),0);
      FUN_00160c3a(param_1);
    }
  }
  return uVar2;
}

