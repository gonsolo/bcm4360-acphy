
void si_pci_pmestat(long param_1)

{
  pcicore_pmestat(*(undefined8 *)(param_1 + 0x90));
  return;
}

