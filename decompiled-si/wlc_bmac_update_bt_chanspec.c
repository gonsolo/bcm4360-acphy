
void wlc_bmac_update_bt_chanspec(long param_1,uint param_2,char param_3,char param_4)

{
  int iVar1;
  long lVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  sbyte sVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  bool bVar8;
  bool bVar9;
  
  lVar2 = *(long *)(param_1 + 0xb8);
  if (((*(uint *)(param_1 + 0x84) < 0xf) || ((*(byte *)(lVar2 + 0x1b) & 0x20) == 0)) ||
     ((*(byte *)(lVar2 + 0x1c) & 1) != 0)) {
    if ((*(byte *)(param_1 + 0x8c) & 1) == 0) {
      return;
    }
    if (*(char *)(param_1 + 0x90) < '\0') {
      return;
    }
    if (((*(uint *)(lVar2 + 0x1c) & 1) == 0) && ((*(uint *)(lVar2 + 0x1c) & 4) == 0)) {
      return;
    }
  }
  if (param_3 != '\0') {
    return;
  }
  if ((*(byte *)(param_1 + 0xa7) & 0x20) == 0) {
    return;
  }
  if (param_4 != '\0') {
    return;
  }
  if ((short)param_2 == 0) {
LAB_0016116a:
    uVar3 = 0x5555f000;
    if (*(int *)(lVar2 + 0x14) < 0x23) {
      uVar3 = 0xf;
    }
    uVar6 = 0;
  }
  else {
    if ((param_2 & 0xc000) == 0) {
      sVar5 = 0xc;
      if (*(int *)(lVar2 + 0x14) < 0x23) {
        sVar5 = 0;
      }
      uVar7 = 0xf;
      if (0x22 < *(int *)(lVar2 + 0x14)) {
        uVar7 = 0x5555f000;
      }
      si_eci_notify_bt(lVar2,uVar7,(param_2 & 0xff) << sVar5,1);
      if ((param_2 & 0x3800) == 0x1800) {
        uVar6 = 0xa00;
        iVar1 = *(int *)(lVar2 + 0x14);
        uVar3 = 0x50;
      }
      else {
        iVar1 = *(int *)(lVar2 + 0x14);
        uVar6 = 0x200;
        uVar3 = 0x10;
      }
      bVar9 = SBORROW4(iVar1,0x23);
      bVar8 = iVar1 + -0x23 < 0;
      if (iVar1 < 0x23) {
        uVar6 = uVar3;
      }
      uVar3 = 0x55550e00;
      uVar4 = 0x70;
    }
    else {
      if ((param_2 & 0xc000) != 0xc000) goto LAB_0016116a;
      iVar1 = *(int *)(lVar2 + 0x14);
      bVar9 = SBORROW4(iVar1,0x23);
      bVar8 = iVar1 + -0x23 < 0;
      uVar4 = 0xf;
      uVar6 = 0xf000;
      uVar3 = 0x5555f000;
      if (iVar1 < 0x23) {
        uVar6 = 0xf;
      }
    }
    if (bVar9 != bVar8) {
      uVar3 = uVar4;
    }
  }
  si_eci_notify_bt(lVar2,uVar3,uVar6,1);
  return;
}

