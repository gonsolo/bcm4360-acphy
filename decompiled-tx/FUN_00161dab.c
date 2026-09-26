
void FUN_00161dab(long param_1)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  uint uVar4;
  long lVar5;
  
  uVar1 = *(uint *)(*(long *)(param_1 + 0xb0) + 0xc);
  if (uVar1 != 0) {
    uVar3 = *(undefined8 *)(param_1 + 0xb8);
    uVar2 = *(uint *)(*(long *)(param_1 + 0xb0) + 0x10);
    lVar5 = *(long *)(param_1 + 0xd0) + 0x49e;
    uVar4 = osl_readw(lVar5);
    osl_writew((uVar4 | *(uint *)(*(long *)(param_1 + 0xb0) + 0x10)) & 0xffff,lVar5);
    si_gpioouten(uVar3,~uVar2 & uVar1,0,0);
    if (*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) == 0x4313) {
      si_gpiopull(*(long *)(param_1 + 0xb8),1,uVar1,0);
    }
    si_gpiocontrol(uVar3,uVar1,uVar1,0);
  }
  return;
}

