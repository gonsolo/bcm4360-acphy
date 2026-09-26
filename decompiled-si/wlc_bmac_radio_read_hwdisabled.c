
uint wlc_bmac_radio_read_hwdisabled(long param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  byte bVar6;
  undefined8 uVar7;
  
  cVar1 = *(char *)(param_1 + 0x187);
  if (cVar1 == '\0') {
    wlc_bmac_xtal(param_1,1);
  }
  cVar2 = *(char *)(param_1 + 0x186);
  if (cVar2 == '\0') {
    if (*(uint *)(param_1 + 0x84) < 0xc) {
      uVar7 = 4;
      bVar6 = 0;
    }
    else {
      uVar7 = 0;
      bVar6 = ~-(*(uint *)(param_1 + 0x84) < 0x12) & 4;
    }
    iVar3 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c);
    if ((iVar3 - 0xa8d8U < 2) || (iVar3 == 0xa99d)) {
      uVar5 = si_setcore(*(long *)(param_1 + 0xb8),0x812,0);
      *(undefined8 *)(param_1 + 0xd0) = uVar5;
    }
    si_core_reset(*(undefined8 *)(param_1 + 0xb8),bVar6,uVar7);
    *(undefined4 *)(param_1 + 0x168) = 0;
    *(undefined1 *)(param_1 + 0x164) = 0;
    *(undefined4 *)(param_1 + 0x170) = 0;
    *(undefined4 *)(param_1 + 0x174) = 0;
    wlc_bmac_mctrl(param_1,0xffffffff,0x4000400);
  }
  uVar4 = osl_readl(*(long *)(param_1 + 0xd0) + 0x158);
  if (cVar2 == '\0') {
    si_core_disable(*(undefined8 *)(param_1 + 0xb8),0);
  }
  if (cVar1 == '\0') {
    wlc_bmac_xtal(param_1,0);
  }
  return uVar4 >> 0x10 & 1;
}

