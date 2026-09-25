
void wlc_phy_ed_thres_acphy(undefined8 param_1,int *param_2,char param_3)

{
  int iVar1;
  ushort uVar2;
  ulong uVar3;
  
  if (param_3 == '\x01') {
    iVar1 = *param_2;
    uVar3 = (long)(iVar1 * 640000 + 0x45a96c0) / 0x7597 & 0xffff;
    phy_reg_write(param_1,0x33a,uVar3);
    phy_reg_write(param_1,0x33b,uVar3);
    phy_reg_write(param_1,0x33e,uVar3);
    phy_reg_write(param_1,0x33f,uVar3);
    phy_reg_write(param_1,0x342,uVar3);
    phy_reg_write(param_1,0x343,uVar3);
    phy_reg_write(param_1,0x346,uVar3);
    phy_reg_write(param_1,0x347,uVar3);
    uVar3 = (long)(iVar1 * 640000 + 0x41ffec0) / 0x7597 & 0xffff;
    phy_reg_write(param_1,0x33c,uVar3);
    phy_reg_write(param_1,0x33d,uVar3);
    phy_reg_write(param_1,0x340,uVar3);
    phy_reg_write(param_1,0x341,uVar3);
    phy_reg_write(param_1,0x344,uVar3);
    phy_reg_write(param_1,0x345,uVar3);
    phy_reg_write(param_1,0x348,uVar3);
    phy_reg_write(param_1,0x349,uVar3);
  }
  else {
    uVar2 = phy_reg_read(param_1,0x33a);
    *param_2 = (int)((uint)uVar2 * 0x7597 + -0x45a96c0) / 640000;
  }
  return;
}

