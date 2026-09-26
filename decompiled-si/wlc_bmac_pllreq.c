
void wlc_bmac_pllreq(long param_1,char param_2,uint param_3)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x160);
  if (param_2 == '\0') {
    if ((param_3 & uVar1) == 0) {
      return;
    }
    *(uint *)(param_1 + 0x160) = ~param_3 & uVar1;
    if ((~param_3 & uVar1 & 4) == 0) {
      return;
    }
    if (*(char *)(param_1 + 0x187) == '\0') {
      return;
    }
    uVar2 = 0;
  }
  else {
    if ((param_3 & uVar1) != 0) {
      return;
    }
    *(uint *)(param_1 + 0x160) = param_3 | uVar1;
    if (((param_3 | uVar1) & 4) == 0) {
      return;
    }
    uVar2 = 1;
    if (*(char *)(param_1 + 0x187) != '\0') {
      return;
    }
  }
  wlc_bmac_xtal(param_1,uVar2);
  return;
}

