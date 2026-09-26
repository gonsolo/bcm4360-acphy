
undefined8 * wlc_bmac_led_attach(long *param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined8 *puVar4;
  long lVar5;
  undefined8 *puVar6;
  int *piVar7;
  int iVar8;
  undefined8 *puVar9;
  undefined1 local_58 [40];
  
  puVar4 = (undefined8 *)osl_malloc(param_1[2],0x328);
  puVar6 = puVar4;
  if (puVar4 == (undefined8 *)0x0) {
    uVar1 = osl_malloced(param_1[2]);
    osl_printf("wlc_bmac_led_attach: out of memory, malloced %d bytes",uVar1);
  }
  else {
    piVar7 = (int *)(puVar4 + 1);
    iVar8 = 0;
    osl_memset(puVar4,0,0x328);
    do {
      *piVar7 = iVar8;
      *(undefined1 *)(piVar7 + 1) = 1;
      iVar8 = iVar8 + 1;
      iVar2 = osl_sysuptime();
      *(undefined1 *)(piVar7 + 5) = 1;
      piVar7[4] = iVar2;
      piVar7 = piVar7 + 6;
    } while (iVar8 != 0x20);
    iVar8 = 0;
    puVar9 = puVar4;
    do {
      osl_snprintf(local_58,0x20,"ledbh%d",iVar8);
      lVar5 = getvar(param_1[0x18],local_58);
      if (lVar5 == 0) {
        osl_snprintf(local_58,0x20,"wl0gpio%d",iVar8);
        lVar5 = getvar(param_1[0x18],local_58);
        if (lVar5 != 0) goto LAB_00162307;
      }
      else {
LAB_00162307:
        uVar3 = bcm_strtoul(lVar5,0,0);
        if ((uVar3 & 0x7f) < 0x19) {
          *(int *)(puVar9 + 1) = iVar8;
          *(byte *)((long)puVar9 + 0xc) = ((byte)(uVar3 >> 7) ^ 1) & 1;
        }
      }
      iVar8 = iVar8 + 1;
      puVar9 = puVar9 + 3;
    } while (iVar8 != 0x20);
    *puVar4 = param_1;
    lVar5 = wl_init_timer(*(undefined8 *)(*param_1 + 0x10),FUN_001623a0,*param_1,"led_blink");
    puVar4[99] = lVar5;
    if (lVar5 == 0) {
      osl_printf("wl%d: wlc_led_attach: wl_init_timer for led_blink_timer failed\n",(int)param_1[3])
      ;
      puVar6 = (undefined8 *)0x0;
      osl_mfree(param_1[2],puVar4,0x328);
    }
  }
  return puVar6;
}

