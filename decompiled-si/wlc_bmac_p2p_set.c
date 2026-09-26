
undefined8 wlc_bmac_p2p_set(long param_1,char param_2)

{
  undefined8 uVar1;
  
  if ((*(char *)(param_1 + 0x1d) == param_2) || (uVar1 = 0xffffffff, param_2 == '\0')) {
    uVar1 = 0;
  }
  return uVar1;
}

