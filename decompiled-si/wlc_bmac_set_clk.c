
undefined8 wlc_bmac_set_clk(long param_1,char param_2)

{
  undefined8 uStack_18;
  
  if (param_2 == '\0') {
    if (*(char *)(param_1 + 0x186) != '\0') {
      wlc_coredisable();
    }
    wlc_bmac_xtal(param_1,0);
  }
  else {
    wlc_bmac_xtal(param_1,1);
    wlc_bmac_corereset(param_1,0xffffffff);
  }
  return uStack_18;
}

