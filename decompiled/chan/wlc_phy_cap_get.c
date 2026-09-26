
ulong wlc_phy_cap_get(long param_1)

{
  ulong uVar1;
  
  switch(*(undefined4 *)(param_1 + 0x160)) {
  case 4:
    if (*(uint *)(param_1 + 0x164) < 3) {
      return 1;
    }
  case 10:
    uVar1 = 7;
    break;
  default:
    uVar1 = 0;
    break;
  case 6:
    uVar1 = (ulong)(2 < *(uint *)(param_1 + 0x164) | 4);
    break;
  case 7:
    uVar1 = 0x17;
    break;
  case 8:
    uVar1 = 4;
    break;
  case 0xb:
    uVar1 = wlc_phy_ac_caps();
  }
  return uVar1;
}

