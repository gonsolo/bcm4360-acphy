
undefined2 wlc_bmac_btc_params_get(long param_1,uint param_2)

{
  ushort uVar1;
  undefined2 uVar2;
  
  if ((param_2 < 0x77) && (uVar1 = *(ushort *)(*(long *)(param_1 + 0xb0) + 0x1a), uVar1 != 0)) {
    uVar2 = wlc_bmac_read_shm(param_1,(uint)uVar1 + param_2 * 2 & 0xffff);
  }
  else {
    uVar2 = 0xbad;
  }
  return uVar2;
}

