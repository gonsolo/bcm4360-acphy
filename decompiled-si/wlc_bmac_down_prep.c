
undefined8 wlc_bmac_down_prep(long *param_1)

{
  char cVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (*(char *)((long)param_1 + 0x10c) != '\0') {
    cVar1 = wlc_hw_deviceremoved(*(undefined8 *)(*param_1 + 0x20));
    if (cVar1 == '\0') {
      wl_intrsoff(*(undefined8 *)(*param_1 + 0x10));
      FUN_001655c7(param_1,0);
      if (*(char *)((long)param_1 + 0x184) == '\0') {
        FUN_0016407d(param_1);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x13) = 0;
    }
    if (*(int *)(param_1[0x17] + 0x3c) == 0x4331) {
      wlc_bmac_write_shm(param_1,100,0x480);
    }
    uVar2 = wlc_phy_down(*(undefined8 *)(param_1[0x1d] + 0x28));
  }
  return uVar2;
}

