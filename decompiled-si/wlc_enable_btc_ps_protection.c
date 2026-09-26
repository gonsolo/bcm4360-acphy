
void wlc_enable_btc_ps_protection(long *param_1)

{
  long lVar1;
  long lVar2;
  char cVar3;
  ushort uVar4;
  uint uVar5;
  
  if (*(int *)(param_1[0xd2] + 0x10) < 3) {
    return;
  }
  if (*(int *)(param_1[0xd2] + 0xc) == 0) {
    return;
  }
  uVar5 = wlc_bmac_btc_flags_get(param_1[4]);
  lVar1 = param_1[0x5f];
  if (*(int *)(*param_1 + 0x84) != 0) {
    return;
  }
  if (*(char *)(*param_1 + 0x34) == '\0') {
    return;
  }
  if ((*(char *)((long)param_1 + 0x253) != '\0') && (cVar3 = wlc_ismpc(param_1), cVar3 != '\0')) {
    return;
  }
  lVar2 = param_1[0xd2];
  wlc_bmac_btc_rssi_threshold_get(param_1[4],lVar2 + 3,lVar2 + 6,lVar2 + 7);
  if (((*(byte *)(param_1[0xd2] + 3) != 0) &&
      ((int)(uint)*(byte *)(param_1[0xd2] + 3) < -*(int *)(*(long *)(param_1[0x5f] + 0x330) + 0x14))
      ) || (uVar4 = 0, (uVar5 & 4) != 0)) {
    uVar4 = 8;
  }
  if ((((*(char *)(*(long *)(lVar1 + 0x318) + 0x34) == '\0') || (*(char *)(lVar1 + 0xc) == '\0')) ||
      ((((*(char *)(lVar1 + 0x22) != '\0' &&
         ((*(char *)(lVar1 + 0xf1) == '\0' && (*(char *)(lVar1 + 0xf0) == '\0')))) &&
        (*(char *)(lVar1 + 0xf2) == '\0')) &&
       (((*(char *)(lVar1 + 0xf3) == '\0' && (*(char *)(lVar1 + 0xf4) == '\0')) &&
        (*(char *)(lVar1 + 0xf5) == '\0')))))) || (*(char *)((long)param_1 + 0x301) != '\x01')) {
    if (*(char *)((long)param_1 + 0x301) != '\0') goto LAB_0012bf98;
  }
  else if (((*(short *)(lVar1 + 0x9a) == 0) || ((*(byte *)(lVar1 + 0x90) & 7) == 0)) ||
          (*(char *)(lVar1 + 0x9d) != '\0')) {
    uVar4 = ~-(ushort)((uVar5 & 0x10) == 0) & 0x200 | uVar4;
    goto LAB_0012bf98;
  }
  uVar4 = 0;
LAB_0012bf98:
  wlc_bmac_mhf(param_1[4],2,0x208,uVar4,2);
  return;
}

