
void wlc_bmac_btc_rssi_threshold_get
               (long param_1,undefined1 *param_2,undefined1 *param_3,undefined1 *param_4)

{
  ushort uVar1;
  undefined1 uVar2;
  
  uVar1 = *(ushort *)(*(long *)(param_1 + 0xb0) + 0x1a);
  if (uVar1 != 0) {
    uVar2 = wlc_bmac_read_shm(param_1,uVar1 + 0x92);
    *param_2 = uVar2;
    uVar2 = wlc_bmac_read_shm(param_1,uVar1 + 200);
    *param_3 = uVar2;
    uVar2 = wlc_bmac_read_shm(param_1,uVar1 + 0xca);
    *param_4 = uVar2;
  }
  return;
}

