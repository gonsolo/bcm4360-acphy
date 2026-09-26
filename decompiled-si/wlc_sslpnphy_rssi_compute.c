
int wlc_sslpnphy_rssi_compute(long param_1,int param_2,long param_3)

{
  byte bVar1;
  
  if (0x7f < param_2) {
    param_2 = param_2 + -0x100;
  }
  bVar1 = (byte)((ushort)*(undefined2 *)(param_3 + 8) >> 10);
  param_2 = param_2 + (char)(&DAT_005674e0)[bVar1];
  if ((-0x2e < param_2) && (0x12 < bVar1)) {
    param_2 = param_2 + 7;
  }
  return param_2 + 2 + (int)*(char *)(*(long *)(param_1 + 0x138) + 0x77);
}

