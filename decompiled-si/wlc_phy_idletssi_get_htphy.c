
uint wlc_phy_idletssi_get_htphy(long param_1)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = phy_reg_read(param_1,0x1e9);
  cVar1 = phy_reg_read(param_1,0x965);
  return (uint)(byte)((char)((char)uVar2 * '\x04') >> 2) | *(int *)(param_1 + 0x109c) << 0x18 |
         (uint)(byte)((char)(cVar1 << 2) >> 2) << 0x10 | (uint)(byte)((char)(uVar2 >> 6) >> 2) << 8;
}

