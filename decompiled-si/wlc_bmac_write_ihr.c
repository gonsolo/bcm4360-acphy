
void wlc_bmac_write_ihr(undefined8 param_1,int param_2,undefined2 param_3)

{
  undefined2 local_c [2];
  
  local_c[0] = param_3;
  wlc_bmac_copyto_objmem(param_1,param_2 << 2,local_c,2,0x30000);
  return;
}

