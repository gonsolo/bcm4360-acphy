
void wlc_bmac_watchdog(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x20);
  if (*(char *)(lVar1 + 0x10c) != '\0') {
    *(int *)(lVar1 + 0x110) = *(int *)(lVar1 + 0x110) + 1;
    wlc_bmac_fifoerrors(lVar1);
    (**(code **)(**(long **)(lVar1 + 0x20) + 0xd8))();
    if (*(int *)(lVar1 + 0x84) == 4) {
      (**(code **)(**(long **)(lVar1 + 0x38) + 0xd8))();
    }
    wlc_phy_watchdog(*(undefined8 *)(*(long *)(lVar1 + 0xe8) + 0x28));
  }
  return;
}

