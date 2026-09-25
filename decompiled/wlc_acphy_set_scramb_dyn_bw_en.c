
void wlc_acphy_set_scramb_dyn_bw_en(undefined8 param_1,char param_2)

{
  ushort uVar1;
  
  wlc_phyreg_enter();
  uVar1 = phy_reg_read(param_1,0x42);
  if (param_2 == '\0') {
    uVar1 = uVar1 & 0x7fff;
  }
  else {
    uVar1 = uVar1 | 0x8000;
  }
  phy_reg_write(param_1,0x42,uVar1);
  wlc_phyreg_exit(param_1);
  return;
}

