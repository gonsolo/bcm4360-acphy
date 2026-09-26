
undefined8 wlc_bmac_btc_wire_set(long param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  undefined4 uVar4;
  
  if (4 < param_2) {
    return 0xfffffffe;
  }
  if (param_2 == 0) {
    if (((((*(uint *)(param_1 + 0x84) < 0xf) ||
          ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x20) == 0)) ||
         ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1c) & 1) != 0)) &&
        ((((*(byte *)(param_1 + 0x8c) & 1) == 0 || (*(char *)(param_1 + 0x90) < '\0')) ||
         ((uVar1 = *(uint *)(*(long *)(param_1 + 0xb8) + 0x1c), (uVar1 & 1) == 0 &&
          ((uVar1 & 4) == 0)))))) || ((*(byte *)(param_1 + 0xa7) & 0x20) == 0)) {
      if ((char)*(uint *)(param_1 + 0x90) < '\0') {
        *(uint *)(*(long *)(param_1 + 0xb0) + 4) =
             ~-(uint)((*(uint *)(param_1 + 0x90) & 0x2000000) == 0) + 4;
      }
      else {
        *(undefined4 *)(*(long *)(param_1 + 0xb0) + 4) = 2;
      }
    }
    else {
      *(undefined4 *)(*(long *)(param_1 + 0xb0) + 4) = 3;
    }
    if (((*(int *)(param_1 + 0x84) == 0xc) && (*(int *)(*(long *)(param_1 + 0xb8) + 0x30) == 0x106b)
        ) && ((iVar2 = *(int *)(*(long *)(param_1 + 0xb8) + 0x28), iVar2 == 0x90 || (iVar2 == 0x8b))
             )) {
      *(undefined4 *)(*(long *)(param_1 + 0xb0) + 4) = 3;
    }
  }
  else {
    *(int *)(*(long *)(param_1 + 0xb0) + 4) = param_2;
  }
  lVar3 = *(long *)(param_1 + 0xb0);
  *(undefined1 *)(param_1 + 0xae) = 0;
  if (*(int *)(lVar3 + 4) < 3) {
    return 0;
  }
  uVar1 = *(uint *)(*(long *)(param_1 + 0xb8) + 0x3c);
  if (uVar1 == 0xa8d8) {
LAB_00160ebd:
    uVar4 = 0x20;
    if ((*(byte *)(param_1 + 0x8e) & 0x40) == 0) goto LAB_00160ed0;
LAB_00160ecb:
    uVar4 = 0xe0;
  }
  else {
    if (uVar1 < 0xa8d9) {
      uVar4 = 0x10;
      if ((uVar1 == 0x4312) || (uVar4 = 0x60, uVar1 == 0x4313)) goto LAB_00160ed0;
    }
    else {
      if (uVar1 == 0xa8d9) goto LAB_00160ecb;
      if (uVar1 == 0xa99d) goto LAB_00160ebd;
    }
    uVar4 = 0;
  }
LAB_00160ed0:
  *(undefined4 *)(lVar3 + 0x10) = uVar4;
  *(undefined4 *)(lVar3 + 0xc) = uVar4;
  return 0;
}

