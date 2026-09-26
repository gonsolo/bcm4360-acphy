
void si_btcgpiowar(long param_1)

{
  undefined4 uVar1;
  byte bVar2;
  undefined4 uVar3;
  long lVar4;
  
  if ((*(byte *)(param_1 + 0x18) & 0x20) != 0) {
    if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
       (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) !=
        *(int *)(param_1 + 0x68))) {
      uVar3 = 0;
    }
    else {
      uVar3 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
    }
    uVar1 = *(undefined4 *)(param_1 + 0x1c0);
    lVar4 = si_setcore(param_1,0x800,0);
    bVar2 = osl_readb(lVar4 + 0x304);
    osl_writeb(bVar2 | 4,lVar4 + 0x304);
    si_setcoreidx(param_1,uVar1);
    if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
       (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) ==
        *(int *)(param_1 + 0x68))) {
      (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),uVar3);
    }
  }
  return;
}

