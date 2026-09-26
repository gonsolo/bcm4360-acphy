
void wlc_bmac_ampdu_set(long param_1,char param_2)

{
  undefined *puVar1;
  
  if ((*(int *)(param_1 + 0x84) == 0x1d) || (*(int *)(param_1 + 0x84) == 0x1a)) {
    if (param_2 == '\x02') {
      puVar1 = &DAT_0059c9b0;
    }
    else {
      puVar1 = &DAT_0059c9c0;
    }
    osl_memcpy(*(undefined8 *)(param_1 + 0x150),puVar1,0xc);
  }
  return;
}

