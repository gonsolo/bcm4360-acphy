
void wlc_phy_txpwr_est_pwr_acphy(long param_1,long param_2,long param_3)

{
  undefined1 uVar1;
  ulong uVar2;
  short sVar3;
  short sVar4;
  uint uVar5;
  
  for (uVar5 = 0; (byte)uVar5 < *(byte *)(param_1 + 0x168); uVar5 = uVar5 + 1) {
    sVar4 = (short)(uVar5 << 9);
    sVar3 = sVar4 + 0x642;
    uVar2 = phy_reg_read(param_1,sVar3);
    if ((uVar2 & 0x100) == 0) {
      *(undefined1 *)(param_2 + (ulong)(uVar5 & 0xff)) = 0;
    }
    else {
      uVar1 = phy_reg_read(param_1,sVar3);
      *(undefined1 *)(param_2 + (ulong)(uVar5 & 0xff)) = uVar1;
    }
    sVar4 = sVar4 + 0x640;
    sVar3 = phy_reg_read(param_1,sVar4);
    if (sVar3 < 0) {
      uVar1 = phy_reg_read(param_1,sVar4);
      *(undefined1 *)(param_3 + (ulong)(uVar5 & 0xff)) = uVar1;
    }
    else {
      *(undefined1 *)(param_3 + (ulong)(uVar5 & 0xff)) = 0;
    }
  }
  return;
}

