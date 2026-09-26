
undefined8 wlc_bmac_led_blink_event(long *param_1,char param_2)

{
  undefined8 *puVar1;
  char cVar2;
  undefined8 *puVar3;
  
  puVar1 = (undefined8 *)param_1[0x33];
  if (param_2 == '\0') {
    cVar2 = wl_del_timer(*(undefined8 *)(*param_1 + 0x10),puVar1[99]);
    if (cVar2 == '\0') {
      return 1;
    }
    *(undefined1 *)(puVar1 + 100) = 0;
    for (puVar3 = puVar1 + 1; puVar3 != puVar1 + 0x61; puVar3 = puVar3 + 3) {
      if ((*(int *)(puVar3 + 1) != 0) || (*(int *)((long)puVar3 + 0xc) != 0)) {
        wlc_bmac_led(*puVar1,1 << ((byte)*(undefined4 *)puVar3 & 0x1f),0,
                     *(undefined1 *)((long)puVar3 + 4));
        *(undefined1 *)((long)puVar3 + 0x15) = 1;
      }
    }
  }
  else {
    wl_del_timer(*(undefined8 *)(*param_1 + 0x10),puVar1[99]);
    wl_add_timer(*(undefined8 *)(*param_1 + 0x10),puVar1[99],*(undefined4 *)(puVar1 + 0x62),1);
    *(undefined1 *)(puVar1 + 100) = 1;
  }
  return 0;
}

