
undefined8 wlc_bmac_up_prep(long *param_1)

{
  char cVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar2 = param_1[0x17];
  if (((*(int *)(lVar2 + 0x3c) == 0x4350) && (*(int *)(lVar2 + 0x40) == 0)) &&
     ((*(uint *)(lVar2 + 0x48) & 0x700000) == 0x300000)) {
    si_pmu_chipcontrol(lVar2,2,0x80000,0x80000);
  }
  wlc_bmac_xtal(param_1,1);
  si_clkctl_init(param_1[0x17]);
  FUN_001655c7(param_1,0);
  lVar2 = param_1[0x17];
  if (*(int *)(lVar2 + 4) == 1) {
    si_pci_setup(lVar2,1 << ((byte)**(undefined4 **)(*param_1 + 0x38) & 0x1f));
  }
  else if (*(int *)(lVar2 + 4) == 2) {
    lVar2 = si_setcore(lVar2,0x812,0);
    param_1[0x1a] = lVar2;
    *(long *)(*param_1 + 0x18) = lVar2;
    si_pcmcia_init(param_1[0x17]);
  }
  cVar1 = wlc_bmac_radio_read_hwdisabled(param_1);
  if (cVar1 == '\0') {
    if (*(int *)(param_1[0x17] + 4) == 1) {
      si_pci_up();
    }
    wlc_bmac_corereset(param_1,0xffffffff);
    uVar3 = 0;
  }
  else {
    if (*(int *)(param_1[0x17] + 4) == 1) {
      si_pci_down();
    }
    wlc_bmac_xtal(param_1,0);
    uVar3 = 0xfffffff7;
  }
  return uVar3;
}

