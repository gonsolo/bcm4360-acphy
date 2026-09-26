
void wlc_lq_rssi_reset_ma(long param_1,undefined4 param_2)

{
  long *plVar1;
  long lVar2;
  
  plVar1 = *(long **)(param_1 + 0x330);
  lVar2 = 0;
  *(undefined4 *)((long)plVar1 + 0xc) = 0;
  *(undefined2 *)(plVar1 + 2) = 0;
  do {
    *(undefined4 *)(*plVar1 + lVar2) = 0;
    lVar2 = lVar2 + 4;
  } while (lVar2 != 0x20);
  *(undefined4 *)(plVar1 + 1) = 0;
  *(undefined4 *)((long)plVar1 + 0x14) = param_2;
  return;
}

