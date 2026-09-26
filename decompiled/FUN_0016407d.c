
void FUN_0016407d(long param_1)

{
  uint uVar1;
  undefined4 uVar2;
  long lVar3;
  uint uVar4;
  long lVar5;
  bool bVar6;
  
  bVar6 = *(char *)(param_1 + 0x187) == '\0';
  if (bVar6) {
    wlc_bmac_xtal(param_1,1);
  }
  uVar1 = *(uint *)(*(long *)(param_1 + 0xb0) + 0xc);
  if (uVar1 != 0) {
    lVar3 = *(long *)(param_1 + 0xb8);
    uVar2 = *(undefined4 *)(*(long *)(param_1 + 0xb0) + 0x10);
    si_gpiocontrol(lVar3,uVar1,0,0);
    si_gpioouten(lVar3,uVar1,0,0);
    if (*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) == 0x4313) {
      si_gpiopull(*(long *)(param_1 + 0xb8),1,uVar1,0x40);
    }
    si_gpioout(lVar3,uVar2,0,0);
    if (*(char *)(param_1 + 0x186) != '\0') {
      lVar5 = *(long *)(param_1 + 0xd0) + 0x49e;
      uVar4 = osl_readw(lVar5);
      osl_writew(uVar4 & ~*(uint *)(*(long *)(param_1 + 0xb0) + 0x10) & 0xffff,lVar5);
    }
    if ((*(int *)(lVar3 + 4) == 1) && ((uVar1 & 0x100) != 0)) {
      si_btcgpiowar(lVar3);
    }
    if (bVar6) {
      wlc_bmac_xtal(param_1,0);
    }
  }
  return;
}

