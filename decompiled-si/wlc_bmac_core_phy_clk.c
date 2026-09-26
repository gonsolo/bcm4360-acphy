
void wlc_bmac_core_phy_clk(long param_1,char param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  *(char *)(param_1 + 400) = param_2;
  if (param_2 == '\0') {
    si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0x200a,10);
    osl_delay(1);
    uVar3 = *(undefined8 *)(param_1 + 0xb8);
    uVar1 = 8;
    uVar2 = 10;
  }
  else {
    if (0x27 < *(uint *)(param_1 + 0x84)) {
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0x300,0x100);
    }
    if (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 0xb) {
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xe,0);
      osl_delay(1);
      uVar3 = *(undefined8 *)(param_1 + 0xb8);
      uVar1 = 4;
      uVar2 = 4;
    }
    else {
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0xe,2);
      osl_delay(1);
      uVar3 = *(undefined8 *)(param_1 + 0xb8);
      uVar1 = 4;
      uVar2 = 6;
    }
  }
  si_core_cflags(uVar3,uVar2,uVar1);
  osl_delay(1);
  return;
}

