
void wlc_set_txh_info(long *param_1,long param_2,undefined4 *param_3)

{
  undefined2 *puVar1;
  
  if (param_2 != 0) {
    puVar1 = *(undefined2 **)(param_3 + 6);
    if (*(uint *)(*param_1 + 0x14) < 0x28) {
      puVar1[0x26] = (short)param_3[1];
      puVar1[0x21] = (short)*param_3;
      puVar1[0x22] = (short)((uint)*param_3 >> 0x10);
      puVar1[4] = *(undefined2 *)((long)param_3 + 10);
      *puVar1 = *(undefined2 *)((long)param_3 + 6);
      puVar1[1] = (short)param_3[2];
      puVar1[0x23] = (short)param_3[4];
    }
    else {
      puVar1[6] = (short)param_3[1];
      puVar1[8] = (short)((uint)*param_3 >> 8);
      puVar1[1] = *(undefined2 *)((long)param_3 + 6);
      puVar1[2] = (short)param_3[2];
      puVar1[10] = *(undefined2 *)((long)param_3 + 10);
      puVar1[0xb] = (short)param_3[3];
      puVar1[0xc] = *(undefined2 *)((long)param_3 + 0xe);
    }
  }
  return;
}

