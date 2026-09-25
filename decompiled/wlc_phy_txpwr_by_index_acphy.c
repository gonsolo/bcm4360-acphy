
void wlc_phy_txpwr_by_index_acphy(long param_1,byte param_2,char param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 local_48 [2];
  undefined1 local_46 [2];
  undefined1 local_44 [4];
  undefined1 local_40 [16];
  
  uVar1 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  for (uVar3 = 0; (ushort)uVar3 < (ushort)*(byte *)(param_1 + 0x168); uVar3 = uVar3 + 1) {
    uVar2 = uVar3 & 0xffff;
    if ((param_2 >> (uVar3 & 0x1f) & 1) != 0) {
      FUN_001993cf(param_1,local_48,(int)param_3);
      wlc_phy_table_write_acphy(param_1,7,1,uVar2 + 0x100,0x10,local_48);
      wlc_phy_table_write_acphy(param_1,7,1,uVar2 + 0x103,0x10,local_46);
      wlc_phy_table_write_acphy(param_1,7,1,uVar2 + 0x106,0x10,local_44);
      FUN_0019d224(param_1,local_40,uVar2);
      *(char *)(*(long *)(param_1 + 0x138) + 0x10 + (long)(int)uVar2) = param_3;
    }
  }
  phy_reg_mod(param_1,0x19e,2,uVar1 & 2);
  return;
}

