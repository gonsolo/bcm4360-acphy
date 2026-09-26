
ulong si_d11_devid(long param_1)

{
  ulong uVar1;
  
  if ((*(int *)(param_1 + 0x3c) == 0x4328) &&
     ((*(int *)(param_1 + 0x44) == 5 || (*(int *)(param_1 + 0x44) == 3)))) {
    uVar1 = 0x4314;
  }
  else {
    uVar1 = si_getdevpathintvar(param_1,"devid");
    if ((short)uVar1 == 0) {
      uVar1 = getintvar(*(undefined8 *)(param_1 + 0xa8),"devid");
      if ((short)uVar1 == 0) {
        uVar1 = getintvar(*(undefined8 *)(param_1 + 0xa8),"wl0id");
        if (((short)uVar1 == 0) && (uVar1 = 0xffffffff, *(int *)(param_1 + 0x3c) == 0x4712)) {
          uVar1 = (ulong)((uint)(*(int *)(param_1 + 0x44) != 1) * 4 + 0x4320);
        }
      }
    }
  }
  return uVar1;
}

