
void wlc_bmac_set_rcmta(long param_1,int param_2,undefined8 param_3)

{
  if (*(uint *)(param_1 + 0x84) < 0x28) {
    wlc_bmac_copyto_objmem(param_1,param_2 << 3,param_3,6,0x40000);
  }
  else {
    wlc_bmac_write_amt();
  }
  return;
}

