
uint si_is_otp_disabled(long param_1)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = *(uint *)(param_1 + 0x3c);
  if (uVar1 == 0x4329) {
LAB_0011f055:
    bVar2 = (*(uint *)(param_1 + 0x48) & 3) == 3;
LAB_0011f06d:
    uVar1 = (uint)bVar2;
  }
  else {
    if (uVar1 < 0x432a) {
      if (uVar1 == 0x4315) goto LAB_0011f055;
      if (uVar1 < 0x4316) {
        if (uVar1 != 0x10f6) {
          if (uVar1 != 0x4313) {
            return 0;
          }
          uVar1 = *(uint *)(param_1 + 0x48) >> 1;
          goto LAB_0011f087;
        }
      }
      else if (uVar1 != 0x4322) {
        if (uVar1 == 0x4325) goto LAB_0011f055;
        if (uVar1 != 0x4319) {
          return 0;
        }
        bVar2 = (*(uint *)(param_1 + 0x48) & 0xc0) == 0xc0;
        goto LAB_0011f06d;
      }
LAB_0011f04d:
      uVar1 = *(uint *)(param_1 + 0x48) >> 7;
    }
    else {
      if (uVar1 != 0x4336) {
        if (0x4336 < uVar1) {
          if (uVar1 != 0xa8df) {
            if (uVar1 == 0xa962) goto LAB_0011f081;
            if (uVar1 != 0xa8d5) {
              return 0;
            }
          }
          goto LAB_0011f04d;
        }
        if (uVar1 == 0x4330) {
          uVar1 = *(uint *)(param_1 + 0x48) >> 4;
          goto LAB_0011f087;
        }
        if (uVar1 != 0x4331) {
          return 0;
        }
      }
LAB_0011f081:
      uVar1 = *(uint *)(param_1 + 0x48) >> 2;
    }
LAB_0011f087:
    uVar1 = (uVar1 ^ 1) & 1;
  }
  return uVar1;
}

