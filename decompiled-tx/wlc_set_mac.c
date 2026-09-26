
undefined8 wlc_set_mac(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)*param_1;
  if (param_1 == (long *)plVar1[0x5f]) {
    if (*(uint *)(*plVar1 + 0x14) < 0x28) {
      wlc_bmac_set_addrmatch(plVar1[4],0);
    }
    else {
      wlc_bmac_write_amt(plVar1[4],0x3f,(long)param_1 + 0xf6,0x8008);
    }
  }
  wlc_ampdu_macaddr_upd(plVar1);
  return 0;
}

