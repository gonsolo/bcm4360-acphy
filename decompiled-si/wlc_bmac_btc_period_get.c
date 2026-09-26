
undefined8 wlc_bmac_btc_period_get(long param_1,short *param_2,undefined1 *param_3)

{
  long lVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  ulong uVar5;
  
  lVar1 = *(long *)(param_1 + 0xd0);
  uVar4 = *(ushort *)(*(long *)(param_1 + 0xb0) + 0x1a);
  if (uVar4 != 0) {
    sVar3 = wlc_bmac_read_shm(param_1,uVar4 + 8);
    if (sVar3 != 0) {
      uVar4 = wlc_bmac_read_shm(param_1,uVar4 + 0x90);
      if (4 < uVar4) goto LAB_00162779;
    }
  }
  sVar3 = 0;
LAB_00162779:
  *(short *)(*(long *)(param_1 + 0xb0) + 0x1c) = sVar3;
  *param_2 = sVar3;
  uVar5 = osl_readl(lVar1 + 0x120);
  if ((uVar5 & 2) != 0) {
    sVar3 = osl_readw(lVar1 + 0x6c2);
    lVar1 = *(long *)(param_1 + 0xb0);
    if (*(char *)(lVar1 + 0x16) == '\0') {
      if (sVar3 == -1) {
        *(undefined1 *)(lVar1 + 0x17) = 0;
      }
      else {
        bVar2 = *(char *)(lVar1 + 0x17) + 1;
        *(byte *)(lVar1 + 0x17) = bVar2;
        if (4 < bVar2) {
          *(undefined1 *)(*(long *)(param_1 + 0xb0) + 0x16) = 1;
        }
      }
    }
    else if (sVar3 == -1) {
      *(undefined1 *)(lVar1 + 0x16) = 0;
      *(undefined1 *)(*(long *)(param_1 + 0xb0) + 0x17) = 0;
    }
  }
  *param_3 = *(undefined1 *)(*(long *)(param_1 + 0xb0) + 0x16);
  return 0;
}

