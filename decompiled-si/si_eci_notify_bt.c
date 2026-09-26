
void si_eci_notify_bt(long param_1,uint param_2,uint param_3,char param_4)

{
  undefined8 uVar1;
  
  if (((*(byte *)(param_1 + 0x1b) & 0x20) == 0) && ((*(uint *)(param_1 + 0x1c) & 1) == 0)) {
    if ((*(uint *)(param_1 + 0x1c) & 4) == 0) {
      return;
    }
    if (param_2 >> 0x10 != 0x5555) {
      return;
    }
    si_gci_direct(param_1,0xd64,param_2 & 0xffff,param_3);
    return;
  }
  if (param_4 != '\0') {
    FUN_00122a5d(param_1,0x140,0x40000000,0);
  }
  if (0x22 < *(int *)(param_1 + 0x14)) {
    if (param_2 >> 0x10 == 0x5555) {
      param_2 = param_2 & 0xffff;
      uVar1 = 0x144;
      goto LAB_00122cf4;
    }
    param_2 = param_2 | 0x40000000;
  }
  param_3 = param_3 & 0xbfffffff;
  uVar1 = 0x140;
LAB_00122cf4:
  FUN_00122a5d(param_1,uVar1,param_2,param_3);
  if (param_4 != '\0') {
    FUN_00122a5d(param_1,0x140,0x40000000,0x40000000);
  }
  return;
}

