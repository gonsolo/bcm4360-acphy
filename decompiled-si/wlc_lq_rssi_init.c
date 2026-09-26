
void wlc_lq_rssi_init(long param_1,undefined2 param_2)

{
  long lVar1;
  short sVar2;
  uint uVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  
  sVar2 = (short)*(undefined4 *)(*(long *)(param_1 + 0x40) + 8);
  if ((sVar2 == 0xb) || (uVar6 = 2, sVar2 == 7)) {
    uVar6 = 3;
  }
  lVar1 = *(long *)(param_1 + 0x550);
  uVar3 = 0;
  do {
    puVar4 = (undefined2 *)(param_1 + 0x494 + (ulong)uVar3 * 2);
    uVar5 = 0;
    do {
      if ((*(byte *)(lVar1 + 5) >> (uVar5 & 0x1f) & 1) != 0) {
        *puVar4 = param_2;
      }
      uVar5 = uVar5 + 1;
      puVar4 = puVar4 + 0x10;
    } while (uVar5 < uVar6);
    uVar3 = uVar3 + 1;
  } while (uVar3 != 0x10);
  *(undefined1 *)(param_1 + 0x514) = 0;
  return;
}

