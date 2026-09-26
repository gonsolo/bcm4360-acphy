
void si_ercx_init(long param_1)

{
  if (*(int *)(param_1 + 0x3c) == 0x4334) {
    si_pmu_chipcontrol(param_1,1,0xf,10);
  }
  else if (*(int *)(param_1 + 0x3c) == 0x4335) {
    si_gci_reset();
    si_gci_direct(param_1,0xc0c,0xffffffff,0x30);
    si_gci_set_functionsel(param_1,2,4);
    si_gci_set_functionsel(param_1,3,4);
    si_gci_set_functionsel(param_1,4,4);
    si_gci_set_functionsel(param_1,5,4);
    si_gci_set_functionsel(param_1,6,4);
    si_gci_set_functionsel(param_1,0,1);
    si_gpiocontrol(param_1,1,1,0);
    si_gci_indirect(param_1,0,0xc44,0xffffffff,0x20101);
    si_gci_indirect(param_1,1,0xc44,0xffffffff,0x2010000);
    si_gci_indirect(param_1,0x10010,0xc4c,0xffffffff,1);
    si_gci_indirect(param_1,0x60010,0xc4c,0xffffffff,2);
    si_gci_indirect(param_1,0x10,0xc4c,0xffffffff,4);
    si_gci_indirect(param_1,0x70000,0xc4c,0xffffffff,0x10);
    si_gci_indirect(param_1,0x20000,0xc4c,0xffffffff,0x40);
  }
  return;
}

