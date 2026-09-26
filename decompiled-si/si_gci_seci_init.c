
undefined8 si_gci_seci_init(long param_1)

{
  undefined8 uStack_18;
  
  if (*(int *)(param_1 + 0x3c) == 0x4335) {
    si_gci_reset();
    si_gci_direct(param_1,0xc0c,0xffffffff,0x14);
    si_gci_set_functionsel(param_1,4,4);
    si_gci_set_functionsel(param_1,5,4);
    si_gci_direct(param_1,0xc54,0xf,0);
    si_gci_direct(param_1,0xde0,0xffffffff,0xf4);
    si_gci_direct(param_1,0xde4,0xffffffff,0);
    si_gci_direct(param_1,0xdec,0xffffffff,0x89);
    si_gci_direct(param_1,0xde8,0xffffffff,0x28);
    si_gci_direct(param_1,0xdd0,0xffffffff,0xdb);
    si_gci_direct(param_1,0xdf8,0xffffffff,0x22);
    si_gci_indirect(param_1,0,0xdbc,0xffffffff,0x43424140);
    si_gci_indirect(param_1,1,0xdbc,0xffffffff,0x47464544);
    si_gci_indirect(param_1,2,0xdbc,0xffffffff,0x4b4a4948);
    si_gci_indirect(param_1,0,0xdb4,0xffffffff,0x12);
    si_gci_indirect(param_1,1,0xdb4,0xffffffff,2);
    si_gci_indirect(param_1,0,0xdb8,0xf00f0,0x10000);
    si_gci_indirect(param_1,4,0xdb8,0xf0,0x20);
    si_gci_direct(param_1,0xd70,0xffffffff,0xf00f0);
    si_gci_direct(param_1,0xdc0,0xffffffff,0x43210);
  }
  return uStack_18;
}

