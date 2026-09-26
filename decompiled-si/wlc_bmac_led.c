
void wlc_bmac_led(long param_1,ulong param_2,ulong param_3,char param_4)

{
  long lVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  uint uVar6;
  
  uVar3 = (uint)param_3;
  lVar1 = *(long *)(param_1 + 0x198);
  if (*(char *)(param_1 + 0x187) != '\0') {
    uVar6 = (uint)param_2;
    if (param_4 == '\0') {
      param_3 = (ulong)(~uVar3 & uVar6);
    }
    uVar4 = (uint)param_3;
    if ((*(byte *)(param_1 + 0x91) & 8) == 0) {
      if (((*(uint *)(lVar1 + 0x308) ^ uVar4) & uVar6) == 0) {
        return;
      }
      uVar2 = si_gpioout(*(undefined8 *)(param_1 + 0xb8),param_2,param_3,0);
    }
    else {
      if (param_4 == '\0') {
        if (((uVar4 ^ *(uint *)(lVar1 + 0x308)) & uVar6) != 0) {
          return;
        }
      }
      else if (((uVar4 ^ *(uint *)(lVar1 + 0x308)) & uVar6) == 0) {
        return;
      }
      uVar5 = 0;
      if (uVar3 == uVar6) {
        uVar5 = param_2 & 0xffffffff;
      }
      uVar2 = si_gpioouten(*(undefined8 *)(param_1 + 0xb8),param_2,uVar5,0);
    }
    *(undefined4 *)(lVar1 + 0x308) = uVar2;
  }
  return;
}

