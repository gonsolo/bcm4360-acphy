
undefined8 wlc_phy_tssivisible_thresh_acphy(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  if (*(uint *)(param_1 + 0x164) < 2) {
    uVar2 = 0x26;
    if (*(short *)(*(long *)(param_1 + 0x138) + 0x342) != 0x203) {
      if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4360) {
        iVar1 = *(int *)(*(long *)(param_1 + 0x20) + 0x58);
        if ((iVar1 == 0x137) || (iVar1 == 0x117)) {
          return 0x14;
        }
        if (((iVar1 == 0x134) || (iVar1 == 0x112)) &&
           (0x94 < (byte)*(undefined2 *)(param_1 + 0x17e))) {
          return 0x16;
        }
      }
      uVar2 = 0x18;
    }
  }
  else {
    uVar2 = 0x80;
    if (*(uint *)(param_1 + 0x164) == 3) {
      uVar2 = 0x1c;
    }
  }
  return uVar2;
}

