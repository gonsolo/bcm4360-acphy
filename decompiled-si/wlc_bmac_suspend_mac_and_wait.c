
void wlc_bmac_suspend_mac_and_wait(long *param_1)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  ulong uVar4;
  
  lVar1 = param_1[0x1a];
  uVar2 = *(int *)((long)param_1 + 0x16c) + 1;
  *(uint *)((long)param_1 + 0x16c) = uVar2;
  if (uVar2 < 2) {
    wlc_ucode_wake_override_set(param_1,4);
    if ((2 < *(int *)(param_1[0x16] + 4)) && (*(uint *)((long)param_1 + 0x84) < 0xd)) {
      si_gpiocontrol(param_1[0x17],*(undefined4 *)(param_1[0x16] + 0xc),0,0);
    }
    iVar3 = osl_readl(lVar1 + 0x120);
    if (iVar3 != -1) {
      iVar3 = osl_readl(lVar1 + 0x128);
      if (iVar3 != -1) {
        wlc_bmac_mctrl(param_1,1,0);
        for (iVar3 = 0x14441; (uVar4 = osl_readl(lVar1 + 0x128), (uVar4 & 1) == 0 && (iVar3 != 9));
            iVar3 = iVar3 + -10) {
          osl_delay(10);
        }
        osl_readl(lVar1 + 0x128);
        iVar3 = osl_readl(lVar1 + 0x120);
        if (iVar3 != -1) {
          if ((*(int *)(param_1[0x17] + 0x3c) != 0xd144) &&
             (*(int *)(param_1[0x17] + 0x3c) != 0x5357)) {
            return;
          }
          wlc_bmac_mctrl(param_1,2,0);
          return;
        }
      }
    }
    wl_down(*(undefined8 *)(*param_1 + 0x10));
  }
  return;
}

