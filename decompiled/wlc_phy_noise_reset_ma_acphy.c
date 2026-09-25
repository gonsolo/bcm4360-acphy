
void wlc_phy_noise_reset_ma_acphy(long param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = 0;
  do {
    lVar2 = (long)iVar1;
    iVar1 = iVar1 + 1;
    *(undefined1 *)(*(long *)(param_1 + 0x20) + 0x96 + lVar2) = 0;
  } while (iVar1 != 8);
  *(undefined4 *)(*(long *)(param_1 + 0x20) + 0xa0) = 0;
  return;
}

