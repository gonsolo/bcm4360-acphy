
void wlc_bmac_enable_mac(long param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  lVar2 = *(long *)(param_1 + 0xd0);
  iVar3 = *(int *)(param_1 + 0x16c) + -1;
  *(int *)(param_1 + 0x16c) = iVar3;
  if (iVar3 == 0) {
    osl_readl(lVar2 + 0x120);
    iVar3 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c);
    if ((iVar3 == 0xd144) || (iVar3 == 0x5357)) {
      uVar4 = 3;
      uVar5 = 3;
    }
    else {
      uVar4 = 1;
      uVar5 = 1;
    }
    wlc_bmac_mctrl(param_1,uVar5,uVar4);
    osl_writel(1,lVar2 + 0x128);
    osl_readl(lVar2 + 0x120);
    osl_readl(lVar2 + 0x128);
    wlc_ucode_wake_override_clear(param_1,4);
    if ((2 < *(int *)(*(long *)(param_1 + 0xb0) + 4)) && (*(uint *)(param_1 + 0x84) < 0xd)) {
      uVar1 = *(undefined4 *)(*(long *)(param_1 + 0xb0) + 0xc);
      si_gpiocontrol(*(undefined8 *)(param_1 + 0xb8),uVar1,uVar1,0);
    }
  }
  return;
}

