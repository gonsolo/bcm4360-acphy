
void wlc_bmac_reset(long *param_1)

{
  int *piVar1;
  char cVar2;
  
  piVar1 = (int *)(*(long *)(*(long *)*param_1 + 0xa0) + 0xb4);
  *piVar1 = *piVar1 + 1;
  cVar2 = wlc_hw_deviceremoved(*(undefined8 *)(*param_1 + 0x20));
  if (cVar2 == '\0') {
    wlc_bmac_corereset(param_1,0xffffffff);
  }
  FUN_00160c3a(param_1);
  wlc_reset_bmac_done(*param_1);
  return;
}

