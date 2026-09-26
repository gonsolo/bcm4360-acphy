
undefined8 wlc_bmac_retrylimit_upd(long param_1,undefined2 param_2,undefined2 param_3)

{
  undefined8 uStack_18;
  
  *(undefined2 *)(param_1 + 0x104) = param_2;
  *(undefined2 *)(param_1 + 0x106) = param_3;
  if (*(char *)(param_1 + 0x10c) != '\0') {
    wlc_bmac_copyto_objmem(param_1,0x18,param_1 + 0x104,2,0x20000);
    wlc_bmac_copyto_objmem(param_1,0x1c,param_1 + 0x106,2,0x20000);
  }
  return uStack_18;
}

