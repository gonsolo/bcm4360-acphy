
void wlc_bmac_txbw_update(long param_1)

{
  if (*(char *)(param_1 + 0x186) != '\0') {
    FUN_00163143();
  }
  return;
}

