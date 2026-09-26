
void wlc_bmac_band_stf_ss_set(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x1a0) = param_2;
  if (*(char *)(param_1 + 0x186) != '\0') {
    FUN_00163143();
  }
  return;
}

