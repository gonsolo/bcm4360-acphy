
void wlc_bmac_macphyclk_set(long param_1,char param_2)

{
  undefined8 uVar1;
  
  if (param_2 == '\x01') {
    uVar1 = 0x10;
  }
  else {
    uVar1 = 0;
  }
  si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0x10,uVar1);
  return;
}

