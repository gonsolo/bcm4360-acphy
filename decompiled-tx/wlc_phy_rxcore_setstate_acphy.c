
void wlc_phy_rxcore_setstate_acphy(long param_1,byte param_2)

{
  undefined2 uVar1;
  uint uVar2;
  
  *(byte *)(*(long *)(param_1 + 0x20) + 0xa7) = param_2;
  if (*(char *)(*(long *)(param_1 + 0x20) + 0x31) != '\0') {
    wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    uVar2 = phy_reg_read(param_1,0x401);
    uVar1 = phy_reg_read(param_1,0x400);
    phy_reg_mod(param_1,0x160,7,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa7));
    phy_reg_mod(param_1,0x401,0x70,(uint)param_2 << 4);
    phy_reg_mod(param_1,0x401,0x7000,0x7000);
    phy_reg_mod(param_1,0x401,7,0);
    phy_reg_mod(param_1,0x400,1,1);
    wlc_phy_force_rfseq_acphy(param_1,0);
    wlc_phy_force_rfseq_acphy(param_1,1);
    phy_reg_mod(param_1,0x401,7,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa6));
    phy_reg_mod(param_1,0x401,0x7000,uVar2 & 0x7000);
    phy_reg_write(param_1,0x400,uVar1);
    wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  }
  return;
}

