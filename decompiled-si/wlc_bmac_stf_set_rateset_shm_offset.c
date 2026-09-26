
void wlc_bmac_stf_set_rateset_shm_offset
               (undefined8 param_1,uint *param_2,ushort param_3,long param_4)

{
  long lVar1;
  ulong uVar2;
  
  for (uVar2 = 0; (uint)uVar2 < *param_2; uVar2 = (ulong)((uint)uVar2 + 1)) {
    lVar1 = param_4 + uVar2 * 6;
    wlc_bmac_write_shm(param_1,(uint)param_3 + (uint)*(ushort *)(lVar1 + 2),
                       *(undefined2 *)(lVar1 + 4));
  }
  return;
}

