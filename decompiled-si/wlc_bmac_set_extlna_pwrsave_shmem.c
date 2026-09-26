
void wlc_bmac_set_extlna_pwrsave_shmem(long param_1)

{
  undefined2 uVar1;
  
  if ((*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) == 0x4331) &&
     ((*(int *)(*(long *)(param_1 + 0xb8) + 0x28) == 0xef ||
      ((((*(byte *)(param_1 + 0x93) & 8) != 0 && (2 < *(byte *)(param_1 + 0x1bd))) &&
       (2 < *(byte *)(param_1 + 0x1be))))))) {
    uVar1 = 0x4c0;
  }
  else {
    uVar1 = 0x480;
  }
  wlc_bmac_write_shm(param_1,100,uVar1);
  return;
}

