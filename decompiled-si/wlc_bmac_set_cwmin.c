
void wlc_bmac_set_cwmin(long param_1,undefined2 param_2)

{
  undefined2 local_c [2];
  
  *(undefined2 *)(*(long *)(param_1 + 0xe8) + 0x14) = param_2;
  local_c[0] = param_2;
  wlc_bmac_copyto_objmem(param_1,0xc,local_c,2,0x20000);
  return;
}

