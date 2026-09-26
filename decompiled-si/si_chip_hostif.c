
uint si_chip_hostif(long param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 == 0x4360) {
LAB_0011eed5:
    if (((*(byte *)(param_1 + 0x44) & 1) == 0) || ((*(byte *)(param_1 + 0x49) & 1) == 0)) {
      return 1;
    }
LAB_0011ef06:
    uVar1 = 2;
  }
  else {
    if (uVar1 < 0x4361) {
      if (uVar1 == 0x4335) {
        uVar1 = *(uint *)(param_1 + 0x48);
        if ((uVar1 & 4) == 0) {
          if ((uVar1 & 1) != 0) {
            return 4;
          }
          return uVar1 >> 3 & 1;
        }
        goto LAB_0011ef06;
      }
    }
    else if ((uVar1 == 0xa9c4) || (uVar1 == 0xaa06)) goto LAB_0011eed5;
    uVar1 = 0;
  }
  return uVar1;
}

