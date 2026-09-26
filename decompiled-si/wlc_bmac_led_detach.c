
bool wlc_bmac_led_detach(long *param_1)

{
  long lVar1;
  char cVar2;
  bool bVar3;
  
  bVar3 = false;
  lVar1 = param_1[0x33];
  if (lVar1 != 0) {
    if (*(long *)(lVar1 + 0x318) != 0) {
      cVar2 = wl_del_timer(*(undefined8 *)(*param_1 + 0x10));
      bVar3 = cVar2 == '\0';
      wl_free_timer(*(undefined8 *)(*param_1 + 0x10),*(undefined8 *)(lVar1 + 0x318));
      *(undefined8 *)(lVar1 + 0x318) = 0;
    }
    osl_mfree(param_1[2],lVar1,0x328);
  }
  return bVar3;
}

