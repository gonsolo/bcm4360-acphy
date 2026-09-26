
void wlc_bmac_sync_macstate(long param_1)

{
  if (((*(byte *)(param_1 + 0x170) & 4) != 0) && (*(int *)(param_1 + 0x16c) == 1)) {
    wlc_bmac_enable_mac();
  }
  return;
}

