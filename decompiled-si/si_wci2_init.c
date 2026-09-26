
void si_wci2_init(long param_1)

{
  if (*(int *)(param_1 + 0x3c) == 0x4335) {
    si_gci_reset();
    si_gci_direct(param_1,0xc0c,0xffffffff,0x24);
    si_gci_set_functionsel(param_1,4,4);
    si_gci_set_functionsel(param_1,5,4);
    si_gci_direct(param_1,0xc54,0xf,0);
    si_gci_direct(param_1,0xde0,0xffffffff,0xf4);
    si_gci_direct(param_1,0xde4,0xffffffff,0);
    si_gci_direct(param_1,0xdec,0xffffffff,0x89);
    si_gci_direct(param_1,0xde8,0xffffffff,0x28);
    si_gci_direct(param_1,0xdd0,0xffffffff,0xdb);
    si_gci_direct(param_1,0xdf8,0xffffffff,0x22);
    si_gci_indirect(param_1,0,0xc44,0x20000000,0x20000000);
    si_gci_indirect(param_1,1,0xc44,0x20202020,0x20202020);
    si_gci_indirect(param_1,0x70010,0xc4c,1,1);
    si_gci_indirect(param_1,0x60010,0xc4c,2,2);
    si_gci_indirect(param_1,0x50010,0xc4c,4,4);
    si_gci_indirect(param_1,0x40010,0xc4c,0x6000000,0x6000000);
    si_gci_indirect(param_1,0x30010,0xc4c,0x8000000,0x8000000);
    si_gci_indirect(param_1,0x50000,0xc4c,0x10,0x10);
    si_gci_indirect(param_1,0x40000,0xc4c,0x20,0x20);
    si_gci_direct(param_1,0xd70,0x30,0x30);
  }
  return;
}

