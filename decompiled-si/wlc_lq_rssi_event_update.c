
void wlc_lq_rssi_event_update(long *param_1)

{
  byte *pbVar1;
  char *pcVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  uint local_1c;
  
  lVar4 = param_1[0x66];
  lVar5 = *param_1;
  if (*(char *)(lVar4 + 0x48) == '\0') {
    lVar6 = *(long *)(lVar4 + 0x30);
    uVar7 = 0;
    pbVar1 = (byte *)(lVar6 + 4);
    while (((int)uVar7 < (int)(uint)*pbVar1 &&
           (pcVar2 = (char *)(lVar6 + 5), lVar6 = lVar6 + 1, (int)*pcVar2 < *(int *)(lVar4 + 0x14)))
          ) {
      uVar7 = uVar7 + 1;
    }
    if (uVar7 != *(byte *)(lVar4 + 0x38)) {
      uVar3 = *(uint *)(lVar4 + 0x14);
      local_1c = uVar3 >> 0x18 | uVar3 << 0x18 | (uVar3 & 0xff00) << 8 | (uVar3 & 0xff0000) >> 8;
      *(char *)(lVar4 + 0x38) = (char)uVar7;
      wlc_bss_mac_event(lVar5,param_1,0x38,0,0,0,0,&local_1c,4);
      if (**(int **)(lVar4 + 0x30) != 0) {
        *(undefined1 *)(lVar4 + 0x48) = 1;
        wl_add_timer(*(undefined8 *)(lVar5 + 0x10),*(undefined8 *)(lVar4 + 0x40),
                     **(int **)(lVar4 + 0x30),0);
      }
    }
  }
  return;
}

