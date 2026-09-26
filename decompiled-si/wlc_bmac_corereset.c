
void wlc_bmac_corereset(long param_1,uint param_2)

{
  char cVar1;
  long *plVar2;
  char cVar3;
  undefined8 uVar4;
  long lVar5;
  
  if (param_2 == 0xffffffff) {
    param_2 = 0;
    if (*(long *)(*(long *)(param_1 + 0xe8) + 0x28) != 0) {
      param_2 = *(uint *)(*(long *)(param_1 + 0xe8) + 0x18);
    }
  }
  cVar1 = *(char *)(param_1 + 0x185);
  if (cVar1 == '\0') {
    FUN_001655c7(param_1,0);
  }
  cVar3 = si_iscoreup(*(undefined8 *)(param_1 + 0xb8));
  if (cVar3 != '\0') {
    lVar5 = 0;
    do {
      plVar2 = *(long **)(param_1 + 0x20 + lVar5);
      if (plVar2 != (long *)0x0) {
        (**(code **)(*plVar2 + 0x10))();
      }
      lVar5 = lVar5 + 8;
    } while (lVar5 != 0x30);
    if (*(long *)(param_1 + 0x20) != 0) {
      FUN_001645e5(param_1,0);
    }
    if ((*(int *)(param_1 + 0x84) == 4) && (*(long *)(param_1 + 0x38) != 0)) {
      FUN_001645e5(param_1,3);
    }
  }
  if (*(char *)(param_1 + 0x184) == '\0') {
    uVar4 = 4;
    if ((0xb < *(uint *)(param_1 + 0x84)) && (uVar4 = 0, 0x11 < *(uint *)(param_1 + 0x84))) {
      param_2 = param_2 | 4;
    }
    *(undefined1 *)(param_1 + 0x186) = 0;
    si_core_reset(*(undefined8 *)(param_1 + 0xb8),param_2,uVar4);
    *(undefined1 *)(param_1 + 0x186) = 1;
    if ((*(long *)(param_1 + 0xe8) != 0) &&
       (lVar5 = *(long *)(*(long *)(param_1 + 0xe8) + 0x28), lVar5 != 0)) {
      wlc_phy_hw_clk_state_upd(lVar5,1);
    }
    if (*(int *)(param_1 + 0x84) == 0x21) {
      wlc_bmac_write_ihr(param_1,0x49,0x4002);
      wlc_bmac_write_ihr(param_1,0x49,2);
    }
    if ((*(long *)(param_1 + 0xe8) != 0) && (*(short *)(*(long *)(param_1 + 0xe8) + 0x1c) == 0xb)) {
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),0x300,0x100);
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),6,0);
      si_core_cflags(*(undefined8 *)(param_1 + 0xb8),4,4);
    }
    *(undefined4 *)(param_1 + 0x168) = 0;
    *(undefined1 *)(param_1 + 0x164) = 0;
    *(undefined4 *)(param_1 + 0x170) = 0;
    *(undefined4 *)(param_1 + 0x174) = 0;
    wlc_bmac_mctrl(param_1,0xffffffff,0x4000400);
    if ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x10) != 0) {
      FUN_001655c7(param_1,0);
    }
    if (*(long *)(param_1 + 0xe8) != 0) {
      wlc_bmac_phy_reset(param_1);
    }
    wlc_bmac_core_phypll_ctl(param_1,1);
    *(undefined4 *)(param_1 + 0x94) = 0;
    if (cVar1 == '\0') {
      FUN_001655c7(param_1,2);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x94) = 0;
    wlc_bmac_mctrl(param_1,3,0);
  }
  return;
}

