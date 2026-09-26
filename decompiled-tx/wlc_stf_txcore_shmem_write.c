
void wlc_stf_txcore_shmem_write(long *param_1,char param_2)

{
  long lVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  
  if (((((param_2 != '\0') || (*(char *)((long)param_1 + 0x31) != '\0')) &&
       (lVar1 = *param_1, 0x19 < *(uint *)(lVar1 + 0x14))) &&
      ((sVar2 = (short)*(undefined4 *)(param_1[8] + 8), sVar2 == 0xb || (sVar2 == 7)))) &&
     ((uVar5 = *(ushort *)(param_1[0xaa] + 0x2a), uVar5 == *(ushort *)(lVar1 + 0xe4) ||
      (uVar5 == *(ushort *)(lVar1 + 0xe6))))) {
    iVar3 = 0;
    iVar4 = (uint)uVar5 * 2;
    do {
      uVar5 = *(byte *)(param_1[0xaa] + 0x17 + (long)iVar3 * 2) & 0xf;
      if (*(short *)(param_1[8] + 8) == 7) {
        sVar2 = FUN_00273ae9(param_1,iVar3);
        uVar5 = uVar5 | sVar2 << 8;
      }
      iVar3 = iVar3 + 1;
      wlc_write_shm(param_1,iVar4,uVar5);
      iVar4 = iVar4 + 2;
    } while (iVar3 != 5);
    if ((*(int *)(*(long *)(*param_1 + 0x100) + 0x30) == 0x106b) &&
       ((iVar4 = *(int *)(*(long *)(*param_1 + 0x100) + 0x3c), iVar4 == 0x4360 || (iVar4 == 0x4331))
       )) {
      wlc_write_shm(param_1,0x5de,*(undefined2 *)(param_1[0xd2] + 0x14));
    }
  }
  return;
}

