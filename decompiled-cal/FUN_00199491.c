
void FUN_00199491(undefined8 param_1,undefined8 param_2,ulong param_3)

{
  uint uVar1;
  undefined2 local_38 [12];
  
  local_38[0] = 99;
  local_38[1] = 0x67;
  local_38[2] = 0x6b;
  local_38[3] = 0x6f;
  uVar1 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  wlc_phy_table_read_acphy(param_1,0xc,1,local_38[param_3 & 0xffff],0x10,param_2);
  phy_reg_mod(param_1,0x19e,2,(uVar1 >> 1 & 1) * 2);
  return;
}

