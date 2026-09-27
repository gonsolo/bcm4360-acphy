
void FUN_0019d550(long param_1,long param_2)

{
  uint uVar1;
  byte bVar2;
  long lVar3;
  
  uVar1 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  for (bVar2 = 0; bVar2 < *(byte *)(param_1 + 0x168); bVar2 = bVar2 + 1) {
    lVar3 = (ulong)bVar2 * 10 + param_2;
    wlc_phy_table_write_acphy(param_1,7,1,bVar2 + 0x100,0x10,lVar3);
    wlc_phy_table_write_acphy(param_1,7,1,bVar2 + 0x103,0x10,lVar3 + 2);
    wlc_phy_table_write_acphy(param_1,7,1,bVar2 + 0x106,0x10,lVar3 + 4);
    FUN_0019d224(param_1,lVar3 + 8,bVar2);
  }
  phy_reg_mod(param_1,0x19e,2,(uVar1 >> 1 & 1) * 2);
  return;
}

