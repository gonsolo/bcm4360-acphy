
undefined8 wlc_lq_rssi_pktrxh_cal(long param_1,long param_2)

{
  long lVar1;
  short sVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  
  uVar3 = *(uint *)(*(long *)(param_1 + 0x40) + 8);
  uVar4 = (ulong)uVar3;
  sVar2 = (short)uVar3;
  if ((sVar2 == 0xb) || (iVar6 = 2, sVar2 == 7)) {
    iVar6 = 3;
  }
  if ((*(char *)(param_2 + 0x1f) == '\0') && (*(char *)(param_2 + 0x1c) != '\0')) {
    lVar1 = *(long *)(param_1 + 0x550);
    uVar3 = 0;
    lVar5 = param_2;
    do {
      if ((*(byte *)(lVar1 + 5) >> (uVar3 & 0x1f) & 1) != 0) {
        *(short *)(param_1 + 4 +
                  ((ulong)*(byte *)(param_1 + 0x514) + 0x248 + (long)(int)uVar3 * 0x10) * 2) =
             (short)*(char *)(lVar5 + 0x20);
      }
      uVar3 = uVar3 + 1;
      lVar5 = lVar5 + 1;
    } while ((int)uVar3 < iVar6);
    uVar4 = 0;
    *(byte *)(param_1 + 0x514) = *(char *)(param_1 + 0x514) + 1U & 0xf;
    *(undefined1 *)(param_2 + 0x1f) = 1;
  }
  return CONCAT71((int7)(uVar4 >> 8),*(undefined1 *)(param_2 + 0x1c));
}

