
undefined1  [16]
FUN_00162b63(undefined8 param_1,int param_2,undefined1 *param_3,undefined2 *param_4)

{
  undefined1 auVar1 [16];
  undefined4 local_28;
  undefined4 local_24;
  undefined8 uStack_20;
  
  wlc_bmac_copyfrom_objmem(param_1,param_2 << 3,&local_28,8,0x40000);
  *param_3 = (char)local_28;
  param_3[1] = (char)((uint)local_28 >> 8);
  param_3[3] = (char)((uint)local_28 >> 0x18);
  param_3[2] = (char)((uint)local_28 >> 0x10);
  param_3[4] = (char)local_24;
  param_3[5] = (char)((uint)local_24 >> 8);
  *param_4 = (short)((uint)local_24 >> 0x10);
  auVar1._4_4_ = local_24;
  auVar1._0_4_ = local_28;
  auVar1._8_8_ = uStack_20;
  return auVar1;
}

