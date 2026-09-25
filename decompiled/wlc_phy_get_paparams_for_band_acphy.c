
void wlc_phy_get_paparams_for_band_acphy
               (long param_1,undefined2 *param_2,undefined2 *param_3,undefined2 *param_4)

{
  byte bVar1;
  long lVar2;
  byte bVar3;
  
  bVar1 = wlc_phy_get_chan_freq_range_acphy((short)param_1,0);
  for (bVar3 = 0; bVar3 < *(byte *)(param_1 + 0x168); bVar3 = bVar3 + 1) {
    if (bVar1 < 5) {
      lVar2 = (ulong)bVar3 * 5 + (ulong)bVar1;
      *param_2 = *(undefined2 *)(param_1 + 0xe04 + lVar2 * 2);
      *param_3 = *(undefined2 *)(param_1 + 0xe2c + lVar2 * 2);
      *param_4 = *(undefined2 *)(param_1 + 0xe54 + lVar2 * 2);
    }
  }
  return;
}

