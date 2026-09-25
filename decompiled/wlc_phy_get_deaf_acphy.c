
undefined1 wlc_phy_get_deaf_acphy(long param_1)

{
  ushort uVar1;
  short sVar2;
  ulong uVar3;
  undefined1 uVar4;
  short sVar5;
  
  wlapi_suspend_mac_and_wait(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  uVar1 = phy_reg_read(param_1,0x140);
  if ((uVar1 & 7) == 4) {
    sVar5 = 0;
    sVar2 = 0;
    if (*(int *)(param_1 + 0x164) == 0) {
      for (; (byte)sVar5 < *(byte *)(param_1 + 0x168); sVar5 = sVar5 + 1) {
        sVar2 = phy_reg_read(param_1,sVar5 * 0x200 + 0x6da);
        if (sVar2 != -1) goto LAB_0019163b;
      }
    }
    else {
      for (; (byte)sVar2 < *(byte *)(param_1 + 0x168); sVar2 = sVar2 + 1) {
        uVar3 = phy_reg_read(param_1,sVar2 * 0x200 + 0x6d4);
        if ((uVar3 & 0x4000) == 0) goto LAB_0019163b;
      }
    }
    uVar4 = 1;
  }
  else {
LAB_0019163b:
    uVar4 = 0;
  }
  wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  return uVar4;
}

