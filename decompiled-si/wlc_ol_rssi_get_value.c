
undefined1 wlc_ol_rssi_get_value(long *param_1)

{
  long lVar1;
  
  if ((((param_1 != (long *)0x0) && (*(char *)((long)param_1 + 0x8c) != '\0')) &&
      (lVar1 = ((long *)*param_1)[0x5f], (*(byte *)(*(long *)*param_1 + 0xec) & 1) != 0)) &&
     (((lVar1 != 0 && (*(char *)(lVar1 + 0x22) != '\0')) && (*(char *)(lVar1 + 8) != '\0')))) {
    lVar1 = param_1[0x12];
    wlc_ol_inc_rssi_cnt_arm();
    return *(undefined1 *)(lVar1 + 0x202c);
  }
  return 0;
}

