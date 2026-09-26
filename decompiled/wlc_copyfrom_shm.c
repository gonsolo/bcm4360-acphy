
void wlc_copyfrom_shm(long param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  if (0 < param_4) {
    wlc_bmac_copyfrom_objmem(*(undefined8 *)(param_1 + 0x20));
  }
  return;
}

