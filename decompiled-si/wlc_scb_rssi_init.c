
void wlc_scb_rssi_init(long param_1,undefined4 param_2)

{
  long lVar1;
  
  *(undefined4 *)(param_1 + 0x114) = 1;
  lVar1 = 0;
  do {
    *(undefined4 *)(*(long *)(param_1 + 0x108) + lVar1) = param_2;
    *(undefined4 *)(param_1 + 0x16c + lVar1) = param_2;
    *(undefined4 *)(param_1 + 0x18c + lVar1) = param_2;
    *(undefined4 *)(param_1 + 0x1ac + lVar1) = param_2;
    *(undefined4 *)(param_1 + 0x1cc + lVar1) = param_2;
    lVar1 = lVar1 + 4;
  } while (lVar1 != 0x20);
  *(undefined4 *)(param_1 + 0x110) = 0;
  return;
}

