
void wlc_bmac_write_amt(undefined8 param_1,undefined8 param_2,byte *param_3,ushort param_4)

{
  uint local_48;
  undefined4 local_44;
  undefined1 local_38 [14];
  ushort local_2a;
  
  local_2a = 0;
  if ((short)param_4 < 0) {
    FUN_00162b63(param_1,param_2,local_38,&local_2a);
    param_4 = param_4 | local_2a;
  }
  local_48 = (uint)param_3[3] << 0x18 | (uint)param_3[2] << 0x10 | (uint)*param_3 |
             (uint)param_3[1] << 8;
  local_44 = CONCAT22(param_4,*(undefined2 *)(param_3 + 4));
  wlc_bmac_copyto_objmem(param_1,(int)param_2 * 8,&local_48,8,0x40000);
  return;
}

