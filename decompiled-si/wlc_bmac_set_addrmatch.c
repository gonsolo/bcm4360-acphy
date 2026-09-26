
void wlc_bmac_set_addrmatch(long param_1,ushort param_2,undefined2 *param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  long lVar4;
  
  if (*(uint *)(param_1 + 0x84) < 0x28) {
    uVar1 = *param_3;
    uVar2 = param_3[1];
    uVar3 = param_3[2];
    lVar4 = *(long *)(param_1 + 0xd0) + 0x422;
    osl_writew(param_2 | 0x20,*(long *)(param_1 + 0xd0) + 0x420);
    osl_writew(uVar1,lVar4);
    osl_writew(uVar2,lVar4);
    osl_writew(uVar3,lVar4);
  }
  return;
}

