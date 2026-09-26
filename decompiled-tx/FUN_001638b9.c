
void FUN_001638b9(long param_1)

{
  ushort uVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  ushort *puVar5;
  ushort uVar6;
  
  uVar6 = 0;
  uVar1 = *(ushort *)(*(long *)(param_1 + 0xb0) + 8);
  wlc_bmac_mhf(param_1,1,0x200,-(uVar1 & 1) & 0x200,2);
  puVar5 = (ushort *)(btc_ucode_flags + 6);
  uVar4 = 1;
  do {
    if ((uVar1 >> (uVar4 & 0x1f) & 1) != 0) {
      uVar6 = uVar6 | *puVar5;
    }
    uVar4 = uVar4 + 1;
    puVar5 = puVar5 + 2;
  } while (uVar4 != 7);
  wlc_bmac_mhf(param_1,2,0x1504,uVar6 & 0xfdf7,2);
  if ((uVar6 & 0xedf7) == 0) {
    wlc_bmac_mhf(param_1,2,0x1000,uVar6 & 0x1000,0);
  }
  uVar6 = 0;
  if ((char)uVar1 < '\0') {
    uVar6 = btc_ucode_flags._30_2_;
  }
  if ((uVar1 & 0x100) != 0) {
    uVar6 = uVar6 | btc_ucode_flags._34_2_;
  }
  wlc_bmac_mhf(param_1,4,6,uVar6,2);
  lVar3 = *(long *)(param_1 + 0xb8);
  if ((*(int *)(lVar3 + 0x30) == 0x106b) &&
     ((((iVar2 = *(int *)(lVar3 + 0x28), iVar2 == 0x10f || (iVar2 == 0xef)) || (iVar2 == 0xf4)) ||
      ((iVar2 == 0x10e || (*(int *)(lVar3 + 0x3c) == 0x4360)))))) {
    wlc_bmac_mhf(param_1,4,1,1,2);
  }
  return;
}

