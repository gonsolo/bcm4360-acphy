
void wlc_bmac_mute(long *param_1,char param_2,undefined4 param_3)

{
  undefined8 uVar1;
  long *plVar2;
  
  if (param_2 == '\0') {
    if (*(char *)(*param_1 + 100) == '\0') {
      wlc_bmac_tx_fifo_resume(param_1,1);
    }
    wlc_bmac_tx_fifo_resume(param_1,3);
    wlc_bmac_tx_fifo_resume(param_1,0);
    wlc_bmac_tx_fifo_resume(param_1,2);
    plVar2 = param_1 + 0x2f;
    uVar1 = 0x8008;
    if (0x27 < *(uint *)((long)param_1 + 0x84)) goto LAB_0016535e;
  }
  else {
    wlc_bmac_tx_fifo_suspend(param_1,1);
    wlc_bmac_tx_fifo_suspend(param_1,3);
    wlc_bmac_tx_fifo_suspend(param_1,0);
    wlc_bmac_tx_fifo_suspend(param_1,2);
    plVar2 = (long *)&DAT_00510bd4;
    if (0x27 < *(uint *)((long)param_1 + 0x84)) {
      uVar1 = 0;
      plVar2 = (long *)&DAT_00510bd4;
LAB_0016535e:
      wlc_bmac_write_amt(param_1,0x3f,plVar2,uVar1);
      goto LAB_0016536b;
    }
  }
  wlc_bmac_set_addrmatch(param_1,0,plVar2);
LAB_0016536b:
  wlc_phy_mute_upd(*(undefined8 *)(param_1[0x1d] + 0x28),param_2,param_3);
  if (param_2 == '\0') {
    if (*(int *)((long)param_1 + 0x174) == 0) {
      return;
    }
    *(undefined4 *)((long)param_1 + 0x174) = 0;
  }
  else {
    *(undefined4 *)((long)param_1 + 0x174) = 1;
  }
  if ((*(uint *)(param_1 + 0x2d) & 0x60000) != 0x20000) {
    FUN_001612ed(param_1);
  }
  return;
}

