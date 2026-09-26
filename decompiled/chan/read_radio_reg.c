
undefined8 read_radio_reg(long param_1,ushort param_2)

{
  uint uVar1;
  undefined8 uVar2;
  ushort uVar3;
  long lVar4;
  bool bVar5;
  
  if (((param_2 == 1) && (*(int *)(param_1 + 0x160) != 7)) && (*(int *)(param_1 + 0x160) != 0xb)) {
    return 0xffffffff;
  }
  uVar3 = param_2;
  switch(*(int *)(param_1 + 0x160)) {
  case 0:
    uVar3 = param_2 | 0x40;
    break;
  case 2:
    uVar3 = param_2 | 0x80;
    break;
  case 4:
    bVar5 = *(uint *)(param_1 + 0x164) < 7;
    goto LAB_001b3e0a;
  case 5:
    bVar5 = *(uint *)(param_1 + 0x164) < 2;
LAB_001b3e0a:
    uVar3 = param_2 | 0x100;
    if (!bVar5) {
      uVar3 = param_2 | 0x200;
    }
    break;
  case 6:
  case 7:
  case 8:
  case 10:
    uVar3 = param_2 | 0x200;
  }
  uVar1 = *(uint *)(*(long *)(param_1 + 0x20) + 0x28);
  if (((uVar1 == 0x1b) || (uVar1 < 0x18)) && ((uVar1 != 0x16 || (*(int *)(param_1 + 0x160) == 6))))
  {
    osl_writew(uVar3,*(long *)(param_1 + 0x148) + 0x3f6);
    lVar4 = *(long *)(param_1 + 0x148) + 0x3fa;
  }
  else {
    osl_writew(uVar3,*(long *)(param_1 + 0x148) + 0x3d8);
    lVar4 = *(long *)(param_1 + 0x148) + 0x3da;
  }
  uVar2 = osl_readw(lVar4);
  *(undefined2 *)(param_1 + 0x226) = 0;
  return uVar2;
}

