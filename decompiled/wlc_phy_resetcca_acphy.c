
void wlc_phy_resetcca_acphy(long param_1)

{
  int iVar1;
  ushort uVar2;
  
  iVar1 = *(int *)(param_1 + 0x164);
  if (((iVar1 == 5) || (iVar1 == 2)) || (iVar1 == 6)) {
    wlapi_bmac_phyclk_fgc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),1);
    uVar2 = phy_reg_read(param_1,1);
    phy_reg_write(param_1,1,uVar2 | 0x4000);
    osl_delay(1);
    phy_reg_mod(param_1,0x19e,0x3c,0);
    osl_delay(1);
    phy_reg_mod(param_1,0x19e,1,1);
    osl_delay(1);
    wlapi_bmac_phyclk_fgc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0);
    osl_delay(1);
    phy_reg_write(param_1,1,uVar2 & 0xbfff);
    osl_delay(1);
    phy_reg_mod(param_1,0x19e,1,0);
  }
  else {
    wlapi_bmac_phyclk_fgc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),1);
    uVar2 = phy_reg_read(param_1,1);
    phy_reg_write(param_1,1,uVar2 | 0x4000);
    osl_delay(1);
    phy_reg_write(param_1,1,uVar2 & 0xbfff);
    wlapi_bmac_phyclk_fgc(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0);
  }
  osl_delay(2);
  return;
}

