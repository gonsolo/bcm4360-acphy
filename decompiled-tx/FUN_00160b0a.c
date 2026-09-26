
ushort FUN_00160b0a(long param_1)

{
  long lVar1;
  ushort uVar2;
  short sVar3;
  
  lVar1 = *(long *)(param_1 + 0xe8);
  sVar3 = (short)*(undefined4 *)(lVar1 + 0x1c);
  if (sVar3 == 5) {
    if (1 < *(ushort *)(lVar1 + 0x1e)) {
LAB_00160b96:
      uVar2 = 200;
      goto LAB_00160b9b;
    }
  }
  else {
    uVar2 = 0x32;
    if (sVar3 == 6) goto LAB_00160b9b;
    if (sVar3 == 8) goto LAB_00160b96;
    uVar2 = 0xdfc;
    if (sVar3 == 0) goto LAB_00160b9b;
    if (sVar3 == 4) {
      uVar2 = 0x600;
      if (2 < *(ushort *)(lVar1 + 0x1e)) goto LAB_00160b9b;
    }
    else {
      uVar2 = 0x8f0;
      if ((sVar3 == 7) || (uVar2 = 500, sVar3 == 10)) goto LAB_00160b9b;
      if (sVar3 == 0xb) {
        uVar2 = 0x200;
        if (*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) == 0x4350) {
          uVar2 = 0x4b0;
        }
        goto LAB_00160b9b;
      }
    }
  }
  uVar2 = 800;
LAB_00160b9b:
  if ((*(int *)(lVar1 + 0x20) == 0x82050) && (uVar2 < 0x960)) {
    uVar2 = 0x960;
  }
  return uVar2;
}

