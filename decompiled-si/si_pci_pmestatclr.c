
void si_pci_pmestatclr(long param_1)

{
  pcicore_pmestatclr(*(undefined8 *)(param_1 + 0x90));
  return;
}

