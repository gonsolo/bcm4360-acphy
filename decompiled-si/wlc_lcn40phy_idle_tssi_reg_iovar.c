
ushort wlc_lcn40phy_idle_tssi_reg_iovar
                 (undefined8 param_1,undefined2 param_2,char param_3,undefined4 *param_4)

{
  short sVar1;
  ushort uVar2;
  undefined8 uVar3;
  
  sVar1 = phy_reg_read(param_1,0x4ae);
  if (param_3 == '\0') {
    if (-1 < sVar1) goto LAB_001f728f;
  }
  else {
    if (-1 < sVar1) {
      phy_reg_mod(param_1,0x4a6,0x1ff,param_2);
LAB_001f728f:
      uVar3 = 0x4a6;
      goto LAB_001f7294;
    }
    *param_4 = 0xffffffe9;
  }
  uVar3 = 0x639;
LAB_001f7294:
  uVar2 = phy_reg_read(param_1,uVar3);
  return uVar2 & 0x1ff;
}

