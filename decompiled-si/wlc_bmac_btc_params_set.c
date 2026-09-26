
undefined8 wlc_bmac_btc_params_set(long param_1,uint param_2,undefined2 param_3)

{
  short sVar1;
  
  if ((param_2 < 0x77) && (sVar1 = *(short *)(*(long *)(param_1 + 0xb0) + 0x1a), sVar1 != 0)) {
    wlc_bmac_write_shm(param_1,sVar1 + (short)param_2 * 2,param_3);
    return 0;
  }
  return 0xfffffffe;
}

