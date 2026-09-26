
void wlc_bmac_stf_get_rateset_shm_offset(long param_1,uint *param_2,ushort param_3,byte *param_4)

{
  ushort uVar1;
  undefined2 uVar2;
  uint *puVar3;
  byte bVar4;
  
  for (puVar3 = param_2; (uint)((int)puVar3 - (int)param_2) < *param_2;
      puVar3 = (uint *)((long)puVar3 + 1)) {
    bVar4 = (byte)puVar3[1] & 0x7f;
    uVar1 = wlc_bmac_rate_shm_offset(param_1,bVar4);
    if (0x27 < *(uint *)(param_1 + 0x84)) {
      uVar2 = wlc_bmac_read_shm(param_1,(uint)uVar1 + (uint)param_3);
      *(undefined2 *)(param_4 + 4) = uVar2;
    }
    *(ushort *)(param_4 + 2) = uVar1;
    *param_4 = bVar4;
    param_4 = param_4 + 6;
  }
  return;
}

