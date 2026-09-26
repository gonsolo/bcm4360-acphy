
void si_pmu_radio_enable(long param_1,char param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 != 0x4330) {
    if (uVar1 < 0x4331) {
      if (uVar1 != 0x4319) {
        if (uVar1 != 0x4325) {
          return;
        }
        if ((*(uint *)(param_1 + 0x34) & 0x8000000) != 0) {
          return;
        }
        if ((*(uint *)(param_1 + 0x34) & 0x200000) != 0) {
          si_corereg(param_1,0,0x618,1,param_2 != '\0');
        }
        if (param_2 == '\0') {
          return;
        }
        osl_delay(100000);
        return;
      }
    }
    else if ((uVar1 != 0x4336) && (uVar1 != 0xa962)) {
      return;
    }
  }
  uVar1 = si_wrapperreg(param_1,0x124,0,0);
  if (param_2 == '\0') {
    uVar1 = uVar1 & 0xff7f7fff;
  }
  else {
    uVar1 = uVar1 | 0x808000;
  }
  si_wrapperreg(param_1,0x124,0xffffffff,uVar1);
  return;
}

