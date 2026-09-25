
void wlc_phy_stf_chain_temp_throttle_acphy(long param_1)

{
  char cVar1;
  byte bVar2;
  long lVar3;
  short sVar4;
  byte local_38 [16];
  
  lVar3 = *(long *)(param_1 + 0x20);
  cVar1 = *(char *)(lVar3 + 0xa7);
  bVar2 = *(byte *)(lVar3 + 0xa6);
  wlapi_suspend_mac_and_wait(*(undefined8 *)(lVar3 + 0x20));
  sVar4 = wlc_phy_tempsense_acphy(param_1);
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  if (*(char *)(param_1 + 0xc32) == '\0') {
    if (sVar4 < (short)(ushort)*(byte *)(param_1 + 0xc2e)) {
      return;
    }
    local_38[0] = 1;
    local_38[1] = 1;
    local_38[2] = 2;
    local_38[3] = 1;
    local_38[4] = 4;
    local_38[5] = 1;
    local_38[6] = 2;
    local_38[7] = 1;
    *(undefined1 *)(param_1 + 0xc32) = 1;
    bVar2 = local_38[bVar2];
  }
  else {
    if ((short)(ushort)*(byte *)(param_1 + 0xc31) < sVar4) {
      return;
    }
    bVar2 = *(byte *)(*(long *)(param_1 + 0x20) + 0xa4);
    *(undefined1 *)(param_1 + 0xc32) = 0;
  }
  *(byte *)(param_1 + 0xc33) = cVar1 << 4 | bVar2;
  return;
}

