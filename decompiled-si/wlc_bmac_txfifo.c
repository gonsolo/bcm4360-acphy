
void wlc_bmac_txfifo(long *param_1,uint param_2,undefined8 param_3,char param_4,short param_5,
                    byte param_6)

{
  short *psVar1;
  int iVar2;
  
  if (param_4 != '\0') {
    psVar1 = (short *)(*(long *)(*param_1 + 0x38) + 0x38 + (ulong)param_2 * 2);
    *psVar1 = *psVar1 + (ushort)param_6;
  }
  if (param_5 != -1) {
    wlc_bmac_write_shm(param_1,0xa8,param_5);
  }
  iVar2 = (**(code **)(*(long *)param_1[(ulong)param_2 + 4] + 0x40))
                    ((long *)param_1[(ulong)param_2 + 4],param_3,param_4);
  if ((iVar2 < 0) && (param_4 != '\0')) {
    psVar1 = (short *)(*(long *)(*param_1 + 0x38) + 0x38 + (ulong)param_2 * 2);
    *psVar1 = *psVar1 - (ushort)param_6;
  }
  return;
}

