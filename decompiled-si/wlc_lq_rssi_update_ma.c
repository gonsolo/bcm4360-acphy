
undefined4 wlc_lq_rssi_update_ma(long param_1,int param_2)

{
  long *plVar1;
  ushort uVar2;
  
  plVar1 = *(long **)(param_1 + 0x330);
  if (param_2 != 0) {
    *(int *)((long)plVar1 + 0xc) =
         (*(int *)((long)plVar1 + 0xc) + param_2) - *(int *)(*plVar1 + (long)(int)plVar1[1] * 4);
    *(int *)(*plVar1 + (long)(int)plVar1[1] * 4) = param_2;
    *(uint *)(plVar1 + 1) = *(ushort *)((long)plVar1 + 0x12) - 1 & (int)plVar1[1] + 1U;
    uVar2 = (ushort)(int)plVar1[2];
    if (uVar2 < *(ushort *)((long)plVar1 + 0x12)) {
      *(ushort *)(plVar1 + 2) = uVar2 + 1;
    }
  }
  if ((short)*(uint *)(plVar1 + 2) == 0) {
    *(undefined4 *)((long)plVar1 + 0x14) = 0;
  }
  else {
    *(int *)((long)plVar1 + 0x14) =
         *(int *)((long)plVar1 + 0xc) / (int)(*(uint *)(plVar1 + 2) & 0xffff);
  }
  return *(undefined4 *)((long)plVar1 + 0x14);
}

