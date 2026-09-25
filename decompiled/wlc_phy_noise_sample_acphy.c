
undefined1 wlc_phy_noise_sample_acphy(long param_1)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  
  uVar2 = 0xa4;
  if (*(char *)(*(long *)(param_1 + 0x20) + 0x31) != '\0') {
    wlapi_bmac_read_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x8c);
    uVar2 = wlc_phy_noise_read_shmem(param_1);
    *(undefined1 *)
     (*(long *)(param_1 + 0x20) + 0x96 + (ulong)*(uint *)(*(long *)(param_1 + 0x20) + 0xa0)) = uVar2
    ;
    iVar1 = *(int *)(*(long *)(param_1 + 0x20) + 0xa0);
    iVar3 = 0;
    if (iVar1 != 7) {
      iVar3 = iVar1 + 1;
    }
    *(int *)(*(long *)(param_1 + 0x20) + 0xa0) = iVar3;
  }
  return uVar2;
}

