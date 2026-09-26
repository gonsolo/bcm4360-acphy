
void wlc_bmac_ifsctl_edcrs_set(long param_1,char param_2)

{
  short sVar1;
  undefined8 uVar2;
  
  sVar1 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
  if (sVar1 == 4) {
    if (*(uint *)(param_1 + 0x84) < 0x10) {
      return;
    }
  }
  else if ((sVar1 != 7) && (sVar1 != 0xb)) {
    return;
  }
  if (param_2 == '\0') {
    uVar2 = 8;
  }
  else {
    if ((sVar1 != 4) || (2 < *(ushort *)(*(long *)(param_1 + 0xe8) + 0x1e))) goto LAB_001630e3;
    uVar2 = 0;
  }
  FUN_00163019(param_1,8,uVar2);
LAB_001630e3:
  sVar1 = (short)*(undefined4 *)(*(long *)(param_1 + 0xe8) + 0x1c);
  if (sVar1 != 7) {
    if (sVar1 != 4) {
      if (sVar1 != 0xb) {
        return;
      }
      FUN_00162e6d(param_1,1);
      return;
    }
    if (*(ushort *)(*(long *)(param_1 + 0xe8) + 0x1e) < 3) {
      return;
    }
  }
  uVar2 = 8;
  if ((*(ushort *)(param_1 + 0x11c) & 0x3800) != 0x1000) {
    uVar2 = 0x38;
  }
  FUN_00163019(param_1,0x38,uVar2);
  return;
}

