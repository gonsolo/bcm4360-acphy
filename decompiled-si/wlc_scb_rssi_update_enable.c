
undefined4 wlc_scb_rssi_update_enable(long param_1,char param_2,byte param_3)

{
  uint uVar1;
  
  if (param_2 == '\0') {
    uVar1 = -2 << (param_3 & 0x1f) | 0xfffffffeU >> 0x20 - (param_3 & 0x1f);
    *(byte *)(param_1 + 0x159) = *(byte *)(param_1 + 0x159) & (byte)uVar1;
  }
  else {
    uVar1 = 1 << (param_3 & 0x1f);
    *(byte *)(param_1 + 0x159) = *(byte *)(param_1 + 0x159) | (byte)uVar1;
  }
  return CONCAT31((int3)(uVar1 >> 8),*(char *)(param_1 + 0x159) != '\0');
}

