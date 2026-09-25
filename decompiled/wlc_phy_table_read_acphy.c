
void wlc_phy_table_read_acphy
               (undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined8 param_6)

{
  undefined8 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_28 = param_6;
  local_20 = param_3;
  local_1c = param_2;
  local_18 = param_4;
  local_14 = param_5;
  wlc_phy_read_table_ext(param_1,&local_28,0xd,0xe,0x11,0x10,0xf);
  return;
}

