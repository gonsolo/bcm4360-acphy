
void FUN_0019d3ac(long param_1,long param_2,long param_3)

{
  ushort uVar1;
  long lVar2;
  long lVar3;
  ushort uVar4;
  
  uVar1 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  for (uVar4 = 0; uVar4 < *(byte *)(param_1 + 0x168); uVar4 = uVar4 + 1) {
    lVar2 = param_3 + (ulong)uVar4 * 10;
    wlc_phy_table_read_acphy(param_1,7,1,uVar4 + 0x100,0x10,lVar2);
    wlc_phy_table_read_acphy(param_1,7,1,uVar4 + 0x103,0x10,lVar2 + 2);
    wlc_phy_table_read_acphy(param_1,7,1,uVar4 + 0x106,0x10,lVar2 + 4);
    lVar3 = (ulong)uVar4 * 10 + param_2;
    wlc_phy_table_write_acphy(param_1,7,1,uVar4 + 0x100,0x10,lVar3);
    wlc_phy_table_write_acphy(param_1,7,1,uVar4 + 0x103,0x10,lVar3 + 2);
    wlc_phy_table_write_acphy(param_1,7,1,uVar4 + 0x106,0x10,lVar3 + 4);
    FUN_00199491(param_1,lVar2 + 8,uVar4);
    FUN_0019d224(param_1,lVar3 + 8,uVar4);
  }
  phy_reg_mod(param_1,0x19e,2,uVar1 & 2);
  return;
}

