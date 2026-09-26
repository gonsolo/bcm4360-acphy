
void wlc_bmac_btc_stuck_war50943(long param_1,char param_2)

{
  undefined8 uVar1;
  
  if (param_2 == '\0') {
    *(undefined1 *)(*(long *)(param_1 + 0xb0) + 0x15) = 0;
    uVar1 = 0;
  }
  else {
    *(undefined1 *)(*(long *)(param_1 + 0xb0) + 0x14) = 0;
    uVar1 = 0x80;
    *(undefined1 *)(*(long *)(param_1 + 0xb0) + 0x15) = 1;
  }
  wlc_bmac_mhf(param_1,2,0x80,uVar1,3);
  return;
}

