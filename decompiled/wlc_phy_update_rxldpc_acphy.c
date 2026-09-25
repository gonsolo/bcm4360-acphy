
void wlc_phy_update_rxldpc_acphy(long param_1,char param_2)

{
  ushort uVar1;
  
  if (param_2 != *(char *)(*(long *)(param_1 + 0x138) + 0x8ff)) {
    *(char *)(*(long *)(param_1 + 0x138) + 0x8ff) = param_2;
    uVar1 = phy_reg_read(param_1,0x1b0);
    if (param_2 == '\0') {
      uVar1 = uVar1 & 0xffbf;
    }
    else {
      uVar1 = uVar1 | 0x40;
    }
    phy_reg_write(param_1,0x1b0,uVar1);
  }
  return;
}

