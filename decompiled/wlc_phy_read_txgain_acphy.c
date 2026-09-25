
void wlc_phy_read_txgain_acphy(long param_1)

{
  ushort uVar1;
  uint uVar2;
  long lVar3;
  ushort uVar4;
  undefined1 local_58 [8];
  undefined1 auStack_50 [32];
  
  uVar1 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  for (uVar4 = 0; uVar4 < *(byte *)(param_1 + 0x168); uVar4 = uVar4 + 1) {
    uVar2 = (uint)uVar4;
    lVar3 = (long)(int)uVar2 * 10;
    wlc_phy_table_read_acphy(param_1,7,1,uVar2 + 0x100,0x10,local_58 + lVar3);
    wlc_phy_table_read_acphy(param_1,7,1,uVar2 + 0x103,0x10,local_58 + lVar3 + 2);
    wlc_phy_table_read_acphy(param_1,7,1,uVar2 + 0x106,0x10,local_58 + lVar3 + 4);
    FUN_00199491(param_1,auStack_50 + lVar3,uVar2);
  }
  phy_reg_mod(param_1,0x19e,2,uVar1 & 2);
  return;
}

