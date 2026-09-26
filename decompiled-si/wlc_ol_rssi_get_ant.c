
undefined8 wlc_ol_rssi_get_ant(long *param_1,uint param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  if ((((param_2 < 4) && (param_1 != (long *)0x0)) && (*(char *)((long)param_1 + 0x8c) != '\0')) &&
     (((lVar1 = ((long *)*param_1)[0x5f], (*(byte *)(*(long *)*param_1 + 0xec) & 1) != 0 &&
       (lVar1 != 0)) && ((*(char *)(lVar1 + 0x22) != '\0' && (*(char *)(lVar1 + 8) != '\0')))))) {
    uVar2 = CONCAT71((int7)((ulong)param_1[0x12] >> 8),
                     *(undefined1 *)(param_1[0x12] + 0x202e + (ulong)param_2));
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

